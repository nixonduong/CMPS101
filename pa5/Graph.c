#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#define WHITE -1
#define GRAY 0
#define BLACK 1

void visit(Graph, int, int*, List);

struct GraphObj{
	List* adjList;
	int* color;
	int* discoverTime;
	int* finishTime;
	int* parent;
	int order; // number of vertices
	int size; // number of edges
}GraphObj;

/*Constructor-Deconstructor*/
Graph newGraph(int n){ // returns reference to a new graph with n vertices and 0 edges
	Graph graph = malloc(sizeof(GraphObj));
	graph->adjList = calloc(n+1, sizeof(List));
	graph->color = calloc(n+1, sizeof(int));
	graph->discoverTime = calloc(n+1, sizeof(int));
	graph->finishTime = calloc(n+1, sizeof(int));
	graph->parent = calloc(n+1, sizeof(int));
	graph->order = n;
	graph->size = 0;
	for(int i = 1; i <= n; i++){
		graph->adjList[i] = newList();
		graph->color[i] = WHITE;
		graph->discoverTime[i] = UNDEF;
		graph->finishTime[i] = UNDEF;
		graph->parent[i] = NIL;
	}	
	return graph;
}

void freeGraph(Graph* pG){ // frees all heap memory associated with pG and sets pG to NULL
	for(int i = 1; i <= getOrder(*pG); i++){
		freeList(&((*pG)->adjList[i]));
	}
	free((*pG)->color);
	free((*pG)->discoverTime);
	free((*pG)->finishTime);
	free((*pG)->parent);
	free(*pG);
	*pG = NULL;
}

/*Access functions*/
int getOrder(Graph G){ // returns order of G
	if(G == NULL){
		fprintf(stderr, "getOrder() called on a NULL reference to graph");
		exit(1);
	}
	return G->order;
}

int getSize(Graph G){ // returns size of G
	if(G == NULL){
		fprintf(stderr, "getSize() called on a NULL reference to graph");
		exit(1);
	}
	return G->size;
}

int getParent(Graph G, int u){ // returns parent of vertex u
	if(G == NULL){
		fprintf(stderr, "getParent() called on a NULL reference to graph");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "getParent() called on a vertex out of bounds");
		exit(1);
	}
	return G->parent[u];
}

int getDiscover(Graph G, int u){ // returns discover time of vertex u
	if(G == NULL){
		fprintf(stderr, "getDiscover() called on a NULL reference to graph");
		exit(1);	
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "getDiscover() called on a vertex out of bounds");
		exit(1);
	}
	return G->discoverTime[u];
}

int getFinish(Graph G, int u){ // returns finish time of vertex u
	if(G == NULL){
		fprintf(stderr, "getFinish() called on a NULL reference to graph");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "getFinish() called on a vertex out of bounds");
		exit(1);
	}
	return G->finishTime[u];
}

/* Manipulation procedures */
void addArc(Graph G, int u, int v){ // adds an arc between vertex u and vertex v
	if(G == NULL){
		fprintf(stderr, "addArc() called on a NULL reference to graph");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "addArc() called on vertex A out of bounds");
		exit(1);
	}
	if(v < 1 || v > getOrder(G)){
		fprintf(stderr, "addArc() called on vertex B out of bounds");
		exit(1);
	}
	moveFront(G->adjList[u]);
	while(index(G->adjList[u]) > 0 && v < get(G->adjList[u])){
		moveNext(G->adjList[u]);
	}
	if(index(G->adjList[u]) == -1){
		append(G->adjList[u], v);
	}
	else{
		insertBefore(G->adjList[u], v);
	}
	G->size++;
}

void addEdge(Graph G, int u, int v){ // adds an edge between vertex u and vertex v
	if(G == NULL){
		fprintf(stderr, "addEdge() called on a NULL reference to graph");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "addEdge() called on vertex A out of bounds");
		exit(1);
	}
	if(v < 1 || v > getOrder(G)){
		fprintf(stderr, "addEdge() called on vertex B out of bounds");
		exit(1);
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}

void DFS(Graph G, List S){
	if(G == NULL){
		fprintf(stderr, "DFS() called on a NULL reference to graph");
		exit(1);
	}
// (i) length(S) == n
	if(length(S) != getOrder(G)){
		fprintf(stderr, "DFS() called on incorrect List");
		exit(1);
	}
/*
// (ii) S contains some permutation of the integers {1,2,3,...,n}
	int checker[getOrder(G) + 1];
	for(int i = 1;i <= getOrder(G); i++){
		checker[i] = 0;
	}
	moveFront(S);
	while(index(S) > 0){
		checker[get(S)] = 1;
		moveNext(S);
	}
	for(int i = 1;i <= getOrder(G); i++){
		if(checker[i] == 0){
			fprintf(stderr, "DFS() called on a list with no permutation of integers {1,2,3,...,n}");
			exit(1);
			break;
		}
	}
// DFS()
*/
	for(int x = 1; x <= getOrder(G); x++){
		G->color[x] = WHITE;
		G->parent[x] = NIL;
	}
	int time = 0;
	for(int i = 0; i < length(S); i++){
		moveBack(S);
		prepend(S, get(S));
		deleteBack(S);
	}
	for(int j = 0; j < length(S); j++){
		moveBack(S);
		if(G->color[get(S)] == WHITE){
			visit(G, get(S), &time, S);
		}
		deleteBack(S);
	}	
}
/*Helper function of DFS() */
void visit(Graph G, int x, int* time, List S){
	G->color[x] = GRAY;
	G->discoverTime[x] = ++(*time);
	for(int y = 0; y < length(G->adjList[x]); y++){
		if(G->color[y] == WHITE){
			G->parent[y] = x;
			visit(G, y, time, S);
		}
	}
	G->color[x] = BLACK;
	G->finishTime[x] = ++(*time);
	prepend(S, x);
}

/*Other functions */
Graph transpose(Graph G){ // returns a reference to a new graph obj representing the transpose 
	if(G == NULL){
		fprintf(stderr, "transpose() called on NULL graph reference");
		exit(1);	
	}
	Graph transpose = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		moveFront(G->adjList[i]);
		while(index(G->adjList[i]) > 0){
			addArc(transpose, get(G->adjList[i]), i);
			moveNext(G->adjList[i]);
		}
	}
	return transpose;
}

Graph copyGraph(Graph G){ // returns a reference to a new graph obj representing a copy of G
	if(G == NULL){
		fprintf(stderr, "copyGraph() called on a NULL graph reference");
		exit(1);
	}
	Graph copy = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		moveFront(G->adjList[i]);
		while(index(G->adjList[i]) > 0){
			append(copy->adjList[i], get(G->adjList[i]));
			moveNext(G->adjList[i]);
		}
	}
	return copy;
}

void printGraph(FILE* out, Graph G){
	if(G == NULL){
		fprintf(stderr, "printGraph() called on a NULL graph reference");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adjList[i]);
		fprintf(out, "\n");
	}
}

































