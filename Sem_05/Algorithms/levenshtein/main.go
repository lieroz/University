package main

import (
	"fmt"
)

const (
	first  = "cpdkU55pbN"//NO7QzCq3JDSF0cR1tfyNqTWsj6FicWbwufJeHhAWhvds8mciYEQWaiEZuxnH1FbmnDSXsaNN6Bam6Bs54a1p8MR1Aw"
	second = "NoQSy5cTDK"//BtxFQ70jmtGHsF2Ad7d9jTITwutxphwPQ9DMBzjaPNnMbeiGi6FGalheQEPMZW0QfMrP8GX2isjMhy7NjBPypH8GKL"
)

func main() {
	fmt.Println(LevenshteinIteraitive(first, second))
	fmt.Println(LevenshteinRecursive(first, second))
	fmt.Println(LevenshteinOptimized(first, second))
}
