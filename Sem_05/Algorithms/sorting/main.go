package main

import "fmt"

func main() {
	arr := []int{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
	a, b, c := make([]int, len(arr), len(arr)), make([]int, len(arr), len(arr)), make([]int, len(arr), len(arr))
	copy(a, arr)
	copy(b, arr)
	copy(c, arr)
	fmt.Println(MergeSort(a))
	fmt.Println(MergeSortMulti(b))
	fmt.Println(MergeSortCombined(c))
}
