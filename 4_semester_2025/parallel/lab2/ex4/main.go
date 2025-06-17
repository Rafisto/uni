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
	NrOfTraps     = 10
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
	Board     = [BoardWidth][BoardHeight]Field{}
)

type GeneralTraveler interface {
	Init(ID int, symbol rune)
	Start()
	StoreTrace()
}

type Response int

const (
	Success Response = iota
	Fail
	Trapped
	Deadlock
)

type Traveler struct {
	ID       int
	Symbol   rune
	Position Position

	traces    TraceSequence
	timeStamp time.Duration
	response  Response
}

type Basic struct {
	Traveler
	steps int
}

type EvictRequest struct {
	Position Position
	Status   Response
}
type Squatter struct {
	Traveler
	RelocateChannel chan EvictRequest

	timeAppear    time.Duration
	timeDisappear time.Duration
}

type TrapRequest struct {
	Traveler        GeneralTraveler
	ResponseChannel chan Response
}
type Trap struct {
	Traveler
	TrapChannel chan TrapRequest
	Done        chan bool

	traveler GeneralTraveler
}

type EnterRequest struct {
	Traveler        GeneralTraveler
	ResponseChannel chan Response
}
type Field struct {
	EnterChannel chan EnterRequest
	LeaveChannel chan bool

	position Position
	traveler GeneralTraveler
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
							Squatter.RelocateChannel <- EvictRequest{newPosition, Success}
							n.traveler = Request.Traveler
							Request.ResponseChannel <- Success
						}
					} else {
						Request.ResponseChannel <- Fail
					}
				} else if trap, ok := n.traveler.(*Trap); ok {
					trap.TrapChannel <- TrapRequest{Request.Traveler, Request.ResponseChannel}
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

func (t *Basic) Init(ID int, symbol rune) {
	t.ID = ID
	t.Symbol = symbol
	t.steps = MinSteps + rand.Intn(MaxSteps-MinSteps+1)

	t.response = Fail
	for t.response == Fail {
		t.Position = Position{
			X: rand.Intn(BoardWidth),
			Y: rand.Intn(BoardHeight),
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

	if t.response == Trapped {
		t.Position = Position{
			X: BoardWidth,
			Y: BoardHeight,
		}
	}

	t.timeStamp = time.Since(StartTime)
	t.StoreTrace()
}

func (t *Basic) Start() {
	go func() {
		for i := 0; i < t.steps; i++ {
			if t.response == Trapped || t.response == Deadlock {
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
			case Trapped:
				Board[t.Position.X][t.Position.Y].LeaveChannel <- true
				t.Position = Position{
					X: BoardWidth,
					Y: BoardHeight,
				}
			case Deadlock:
				t.Symbol = unicode.ToLower(t.Symbol)
			}

			t.timeStamp = time.Since(StartTime)
			t.StoreTrace()
		}

		printer.TraceChannel <- t.traces
	}()
}

func (t *Squatter) Init(ID int, symbol rune) {
	t.RelocateChannel = make(chan EvictRequest)
	t.ID = ID
	t.Symbol = symbol
	t.timeAppear = 10 * time.Millisecond
	t.timeDisappear = t.timeAppear + time.Duration(rand.Int63n(int64(MaxDelay*MaxSteps-t.timeAppear)))
}

func (t *Squatter) Start() {
	go func() {
		time.Sleep(t.timeAppear)

		t.response = Fail
		for t.response == Fail {
			t.Position = Position{
				X: rand.Intn(BoardWidth),
				Y: rand.Intn(BoardHeight),
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

		t.RelocateChannel = make(chan EvictRequest)
		for true {
			if t.response == Trapped || time.Since(StartTime) > t.timeDisappear {
				break
			}

			select {
			case Request := <-t.RelocateChannel:
				t.response = Request.Status
				t.Position = Request.Position
				t.timeStamp = time.Since(StartTime)
				t.StoreTrace()
			case <-time.After(t.timeDisappear - time.Since(StartTime)):
			}
		}

		if t.response != Trapped {
			Board[t.Position.X][t.Position.Y].LeaveChannel <- true
			t.Position = Position{
				X: BoardWidth,
				Y: BoardHeight,
			}
			t.timeStamp = time.Since(StartTime)
			t.StoreTrace()
		}

		printer.TraceChannel <- t.traces
	}()
}

func (t *Trap) Init(ID int, symbol rune) {
	t.TrapChannel = make(chan TrapRequest, 4)
	t.Done = make(chan bool)
	t.ID = ID
	t.Symbol = '#'
	t.traveler = nil

	t.response = Fail
	for t.response == Fail {
		t.Position = Position{
			X: rand.Intn(BoardWidth),
			Y: rand.Intn(BoardHeight),
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

	t.Start()
}

func (t *Trap) Start() {
	go func() {

		for true {
			if t.response == Deadlock {
				break
			}

			select {
			case Request := <-t.TrapChannel:
				switch v := Request.Traveler.(type) {
				case *Basic:
					t.response = Trapped
					t.Symbol = unicode.ToLower(t.Symbol)
				case *Squatter:
					select {
					case v.RelocateChannel <- EvictRequest{Position{BoardWidth, BoardHeight}, Trapped}:
						t.response = Trapped
						t.Symbol = '*'
					default:
						t.response = Fail
					}
				default:
					t.response = Fail
				}

				Request.ResponseChannel <- t.response

				if t.response == Trapped {
					if basic, ok := Request.Traveler.(*Basic); ok {

						t.Symbol = unicode.ToLower(basic.Symbol)
					} else if _, ok := Request.Traveler.(*Squatter); ok {

						t.Symbol = '*'
					} else {

					}

					t.timeStamp = time.Since(StartTime)

					t.StoreTrace()

					time.Sleep(10 * MaxDelay)

					t.Symbol = '#'
					t.timeStamp = time.Since(StartTime)
					t.StoreTrace()
				}
			case <-t.Done:
				t.response = Deadlock
			}
		}

		printer.TraceChannel <- t.traces
	}()
}

func main() {
	var travelers [NrOfTraps + NrOfTravelers + NrOfSquatters]GeneralTraveler

	fmt.Printf(
		"-1 %d %d %d\n",
		NrOfTraps+NrOfTravelers+NrOfSquatters,
		BoardWidth,
		BoardHeight,
	)

	printer.Start()

	for i := 0; i < BoardWidth; i++ {
		for j := 0; j < BoardHeight; j++ {
			Board[i][j].Init(Position{i, j})
		}
	}

	ID := 0
	for i := 0; i < NrOfTraps; i++ {
		travelers[ID] = &Trap{}
		travelers[ID].Init(ID, '#')
		ID++
	}

	symbol := 'A'
	for i := 0; i < NrOfTravelers; i++ {
		travelers[ID] = &Basic{}
		travelers[ID].Init(ID, symbol)
		ID++
		symbol++
	}

	symbol = '0'
	for i := 0; i < NrOfSquatters; i++ {
		travelers[ID] = &Squatter{}
		travelers[ID].Init(ID, symbol)
		ID++
		symbol++
	}

	ID = NrOfTraps
	for i := 0; i < NrOfTravelers; i++ {
		travelers[ID].Start()
		ID++
	}

	for i := 0; i < NrOfSquatters; i++ {
		travelers[ID].Start()
		ID++
	}

	<-printer.Done

	for i := 0; i < NrOfTraps; i++ {
		trap, _ := travelers[i].(*Trap)
		trap.Done <- true
	}

	<-printer.Done
}
