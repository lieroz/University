package main

import "testing"

const (
	first  = "cp"//dkU55pbNNO7QzCq3JDSF0cR1tfyNqTWsj6FicWbwufJeHhAWhvds8mciYEQWaiEZuxnH1FbmnDSXsaNN6Bam6Bs54a1p8MR1Awe9iY3oGLe7C5Zxn9QhLliMIiuYz9"
	second = "No"//QSy5cTDKBtxFQ70jmtGHsF2Ad7d9jTITwutxphwPQ9DMBzjaPNnMbeiGi6FGalheQEPMZW0QfMrP8GX2isjMhy7NjBPypH8GKLDuyn4liTA1SZGRcJGplP0QVJ3U6y"
)

func BenchmarkLevenshteinIteraitive(b *testing.B) {
	for i := 0; i < b.N; i++ {
		_ = LevenshteinIteraitive(first, second)
	}
}

func BenchmarkLevenshteinRecursive(b *testing.B) {
	for i := 0; i < b.N; i++ {
		_ = LevenshteinRecursive(first, second)
	}
}

func BenchmarkLevenshteinOptimized(b *testing.B) {
	for i := 0; i < b.N; i++ {
		_ = LevenshteinOptimized(first, second)
	}
}
