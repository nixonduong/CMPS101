#define WHITE -1
#define GRAY -2
#define BLACK -3

struct GraphObj{
	List adjList*;
	int color*;
	int discoverTime*;
	int finishTime*;
	int parent*;
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
		graph->discoverTime = UNDEF;
		graph->finishTime = UNDEF;
		graph->parent = NIL;
	}	
	return graph;
}

void freeGraph(Graph* pG){ // frees all heap memory associated with pG and sets pG to NULL
	for(int i = 1; i <= getOrder(*pG); i++){
		freeList(&(*pG->adjList[i]));
	}
	free(*pG->color);
	free(*pG->discoverTime);
	free(*pG->finishTime);
	free(*pG->parent);
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
	if(index(G->adjList[u] == -1)){
		append(G->adjList[u], v)
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
	addArc(u, v);
	addArc(v, u);
	G->size--;
}




































