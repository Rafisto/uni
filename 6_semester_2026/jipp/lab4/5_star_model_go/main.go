package main

import (
	"fmt"
	"math/rand/v2"
	"sync"
	"time"
)

const (
	NUsers         = 5
	NMessages      = 100
	BaseBackoff    = 2 * time.Millisecond
	MaxBackoff     = 2000 * time.Millisecond
	ProcessingTime = 1 * time.Millisecond
	UserThinkTime  = 20 * time.Millisecond
)

type Message struct {
	From int
	To   int
	Body string
	Done chan struct{}
}

type User struct {
	sync.Mutex
	InboxCount int
	FailCount  int
}

type Server struct {
	Inbox chan *Message
}

func exponentialBackoff(attempt int) time.Duration {
	max := time.Duration(1<<attempt) * BaseBackoff
	if max > MaxBackoff {
		max = MaxBackoff
	}
	return rand.N(max)
}

func userWorker(id int, server *Server, users []*User, wg *sync.WaitGroup) {
	defer wg.Done()

	for i := 1; i <= NMessages; i++ {
		time.Sleep(time.Duration(rand.Float64() * float64(UserThinkTime)))

		targetID := rand.IntN(NUsers) + 1
		msg := &Message{
			From: id,
			To:   targetID,
			Body: fmt.Sprintf("Msg %d from User %d", i, id),
			Done: make(chan struct{}),
		}

		attempt := 1

		for {
			select {
			case server.Inbox <- msg:
				fmt.Printf("User(id %d) successfully acquired Server Inbox for transfer %d.\n", id, i)
				attempt = 1
				goto HandoffSuccess
			default:
				users[id-1].Lock()
				users[id-1].FailCount++
				users[id-1].Unlock()

				backoff := exponentialBackoff(attempt)
				fmt.Printf("User(id %d, transfer %d) found Server busy. Backing off for %v (attempt %d).\n", id, i, backoff, attempt)
				time.Sleep(backoff)
				attempt++
			}
		}

	HandoffSuccess:
		<-msg.Done
	}

	fmt.Printf("User(id %d) finished sending all %d messages.\n", id, NMessages)
}

func serverDispatcher(server *Server, users []*User) {
	for msg := range server.Inbox {
		recipient := users[msg.To-1]

		fmt.Printf("Server: Received message from User %d destined for User %d. Forwarding...\n", msg.From, msg.To)

		recipient.Lock()
		time.Sleep(ProcessingTime)
		recipient.InboxCount++
		recipient.Unlock()

		fmt.Printf("Server: Successfully delivered message from User %d to User %d.\n", msg.From, msg.To)

		close(msg.Done)
	}
}

func main() {
	fmt.Println("Star Topology Communication System (No Buffer Server)")

	var wg sync.WaitGroup

	server := &Server{
		Inbox: make(chan *Message),
	}

	users := make([]*User, NUsers)
	for i := 0; i < NUsers; i++ {
		users[i] = new(User)
	}

	go serverDispatcher(server, users)

	for i := 0; i < NUsers; i++ {
		wg.Add(1)
		go userWorker(i+1, server, users, &wg)
	}

	wg.Wait()

	close(server.Inbox)

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
