/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA5
Description: Main client. Reads input file and displays the adjcency list representation, then preforms dfs to find SCC of the graph. All outputs are displayed outfile
File: FindComponents.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
	FILE *in, *out;
	int SIZE_GRAPH;
	int X, Y;
	// check for correct terminal inputs
	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL){
		printf("Unable to open file %s for reading", argv[1]);
		exit(1);
	}
	if(out == NULL){
		printf("Unable to open file %s for writing", argv[2]);
		exit(1);
	}
	// create a graph with the input data
	fscanf(in, "%d", &SIZE_GRAPH);
	Graph graph = newGraph(SIZE_GRAPH);
	
	while(fgetc(in) != EOF){
		fscanf(in, "%d %d", &X, &Y);
		if(X != 0 && Y != 0){
			addArc(graph, X, Y);
		}
		else{
			break;
		}
	}
	// print onto output file the adjacency list representation of G
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, graph);
	fprintf(out, "\n");
	// run DFS()
	// initialize order of DFS from increasing order
	List S = newList();
	for(int i = 1; i <= getOrder(graph);i++){
		append(S, i);
	}
	// run DFS in increasing order
	DFS(graph, S);
	// transpose the graph
	Graph graph_transpose = transpose(graph);
	// run DFS in decreasing finish time
	DFS(graph_transpose, S);
	// DFS now spans a forrest of connected components
	int counter = 0;
	// count the number of connected components(when parent is NIL) and display it
	moveFront(S);
	while(index(S) != -1){
		if(getParent(graph_transpose, get(S)) == NIL){
			counter++;
		}
		moveNext(S);
	}
	fprintf(out, "G contains %d strongly connected components:\n",counter);
	//display the connected components
	List* formatS = calloc(counter, sizeof(List));
	for(int i = 0; i < counter;i++){
		formatS[i] = newList();
	}
	moveFront(S);
	int ptr = counter - 1;
	while(index(S) != -1){
		if(getParent(graph_transpose, get(S)) == NIL){
			append(formatS[ptr], get(S));
			moveNext(S);
		}
		while(index(S) != -1 && getParent(graph_transpose, get(S)) != NIL){
			append(formatS[ptr], get(S));
			moveNext(S);
		}
		ptr--;
	}
	for(int i = 0; i < counter; i++){
		fprintf(out, "Component %d: ", i + 1);
		printList(out, formatS[i]);
		fprintf(out, "\n");
	}

	// free all allocated memory
	for(int i = 0; i < counter;i++){
		freeList(&formatS[i]);
	}
	fclose(in);
	fclose(out);	
	freeGraph(&graph_transpose);
	freeList(&S);
	freeGraph(&graph);
	return 0;
}
