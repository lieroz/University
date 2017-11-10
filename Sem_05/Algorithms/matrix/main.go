package main

import "fmt"

func main() {
	m1, m2 := NewMatrix(5, 3), NewMatrix(3, 2)
	m1.Fill()
	m2.Fill()
	fmt.Println(ClassicMatrixMultiplication(m1, m2))
}
