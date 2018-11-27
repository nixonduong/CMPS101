/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA4
Description: Reads in input file of graph data and outputs an adjacency list representation of the graph and pathways from source to given vertex
File: FindPath.c
Clients: none
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"
#define MAX_LEN 160

int main(int argc, char* argv[]){
	FILE *in, *out;
	int X,Y;
	int SIZE_GRAPH;
	// check command line for correct number of arguments
	if(argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if(in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

   	fscanf(in, "%d", &SIZE_GRAPH);
    Graph graph = newGraph(SIZE_GRAPH);
    while(fgetc(in) != EOF){
    	fscanf(in, "%d %d", &X, &Y);
    	if(X != 0 && Y != 0){
    		addEdge(graph, X, Y);
    	}
    	else{
    		break;
    	}
    }
    printGraph(out,graph);
	fprintf(out, "\n");
    while(fgetc(in) != EOF){
    	fscanf(in, "%d %d", &X, &Y);
    	if(X != 0 && Y != 0){
    		BFS(graph, X);
    		if(getDist(graph, Y) == INF){
    			fprintf(out, "The distance from %d to %d is infinity\n", X, Y);
    			fprintf(out, "No %d-%d path exists", X, Y);
    			fprintf(out, "\n");
    		}
    		else{
				List L = newList();
				getPath(L, graph, Y);
    			fprintf(out, "The distance from %d to %d is %d\n", X, Y, length(L) - 1);
    			fprintf(out, "A shortest %d-%d path is: ", X, Y);
    			printList(out, L);
    			fprintf(out, "\n");
				freeList(&L);
    		}
    	}
    	else{
    		break;
    	}
    }
    //closes files
    fclose(in);
    fclose(out);
    freeGraph(&graph);
}

