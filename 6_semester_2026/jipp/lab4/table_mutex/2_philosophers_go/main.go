package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NPhilosophers  = 5
	NIterations    = 100
	TimeConstraint = 10 * time.Millisecond
)

type TableArbiter struct {
	mu    sync.Mutex
	forks [NPhilosophers + 1]bool
}

func (ta *TableArbiter) AtomicPick(left, right int) bool {
	ta.mu.Lock()
	defer ta.mu.Unlock()

	if !ta.forks[left] && !ta.forks[right] {
		ta.forks[left] = true
		ta.forks[right] = true
		return true
	}
	return false
}

func (ta *TableArbiter) AtomicPut(left, right int) {
	ta.mu.Lock()
	defer ta.mu.Unlock()

	ta.forks[left] = false
	ta.forks[right] = false
}

func philosopher(id, forkLeft, forkRight int, arbiter *TableArbiter, done chan int) {
	failures := 0

	for i := 1; i <= NIterations; i++ {
		thinkTime := time.Duration(rand.Float64() * float64(TimeConstraint))
		fmt.Printf("Philosopher(id %d, meal %d) thinks for %v.\n", id, i, thinkTime)
		time.Sleep(thinkTime)

		for {
			success := arbiter.AtomicPick(forkLeft, forkRight)
			if success {
				break
			}

			fmt.Printf("Philosopher(id %d, meal %d) failed to pick up forks.\n", id, i)
			failures++
			retryTime := time.Duration(rand.Float64() * float64(TimeConstraint))
			time.Sleep(retryTime)
		}

		eatTime := time.Duration(rand.Float64() * float64(TimeConstraint))
		fmt.Printf("Philosopher(id %d, meal %d) eats for %v.\n", id, i, eatTime)
		time.Sleep(eatTime)

		arbiter.AtomicPut(forkLeft, forkRight)
	}

	fmt.Printf("Philosopher(id %d) finished with %d failures.\n", id, failures)

	done <- failures
}

func main() {
	fmt.Println("Dining Philosophers Problem")

	arbiter := &TableArbiter{}

	results := make([]chan int, NPhilosophers)

	for i := 1; i <= NPhilosophers; i++ {
		results[i-1] = make(chan int)

		forkLeft := i
		forkRight := (i % NPhilosophers) + 1

		go philosopher(i, forkLeft, forkRight, arbiter, results[i-1])
	}

	totalFailures := 0
	for i := 1; i <= NPhilosophers; i++ {
		failures := <-results[i-1]
		totalFailures += failures
		fmt.Printf("Philosopher(id %d) had %d failures.\n", i, failures)
	}

	fmt.Printf("Total system failures: %d\n", totalFailures)
}
