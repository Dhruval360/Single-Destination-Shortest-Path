//This file contains the definitions of the functions used

#include "PES1UG19CS313_H.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

///////////////////////////////////////////////// Graph Functions /////////////////////////////////////////////////
Graph* GraphInit(int n){ // Returns an initialised graph
    Graph *graph = (Graph*)malloc(sizeof(Graph));  
    graph->list = (AdjacencyList*)malloc(sizeof(AdjacencyList) * n); 
    for(int i = 0; i < n; i++) graph->list[i].head = NULL; 
    graph->numVertices = n; 
    return graph;
}

void GraphAppend(Graph *g, int source, int destination, int weight){ // Appends a new edge from source to destination with the given weight
    Vertex *new = (Vertex*)malloc(sizeof(Vertex)); 
    new->id = destination - 1; 
    new->weight = weight;
    new->next = g->list[source - 1].head;
    g->list[source - 1].head = new;
}

void GraphDestroy(Graph *g){ // Destroys the given graph (frees all allocated memory)
    for(int i = 0; i < g->numVertices; i++){ // Freeing the edges of the graph (the linked lists present in the list array)
        Vertex *del;
        while((del = g->list[i].head) != NULL){
            g->list[i].head = del->next;
            free(del);
        }
    }
    free(g->list); // Freeing the adjacency list array (list of all the vertices of the graph)
    free(g); // Freeing the graph itself 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////// Heap Functions /////////////////////////////////////////////////
MinHeap* HeapInit(int n){ // Initialises the Heap
    MinHeap *h = (MinHeap*)malloc(sizeof(MinHeap));
    h->heap = (HeapNode*)malloc(sizeof(HeapNode) * n);
    h->positionArray = (int*)malloc(sizeof(int) * n);
    h->currentSize = 0;
    h->capacity = n;
    return h;
}

void HeapDestroy(MinHeap *h){ // Destroys the given heap (frees all allocated memory)
    free(h->positionArray); 
    free(h->heap);
    free(h);
}

void HeapInsert(MinHeap* h, int id, int distance, int predecessor){ // Inserts a node to the Heap array 
    h->heap[h->currentSize].id = id;
    h->heap[h->currentSize].distance = distance;
    h->heap[h->currentSize].predecessor = predecessor;
    h->positionArray[id] = h->currentSize++; 
}

/*
 Note: 
 HeapInsert function does not Heapify after insertion. HeapUpdate and HeapDelete functions on the other hand perform heapification each time.
 The reason behind this is, we do not perform any operations that require a heap structure soon after inserting elements into the heap.
 There will always be a call to HeapUpdate and this will take care of the heapification
*/

int HeapDelete(MinHeap* h){ // Deletes the smallest element in the heap (the zeroth element) and readjusts the remaining heap using top down approach
    int retVal = h->heap[0].id; // The id of the nearest node in the heap
    HeapNode temp = h->heap[h->currentSize - 1];
    h->heap[h->currentSize - 1] = h->heap[0]; // Moving the smallest element in the heap to the end
    h->positionArray[h->heap[0].id] = h->currentSize - 1;
    h->currentSize--; // Decrementing the heap size

    // Readjust top down [O(logn)]
    int parentPos = 0;
    int childPos = 2*parentPos + 1;
    HeapNode parent = temp; // The last element in the heap will become the root when the minimum element from the heap is removed
    while(childPos < h->currentSize){
        HeapNode child = h->heap[childPos];
        if((childPos + 1 < h->currentSize) && child.distance > h->heap[childPos + 1].distance){ // To get the smallest child
            child = h->heap[childPos + 1];
            childPos++;
        }
        if(child.distance < parent.distance){
            h->heap[parentPos] = child;
            h->positionArray[child.id] = parentPos;
            parentPos = childPos;
            childPos = 2*parentPos + 1;
        } 
        else break; // Heap condition satisfied
    }
    h->heap[parentPos] = parent;
    h->positionArray[parent.id] = parentPos;
    return retVal;
}

void HeapUpdate(MinHeap* h, int index, int newDistance, int newPredecessor){ // Updates the distance (priority) of a node at the given index in the heap
    h->heap[index].predecessor = newPredecessor;
    h->heap[index].distance = newDistance;

    // Readjust bottom up [O(logn)]
    int childPos = index; // We need to readjust only from this node as everything below it is already a heap
    int parentPos = (childPos-1)/2;
    HeapNode child = h->heap[childPos];
    while(parentPos >= 0 && childPos != parentPos){
        HeapNode parent = h->heap[parentPos];
        if(parent.distance > child.distance){
            h->heap[childPos] = parent; // A vertex slides down if its distance is greater
            h->positionArray[parent.id] = childPos;
            childPos = parentPos;
            parentPos = (childPos - 1)/2;
        }
        else break; // Heap condition satisfied
    }
    h->heap[childPos] = child;
    h->positionArray[child.id] = childPos;
}

int HeapSearch(MinHeap* h, int id){ // Returns the index of a given vertex in the heap
    return h->positionArray[id];
}

int HeapSize(MinHeap *h){ // Returns the current size of the heap
    return h->currentSize;
}

int HeapGetDistance(MinHeap* h, int index){ // Returns the current minimum distance of the node at the given index in the heap from the source 
    return h->heap[index].distance;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////// Dijkstra Function ///////////////////////////////////////////////
void Dijkstra(Graph g, int vertex){
    MinHeap *queue = HeapInit(g.numVertices);
    for(int i = 0; i < g.numVertices; i++) HeapInsert(queue, i, INT_MAX, vertex-1);
    HeapUpdate(queue, HeapSearch(queue, vertex-1), 0, vertex-1);
    while(HeapSize(queue) != 0){ // While priority queue is not empty
        int nearestNode = HeapDelete(queue);
        int prevIndex = HeapSearch(queue, nearestNode);
        int distance = HeapGetDistance(queue, prevIndex);
        Vertex *temp = g.list[nearestNode].head;
        while(temp != NULL){
            int index = HeapSearch(queue, temp->id); // Finding the position of this vertex in the MinHeap array
            if(index < HeapSize(queue)){ // This vertex is a part of the heap (its minimum distance hasn't been found yet)
                int newDistance = distance + temp->weight;
                int oldDistance = HeapGetDistance(queue, index);
                if(newDistance < oldDistance) HeapUpdate(queue, index, newDistance, nearestNode); // Updating the distance of this vertex as a newer minimum has been found
            }
            temp = temp->next;
        }
    }
    printPath(queue, vertex);
    HeapDestroy(queue); // Freeing the memory allocated to the heap
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////// Utility Functions ////////////////////////////////////////////////
void printPath(MinHeap *h, int destination){ // Prints the path and distance from each vertex to the given destination
    int *parent = (int*)malloc(sizeof(int) * h->capacity);
    int *distance = (int*)malloc(sizeof(int) * h->capacity);
    for(int i = 0; i < h->capacity; i++){
        int j = h->heap[i].id;
        parent[j] = h->heap[i].predecessor;
        distance[j] = h->heap[i].distance;
    }
    for(int i = 0; i < h->capacity; i++){
        if(i == destination - 1) continue;
        printf("%d ", i+1);
        if(distance[i] == INT_MAX) printf("NO PATH\n");
        else{
            printf("%d ", i+1);
            int next = i;
            while((next = parent[next]) != destination - 1) printf("%d ", next + 1);
            printf("%d %d\n", destination, distance[i]);
        }
    }
    free(parent);
    free(distance);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////