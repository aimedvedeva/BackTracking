#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include "graph.h"

void PrintResult(int *path, int lenght, double result) {
	FILE *output = NULL;
	if ((output = fopen("output.txt", "w")) == NULL) {
		return 1;
	}

	int curLen = 0;
	for (int i = 0; i < lenght; i++) {
		fprintf(output, "%i ", path[i] + 1);
		curLen++;
	}

	if (lenght == 0) {
		fprintf(output, "%i ", 0);
	}

	fprintf(output, "\n%lf\n", result);
	fprintf(output, "%i ", curLen);
	fclose(output);
}

void ReadInfo(int *V, int *s, int *t, int *K, int **nodes) {
	FILE *input = NULL;
	if ((input = fopen("graph.txt", "r")) == NULL) {
		return 1;
	}

	fscanf(input, "%i", V);
	fscanf(input, "%i", s);
	fscanf(input, "%i", t);
	fscanf(input, "%i", K);


	int maxNumOfLinks = *V * (*V - 1) / 2;

	//записываем всевозможные пары узлов
	*nodes = (int*)malloc(sizeof(int) * maxNumOfLinks * 2);

	for (int i = 0; i < 2 * maxNumOfLinks; i++) {
		int result = fscanf(input, "%i", &((*nodes)[i]));
		if (result == -1) {
			(*nodes)[i] = 0;
		}
	}

	fclose(input);
}

int main(void) {
	//обозначения в терминах формулировки задачи
	int V, s, t, K;
	int *nodes;
	
	ReadInfo(&V, &s, &t, &K, &nodes);

	PrepareGraphSystem(V, nodes);
    free(nodes);

	int *path = NULL;
	int lenght;
	srand(time(NULL));
	__int64 start, end, tps;
	int num = rand();

	QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
	QueryPerformanceCounter((LARGE_INTEGER *)&start);
	
	path = SearchPathBackTrack(s, t, K, &lenght);
 
 
	QueryPerformanceCounter((LARGE_INTEGER *)&end);
    double result = ((double)(end - start)) / tps;

	
	PrintResult(path, lenght, result);
	
	DestroyGraphSystem();

	_CrtDumpMemoryLeaks();
}

