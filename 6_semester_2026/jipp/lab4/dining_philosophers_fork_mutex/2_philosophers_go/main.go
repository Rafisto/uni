package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NPhilosophers  = 100
	NIterations    = 100
	TimeConstraint = 10 * time.Millisecond
)

type Fork struct {
	sync.Mutex
}

func philosopher(id int, leftFork, rightFork *Fork, results []int, wg *sync.WaitGroup) {
	defer wg.Done()
	failures := 0

	for i := 1; i <= NIterations; i++ {
		thinkTime := time.Duration(rand.Float64() * float64(TimeConstraint))
		fmt.Printf("Philosopher(id %d, meal %d) thinks for %v.\n", id, i, thinkTime)
		time.Sleep(thinkTime)

		for {
			leftFork.Lock()

			if rightFork.TryLock() {
				break
			}

			leftFork.Unlock()

			fmt.Printf("Philosopher(id %d, meal %d) failed to pick up forks.\n", id, i)
			failures++
			retryTime := time.Duration(rand.Float64() * float64(TimeConstraint))
			time.Sleep(retryTime)
		}

		eatTime := time.Duration(rand.Float64() * float64(TimeConstraint))
		fmt.Printf("Philosopher(id %d, meal %d) eats for %v.\n", id, i, eatTime)
		time.Sleep(eatTime)

		rightFork.Unlock()
		leftFork.Unlock()
	}

	fmt.Printf("Philosopher(id %d) finished with %d failures.\n", id, failures)
	results[id-1] = failures
}

func main() {
	fmt.Println("Dining Philosophers Problem")

	var wg sync.WaitGroup
	forks := make([]*Fork, NPhilosophers)
	for i := 0; i < NPhilosophers; i++ {
		forks[i] = new(Fork)
	}

	finalFailures := make([]int, NPhilosophers)

	for i := 0; i < NPhilosophers; i++ {
		wg.Add(1)

		leftFork := forks[i]
		rightFork := forks[(i+1)%NPhilosophers]

		go philosopher(i+1, leftFork, rightFork, finalFailures, &wg)
	}

	wg.Wait()

	totalFailures := 0
	for i := 1; i <= NPhilosophers; i++ {
		failures := finalFailures[i-1]
		totalFailures += failures
		fmt.Printf("Philosopher(id %d) had %d failures.\n", i, failures)
	}

	fmt.Printf("Total system failures: %d\n", totalFailures)
}
