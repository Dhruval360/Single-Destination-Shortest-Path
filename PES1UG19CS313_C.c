// This file contains the driver code that calls the Dijkstra function on the given input

#include "PES1UG19CS313_H.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int main(){
    char c; // Used for finding line feed or carriage return characters in the input
    int numVertices, source, destination, weight;
    scanf("%d", &numVertices);
    Graph *graph = GraphInit(numVertices); // Initialising a graph with the required number of vertices
    for(int i = 0; i < numVertices; i++){
        scanf("%d", &source);            
        while((c = getchar()) != '\n' && c != '\r' && c != EOF){
            scanf("%d %d", &destination, &weight);
            GraphAppend(graph, destination, source, weight); // Adding an edge from destination to source (opposite of what is given)
        }        
    }
    Dijkstra(*graph, numVertices); // Calling the Dijkstra function on the graph with destination being the last vertex in the graph
    GraphDestroy(graph); // Freeing the memory allocated for the graph
    return 0;
}