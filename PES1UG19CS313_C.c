/*
This file contains the driver code that calls the Dijkstra function on the given input
*/

#include "PES1UG19CS313_H.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int main(){
    int numVertices;
    scanf("%d", &numVertices);
    Graph *graph = GraphInit(numVertices);
    int source, destination, weight, temp1, temp2;
    for(int i = 0; i < numVertices; i++){
        scanf("%d", &source);            
        char c;
        while((c = getchar()) != '\n' && c != '\r'){
            scanf("%d %d", &temp1, &temp2);
            if(temp1 != destination){
                destination = temp1;
                weight = temp2;
                GraphAppend(graph, destination, source, weight); // Generating the reverse of the graph given
            }
            else break;
        }        
    }
    Dijkstra(*graph, numVertices); // Calling the Dijkstra function on the graph with destination being the last vertex in the graph
    GraphDestroy(graph); // Freeing the memory alotted to the graph
    return 0;
}