#include "header.h"

/* Dylan Bunch - created data structrues and their corresponding functions to work
				 with the algorithm's needs
   Ben Blanquart - created the mstPrims function and heapify with Byron
   Byron Hammann - created the heapify and mstPrims functions with Ben
*/

int main(void){
	
	//read in the file
	edge* initialEdgeList = openfile("input.txt");

	//print the resulting list
	printEdgeList(initialEdgeList);

	//translate that list into an array of vertices and prints them
	vertex* initialVertexArray = createVertexList(initialEdgeList);

	//converts the edge list into an edge array
	edge* edgeArray = convertToEdgeArray(initialEdgeList);
	
	//prints the edge array
	printEdgeArray(edgeArray);

	//add adjacent edges to the vertex list for more information
	addAdjacentEdges(initialVertexArray, edgeArray);

	//print the adjacency list (i.e. vertex array and its adjacency list pointer)
	printAdjacencies(initialVertexArray);

	//sort adjacencies by edge weight
	sortAdjacencies(initialVertexArray);

	//print sorted adjacencies
	printAdjacencies(initialVertexArray);

	//heap* heap = createMinHeap(initialVertexArray);

	//printMinHeap(heap);

	//visited* visitedArray = createVisitedArray(initialVertexArray);
	//printf("Created the thing\n");

	//printVisitedArray(visitedArray);


	int* minHeap = createHeap(initialVertexArray); 

	int* heapKeys = createKeyArray(initialVertexArray);

	int* onHeap = createOnHeapArray(initialVertexArray);

	mstPrims(minHeap, onHeap, heapKeys, initialVertexArray);

	printMSTWeight();
	printMinHeapifyCalls();

	return 0;
}

