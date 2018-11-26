#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE -1
#define GRAY 0
#define BLACK 1

typedef struct GraphObj{
	List *adjList;
	int *color;
	int *distance;
	int *parent;
	int order;
	int size;
	int source;
}GraphObj;

/* Constructors - Destructors */
Graph newGraph(int n){ // returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
	Graph graph = malloc(sizeof(struct GraphObj));
	graph->adjList = calloc(n+1, sizeof(List));
	graph->color = calloc(n+1, sizeof(int));
	graph->distance = calloc(n+1, sizeof(int));
	graph->parent = calloc(n+1, sizeof(int));
	graph->order = n;
	graph->size = 0;
	graph->source = NIL;
	for(int i = 0; i <= n; i++){
		graph->adjList[i] = newList();
		graph->color[i] = WHITE;
		graph->distance[i] = INF;
		graph->parent[i] = NIL;
	}
	return (graph);
}

void freeGraph(Graph *pG){ // frees all dynamic memory associated with the Graph *pG, then sets *pG to NUL
	for(int i = 0; i <= (*pG)->order; i++){
		freeList(&(*pG)->adjList[i]));
	}
	free((*pG)->adjList);
	free((*pG)->color);
	free((*pG)->distance);
	free((*pG)->parent);
	free(*pG);
	*pG = NULL;	
}

/*Access functions*/
int getOrder(Graph G){ // returns corresponding field value
	if(G == NULL){
		fprintf(stderr, "getOrder() called on NULL graph reference");
		exit(1);
	}
	else{
		return (G->order);
	}
}

int getSize(Graph G){ // returns corresponding field value
	if(G == NULL){
		fprintf(stderr, "getSize() called on NULL graph reference");
		exit(1);
	}
	else{
		return (G->size);
	}
}

int getSource(Graph G){ // returns source vertex most recently used in BFS() or NIL if BFS() has not been called yet
	if(G == NULL){
		fprintf(stderr, "getSource() called on NULL graph reference");
		exit(1);
	}
	else{
		return (G->source);
	}
}

int getParent(Graph G, int u){ // Pre: 1<=u<=getOrder(G) returns parent of u
	if(G == NULL){
		fprintf(stderr, "getParent() called on NULL graph reference");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "getParent() called on vertex out of bounds");
		exit(1);
	}
	return G->parent[u];
}

int getDist(Graph G, int u){ // Pre: 1<=u<=getOrder(G) returns distance from most recent BFS source to u or INF if no path
	if(G == NULL){
		fprintf(stderr, "getDist() called on NULL graph reference");
		exit(1);
	}
	if(getSource(G) == NIL){
		return INF;
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "GetDist() arguments are out of bounds");
		exit(1);
	}
	return (G->distance[u]);
}

void getPath(List L, Graph G, int u){ // appends to the List L the vertices of a shortest path in G from source u, or appends to L the value NIL if no such path exist Pre: getSource(G) != NIL && 1<=u<=getOrder(G)
	if(G == NULL){
		fprintf(stderr, "getPath() called on NULL graph reference");
		exit(1);
	}
	if(getSource(G) == NIL){
		fprintf(stderr, "getPath() : getSource(): source not yet defined");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "getPath(): vertex out of bounds");
		exit(1);
	}
	if(u == getSource(G)){
		prepend(L, u);
	}
	else if(getParent(G, u) == NIL){
		append(L, NIL);
	}
	else{
		getPath(L, G, getParent(G, u));
		prepend(L, u);
	}
}

/*Manipulation procedures*/
void makeNull(Graph G){ // deletes all edges of G, restoring it to its original (no edge) state
	if(G == NULL){
		fprintf(stderr, "makeNull() called on NULL graph reference");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++){
		clear(G->adjList[i]);
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->order = 1;
	G->size = 0;
	G->source = NIL;
}

void addEdge(Graph G, int u, int v){ // inserts a new edge joining u to v (u is added to the adjacency List of v and v to the adjacency list of u)
	if(G == NULL){
		fprintf(stderr, "addEdge() called on NULL grapg reference");
		exit(1);
	}
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		fprintf(stderr, "addEdge() called on arguments out of bounds");
		exit(1);
	}
	addArc(G,u,v);
	addArc(G,v,u);
	G->size--;
}

void addArc(Graph G, int u, int v){ // inserts a new directed edge (v is added to the adjacency list of u, but not u to v)
	if(G == NULL){
		fprintf(stderr, "addArc() called on NULL graph reference");
		exit(1);
	}
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		fprintf(stderr, "addArc() called on arguments out of bounds");
		exit(1);
	}
	if(length(G->adjList[u]) == 0){
		append(G->adjList[u], v);
	}
	else{
		moveFront(G->adjList[u]);
		while(index(G->adjList[u]) != -1 && get(G->adjList[u]) < v){
			moveNext(G->adjList[u]);
		}
		if(index(G->adjList[u]) >= 0){
			insertBefore(G->adjList[u], v);
		}
		else{
			append(G->adjList[u], v);
		}
		G->size++;
	}
}

void BFS(Graph G, int s){ // runs BFS on G
	if(G == NULL){
		fprintf(stderr, "BFS() called on NULL graph reference");
		exit(1);
	}
	if(s < 1 || s > getOrder(G)){
		fprintf(stderr, "BFS() called on invalid source");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++){
		if(i != s){
			G->color[i] = WHITE;
			G->distance[i] = INF;
			G->parent[i] = NIL;
		}
	}
	int x;
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List queue = newList();
	append(queue, s);
	while(length(queue) != 0){
		moveFront(queue);
		x = get(queue);
		deleteFront(queue);
		for(int y = 0; y < length(G->adjList[x]); y++){
			if(G->color[y] == WHITE){
				G->color[y] = GRAY;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(queue, y);
			}
		}
		G->color[x] = BLACK;
	}
	//free(&queue);
}

/* Other operations */
void printGraph(FILE* out, Graph G){ // prints the adjacency list representation of G to the file pointed to by out
	if(out == NULL || G == NULL){
		fprintf(stderr, "printGraph() called on NULL reference parameters");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adjList[i]);
		fprintf(out, "\n");
	}
}

