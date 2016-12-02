#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// A structure to represent a node in adjacency list
typedef struct AdjListNode {
	int dest;
	int weight;
	struct AdjListNode* next;
} AdjListNode;

// A structure to represent an adjacency list
typedef struct {
	AdjListNode* head;  // pointer to head node of list
} AdjList;

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
typedef struct {
	int V;
	AdjList* array;
} Graph;

// A utility function to create a new adjacency list node
AdjListNode* NewAdjListNode(int dest, int weight) {
	AdjListNode* new_node = (AdjListNode*) malloc(sizeof(struct AdjListNode));

	new_node->dest = dest;
	new_node->weight = weight;
	new_node->next = NULL;

	return new_node;
}

// A utility function that creates a graph of V vertices
Graph* CreateGraph(int V) {
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->V = V;

	// Create an array of adjacency lists.  Size of array will be V
	graph->array = (AdjList*) malloc(V * sizeof(AdjList));

	// Initialize each adjacency list as empty by making head as NULL
	for (int i = 0; i < V; ++i) {
		graph->array[i].head = NULL;
	}

	return graph;
}

// Adds an edge to an undirected graph
void AddEdge(Graph* graph, int src, int dest, int weight) {
	// Add an edge from src to dest.  A new node is added to the adjacency
	// list of src.  The node is added at the begining
	AdjListNode* new_node = NewAdjListNode(dest, weight);
	new_node->next = graph->array[src].head;
	graph->array[src].head = new_node;

	// Since graph is undirected, add an edge from dest to src also
	new_node = NewAdjListNode(src, weight);
	new_node->next = graph->array[dest].head;
	graph->array[dest].head = new_node;
}

// Structure to represent a min heap node
typedef struct {
	int v;
	int dist;
} MinHeapNode;

// Structure to represent a min heap
typedef struct {
	int size;      // Number of heap nodes present currently
	int capacity;  // Capacity of min heap
	int* pos;     // This is needed for DecreaseKey()
	MinHeapNode** array;
} MinHeap;

// An utility function to create a new Min Heap Node
MinHeapNode* NewMinHeapNode(int v, int dist) {
	MinHeapNode* min_heap_node = (MinHeapNode*) malloc(sizeof(MinHeapNode));

	min_heap_node->v = v;
	min_heap_node->dist = dist;

	return min_heap_node;
}

// A utility function to create a Min Heap
MinHeap* CreateMinHeap(int capacity) {
	MinHeap* min_heap = (MinHeap*) malloc(sizeof(MinHeap));

	min_heap->pos = (int*) malloc(capacity * sizeof(int));
	min_heap->size = 0;
	min_heap->capacity = capacity;
	min_heap->array = (MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));

	return min_heap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void SwapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
	MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void MinHeapify(MinHeap* min_heap, int idx) {
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < min_heap->size &&
		min_heap->array[left]->dist < min_heap->array[smallest]->dist) {
		smallest = left;
	}

	if (right < min_heap->size &&
		min_heap->array[right]->dist < min_heap->array[smallest]->dist) {
		smallest = right;
	}

	if (smallest != idx) {
		// The nodes to be swapped in min heap
		MinHeapNode* smallestNode = min_heap->array[smallest];
		MinHeapNode* idx_node = min_heap->array[idx];

		// Swap positions
		min_heap->pos[smallestNode->v] = idx;
		min_heap->pos[idx_node->v] = smallest;

		// Swap nodes
		SwapMinHeapNode(&min_heap->array[smallest], &min_heap->array[idx]);

		MinHeapify(min_heap, smallest);
	}
}

// A utility function to check if the given minHeap is ampty or not
int IsEmpty(MinHeap* min_heap) {
	return min_heap->size == 0;
}

// Standard function to extract minimum node from heap
MinHeapNode* ExtractMin(MinHeap* min_heap) {
	if (IsEmpty(min_heap)) {
		return NULL;
	}

	// Store the root node
	MinHeapNode* root = min_heap->array[0];

	// Replace root node with last node
	MinHeapNode* last_node = min_heap->array[min_heap->size - 1];
	min_heap->array[0] = last_node;

	// Update position of last node
	min_heap->pos[root->v] = min_heap->size - 1;
	min_heap->pos[last_node->v] = 0;

	// Reduce heap size and heapify root
	--min_heap->size;
	MinHeapify(min_heap, 0);

	return root;
}

// Function to decrease dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void DecreaseKey(MinHeap* min_heap, int v, int dist) {
	// Get the index of v in  heap array
	int i = min_heap->pos[v];

	// Get the node and update its dist value
	min_heap->array[i]->dist = dist;

	// Travel up while the complete tree is not hepified.
	// This is a O(Logn) loop
	while (i && min_heap->array[i]->dist < min_heap->array[(i - 1) / 2]->dist) {
		// Swap this node with its parent
		min_heap->pos[min_heap->array[i]->v] = (i - 1) / 2;
		min_heap->pos[min_heap->array[(i - 1) / 2]->v] = i;
		SwapMinHeapNode(&min_heap->array[i], &min_heap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool IsInMinHeap(MinHeap* min_heap, int v) {
	if (min_heap->pos[v] < min_heap->size) {
		return true;
	}

	return false;
}

// Function to print shortest path from source to j
// using parent array
void PrintPath(int parent[], int j) {
	// Base Case : If j is source
	if (parent[j] == -1) {
		return;
	}

	PrintPath(parent, parent[j]);

	fprintf(stdout, "%d ", j);
}

// A utility function used to print the solution
void PrintArr(int dist[], int n, int parent[]) {
	int src = 0;
	fprintf(stdout, "Vertex\t  Distance\tPath");

	for (int i = 1; i < n; i++) {
		fprintf(stdout, "\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
		PrintPath(parent, i);
	}
}

// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void DijkstraShortestDistance(Graph* graph, int src) {
	int V = graph->V;// Get the number of vertices in graph
	int dist[V];      // dist values used to pick minimum weight edge in cut
	int parent[V];

	// minHeap represents set E
	MinHeap* min_heap = CreateMinHeap(V);

	// Initialize min heap with all vertices. dist value of all vertices
	for (int v = 0; v < V; ++v) {
		parent[0] = -1;
		dist[v] = INT_MAX;
		min_heap->array[v] = NewMinHeapNode(v, dist[v]);
		min_heap->pos[v] = v;
	}

	// Make dist value of src vertex as 0 so that it is extracted first
	min_heap->array[src] = NewMinHeapNode(src, dist[src]);
	min_heap->pos[src] = src;
	dist[src] = 0;
	DecreaseKey(min_heap, src, dist[src]);

	// Initially size of min heap is equal to V
	min_heap->size = V;

	// In the following loop, min heap contains all nodes
	// whose shortest distance is not yet finalized.
	while (!IsEmpty(min_heap)) {
		// Extract the vertex with minimum distance value
		MinHeapNode* min_heap_node = ExtractMin(min_heap);
		int u = min_heap_node->v; // Store the extracted vertex number

		// Traverse through all adjacent vertices of u (the extracted
		// vertex) and update their distance values
		AdjListNode* p_crawl = graph->array[u].head;
		while (p_crawl != NULL) {
			int v = p_crawl->dest;

			// If shortest distance to v is not finalized yet, and distance to v
			// through u is less than its previously calculated distance
			if (IsInMinHeap(min_heap, v) && dist[u] != INT_MAX &&
				p_crawl->weight + dist[u] < dist[v]) {
				dist[v] = dist[u] + p_crawl->weight;
				parent[v] = u;
				// update distance value in min heap also
				DecreaseKey(min_heap, v, dist[v]);
			}
			p_crawl = p_crawl->next;
		}
	}

	// print the calculated shortest distances
	PrintArr(dist, V, parent);
}

// Driver program to test above functions
int main() {
	// create the graph given in above fugure
	int V = 9;
	Graph* graph = CreateGraph(V);
	AddEdge(graph, 0, 1, 4);
	AddEdge(graph, 0, 7, 8);
	AddEdge(graph, 1, 2, 8);
	AddEdge(graph, 1, 7, 11);
	AddEdge(graph, 2, 3, 7);
	AddEdge(graph, 2, 8, 2);
	AddEdge(graph, 2, 5, 4);
	AddEdge(graph, 3, 4, 9);
	AddEdge(graph, 3, 5, 14);
	AddEdge(graph, 4, 5, 10);
	AddEdge(graph, 5, 6, 2);
	AddEdge(graph, 6, 7, 1);
	AddEdge(graph, 6, 8, 6);
	AddEdge(graph, 7, 8, 7);

	DijkstraShortestDistance(graph, 0);

	return 0;
}