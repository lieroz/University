package main

import "math"

func LevenshteinIteraitive(first, second string) int {
	lenFirst, lenSecond := len(first), len(second)
	if lenFirst == 0 {
		return lenSecond
	}
	if lenSecond == 0 {
		return lenFirst
	}
	rows, cols := lenFirst+1, lenSecond+1
	storage := make([][]int, 2, 2)
	storage[0], storage[1] = make([]int, cols, cols), make([]int, cols, cols)
	for i := 0; i < cols; i++ {
		storage[0][i] = i
	}
	for i := 1; i < rows; i++ {
		storage[1][0] = storage[0][0] + 1
		for j := 1; j < cols; j++ {
			flag := 0
			if first[i-1] != second[j-1] {
				flag = 1
			}
			storage[1][j] = int(math.Min(float64(math.Min(float64(storage[0][j]+1),
				float64(storage[1][j-1]+1))), float64(storage[0][j-1]+flag)))
		}
		storage[0], storage[1] = storage[1], storage[0]
	}
	return storage[0][cols-1]
}

func LevenshteinRecursive(first, second string) int {
	lenFirst, lenSecond := len(first), len(second)
	if lenFirst == 0 {
		return lenSecond
	}
	if lenSecond == 0 {
		return lenFirst
	}
	var flag float64 = 0
	if first[0] != second[0] {
		flag = 1
	}
	return int(math.Min(math.Min(float64(LevenshteinRecursive(first[1:], second)+1),
		float64(LevenshteinRecursive(first, second[1:]))+1),
		float64(LevenshteinRecursive(first[1:], second[1:]))+flag))
}

func LevenshteinOptimized(first, second string) int {
	lenFirst, lenSecond := len(first), len(second)
	if lenFirst < 2 || lenSecond < 2 {
		return LevenshteinIteraitive(first, second)
	}
	rows, cols := lenFirst+1, lenSecond+1
	storage := make([][]int, 3, 3)
	storage[0], storage[1], storage[2] = make([]int, cols, cols), make([]int, cols, cols), make([]int, cols, cols)
	for i := 0; i < cols; i++ {
		storage[0][i] = i
	}
	storage[1][0] = 1
	for i := 1; i < cols; i++ {
		flag := 0
		if first[0] != second[i-1] {
			flag = 1
		}
		storage[1][i] = int(math.Min(float64(math.Min(float64(storage[0][i]+1),
			float64(storage[1][i-1]+1))), float64(storage[0][i-1]+flag)))
	}
	for i := 2; i < rows; i++ {
		storage[2][i] = storage[1][i] + 1
		flag := 0
		if first[i-1] != second[0] {
			flag = 1
		}
		storage[2][1] = int(math.Min(float64(math.Min(float64(storage[1][1]+1),
			float64(storage[2][0]+1))), float64(storage[1][0]+flag)))
		for j := 2; j < cols; j++ {
			flag := 0
			if first[i-1] != second[j-1] {
				flag = 1
			}
			a := float64(math.Min(float64(storage[1][j]+1), float64(storage[2][j-1]+1)))
			b := float64(math.Min(a, float64(storage[1][j-1]+flag)))
			storage[2][j] = int(math.Min(b, float64(storage[0][j-2]+1)))
		}
		storage[0], storage[1], storage[2] = storage[1], storage[2], storage[0]
	}
	return storage[1][cols-1]
}
