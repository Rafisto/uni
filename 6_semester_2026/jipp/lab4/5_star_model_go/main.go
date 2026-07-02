package main

import (
	"fmt"
	"math/rand/v2"
	"sync"
	"time"
)

const (
	NUsers         = 5
	NFrames        = 100
	BaseBackoff    = 2 * time.Millisecond
	MaxBackoff     = 2000 * time.Millisecond
	ProcessingTime = 1 * time.Millisecond
	UserThinkTime  = 20 * time.Millisecond
)

type Frame struct {
	From int
	To   int
	Done chan struct{}
}

type User struct {
	sync.Mutex
	IngressCount int
	FailCount    int
}

type Switch struct {
	FrameChannel chan *Frame
}

func exponentialBackoff(attempt int) time.Duration {
	max := time.Duration(1<<attempt) * BaseBackoff
	if max > MaxBackoff {
		max = MaxBackoff
	}
	return rand.N(max)
}

func userTask(id int, Switch *Switch, users []*User, wg *sync.WaitGroup) {
	defer wg.Done()

	for i := range NFrames {
		time.Sleep(time.Duration(rand.Float64() * float64(UserThinkTime)))

		targetID := rand.IntN(NUsers) + 1
		frame := &Frame{
			From: id,
			To:   targetID,
			Done: make(chan struct{}),
		}

		attempt := 1

		for {
			select {
			case Switch.FrameChannel <- frame:
				fmt.Printf("User(id %d) successfully acquired Switch Lock for transfer %d.\n", id, i+1)
				attempt = 1
				goto HandoffSuccess
			default:
				users[id-1].Lock()
				users[id-1].FailCount++
				users[id-1].Unlock()

				backoff := exponentialBackoff(attempt)
				fmt.Printf("User(id %d, transfer %d) found Switch busy. Backing off for %v (attempt %d).\n", id, i+1, backoff, attempt)
				time.Sleep(backoff)
				attempt++
			}
		}

	HandoffSuccess:
		<-frame.Done
	}

	fmt.Printf("User(id %d) finished sending all %d Frames.\n", id, NFrames)
}

func switchTask(Switch *Switch, users []*User) {
	for frame := range Switch.FrameChannel {
		recipient := users[frame.To-1]

		fmt.Printf("Switch: Received Frame from User %d destined for User %d. Forwarding...\n", frame.From, frame.To)

		recipient.Lock()
		time.Sleep(ProcessingTime)
		recipient.IngressCount++
		recipient.Unlock()

		fmt.Printf("Switch: Successfully delivered Frame from User %d to User %d.\n", frame.From, frame.To)

		close(frame.Done)
	}
}

func main() {
	fmt.Println("Star topology communication.")

	var wg sync.WaitGroup

	sw := &Switch{
		FrameChannel: make(chan *Frame),
	}

	users := make([]*User, NUsers)
	for i := range NUsers {
		users[i] = new(User)
	}

	go switchTask(sw, users)

	for i := range NUsers {
		wg.Add(1)
		go userTask(i+1, sw, users, &wg)
	}

	wg.Wait()

	close(sw.FrameChannel)

	fmt.Println("\nStar topology communication complete.")
	totalReceived := 0
	totalFailed := 0
	for i := range NUsers {
		users[i].Lock()
		received := users[i].IngressCount
		failCount := users[i].FailCount
		users[i].Unlock()

		totalFailed += failCount
		totalReceived += received
		fmt.Printf("User(id %d) received %d Frames (%d failed attempts).\n", i+1, received, failCount)
	}

	fmt.Printf("\nTotal Frames sent across system: %d\n", NUsers*NFrames)
	fmt.Printf("Total Frames verified delivered: %d\n", totalReceived)
	fmt.Printf("Total failed send attempts across all users: %d\n", totalFailed)
}
