package main

import "fmt"

func main() {
	fmt.Println(LevenshteinIteraitive("abcdefg", "badclth"))
	fmt.Println(LevenshteinRecursive("abcdefg", "badclth"))
	fmt.Println(LevenshteinOptimized("abcdefg", "badclth"))
}
