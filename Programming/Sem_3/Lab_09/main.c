#include <stdio.h>

#include "graph.h"

int main() {
	int vertex_count = 0;

	fprintf(stdout, "Enter number of vertexes n graph: ");
	fscanf(stdin, "%d", &vertex_count);

	Graph* graph = InitializeStructure(vertex_count);
	InputMatrix(graph);
	ClearStructure(graph);

	return 0;
}