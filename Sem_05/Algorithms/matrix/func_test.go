package main

import "testing"

const (
	Rows = 100
	Cols = 100
)

var (
	A = NewMatrix(Rows, Cols)
	B = NewMatrix(Rows, Cols)
)

func init() {
	A.Fill()
	B.Fill()
}

func BenchmarkClassicProduct(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ClassicProduct(A, B)
	}
}

func BenchmarkClassicBufferedProduct(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ClassicBufferedProduct(A, B)
	}
}

func BenchmarkWinogradProduct(b *testing.B) {
	for i := 0; i < b.N; i++ {
		WinogradProduct(A, B)
	}
}

func BenchmarkWinogradImprovedProduct(b *testing.B) {
	for i := 0; i < b.N; i++ {
		WinogradImprovedProduct(A, B)
	}
}

func BenchmarkParallelProduct(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ParallelProduct(A, B)
	}
}
