package main

import "testing"

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
