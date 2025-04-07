package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NrOfTravelers = 15
	MinSteps      = 10
	MaxSteps      = 100
	MinDelay      = 0.01
	MaxDelay      = 0.05
	BoardWidth    = 15
	BoardHeight   = 15
	seed          = 42
)

var (
	StartTime   = time.Now()
	RandomClass = rand.New(rand.NewSource(seed))
)

type Grid struct {
	Cells map[Position]chan struct{}
	mu    sync.Mutex
}

var grid = NewGrid(BoardWidth, BoardHeight)

func NewGrid(width, height int) *Grid {
	grid := &Grid{Cells: make(map[Position]chan struct{})}
	for x := 0; x < width; x++ {
		for y := 0; y < height; y++ {
			grid.Cells[Position{x, y}] = make(chan struct{}, 1)
		}
	}
	return grid
}

type TravelerTask struct {
	ID       int
	Symbol   rune
	Position Position
	Traces   TracesSequence
	Steps    int
	Active   bool
}

func (t *TravelerTask) Init(ID int, seed int64, symbol rune) {
	t.ID = ID
	t.Symbol = symbol

	t.Position = Position{
		X: int(float64(BoardWidth) * RandomClass.Float64()),
		Y: int(float64(BoardHeight) * RandomClass.Float64()),
	}

	t.Active = true

	t.Traces = TracesSequence{}
	t.Traces.Last = -1
	t.storeTrace(0)
	t.Steps = MinSteps + int(float64(MaxSteps-MinSteps)*RandomClass.Float64())
}

func (t *TravelerTask) Start() {
	// for step := 0; step < t.Steps; step++
	for range t.Steps {
		if !t.Active {
			break
		}
		delay := MinDelay + (MaxDelay-MinDelay)*RandomClass.Float64()
		time.Sleep(time.Duration(delay * float64(time.Second)))
		t.Active = t.makeStep()
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

func (t *TravelerTask) makeStep() bool {
	oldPosition := t.Position
	start := time.Now()

	direction := RandomClass.Intn(4)

	for {
		switch direction {
		case 0:
			t.Position.MoveUp()
		case 1:
			t.Position.MoveDown()
		case 2:
			t.Position.MoveLeft()
		case 3:
			t.Position.MoveRight()
		}

		if time.Since(start) > 5*time.Duration(MaxDelay*float64(time.Second)) {
			t.Position = oldPosition
			t.Symbol = t.Symbol + 32
			return false
		}

		grid.mu.Lock()
		if _, taken := grid.Cells[t.Position]; !taken || len(grid.Cells[t.Position]) == 0 {
			grid.Cells[t.Position] <- struct{}{}
			if len(grid.Cells[oldPosition]) > 0 {
				<-grid.Cells[oldPosition]
			}
			grid.mu.Unlock()
			break
		}
		grid.mu.Unlock()

		t.Position = oldPosition
	}
	return true
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
