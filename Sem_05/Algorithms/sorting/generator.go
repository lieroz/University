package main

import "math/rand"

func generateSortedArray(n int) []int {
	arr := make([]int, n, n)
	for i := 0; i < n; i ++ {
		arr[i] = i
	}
	return arr
}

func generateRandomArray(n int) []int {
	arr := make([]int, n, n)
	for i := 0; i < n; i ++ {
		arr[i] = rand.Intn(n)
	}
	return arr
}

func generateReversedArray(n int) []int {
	arr := make([]int, n, n)
	for i := 0; i < n; i ++ {
		arr[i] = n - i - 1
	}
	return arr
}
