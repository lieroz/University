package main

type Matrix struct {
	Buffer [][]int
	Rows   int
	Cols   int
}

func NewMatrix(rows, cols int) *Matrix {
	m := new(Matrix)
	m.Buffer = make([][]int, rows, rows)
	m.Rows, m.Cols = rows, cols
	for i := 0; i < rows; i++ {
		m.Buffer[i] = make([]int, cols, cols)
	}
	return m
}

func (m *Matrix) Get(row, col int) int {
	return m.Buffer[row][col]
}

func (m *Matrix) Set(row, col, val int) {
	m.Buffer[row][col] = val
}
