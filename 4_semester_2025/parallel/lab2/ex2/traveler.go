package main

import "time"

type Traveler struct {
	ID       int
	Symbol   rune
	Position Position

	traces    TraceSequence
	timeStamp time.Duration
	response  Response
}
