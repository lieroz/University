//
// Created by lieroz on 29.11.16.
//

#include <stdio.h>
#include <stdlib.h>

#ifndef LAB_09_MATRIX_H
#define LAB_09_MATRIX_H

typedef struct {
	int vertex_count;
	int** adjacency_matrix;
} Graph;

Graph* InitializeStructure(int);

void ClearStructure(Graph*);

void InputMatrix(Graph*);

#endif //LAB_09_MATRIX_H
