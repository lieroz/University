package main

func ParallelProduct(A, B *Matrix) (C *Matrix) {
	if A.Cols != B.Rows {
		return nil
	}
	C = NewMatrix(A.Rows, B.Cols)
	in := make(chan int)
	quit := make(chan bool)
	dotRowCol := func() {
		for {
			select {
			case i := <-in:
				sums := make([]int, B.Cols)
				for k := 0; k < A.Cols; k++ {
					for j := 0; j < B.Cols; j++ {
						sums[j] += A.Get(i, k) * B.Get(k, j)
					}
				}
				for j := 0; j < B.Cols; j++ {
					C.Set(i, j, sums[j])
				}
			case <-quit:
				return
			}
		}
	}
	threads := 2
	for i := 0; i < threads; i++ {
		go dotRowCol()
	}
	for i := 0; i < A.Rows; i++ {
		in <- i
	}
	for i := 0; i < threads; i++ {
		quit <- true
	}
	return
}
