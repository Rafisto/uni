package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const NrOfTravelers = 15

const MinSteps = 10
const MaxSteps = 100

const MinDelay = 0.01
const MaxDelay = 0.05

const BoardWidth = 15
const BoardHeight = 15

const seed = 42

var StartTime = time.Now()
var RandomClass = rand.New(rand.NewSource(seed))

type TravelerTask struct {
	ID       int
	Symbol   rune
	Position Position
	Traces   TracesSequence
	Steps    int
}

func (t *TravelerTask) Init(ID int, seed int64, symbol rune) {
	t.ID = ID
	t.Symbol = symbol

	t.Position = Position{
		X: int(float64(BoardWidth) * RandomClass.Float64()),
		Y: int(float64(BoardHeight) * RandomClass.Float64()),
	}

	t.Traces = TracesSequence{}
	t.Traces.Last = -1
	t.storeTrace(0)
	t.Steps = MinSteps + int(float64(MaxSteps-MinSteps)*RandomClass.Float64())
}

func (t *TravelerTask) Start() {
	// for step := 0; step < t.Steps; step++
	for range t.Steps {
		delay := MinDelay + (MaxDelay-MinDelay)*RandomClass.Float64()
		time.Sleep(time.Duration(delay * float64(time.Second)))
		t.makeStep()
		t.storeTrace(time.Now().Sub(StartTime))
	}
	t.report()
}

func (t *TravelerTask) storeTrace(timestamp time.Duration) {
	t.Traces.Last++
	t.Traces.TraceArray[t.Traces.Last] = Trace{
		TimeStamp: timestamp,
		ID:        t.ID,
		Position:  t.Position,
		Symbol:    t.Symbol,
	}
}

func (t *TravelerTask) makeStep() {
	switch rand.Intn(4) {
	case 0:
		t.Position.MoveUp()
	case 1:
		t.Position.MoveDown()
	case 2:
		t.Position.MoveLeft()
	case 3:
		t.Position.MoveRight()
	}
}

func (t *TravelerTask) report() {
	t.Traces.PrintTraces()
}

func main() {
	fmt.Printf("-1 %d %d %d\n", NrOfTravelers, BoardWidth, BoardHeight)

	travelTasks := make([]TravelerTask, NrOfTravelers)
	symbol := 'A'

	for i := range NrOfTravelers {
		travelTasks[i].Init(i, time.Now().UnixNano()+int64(i), symbol)
		symbol++
	}

	var wg sync.WaitGroup
	wg.Add(NrOfTravelers)

	for i := range NrOfTravelers {
		go func(task *TravelerTask) {
			defer wg.Done()
			task.Start()
		}(&travelTasks[i])
	}

	wg.Wait()
}
