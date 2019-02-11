#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// defines where the "left" child node should be
#define left(x) (2*x)+1
//#define left(x) (2*x) 
// defines where the "right" chile node should be
#define right(x) (2*x)+2 
//#define right(x) (2*x)+1
// defines where to fine the parent of a given element
#define parent(x) (x-1)/2

typedef struct vertex{
	int key;
	struct adjacentEdge* adjacentEdges;
}vertex;

typedef struct edge{
	struct vertex u;
	struct vertex v;
	int w;
	struct edge* next;
}edge;

typedef struct adjacentEdge{
	vertex v;
	int w;
	struct adjacentEdge* next;
}adjacentEdge;

typedef struct heapStruct{
	int parentKey;
	int weight;
	int key;
}heap;

typedef struct visited{
	int key;
	bool inArray;
}visited;

edge* openfile(char*);
void printEdgeList(edge*);
vertex* createVertexList(edge*);
edge* convertToEdgeArray(edge*);
void printEdgeArray(edge*);
void addAdjacentEdges(vertex*,edge*);
vertex* addAdjacentEdge(vertex*,int,vertex,int);
void printAdjacencies(vertex*);
void sortAdjacencies(vertex*);
heap* createMinHeap(vertex*);
void printMinHeap(heap*);
void printMSTWeight(void);
void printMinHeapifyCalls(void);
visited* createVisitedArray(vertex*);
void printVisitedArray(visited*);

int* createHeap(vertex*);
int* createKeyArray(vertex*);
int* createOnHeapArray(vertex*);
int extractMin(int*, int*, int* );
void heapify(int*, int*, int);
void swap(int*, int*);
void mstPrims(int*, int*, int*, vertex*);

