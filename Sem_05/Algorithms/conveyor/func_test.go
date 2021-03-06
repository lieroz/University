package main

import "testing"

func BenchmarkConveyor(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ExecutePipeline(job(fill), job(SingleHash), job(MultiHash), job(CombineResults))
	}
}
