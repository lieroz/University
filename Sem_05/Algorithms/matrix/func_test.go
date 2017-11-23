package main

import "testing"

const (
	Rows = 500
	Cols = 500
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

func BenchmarkParallelProduct2(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ParallelProduct(A, B, 2)
	}
}

func BenchmarkParallelProduct4(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ParallelProduct(A, B, 4)
	}
}

func BenchmarkParallelProduct8(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ParallelProduct(A, B, 8)
	}
}

func BenchmarkParallelProduct16(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ParallelProduct(A, B, 16)
	}
}

func BenchmarkParallelProduct32(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ParallelProduct(A, B, 32)
	}
}
