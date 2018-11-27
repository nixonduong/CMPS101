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

#define MAX_LEN 160

int main(int argc, char* argv[]){
	FILE *in, *out;
	char line[MAX_LEN];
	char temp;
	char X,Y;
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

    if(fgets(&temp,MAX_LEN,in) != NULL){
    	SIZE_GRAPH = atoi(&temp);
    }
    Graph graph = newGraph(SIZE_GRAPH);
    while(fgets(line,MAX_LEN,in) != NULL){
    	X = line[0];
    	Y = line[2];
    	if(atoi(&X) != 0 && atoi(&Y) != 0){
    		addEdge(graph, atoi(&X), atoi(&Y));
    	}
    	else{
    		break;
    	}
    }

    printGraph(out,graph);
    List L = newList();
    while(fgets(line,MAX_LEN,in) != NULL){
    	X = line[0];
    	Y = line[2];
    	if(atoi(&X) != 0 && atoi(&Y) != 0){
    		BFS(graph, atoi(&X));
    		getPath(L, graph, atoi(&Y));
    		if(front(L) == NIL){
    			fprintf(out, "The distance from ",atoi(&X), " to ", atoi(&Y), " is infinity\n");
    			fprintf(out, "No ", atoi(&X), "-", atoi(&Y), " path exists");
    			fprintf(out, "\n");
    		}
    		else{
    			fprintf(out, "The distance from ",atoi(&X), " to ", atoi(&Y), " is ", length(L), "\n");
    			fprintf(out, "A shortest ", atoi(&X), "-", atoi(&Y), " path is: ");
    			printList(out, L);
    			fprintf(out, "\n");

    		}
    		clear(L);
    	}
    	else{
    		break;
    	}
    }
    //closes files
    fclose(in);
    fclose(out);
    freeList(&L);
    freeGraph(&graph);
}

