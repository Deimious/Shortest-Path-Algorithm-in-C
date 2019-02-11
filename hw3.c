#include "header.h"

int minHeapifyCalls = 0;
int totalMSTWeight = 0;

//opens input.txt and reads through the edge list and puts into an array
edge* openfile(char* file){

	FILE* fptr = fopen(file, "r");

	if(fptr == NULL){
		printf("Error opening file %s. Exiting.\n",  file);
		exit(0);
	}

	vertex u, v;
	u.key = 0, v.key = 0;
	int w = 0;

	edge* head = NULL;

	while(!feof(fptr)){
		fscanf(fptr, "%d %d %d\n", &u.key, &v.key, &w);

		edge* temp  = malloc(sizeof(edge));
		temp->u.key = u.key;
		temp->v.key = v.key;
		temp->w = w;
		temp->next = NULL;

		if(head != NULL){
			temp->next = head;
			head = temp;
		}
		if(head == NULL)
			head = temp;
	}

	fclose(fptr);

	return head;
}

//prints the edge linked list
void printEdgeList(edge* head){

	printf("\nEdge List is as follows: \n");

	edge* cursor = head;

	while(cursor != NULL){
		printf("[%d]<---%d--->[%d]\n", cursor->u.key, cursor->w, cursor->v.key);
		cursor = cursor->next;
	}

	return;
}

//translates the edge linked list into a vertex array with size at vertexs[-1].key
vertex* createVertexList(edge* head){

	edge* cursor = head;
	int maxvertex = 0;
	int maxweight = 0;

	while(cursor != NULL){
		if(cursor->u.key > maxvertex)
			maxvertex = cursor->u.key;
		if(cursor->v.key > maxvertex)
			maxvertex = cursor->v.key;
		if(cursor->w >= maxweight)
			maxweight = cursor->w;
		cursor = cursor->next;
	}

	vertex* vertexes = malloc(sizeof(vertex) * (maxvertex + 2));
	vertexes[0].key = maxweight;
	vertexes++;
	vertexes[0].key = maxvertex;
	vertexes++;

	printf("\nVertex array is as follows:\n");
	for(int i = 0; i < maxvertex; i++){
		vertexes[i].key = i + 1;
		vertexes[i].adjacentEdges = NULL;
		printf("[%d]\n", vertexes[i].key);
	}
	printf("\n");

	return vertexes;
}

//converts the  edge list into an edge array with size stored at edgearray[-1].w
edge* convertToEdgeArray(edge* edgelist){

	edge* cursor = edgelist;
	int count = 0;
	while(cursor != NULL){
		count++;
		cursor = cursor->next;
	}

	edge* edgearray = malloc(sizeof(edge) * (count + 1));
	edgearray[0].w = count;
	edgearray++;

	count = 0;
	cursor = edgelist;
	while(cursor != NULL){
		edgearray[count] = *cursor;
		count++;
		cursor = cursor->next;
	}

	return edgearray;
}

//prints edge array
void printEdgeArray(edge* edgearray){

	printf("\nEdgeArray is as follows:\n");

	for(int i = 0; i < edgearray[-1].w; i++){
		//printf("%d %d %d\n", edgearray[i].u.key, edgearray[i].v.key, edgearray[i].w);
		printf("%d: [%d]---%d---[%d]\n", i, edgearray[i].u.key, edgearray[i].w, edgearray[i].v.key);
	}
}

//adds adjacent edges to the vertex list to form an adjacency list
void addAdjacentEdges(vertex* vertexList, edge* edgeArray){

	int index = 0;
	vertex temp;
	int weight = 0;

	//iterate through the dge array
	for(int i = 0; i < edgeArray[-1].w; i++){

		//look at left side and add right side to the left side's adjacency list
		index = edgeArray[i].u.key;
		temp = edgeArray[i].v;
		weight = edgeArray[i].w;
		vertexList = addAdjacentEdge(vertexList, (index - 1), temp, weight);

		//look at right side and add left side to the right side's adjacency list
		index = edgeArray[i].v.key;
		temp = edgeArray[i].u;
		weight = edgeArray[i].w;
		vertexList = addAdjacentEdge(vertexList, (index - 1), temp, weight);
	}
}

//helper function for above
vertex* addAdjacentEdge(vertex* vertexList, int index, vertex vert, int weight){

	adjacentEdge* mallocator = malloc(sizeof(adjacentEdge));
	mallocator->v = vert;
	mallocator->w = weight;

	mallocator->next = vertexList[index].adjacentEdges;
	vertexList[index].adjacentEdges = mallocator;

	return vertexList;
}

//prints the adjacency lists
void printAdjacencies(vertex* vertexList){

	adjacentEdge* cursor = NULL;

	printf("\nVertexes and edges are\n");
	for(int i = 0; i < vertexList[-1].key; i++){
		cursor = vertexList[i].adjacentEdges;
		printf("%d: ", vertexList[i].key);
		while(cursor != NULL){
			printf("(%d,%d)-> ", cursor->v.key, cursor->w);
			cursor = cursor->next;
		}
		printf("\n");
	}
}

//bubble sorts adjacent edges based on edge weight
void sortAdjacencies(vertex* vertexArray){
	int size = vertexArray[-1].key;
	int k;
	adjacentEdge *i, *j;

	int tempW;
	vertex tempV;
	adjacentEdge* cursor;

	for(k=0; k<size; k++){
		cursor = vertexArray[k].adjacentEdges;
		for(i=cursor; i->next != NULL; i=i->next){
			for(j=i->next; j != NULL; j=j->next){
				if(i->w > j->w){//swap
					tempW = i->w;
					tempV = i->v;
					i->w = j->w;
					i->v = j->v;
					j->w = tempW;
					j->v = tempV;
				}
			}
		}
	}
}

void printMinHeapifyCalls(void){

	printf("\nMin-Heapify Calls: %d\n", minHeapifyCalls);
}

void printMSTWeight(void){

	printf("\nTotal Weight of the MST: %d", totalMSTWeight);
}

//creates an array of size equal to the number of vertexes
heap* createMinHeap(vertex* vertexArray){

	int infinity = vertexArray[-2].key + 1;
	heap* heap = malloc(sizeof(heap) * (vertexArray[-1].key + 2));
	heap[0].key = vertexArray[-2].key;
	heap++;
	heap[0].key = vertexArray[-1].key;
	heap++;

	for(int i = 0; i < vertexArray[-1].key; i++){
		heap[i].parentKey = 0;
		heap[i].weight = infinity;
		heap[i].key = i+1;
		if(i == 0){
			heap[i].weight = 0;
		}
	}

	return heap;
}

void printMinHeap(heap* heap){

	printf("\nHeap Array is:\n");

	for(int i = 0; i < heap[-1].key; i++){
		printf("[%d, %d]\n", heap[i].key, heap[i].weight);
	}

	return;
}

visited* createVisitedArray(vertex* vertexArray){

	int size = vertexArray[-1].key;

	visited* visitedArray = malloc(sizeof(visited) * (vertexArray[-1].key + 1));

	printf("%d\n", size);

	//visitedArray[0].key = size;
	//visitedArray++;

	for(int i = 0; i < vertexArray[-1].key; i++){
		//visitedArray[i].key = i + 1;
		//visitedArray[i].inArray = true;
	}

	return visitedArray;
}

void printVisitedArray(visited* visitedArray){



	return;
}




//works to swap the values of 2 ints inside the pointers
// run of the mill swap 
void swap(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}




//creates an array of numbers with each index corresponding to a vertex number
//heap max weight is in heap[-2]
//heap size is in heap[-1]
int* createHeap(vertex* vertexArray){
	int maxWeight = vertexArray[-2].key;
	int size = vertexArray[-1].key;

	int* heap = malloc(sizeof(int)*(size+2));

	//hiding the maximum edge weight in the -2 index
	heap[0] = maxWeight;
	//hiding the heapsize in the -1 index
	heap[1] = size;
	heap+=2;

	for(int i=0; i<size; i++){
		heap[i] = i+1;
	}

	return heap;
}

//create an array of ints that contain the keys corresponding to the vertex number
//initializes them all to infinity
int* createKeyArray(vertex* vertexArray){

	int maxWeight = vertexArray[-2].key;
	int size = vertexArray[-1].key;
	int infinity = maxWeight + 1;

	int* keys = malloc(sizeof(int)*size);

	keys[0] = 0;

	for(int i=1; i<size; i++){
		keys[i] = infinity;
	}

	return keys;
}

//creates an array of numbers each with indices corresponding to a vertex number
//corresponds to which elements are  on the heap
int* createOnHeapArray(vertex* vertexArray){
	int size = vertexArray[-1].key;

	int* onHeap = malloc(sizeof(int)*size);

	for(int i=0; i<size; i++){
		onHeap[i] = i+1;
	}

	return onHeap;
}





//calls extractMin and heapify
void mstPrims(int* heap, int* onHeap, int* keyArray, vertex* vertexArray){

	printf("\n");

	int u;
	int* set = malloc((sizeof(int)*(heap[-1] +1)));

	//hiding posistion in set in -1 index
	set[0] = 0;
	set++;

	adjacentEdge* cursor;
	while(heap[-1] > 0){
		u = extractMin(heap, onHeap, keyArray);
		set[set[-1]] = u;
		set[-1]++;
		cursor = vertexArray[u-1].adjacentEdges;
		while(cursor != NULL){

			if(onHeap[(cursor->v.key)-1] > 0 && cursor->w < keyArray[(cursor->v.key)-1]){
				//decrease key
				printf("decreasing key\n");
				keyArray[(cursor->v.key)-1] = cursor->w;
				heapify(heap, keyArray, ((cursor->v.key)-1));

			}
			cursor = cursor->next;
		}
	}

	for(int i=0; i < set[-1]; i++){
		printf("%d \n", set[i]);
	}
}

//calls heapify
int extractMin(int* heap, int* onHeap, int* keyArray){

	//if, for some reason, the array is of size 0 or negative size, the program crashes
	if(heap[-1] < 1){
		printf("HEAP UNDERFLOW, exiting...\n");
		exit(1);
	}

	int min = heap[0];
	onHeap[min] = 0;

	//set the 0th element to the size minus 1
	heap[0] = heap[(heap[-1])-1];

	//decrease heapsize
	heap[-1]--;

	heapify(heap, keyArray, 0);

	return min;
} 

void heapify(int *heap, int* keyArray, int index){

	minHeapifyCalls++;

	int size = heap[-1];
	int smallest = index;

	if(index > size){
			printf("test\n");
			return;
	}

	if(left(index) <= size && keyArray[(heap[left(index)])-1] <= keyArray[heap[index]-1]){
		smallest = left(index);
		//printf("x\n");
	} 
	if(right(index) <= size && keyArray[heap[right(index)]-1] < keyArray[heap[index]-1] && keyArray[heap[index]] <= keyArray[heap[smallest]]){
		smallest = right(index);
		//printf("y\n");
	}
	if(smallest != index){
		//printf("z\n");
		swap(&heap[index], &heap[smallest]);
		heapify(heap, keyArray, smallest);
	}

	return;
}

