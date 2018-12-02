#include "List.h"
#include <stdio.h>
#define NIL -1
#define UNDEF -2
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

/*Exported type*/
typedef struct GraphObj* Graph;

/*Constructors-Deconstructors*/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*Access functions*/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*Manipulation functions*/
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void DFS(Graph G, List S);

/*Other functions*/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
