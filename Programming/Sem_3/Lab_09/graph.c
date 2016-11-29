//
// Created by lieroz on 29.11.16.
//

#include "graph.h"

Graph* InitializeStructure(int vertex_count) {
	Graph* g = (Graph*) malloc(sizeof(Graph));
	g->vertex_count = vertex_count;
	g->adjacency_matrix = (int**) malloc(sizeof(int*) * vertex_count);

	for (size_t i = 0; i < vertex_count; ++i) {
		g->adjacency_matrix[i] = (int) malloc(sizeof(int) * vertex_count);
	}

	return g;
}

void ClearStructure(Graph* g) {
	for (size_t i = 0; i < g->vertex_count; ++i) {
		free(g->adjacency_matrix[i]);
	}

	free(g->adjacency_matrix);

	g->adjacency_matrix = NULL;
	g->vertex_count = 0;

	free(g);
}

void InputMatrix(Graph* g) {
	for (size_t i = 0; i < g->vertex_count; ++i) {

		for (size_t j = 0; j < g->vertex_count; ++j) {

			int adjacency = 0;
			fscanf(stdin, "%d", &adjacency);

			if (adjacency != 0 && adjacency != 1) {
				fprintf(stderr, "[error]\n");\
				return;
			}

			g->adjacency_matrix[i][j] = adjacency;
		}
	}
}