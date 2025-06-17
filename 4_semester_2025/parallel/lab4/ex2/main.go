package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	NrOfProcesses = 15
	MinSteps      = 50
	MaxSteps      = 100
	MinDelay      = 10 * time.Millisecond
	MaxDelay      = 50 * time.Millisecond
)

type ProcessState int

const (
	LocalSection ProcessState = iota
	EntryProtocol1
	EntryProtocol2
	EntryProtocol3
	EntryProtocol4
	CriticalSection
	ExitProtocol
)

type Position struct {
	X int
	Y ProcessState
}

type Trace struct {
	Timestamp time.Duration
	ID        int
	Position  Position
	Symbol    rune
}

type TracesSequence struct {
	Traces []Trace
}

func (ts *TracesSequence) Add(t Trace) {
	ts.Traces = append(ts.Traces, t)
}

var (
	flags = make([]int, NrOfProcesses)

	startTime = time.Now()
)

func minMaxDelayDuration(r *rand.Rand) time.Duration {
	delta := MaxDelay - MinDelay
	return MinDelay + time.Duration(float64(delta)*r.Float64())
}

func process(id int, symbol rune, done chan struct{}, tracesChan chan []Trace) {
	r := rand.New(rand.NewSource(time.Now().UnixNano() + int64(id)))
	nrOfSteps := MinSteps + r.Intn(MaxSteps-MinSteps+1)

	traces := make([]Trace, 0, nrOfSteps)

	recordTrace := func(state ProcessState) {
		traces = append(traces, Trace{
			Timestamp: time.Since(startTime),
			ID:        id,
			Position:  Position{X: id, Y: state},
			Symbol:    symbol,
		})
	}

	recordTrace(LocalSection)

	for step := 0; step < nrOfSteps/7; step++ {
		time.Sleep(minMaxDelayDuration(r))

		// ENTRY_PROTOCOL_1
		flags[id] = 1
		recordTrace(EntryProtocol1)

		for {
			enter := true
			for _, f := range flags {
				if f > 2 {
					enter = false
					break
				}
			}
			if enter {
				break
			}
			time.Sleep(1 * time.Millisecond)
		}

		// ENTRY_PROTOCOL_2
		flags[id] = 3
		recordTrace(EntryProtocol2)

		anyFlagOne := false
		for i, f := range flags {
			if i != id && f == 1 {
				anyFlagOne = true
				break
			}
		}

		if anyFlagOne {
			flags[id] = 2
			recordTrace(EntryProtocol3)

			for {
				condition := false
				for _, f := range flags {
					if f == 4 {
						condition = true
						break
					}
				}
				if condition {
					break
				}
				time.Sleep(1 * time.Millisecond)
			}
		}

		// ENTRY_PROTOCOL_4
		flags[id] = 4
		recordTrace(EntryProtocol4)

		if id != 0 {
			for {
				condition := true
				for i := 0; i < id; i++ {
					if flags[i] > 1 {
						condition = false
						break
					}
				}
				if condition {
					break
				}
				time.Sleep(1 * time.Millisecond)
			}
		}

		// CRITICAL_SECTION
		recordTrace(CriticalSection)

		time.Sleep(minMaxDelayDuration(r))

		// EXIT_PROTOCOL
		recordTrace(ExitProtocol)

		for {
			condition := true
			for i := id + 1; i < NrOfProcesses; i++ {
				if flags[i] == 2 || flags[i] == 3 {
					condition = false
					break
				}
			}
			if condition {
				break
			}
			time.Sleep(1 * time.Millisecond)
		}

		flags[id] = 0

		// LOCAL_SECTION
		recordTrace(LocalSection)
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

	fmt.Printf("LOCAL_SECTION;ENTRY_PROTOCOL_1;ENTRY_PROTOCOL_2;ENTRY_PROTOCOL_3;ENTRY_PROTOCOL_4;CRITICAL_SECTION;EXIT_PROTOCOL;")
	fmt.Printf("EXTRA_LABEL;\n")
	done <- true
}

func main() {
	tracesChan := make(chan []Trace, NrOfProcesses)
	printerDone := make(chan bool)
	processesDone := make(chan struct{}, NrOfProcesses)

	go printer(tracesChan, printerDone)

	symbol := 'A'
	for i := range NrOfProcesses {
		go process(i, symbol, processesDone, tracesChan)
		symbol++
	}

	for range NrOfProcesses {
		<-processesDone
	}
	close(tracesChan)
	<-printerDone
}
