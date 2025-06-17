package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	NrOfReaders   = 10
	NrOfWriters   = 5
	NrOfProcesses = NrOfReaders + NrOfWriters

	MinSteps = 50
	MaxSteps = 100

	MinDelay = 10 * time.Millisecond
	MaxDelay = 50 * time.Millisecond

	BoardWidth  = NrOfProcesses
	BoardHeight = 4
)

type ProcessState int

const (
	LocalSection ProcessState = iota
	Start
	ReadingRoom
	Stop
)

var Flags = [NrOfProcesses]int{}

type Position struct {
	X int
	Y int
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

type ProcessType int

const (
	Reader ProcessType = iota
	Writer
)

func ProcessTask(id int, StartTime time.Time, tracesChan chan []Trace, rw *RWMonitor, processType ProcessType, done chan struct{}) {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	var symbol rune
	var startAction, stopAction func()

	if processType == Reader {
		symbol = 'R'
		startAction = rw.StartRead
		stopAction = rw.StopRead
	} else {
		symbol = 'W'
		startAction = rw.StartWrite
		stopAction = rw.StopWrite
	}

	process := Process{
		ID:       id,
		Symbol:   symbol,
		Position: Position{X: id, Y: int(LocalSection)},
	}
	traces := make([]Trace, 0)

	nrOfSteps := MinSteps + r.Intn(MaxSteps-MinSteps+1)

	recordTrace := func(state ProcessState) {
		traces = append(traces, Trace{
			Timestamp: time.Since(StartTime),
			ID:        id,
			Position:  Position{X: id, Y: int(state)},
			Symbol:    symbol,
		})
	}

	recordTrace(LocalSection)

	for range make([]struct{}, nrOfSteps/4) {
		// Local Section
		time.Sleep(MinDelay + time.Duration(r.Float64()*float64(MaxDelay-MinDelay)))

		process.Position.Y = int(Start)

		// Entry Protocol
		recordTrace(Start)
		startAction()

		process.Position.Y = int(ReadingRoom)
		recordTrace(ReadingRoom)

		// Critical Section
		time.Sleep(MinDelay + time.Duration(r.Float64()*float64(MaxDelay-MinDelay)))

		process.Position.Y = int(Stop)

		// Exit Protocol
		recordTrace(Stop)
		stopAction()

		process.Position.Y = int(LocalSection)
		recordTrace(LocalSection)
	}

	tracesChan <- traces
	done <- struct{}{}
}

func printer(tracesChan chan []Trace, done chan bool) {
	for range NrOfProcesses {
		traces := <-tracesChan
		for _, trace := range traces {
			fmt.Printf("%.9f %d %d %d %c\n",
				float64(trace.Timestamp.Nanoseconds())/1e9,
				trace.ID,
				trace.Position.X,
				trace.Position.Y,
				trace.Symbol)
		}
	}

	fmt.Printf("-1 %d %d %d ",
		NrOfProcesses,
		BoardWidth,
		BoardHeight)

	fmt.Printf("LOCAL_SECTION;START;READING_ROOM;STOP;EXTRA_LABEL;\n")
	done <- true
}

func main() {
	StartTime := time.Now()

	tracesChan := make(chan []Trace, NrOfProcesses)
	printerDone := make(chan bool)
	processesDone := make(chan struct{}, NrOfProcesses)

	go printer(tracesChan, printerDone)

	rw := NewRWMonitor()

	for i := range NrOfReaders {
		go ProcessTask(i, StartTime, tracesChan, rw, Reader, processesDone)
	}

	for i := range NrOfWriters {
		go ProcessTask(i+NrOfReaders, StartTime, tracesChan, rw, Writer, processesDone)
	}

	for range NrOfProcesses {
		<-processesDone
	}
	close(tracesChan)
	<-printerDone
}
