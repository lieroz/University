package main

func ClassicProduct(A, B *Matrix) *Matrix {
	if A.Cols != B.Rows {
		panic("can't multiply: columns != rows")
	}
	C := NewMatrix(A.Rows, B.Cols)
	for i := 0; i < A.Rows; i++ {
		for j := 0; j < B.Cols; j++ {
			for k := 0; k < A.Cols; k++ {
				val := C.Get(i, j)
				val += A.Get(i, k) * B.Get(k, j)
				C.Set(i, j, val)
			}
		}
	}
	return C
}

func ClassicBufferedProduct(A, B *Matrix) *Matrix {
	if A.Cols != B.Rows {
		panic("can't multiply: columns != rows")
	}
	C := NewMatrix(A.Rows, B.Cols)
	for i := 0; i < A.Rows; i++ {
		for j := 0; j < B.Cols; j++ {
			val := C.Get(i, j)
			for k := 0; k < A.Cols; k++ {
				val += A.Get(i, k) * B.Get(k, j)
			}
			C.Set(i, j, val)
		}
	}
	return C
}

func WinogradProduct(A, B *Matrix) *Matrix {
	if A.Cols != B.Rows {
		panic("can't multiply: columns != rows")
	}
	mulH := make([]int, A.Rows, A.Rows)
	mulW := make([]int, B.Cols, B.Cols)
	for i := 0; i < A.Rows; i++ {
		for j := 0; j < A.Cols/2; j++ {
			mulH[i] += A.Get(i, 2*j) * A.Get(i, 2*j+1)
		}
	}
	for i := 0; i < B.Cols; i++ {
		for j := 0; j < A.Cols/2; j++ {
			mulW[i] += B.Get(2*j, i) * B.Get(2*j+1, i)
		}
	}
	C := NewMatrix(A.Rows, B.Cols)
	for i := 0; i < A.Rows; i++ {
		for j := 0; j < B.Cols; j++ {
			val := -mulH[i] - mulW[j]
			for k := 0; k < A.Cols/2; k++ {
				val += (A.Get(i, 2*k) + B.Get(2*k+1, j)) * (A.Get(i, 2*k+1) + B.Get(2*k, j))
			}
			C.Set(i, j, val)
		}
	}
	if A.Cols%2 != 0 {
		for i := 0; i < A.Rows; i++ {
			for j := 0; j < B.Cols; j++ {
				val := C.Get(i, j)
				val += A.Get(i, A.Cols-1) * B.Get(A.Cols-1, j)
				C.Set(i, j, val)
			}
		}
	}
	return C
}

func WinogradImprovedProduct(A, B *Matrix) *Matrix {
	if A.Cols != B.Rows {
		panic("can't multiply: columns != rows")
	}
	mulH := make([]int, A.Rows, A.Rows)
	mulW := make([]int, B.Cols, B.Cols)
	for i := 0; i < A.Rows; i++ {
		for j := 1; j < A.Cols; j += 2 {
			mulH[i] -= A.Get(i, j-1) * A.Get(i, j)
		}
	}
	for i := 0; i < B.Cols; i++ {
		for j := 1; j < A.Cols; j += 2 {
			mulW[i] -= B.Get(j-1, i) * B.Get(j, i)
		}
	}
	C := NewMatrix(A.Rows, B.Cols)
	for i := 0; i < A.Rows; i++ {
		for j := 0; j < B.Cols; j++ {
			val := mulH[i] + mulW[j]
			for k := 1; k < A.Cols; k += 2 {
				val += (A.Get(i, k-1) + B.Get(k, j)) * (A.Get(i, k) + B.Get(k-1, j))
			}
			if A.Cols%2 != 0 {
				val += A.Get(i, A.Cols-1) * B.Get(A.Cols-1, j)
			}
			C.Set(i, j, val)
		}
	}
	return C
}

func ParallelProduct(A, B *Matrix) (C *Matrix) {
	if A.Cols != B.Rows {
		panic("can't multiply: columns != rows")
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
	threads := 32
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
