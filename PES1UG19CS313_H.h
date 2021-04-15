//This is the header file that contains function prototypes and user defined data type definitions

#ifndef PES1UG19CS313_H
#define PES1UG19CS313_H

#ifdef __cplusplus
extern "C" {
#endif
///////////////////////////////////////////////// Graph /////////////////////////////////////////////////

// Structure of a vertex in the graph
typedef struct vertex{
    int id;
    int weight;           
    struct vertex *next;
}Vertex;

// Structure of the root node of the adjacency list 
typedef struct adjacencylist{
    Vertex *head;
}AdjacencyList;

// A wrapper structure that holds the graph
typedef struct graph{
    int numVertices;     // Number of vertices in the graph
    AdjacencyList *list; // Adjacency list
}Graph;

// Graph Routines
Graph* GraphInit(int n); // Returns an initialised graph
void GraphAppend(Graph *g, int source, int destination, int weight); // Adds an edge to the graph
void GraphDestroy(Graph *g); // Destroys the graph (frees up allocated memory)

/////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////// Priority Queue using Min Heap /////////////////////////////////////

// Structure of a node in the heap
typedef struct heapnode{
    int id;
    int distance;
    int predecessor;
}HeapNode;

// Structure of the min heap
typedef struct minheap{
    int currentSize;
    int capacity;
    int *positionArray; // This array holds the position of the vertices in the heap
    HeapNode *heap;
}MinHeap;

// Heap Routines
MinHeap* HeapInit(int n); // Returns an initialised heap
void HeapInsert(MinHeap* h, int id, int distance, int predecessor); // Inserts a node into the heap
int HeapDelete(MinHeap* h); // Deletes the minimum node from the heap
int HeapSearch(MinHeap* h, int id); // Returns the index of a vertex in the heap (using the position array)
void HeapUpdate(MinHeap* h, int id, int newDistance, int newPredecessor); // Updates the priority of an element in the heap
int HeapSize(MinHeap* h); // Returns the current size of the heap
int HeapGetDistance(MinHeap* h, int id); // Returns the current minimum distance of a node in the heap from the source

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Utility functions
void printPath(MinHeap *h, int destination);

// Dijkstra
void Dijkstra(Graph g, int vertex);

#ifdef __cplusplus
}
#endif

#endif // PES1UG19CS313_H