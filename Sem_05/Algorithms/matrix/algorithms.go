package main

func ClassicMatrixMultiplication(first, second *Matrix) *Matrix {
	if first.Cols != second.Rows {
		panic("can't multiply: columns != rows")
	}
	result := NewMatrix(first.Rows, second.Cols)
	for i := 0; i < first.Rows; i++ {
		for j := 0; j < second.Cols; j++ {
			for k := 0; k < first.Cols; k++ {
				val := result.Get(i, j)
				val += first.Get(i, k) * second.Get(k, j)
				result.Set(i, j, val)
			}
		}
	}
	return result
}
