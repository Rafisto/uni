package main

import (
	"fmt"
	"math/rand/v2"
	"sync"
	"time"
)

const (
	NUsers         = 100
	NMessages      = 100
	BaseBackoff    = 2 * time.Millisecond
	MaxBackoff     = 2000 * time.Millisecond
	ProcessingTime = 1 * time.Millisecond
)

type Server struct {
	sync.Mutex
	ActiveMessage *Message
	ForwardDone   chan struct{}
}

type Message struct {
	From int
	To   int
	Body string
}

type User struct {
	sync.Mutex
	InboxCount int
	FailCount  int
}

func linearBackoff(attempt int) time.Duration {
	max := time.Duration(attempt) * BaseBackoff
	if max > MaxBackoff {
		max = MaxBackoff
	}

	return rand.N(max)
}

func exponentialBackoff(attempt int) time.Duration {
	max := time.Duration(1<<attempt) * BaseBackoff
	if max > MaxBackoff {
		max = MaxBackoff
	}

	return rand.N(max)
}

func userWorker(id int, server *Server, users []*User, finalReceived []int, wg *sync.WaitGroup) {
	defer wg.Done()

	for i := 1; i <= NMessages; i++ {
		thinkTime := time.Duration(rand.Float64() * float64(BaseBackoff))
		time.Sleep(thinkTime)

		targetID := rand.IntN(NUsers) + 1
		msg := &Message{
			From: id,
			To:   targetID,
			Body: fmt.Sprintf("Msg %d from User %d", i, id),
		}

		attempt := 1

		for {
			if server.TryLock() {
				fmt.Printf("User(id %d) successfully acquired Server Inbox for transfer %d.\n", id, i)
				break
			}

			users[id-1].Lock()
			users[id-1].FailCount++
			users[id-1].Unlock()

			backoff := exponentialBackoff(attempt)
			fmt.Printf("User(id %d, transfer %d) found Server busy. Backing off for %v (attempt %d).\n", id, i, backoff, attempt)
			time.Sleep(backoff)

			attempt++
		}

		server.ActiveMessage = msg
		server.ForwardDone = make(chan struct{})

		<-server.ForwardDone

		server.Unlock()
	}

	fmt.Printf("User(id %d) finished sending all %d messages.\n", id, NMessages)
}

func serverDispatcher(server *Server, users []*User, quit chan struct{}) {
	for {
		select {
		case <-quit:
			return
		default:
			if server.ActiveMessage != nil {
				msg := server.ActiveMessage
				recipient := users[msg.To-1]

				fmt.Printf("Server: Received message from User %d destined for User %d. Forwarding...\n", msg.From, msg.To)

				recipient.Lock()
				time.Sleep(ProcessingTime)
				recipient.InboxCount++
				recipient.Unlock()

				fmt.Printf("Server: Successfully delivered message from User %d to User %d.\n", msg.From, msg.To)

				server.ActiveMessage = nil
				close(server.ForwardDone)
			}
			time.Sleep(100 * time.Microsecond)
		}
	}
}

func main() {
	fmt.Println("Star Topology Communication System (No Buffer Server)")

	var wg sync.WaitGroup
	server := &Server{}

	users := make([]*User, NUsers)
	for i := 0; i < NUsers; i++ {
		users[i] = new(User)
	}

	finalReceived := make([]int, NUsers)

	quitServer := make(chan struct{})
	go serverDispatcher(server, users, quitServer)

	for i := 0; i < NUsers; i++ {
		wg.Add(1)
		go userWorker(i+1, server, users, finalReceived, &wg)
	}

	wg.Wait()

	close(quitServer)

	fmt.Println("\n--- Final System Statistics ---")
	totalReceived := 0
	totalFailed := 0
	for i := 1; i <= NUsers; i++ {
		users[i-1].Lock()
		received := users[i-1].InboxCount
		failCount := users[i-1].FailCount
		users[i-1].Unlock()

		totalFailed += failCount
		totalReceived += received
		fmt.Printf("User(id %d) received %d messages (%d failed attempts).\n", i, received, failCount)
	}

	fmt.Printf("\nTotal messages sent across system: %d\n", NUsers*NMessages)
	fmt.Printf("Total messages verified delivered: %d\n", totalReceived)
	fmt.Printf("Total failed send attempts across all users: %d\n", totalFailed)
}
