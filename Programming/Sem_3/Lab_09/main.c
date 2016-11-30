#include "graph.h"

int main() {
	int vertex_count = 6;

//	fprintf(stdout, "Enter number of vertexes n graph: ");
//	fscanf(stdin, "%d", &vertex_count);

//	Graph* graph = InitializeGraph(vertex_count);
//
//	AddEdge(graph, 0, 1);
//	AddEdge(graph, 0, 2);
//	AddEdge(graph, 1, 2);
//	AddEdge(graph, 2, 0);
//	AddEdge(graph, 2, 3);
//	AddEdge(graph, 3, 3);
//
//	BFS(graph, 2);

//	ClearGraph(graph);

//	Graph* graph = InitializeGraph(vertex_count);
//
//	AddEdge(graph, 1, 0);
//	AddEdge(graph, 0, 2);
//	AddEdge(graph, 2, 1);
//	AddEdge(graph, 0, 3);
//	AddEdge(graph, 3, 4);
//	AddEdge(graph, 4, 0);
//
//	DFS(graph, 0);
//
//	ClearGraph(graph);

	Graph* graph = InitializeGraph(vertex_count);

	AddEdge(graph, 5, 2);
	AddEdge(graph, 5, 0);
	AddEdge(graph, 4, 0);
	AddEdge(graph, 4, 1);
	AddEdge(graph, 2, 3);
	AddEdge(graph, 3, 1);

	TopSort(graph);

	ClearGraph(graph);

	return 0;
}