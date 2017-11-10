package main

import (
	"fmt"
)

type Matrix struct {
	Buffer [][]int
	Rows   int
	Cols   int
}

func NewMatrix(rows, cols int) *Matrix {
	if rows <= 0 || cols <= 0 {
		panic("invalid matrix parameters!")
	}
	m := new(Matrix)
	m.Buffer = make([][]int, rows, rows)
	m.Rows, m.Cols = rows, cols
	for i := 0; i < rows; i++ {
		m.Buffer[i] = make([]int, cols, cols)
	}
	return m
}

func (m *Matrix) Get(row, col int) int {
	if row < 0 || col < 0 {
		panic("index out of range!")
	}
	return m.Buffer[row][col]
}

func (m *Matrix) Set(row, col, val int) {
	if row < 0 || col < 0 {
		panic("index out of range!")
	}
	m.Buffer[row][col] = val
}

func (m *Matrix) String() string {
	var result string
	for i := 0; i < m.Rows; i++ {
		for j := 0; j < m.Cols; j ++ {
			result += fmt.Sprintf("%5d", m.Get(i, j))
		}
		result += "\n"
	}
	return result
}

func (m *Matrix) Fill() {
	for i := 0; i < m.Rows; i++ {
		for j := 0; j < m.Cols; j++ {
			m.Set(i, j, i*j)
		}
	}
}
