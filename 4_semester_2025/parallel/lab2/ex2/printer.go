package main

type Printer struct {
	TraceChannel chan TraceSequence
	Done         chan bool
}

func (p *Printer) Start() {
	p.TraceChannel = make(chan TraceSequence, NrOfTravelers)
	p.Done = make(chan bool)

	go func() {
		for i := 0; i < NrTotal; i++ {
			traces := <-p.TraceChannel
			traces.PrintTraces()
		}

		p.Done <- true
	}()
}
