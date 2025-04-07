package main

import (
	"fmt"
	"time"
)

type Trace struct {
	ID        int
	Symbol    rune
	TimeStamp time.Duration
	Position  Position
}

type TraceArray [MaxSteps]Trace

type TracesSequence struct {
	Last       int
	TraceArray TraceArray
}

func (t *Trace) Print() {
	fmt.Printf("%.9f %d %d %d %c\n", t.TimeStamp.Seconds(), t.ID, t.Position.X, t.Position.Y, t.Symbol)
}

func (ts *TracesSequence) PrintTraces() {
	for i := 0; i <= ts.Last; i++ {
		ts.TraceArray[i].Print()
	}
}
