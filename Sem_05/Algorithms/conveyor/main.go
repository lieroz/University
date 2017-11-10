package main

import (
	"fmt"
	"time"
	"os"
)

var sliceLen int

func main() {
	fmt.Print("Enter data slice length: ")
	_, err := fmt.Scanf("%d", &sliceLen)
	if err != nil {
		os.Exit(1)
	}
	start := time.Now()
	ExecutePipeline(job(fill), job(SingleHash), job(MultiHash), job(CombineResults))
	fmt.Println(time.Since(start))
}
