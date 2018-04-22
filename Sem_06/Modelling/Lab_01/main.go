package main

import (
	"math"
	"sync/atomic"

	"github.com/tatsushid/go-prettytable"
)

type Term struct {
	power  float64
	factor float64
}

func Multiply(t1, t2 *Term) *Term {
	result := new(Term)
	result.power = t1.power + t2.power
	result.factor = t1.factor * t2.factor
	return result
}

func Add(t1, t2 *Term) *Term {
	result := new(Term)

	if t1.power == t2.power {
		result.power = t1.power
		result.factor = t1.factor + t2.factor
	}

	return result
}

func f(x, y float64) float64 {
	return math.Pow(x, 2) * math.Pow(y, 2)
}

func main() {
	tableHeaders := []prettytable.Column{
		//{Header: "X"},
		{Header: "Pikar 3"},
		{Header: "Pikar 4"},
		{Header: "Pikar 5"},
		{Header: "Linear"},
		{Header: "Runge-Kutta 2"},
		{Header: "Runge-Kutta 4"},
	}

	tbl, err := prettytable.NewTable(tableHeaders...)
	if err != nil {
		panic(err)
	}
	tbl.Separator = " | "
	tbl.AddRow("sad", 1, 2, 3 ,100.4, 5)
	tbl.AddRow("jsdjfhkjsdfjshdkfhj", 1, 2, "sjdhfjsdhjkfhkjsdhfkjsdfjh" ,4, 5)
	tbl.Print()
}
