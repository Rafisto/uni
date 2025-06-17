package main

import (
	"fmt"
	"math/rand"
	"time"
	"unicode"
)

const (
	NrOfTravelers = 15
	NrOfSquatters = 10
	NrTotal       = NrOfTravelers + NrOfSquatters
	MinSteps      = 10
	MaxSteps      = 100
	MinDelay      = 10 * time.Millisecond
	MaxDelay      = 50 * time.Millisecond
	BoardWidth    = 15
	BoardHeight   = 15
)

var (
	StartTime = time.Now()
	printer   = Printer{}
	Board     = [BoardWidth + 1][BoardHeight + 1]Field{}
)

type BasicTraveler interface {
	Init(id int, symbol rune)
	Start()
	StoreTrace()
}

type Response int

const (
	Success Response = iota
	Fail
	Deadlock
)

type Basic struct {
	Traveler
	steps int
}

type RelocateRequest struct {
	Position Position
	Status   Response
}
type Squatter struct {
	Traveler
	RelocateChannel chan RelocateRequest

	timeBegin time.Duration
	timeEnd   time.Duration
}

type EnterRequest struct {
	Traveler        BasicTraveler
	ResponseChannel chan Response
}
type Field struct {
	EnterChannel chan EnterRequest
	LeaveChannel chan bool

	position Position
	traveler BasicTraveler
	waiting  []EnterRequest
}

func (n *Field) Init(position Position) {
	n.EnterChannel = make(chan EnterRequest)
	n.LeaveChannel = make(chan bool)

	n.position = position
	n.traveler = nil

	n.Start()
}

func (n *Field) Start() {
	go func() {
		for true {
			select {
			case Request := <-n.EnterChannel:
				if n.traveler == nil {

					n.traveler = Request.Traveler
					Request.ResponseChannel <- Success
				} else if _, ok := n.traveler.(*Basic); ok {

					n.waiting = append(n.waiting, Request)
				} else if Squatter, ok := n.traveler.(*Squatter); ok {

					if _, ok := Request.Traveler.(*Basic); ok {
						var newPosition Position
						var nodeResponse Response
						directions := []int{0, 1, 2, 3}

						for _, dir := range directions {
							newPosition = n.position
							newPosition.Move_Direction(dir)

							request := EnterRequest{n.traveler, make(chan Response, 1)}
							Board[newPosition.X][newPosition.Y].EnterChannel <- request
							select {
							case nodeResponse = <-request.ResponseChannel:
							case <-time.After(100 * time.Millisecond):
								request.ResponseChannel <- Fail
								nodeResponse = Fail
							}
							if nodeResponse == Success {

								break
							}
						}

						if nodeResponse != Fail {
							Squatter.RelocateChannel <- RelocateRequest{newPosition, Success}
							n.traveler = Request.Traveler
							Request.ResponseChannel <- Success
						}
					} else {
						Request.ResponseChannel <- Fail
					}
				} else {
					Request.ResponseChannel <- Fail
				}
			case <-n.LeaveChannel:
				n.traveler = nil
				for _, request := range n.waiting {
					select {
					case <-request.ResponseChannel:
						continue
					default:
						request.ResponseChannel <- Success
						n.traveler = request.Traveler
						n.waiting = n.waiting[:0]
					}
					if n.traveler != nil {
						break
					}
				}
			}
		}
	}()
}

func (t *Traveler) StoreTrace() {
	t.traces.Last++
	t.traces.TraceArray[t.traces.Last] = Trace{
		TimeStamp: t.timeStamp,
		ID:        t.ID,
		Position:  t.Position,
		Symbol:    t.Symbol,
	}
}

func (t *Basic) Init(id int, symbol rune) {
	t.ID = id
	t.Symbol = symbol
	t.steps = MinSteps + rand.Intn(MaxSteps-MinSteps+1)

	t.response = Fail
	for t.response == Fail {
		t.Position = Position{
			X: rand.Intn(BoardWidth - 1),
			Y: rand.Intn(BoardHeight - 1),
		}

		request := EnterRequest{t, make(chan Response, 1)}
		Board[t.Position.X][t.Position.Y].EnterChannel <- request
		select {
		case t.response = <-request.ResponseChannel:
		case <-time.After(100 * time.Millisecond):
			request.ResponseChannel <- Fail
			t.response = Fail
		}
	}

	t.timeStamp = time.Since(StartTime)
	t.StoreTrace()
}

func (t *Basic) Start() {
	go func() {
		for i := 0; i < t.steps; i++ {
			if t.response == Deadlock {
				break
			}
			time.Sleep(MinDelay + time.Duration(rand.Int63n(int64(MaxDelay-MinDelay))))

			var newPosition Position
			t.response = Fail
			for t.response == Fail {
				newPosition = t.Position
				newPosition.Move_Direction(rand.Intn(4))
				request := EnterRequest{t, make(chan Response, 1)}
				Board[newPosition.X][newPosition.Y].EnterChannel <- request
				select {
				case t.response = <-request.ResponseChannel:
				case <-time.After(6 * MaxDelay):
					request.ResponseChannel <- Deadlock
					t.response = Deadlock
				}
			}

			switch t.response {
			case Success:
				Board[t.Position.X][t.Position.Y].LeaveChannel <- true
				t.Position = newPosition
			case Deadlock:
				t.Symbol = unicode.ToLower(t.Symbol)
			}

			t.timeStamp = time.Since(StartTime)
			t.StoreTrace()
		}

		printer.TraceChannel <- t.traces
	}()
}

func (t *Squatter) Init(id int, symbol rune) {
	t.RelocateChannel = make(chan RelocateRequest)
	t.ID = id
	t.Symbol = symbol
	t.timeBegin = 10 * MaxDelay * time.Duration(rand.Float64())
	t.timeEnd = t.timeBegin + time.Duration(float64(MaxDelay*MaxSteps-t.timeBegin)*rand.Float64())
}

func (t *Squatter) Start() {
	go func() {
		time.Sleep(t.timeBegin)

		t.response = Fail
		for t.response == Fail {
			t.Position = Position{
				X: rand.Intn(BoardWidth - 1),
				Y: rand.Intn(BoardHeight - 1),
			}

			request := EnterRequest{t, make(chan Response, 1)}
			Board[t.Position.X][t.Position.Y].EnterChannel <- request
			select {
			case t.response = <-request.ResponseChannel:
			case <-time.After(100 * time.Millisecond):
				request.ResponseChannel <- Fail
				t.response = Fail
			}
		}

		t.timeStamp = time.Since(StartTime)
		t.StoreTrace()

		t.RelocateChannel = make(chan RelocateRequest)
		for true {
			if time.Since(StartTime) > t.timeEnd {
				break
			}

			select {
			case Request := <-t.RelocateChannel:
				t.response = Request.Status
				t.Position = Request.Position
				t.timeStamp = time.Since(StartTime)
				t.StoreTrace()
			case <-time.After(t.timeEnd - time.Since(StartTime)):
			}
		}

		t.Position = Position{X: BoardWidth, Y: BoardHeight}
		t.StoreTrace()
		printer.TraceChannel <- t.traces
	}()
}

func main() {
	var travelers [NrTotal]BasicTraveler

	fmt.Printf(
		"-1 %d %d %d\n",
		NrTotal,
		BoardWidth,
		BoardHeight,
	)

	printer.Start()

	for i := 0; i < BoardWidth; i++ {
		for j := 0; j < BoardHeight; j++ {
			Board[i][j].Init(Position{i, j})
		}
	}

	id := 0

	symbol := 'A'
	for i := 0; i < NrOfTravelers; i++ {
		travelers[id] = &Basic{}
		travelers[id].Init(id, symbol)
		id++
		symbol++
	}

	symbol = '0'
	for i := 0; i < NrOfSquatters; i++ {
		travelers[id] = &Squatter{}
		travelers[id].Init(id, symbol)
		id++
		symbol++
	}

	id = 0
	for i := 0; i < NrOfTravelers; i++ {
		travelers[id].Start()
		id++
	}

	for i := 0; i < NrOfSquatters; i++ {
		travelers[id].Start()
		id++
	}

	<-printer.Done
}
