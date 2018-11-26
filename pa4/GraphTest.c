#include <stdio.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(4); // creates a new Graph with 4 vertices

	/* Testing manipulation procedures */
	// adds 5 edges to the graph
	addEdge(G,1,2);
	addEdge(G,1,3);
	addEdge(G,2,4);
	addArc(G,2,3);
	addEdge(G,3,4);

	printGraph(stdout, G);

	BFS(G,1); // runs BFS on graph with source 1

	/*testing access functions */

	// getOrder()
	printf("int getOrder() test: \n");
	printf("%d",getOrder(G));

	// getSize()
	printf("int getSize() test: \n");
	printf("%d",getSize(G));

	// getSource()
	printf("int getSource() test: \n");
	printf("%d",getSource(G));

	// getParent()
	printf("int getParent(2) test: \n");
	printf("%d",getParent(G, 2));

	// getDist()
	printf("int getDist(3) test: \n");
	printf("%d",getDist(G, 3));

	//getPath()
	List L = newList();
	printf("void getPath(3) test: \n");
	getPath(L, G, 3);
	printList(stdout, L);


	// Test clear list
	printf("clearing List\n");
	makeNull(G);
	printGraph(stdout, G);


	return (0);
}
