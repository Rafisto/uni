package main

type Position struct {
	X int
	Y int
}

func (p *Position) MoveDown() {
	p.Y = (p.Y + 1) % BoardHeight
}

func (p *Position) MoveUp() {
	p.Y = (p.Y - 1 + BoardHeight) % BoardHeight
}

func (p *Position) MoveRight() {
	p.X = (p.X + 1) % BoardWidth
}

func (p *Position) MoveLeft() {
	p.X = (p.X - 1 + BoardWidth) % BoardWidth
}

func (p *Position) Move_Direction(dir int) {
	switch dir {
	case 0:
		p.MoveUp()
	case 1:
		p.MoveDown()
	case 2:
		p.MoveLeft()
	case 3:
		p.MoveRight()
	}
}
