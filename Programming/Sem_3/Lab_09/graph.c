//
// Created by lieroz on 29.11.16.
//

#include "graph.h"

Graph* InitializeGraph(int vertex_count) {
	Graph* g = (Graph*) malloc(sizeof(Graph));

	g->vertex_count = vertex_count;
	g->adjacency_lists = (Dequeue**) malloc(sizeof(Dequeue*) * vertex_count);

	for (size_t i = 0; i < vertex_count; ++i) {
		g->adjacency_lists[i] = Constructor();
	}

	return g;
}

void ClearGraph(Graph* g) {
	for (size_t i = 0; i < g->vertex_count; ++i) {
		Destructor(g->adjacency_lists[i]);
	}

	free(g->adjacency_lists);

	g->adjacency_lists = NULL;
	g->vertex_count = 0;

	free(g);
}

void AddEdge(Graph* g, int index, int vertex) {
	push_back(g->adjacency_lists[index], vertex);
}

void BFS(Graph* g, int start) {
	bool* visited = (bool*) malloc(sizeof(bool) * g->vertex_count);

	for (size_t i = 0; i < g->vertex_count; ++i) {
		visited[i] = false;
	}

	Dequeue* queue = Constructor();
	push_back(queue, start);
	visited[start] = true;

	while (!empty(queue)) {
		start = pop_front(queue);
		fprintf(stdout, "%d ", start);

		for (size_t i = 0; i < size(g->adjacency_lists[start]); ++i) {

			if (!visited[g->adjacency_lists[start]->base[i]]) {
				visited[g->adjacency_lists[start]->base[i]] = true;
				push_back(queue, g->adjacency_lists[start]->base[i]);
			}
		}
	}

	free(visited);
	Destructor(queue);
}

void DFS(Graph* g, int start) {
	bool* visited = (bool*) malloc(sizeof(bool) * g->vertex_count);

	for (size_t i = 0; i < g->vertex_count; ++i) {
		visited[i] = false;
	}

	Dequeue* stack = Constructor();
	push_back(stack, start);
	visited[start] = true;

	while (!empty(stack)) {
		start = pop_back(stack);
		fprintf(stdout, "%d ", start);

		for (size_t i = 0; i < size(g->adjacency_lists[start]); ++i) {

			if (!visited[g->adjacency_lists[start]->base[i]]) {
				visited[g->adjacency_lists[start]->base[i]] = true;
				push_back(stack, g->adjacency_lists[start]->base[i]);
			}
		}
	}

	free(visited);
	Destructor(stack);
}

void TopSortUtil(Graph* g, int vertex, bool* visited, Dequeue* stack) {
	visited[vertex] = true;

	for (size_t i = 0; i < size(g->adjacency_lists[vertex]); ++i) {

		if (!visited[g->adjacency_lists[vertex]->base[i]]) {
			TopSortUtil(g, g->adjacency_lists[vertex]->base[i], visited, stack);
		}
	}

	push_back(stack, vertex);
}

void TopSort(Graph* g) {
	Dequeue* stack = Constructor();
	bool* visited = (bool*) malloc(sizeof(bool) * g->vertex_count);

	for (size_t i = 0; i < g->vertex_count; ++i) {
		visited[i] = false;
	}

	for (size_t i = 0; i < g->vertex_count; ++i) {

		if (!visited[i]) {
			TopSortUtil(g, i, visited, stack);
		}
	}

	while (!empty(stack)) {
		fprintf(stdout, "%d ", pop_back(stack));
	}

	free(visited);
	Destructor(stack);
}