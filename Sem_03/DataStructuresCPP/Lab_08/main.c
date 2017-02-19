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

	int longest_path = 0;
	fprintf(stdout, BOLD LIGHT_MAGENTA "Enter maximum distance: ");

	if (fscanf(stdin, "%d", &longest_path) != 1 || longest_path < 0) {
		fprintf(stderr, "ERROR: INVALID INPUT!");
		return 0;
	}

	FILE* a = fopen("a.txt", "r");
	Graph* A = BuildGraph(a);

	fprintf(stdout, BOLD LIGHT_CYAN "ShortestDistance A:\n" RST);
	DijkstraShortestDistance(A, 0, longest_path);
	fprintf(stdout, "\n\n");

	DestroyGraph(A);
	fclose(a);

	FILE* b = fopen("b.txt", "r");
	Graph* B = BuildGraph(b);

	fprintf(stdout, BOLD LIGHT_CYAN "ShortestDistance B:\n" RST);
	DijkstraShortestDistance(B, 0, longest_path);
	fprintf(stdout, "\n\n");

	DestroyGraph(B);
	fclose(b);

	FILE* c = fopen("c.txt", "r");
	Graph* C = BuildGraph(c);

	fprintf(stdout, BOLD LIGHT_CYAN "ShortestDistance C:\n" RST);
	DijkstraShortestDistance(C, 0, longest_path);
	fprintf(stdout, "\n\n");

	DestroyGraph(C);
	fclose(c);

	FILE* d = fopen("d.txt", "r");
	Graph* D = BuildGraph(d);

	fprintf(stdout, BOLD LIGHT_CYAN "ShortestDistance D:\n" RST);
	DijkstraShortestDistance(D, 0, longest_path);

	DestroyGraph(D);
	fclose(d);

	return 0;
}