//
// Created by lieroz on 29.11.16.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dequeue.h"

#ifndef LAB_09_MATRIX_H
#define LAB_09_MATRIX_H

typedef struct {
	int vertex_count;
	Dequeue** adjacency_lists;
} Graph;

Graph* InitializeGraph(int);

void ClearGraph(Graph*);

void AddEdge(Graph*, int, int);

void BFS(Graph*, int);

void DFS(Graph*, int);

void TopSort(Graph*);

#endif //LAB_09_MATRIX_H
