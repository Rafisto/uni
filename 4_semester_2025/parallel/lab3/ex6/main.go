package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	NrOfProcesses = 2
	MinSteps      = 50
	MaxSteps      = 100
	MinDelay      = 10 * time.Millisecond
	MaxDelay      = 50 * time.Millisecond
)

type ProcessState int

const (
	LocalSection ProcessState = iota
	EntryProtocol
	CriticalSection
	ExitProtocol
)

type Position struct {
	X, Y int
}

type Trace struct {
	Timestamp time.Duration
	ID        int
	Position  Position
	Symbol    rune
}

type Process struct {
	ID       int
	Symbol   rune
	Position Position
}

var (
	// Peterson's algorithm variables
	c1        = 0
	c2        = 0
	last      = 1
	startTime = time.Now()
)

func process(id int, symbol rune, done chan struct{}, tracesChan chan []Trace) {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	nrOfSteps := MinSteps + r.Intn(MaxSteps-MinSteps+1)
	traces := make([]Trace, 0, nrOfSteps)

	// INITIAL POSITION
	pos := Position{X: id, Y: int(LocalSection)}
	traces = append(traces, Trace{
		Timestamp: 0,
		ID:        id,
		Position:  pos,
		Symbol:    symbol,
	})

	for step := 0; step < nrOfSteps; step++ {
		// LOCAL_SECTION
		delay := MinDelay + time.Duration(float64(MaxDelay-MinDelay)*r.Float64())
		time.Sleep(delay)

		// ENTRY_PROTOCOL - Peterson's algorithm
		pos.Y = int(EntryProtocol)
		traces = append(traces, Trace{
			Timestamp: time.Since(startTime),
			ID:        id,
			Position:  pos,
			Symbol:    symbol,
		})

		if id == 0 {
			c1 = 1
			last = 1
			for {
				if c2 == 0 || last != 1 {
					break
				}
			}

		} else {
			c2 = 1
			last = 2
			for {
				if c1 == 0 || last != 2 {
					break
				}
			}
		}

		// CRITICAL_SECTION
		pos.Y = int(CriticalSection)
		traces = append(traces, Trace{
			Timestamp: time.Since(startTime),
			ID:        id,
			Position:  pos,
			Symbol:    symbol,
		})

		delay = MinDelay + time.Duration(float64(MaxDelay-MinDelay)*r.Float64())
		time.Sleep(delay)

		// EXIT_PROTOCOL - Peterson's algorithm
		pos.Y = int(ExitProtocol)
		traces = append(traces, Trace{
			Timestamp: time.Since(startTime),
			ID:        id,
			Position:  pos,
			Symbol:    symbol,
		})

		if id == 0 {
			c1 = 0
		} else {
			c2 = 0
		}

		pos.Y = int(LocalSection)
		traces = append(traces, Trace{
			Timestamp: time.Since(startTime),
			ID:        id,
			Position:  pos,
			Symbol:    symbol,
		})
	}

	tracesChan <- traces
	done <- struct{}{}
}

func printer(tracesChan chan []Trace, done chan bool) {
	for i := 0; i < NrOfProcesses; i++ {
		traces := <-tracesChan
		for _, trace := range traces {
			fmt.Printf("%.9f %d %d %d %c\n",
				trace.Timestamp.Seconds(),
				trace.ID,
				trace.Position.X,
				trace.Position.Y,
				trace.Symbol)
		}
	}

	fmt.Printf("-1 %d %d %d ",
		NrOfProcesses,
		NrOfProcesses,
		int(ExitProtocol)+1)

	fmt.Printf("LOCAL_SECTION;ENTRY_PROTOCOL;CRITICAL_SECTION;EXIT_PROTOCOL;")
	fmt.Printf("EXTRA_LABEL;\n")
	done <- true
}

func main() {
	tracesChan := make(chan []Trace, NrOfProcesses)
	printerDone := make(chan bool)
	processesDone := make(chan struct{}, NrOfProcesses)

	go printer(tracesChan, printerDone)

	symbol := 'A'
	for i := 0; i < NrOfProcesses; i++ {
		go process(i, symbol, processesDone, tracesChan)
		symbol++
	}

	for i := 0; i < NrOfProcesses; i++ {
		<-processesDone
	}
	close(tracesChan)
	<-printerDone
}
