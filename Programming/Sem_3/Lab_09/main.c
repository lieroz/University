#include "graph.h"

Graph* BuildGraph(FILE* f) {
	int vertex_count = 0;

	fscanf(f, "%d", &vertex_count);

	Graph* G = InitializeGraph(vertex_count);

	while (!feof(f)) {
		int vertex_index = 0;
		int vertex = 0;

		fscanf(f, "%d %d", &vertex_index, &vertex);
		AddEdge(G, vertex_index, vertex);
	}

	return G;
}

int main() {
	FILE* a = fopen("a.txt", "r");
	Graph* A = BuildGraph(a);

	fprintf(stdout, "TopologicalSort A: ");
	TopSort(A);
	fprintf(stdout, "\n\n");

	ClearGraph(A);
	fclose(a);

	FILE* b = fopen("b.txt", "r");
	Graph* B = BuildGraph(b);

	fprintf(stdout, "BFS B: ");
	BFS(B, 0);
	fprintf(stdout, "\n");
	fprintf(stdout, "DFS B: ");
	DFS(B, 0);
	fprintf(stdout, "\n\n");

	ClearGraph(B);
	fclose(b);

	FILE* c = fopen("c.txt", "r");
	Graph* C = BuildGraph(c);

	fprintf(stdout, "BFS C: ");
	BFS(C, 0);
	fprintf(stdout, "\n");
	fprintf(stdout, "DFS C: ");
	DFS(C, 0);
	fprintf(stdout, "\n\n");

	ClearGraph(C);
	fclose(c);

	FILE* d = fopen("d.txt", "r");
	Graph* D = BuildGraph(d);

	fprintf(stdout, "BFS D: ");
	BFS(D, 0);
	fprintf(stdout, "\n");
	fprintf(stdout, "DFS D: ");
	DFS(D, 0);
	fprintf(stdout, "\n\n");

	ClearGraph(D);
	fclose(d);

	return 0;
}