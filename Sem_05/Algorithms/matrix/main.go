package main

import "fmt"

func main() {
	m1, m2 := NewMatrix(4, 4), NewMatrix(4, 4)
	m1.Fill()
	m2.Fill()
	fmt.Println(GrapeProduct(m1, m2))
}
