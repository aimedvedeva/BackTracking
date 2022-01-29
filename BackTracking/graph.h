#pragma once
typedef enum {
	false,
	true,
}myBool;

void PrepareGraphSystem(int num, int *mas);
void DestroyGraphSystem();

int *SearchPathBackTrack(int startPath, int endPath, int pathLenght, int *lenght /* out */);
