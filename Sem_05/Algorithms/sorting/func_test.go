package main

import (
	"math"
	"testing"
)

const (
	Base   = 10
	Degree = 6
)

var (
	arrLen = int(math.Pow(Base, Degree))
	best   = generateSortedArray(arrLen)
	random = generateRandomArray(arrLen)
	worst  = generateReversedArray(arrLen)
)

func BenchmarkMergeSortSorted(b *testing.B) {
	arr := make([]int, arrLen, arrLen)
	for i := 0; i < b.N; i++ {
		copy(arr, best)
		MergeSort(arr)
	}
}

func BenchmarkMergeSortMultiSorted(b *testing.B) {
	arr := make([]int, arrLen, arrLen)
	for i := 0; i < b.N; i++ {
		copy(arr, best)
		MergeSortMulti(arr)
	}
}

func BenchmarkMergeSortCombinedSorted(b *testing.B) {
	arr := make([]int, arrLen, arrLen)
	for i := 0; i < b.N; i++ {
		copy(arr, best)
		MergeSortCombined(arr)
	}
}

func BenchmarkMergeSortRandom(b *testing.B) {
	arr := make([]int, arrLen, arrLen)
	for i := 0; i < b.N; i++ {
		copy(arr, random)
		MergeSort(arr)
	}
}

func BenchmarkMergeSortMultiRandom(b *testing.B) {
	arr := make([]int, arrLen, arrLen)
	for i := 0; i < b.N; i++ {
		copy(arr, random)
		MergeSortMulti(arr)
	}
}

func BenchmarkMergeSortCombinedRandom(b *testing.B) {
	arr := make([]int, arrLen, arrLen)
	for i := 0; i < b.N; i++ {
		copy(arr, random)
		MergeSortCombined(arr)
	}
}

func BenchmarkMergeSortReversed(b *testing.B) {
	arr := make([]int, arrLen, arrLen)
	for i := 0; i < b.N; i++ {
		copy(arr, worst)
		MergeSort(arr)
	}
}

func BenchmarkMergeSortMultiReversed(b *testing.B) {
	arr := make([]int, arrLen, arrLen)
	for i := 0; i < b.N; i++ {
		copy(arr, worst)
		MergeSortMulti(arr)
	}
}

func BenchmarkMergeSortCombinedReversed(b *testing.B) {
	arr := make([]int, arrLen, arrLen)
	for i := 0; i < b.N; i++ {
		copy(arr, worst)
		MergeSortCombined(arr)
	}
}
