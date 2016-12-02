#include "graph.h"
#include "dijkstra.h"

Graph* BuildGraph(FILE* f) {
	int vertex_count = 0;

	fscanf(f, "%d", &vertex_count);

	Graph* G = CreateGraph(vertex_count);

	while (!feof(f)) {
		int vertex_index = 0;
		int vertex = 0;
		int weight = 0;

		fscanf(f, "%d %d %d", &vertex_index, &vertex, &weight);
		AddEdge(G, vertex_index, vertex, weight);
	}

	return G;
}

int main() {
	FILE* a = fopen("a.txt", "r");
	Graph* A = BuildGraph(a);

	fprintf(stdout, "ShortestDistance A:\n");
	DijkstraShortestDistance(A, 0);
	fprintf(stdout, "\n\n");

	fclose(a);

	FILE* b = fopen("b.txt", "r");
	Graph* B = BuildGraph(b);

	fprintf(stdout, "ShortestDistance B:\n");
	DijkstraShortestDistance(B, 0);
	fprintf(stdout, "\n\n");

	fclose(b);

	FILE* c = fopen("c.txt", "r");
	Graph* C = BuildGraph(c);

	fprintf(stdout, "ShortestDistance C:\n");
	DijkstraShortestDistance(C, 0);
	fprintf(stdout, "\n\n");

	fclose(c);

	FILE* d = fopen("d.txt", "r");
	Graph* D = BuildGraph(d);

	fprintf(stdout, "ShortestDistance D:\n");
	DijkstraShortestDistance(D, 0);
	fprintf(stdout, "\n\n");

	fclose(d);

	return 0;
}