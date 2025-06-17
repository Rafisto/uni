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

type TraceArray [MaxSteps * 2]Trace

type TraceSequence struct {
	Last       int
	TraceArray TraceArray
}

func (t *Trace) Print() {
	fmt.Printf("%.9f  %d  %d  %d  %c\n", t.TimeStamp.Seconds(), t.ID, t.Position.X, t.Position.Y, t.Symbol)
}

func (ts *TraceSequence) PrintTraces() {
	for i := 0; i <= ts.Last; i++ {
		if ts.TraceArray[i].TimeStamp.Seconds() > 0 {
			ts.TraceArray[i].Print()
		}
	}
}
