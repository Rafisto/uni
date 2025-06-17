package main

import (
	"fmt"
	"math/rand"
	"sync"
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

type MaxTicket struct {
	sync.Mutex
	value int
}

func (mt *MaxTicket) UpdateMax(value int) {
	mt.Lock()
	defer mt.Unlock()
	if value > mt.value {
		mt.value = value
	}
}

func (mt *MaxTicket) GetMax() int {
	mt.Lock()
	defer mt.Unlock()
	return mt.value
}

var (
	choosing  = make([]int, NrOfProcesses)
	number    = make([]int, NrOfProcesses)
	maxTicket MaxTicket
	startTime = time.Now()
)

func max() int {
	current := 0
	for _, n := range number {
		if n > current {
			current = n
		}
	}
	maxTicket.UpdateMax(current)
	return current
}

func process(id int, symbol rune, done chan struct{}, tracesChan chan []Trace) {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	nrOfSteps := MinSteps + r.Intn(MaxSteps-MinSteps+1)
	traces := make([]Trace, 0, nrOfSteps)
	myMaxTicket := 0

	// INITIAL POSITION
	pos := Position{X: id - 1, Y: int(LocalSection)}
	traces = append(traces, Trace{
		Timestamp: 0,
		ID:        id,
		Position:  pos,
		Symbol:    symbol,
	})

	for step := 0; step < nrOfSteps/4-1; step++ {
		// LOCAL_SECTION
		delay := MinDelay + time.Duration(float64(MaxDelay-MinDelay)*r.Float64())
		time.Sleep(delay)

		choosing[id-1] = 1
		number[id-1] = 1 + max()
		choosing[id-1] = 0

		if number[id-1] > myMaxTicket {
			myMaxTicket = number[id-1]
		}

		// ENTRY_PROTOCOL
		pos.Y = int(EntryProtocol)
		traces = append(traces, Trace{
			Timestamp: time.Since(startTime),
			ID:        id,
			Position:  pos,
			Symbol:    symbol,
		})

		for j := 0; j < NrOfProcesses; j++ {
			time.Sleep(10 * time.Millisecond)
			if j != id-1 {
				for choosing[j] == 1 {
				}

				for number[j] != 0 &&
					(number[id-1] > number[j] ||
						(number[id-1] == number[j] && id-1 > j)) {
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

		// CRITICAL_SECTION - start
		delay = MinDelay + time.Duration(float64(MaxDelay-MinDelay)*r.Float64())
		time.Sleep(delay)
		// CRITICAL_SECTION - end

		// EXIT_PROTOCOL
		pos.Y = int(ExitProtocol)
		traces = append(traces, Trace{
			Timestamp: time.Since(startTime),
			ID:        id,
			Position:  pos,
			Symbol:    symbol,
		})

		number[id-1] = 0

		// LOCAL_SECTION
		pos.Y = int(LocalSection)
		traces = append(traces, Trace{
			Timestamp: time.Since(startTime),
			ID:        id,
			Position:  pos,
			Symbol:    symbol,
		})
	}

	maxTicket.UpdateMax(myMaxTicket)

	tracesChan <- traces
	done <- struct{}{}
}

func printer(tracesChan chan []Trace, done chan bool) {
	for i := 0; i < NrOfProcesses; i++ {
		traces := <-tracesChan
		for _, trace := range traces {
			fmt.Printf("%.9f %d %d %d %c\n",
				trace.Timestamp.Seconds(),
				trace.ID-1,
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
	fmt.Printf("MAX_TICKET=%d;\n", maxTicket.GetMax())
	done <- true
}

func main() {
	tracesChan := make(chan []Trace, NrOfProcesses)
	printerDone := make(chan bool)
	processesDone := make(chan struct{}, NrOfProcesses)
	go printer(tracesChan, printerDone)

	symbol := 'A'
	for i := 0; i < NrOfProcesses; i++ {
		go process(i+1, symbol, processesDone, tracesChan)
		symbol++
	}

	for i := 0; i < NrOfProcesses; i++ {
		<-processesDone
	}
	close(tracesChan)
	<-printerDone
}
