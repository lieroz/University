package main

import (
	"fmt"
	"os"
)

var sliceLen int

func main() {
	fmt.Print("Enter data slice length: ")
	_, err := fmt.Scanf("%d", &sliceLen)
	if err != nil {
		os.Exit(1)
	}
	ExecutePipeline(job(fill), job(SingleHash), job(MultiHash), job(CombineResults))
}
