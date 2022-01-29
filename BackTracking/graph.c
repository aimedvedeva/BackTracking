#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "list.h"

/*   
What is needed to solve the problem:
	 --> adjacency list (need to know which edges surround a given node)
	 Implemented as: an array of pointers to the corresponding indexes (node ​​numbers) of adjacency lists

--> adjacency matrix (needed to mark edges we've already been on)
	 Implemented as: bitmap

--> set of nodes we have already visited (future result)
	 Implemented as: array with node numbers
*/

static int **AdjacencyMatrix;
static list **AdjacencyList;
static int V;

#define PATHLENGHT 1
static int *PassingNodes;
static int curPathLenght = 0;
static int End;
static int LowPathLimit;
myBool isSolved = false;

/*

This function is located in the graph.c file, since it characterizes the property of the graph (the path found with a certain condition inside it)

   The function will terminate as soon as it finds the first suitable simple path whose length is >= K;
   The result will be captured in the PassingNodes arr
*/
void SearchPathByBackTracking(int step, int node) {
	if (node == End && curPathLenght >= LowPathLimit) {
		isSolved = true;
		return;
	}

	list *iter = AdjacencyList[node]->Next;
	while (iter != NULL) {
		if (AdjacencyMatrix[iter->data][node] == 0) {

			AdjacencyMatrix[iter->data][node] = AdjacencyMatrix[node][iter->data] = 1;
			PassingNodes[step] = iter->data;
			curPathLenght += PATHLENGHT;

			if (iter->data == End && curPathLenght < LowPathLimit) {
				PassingNodes[step] = node;
				return;
			}
			SearchPathByBackTracking(step + 1, iter->data);
			if (isSolved) {                                                
				return;
			}
			AdjacencyMatrix[iter->data][node] = AdjacencyMatrix[node][iter->data] = 0;
			PassingNodes[node] = -1;
			curPathLenght -= PATHLENGHT;
		}
		iter = iter->Next;
	}
}

int *SearchPathBackTrack(int startPath, int endPath, int pathLenght, int *lenght /* out */) {
	End = endPath - 1;
	LowPathLimit = pathLenght;

	PassingNodes = (int*)malloc(sizeof(int) * V * V);
	memset(PassingNodes, -1, sizeof(int));

	PassingNodes[0] = startPath - 1;

	SearchPathByBackTracking(1, startPath - 1);
	*lenght = curPathLenght + 1;

	return PassingNodes;
}

void initGraphConstants(int num) {
	V = num;
}
void initAdjacencyList(int *mas) {
	AdjacencyList = (list**)malloc(sizeof(list*) * V);

	for (int i = 0; i < V; i++) {
		AdjacencyList[i] = (list*)malloc(sizeof(list));
		AdjacencyList[i]->Next = NULL;
		AdjacencyList[i]->data = 0;
	}

	for (int i = 0; i < V * (V - 1); i += 2) {
		if (mas[i] == 0) {
			break;
		}
		Add(AdjacencyList[mas[i] - 1], mas[i + 1] - 1);
		Add(AdjacencyList[mas[i + 1] - 1], mas[i] - 1);
	}
}
void initAdjacencyMatrix() {
	AdjacencyMatrix = (int**)malloc(sizeof(int*) * V);

	for (int i = 0; i < V; i++) {
		AdjacencyMatrix[i] = (int*)malloc(sizeof(int) * V);

		for (int j = 0; j < V; j++) {
			AdjacencyMatrix[i][j] = 0;
		}
	}
}

void PrepareGraphSystem(int num, int *mas) {
	initGraphConstants(num);
	initAdjacencyList(mas);
	initAdjacencyMatrix();
}

void destroyAdjacencyList() {
	for (int i = 0; i < V; i++) {
		DestroyList(AdjacencyList[i]);
	}
	free(AdjacencyList);
}
void destroyAdjacencyMatrix() {
	for (int i = 0; i < V; i++) {
		free(AdjacencyMatrix[i]);
	}
	free(AdjacencyMatrix);
}

void DestroyGraphSystem() {
	destroyAdjacencyList();
 	destroyAdjacencyMatrix();
	free(PassingNodes);
}

