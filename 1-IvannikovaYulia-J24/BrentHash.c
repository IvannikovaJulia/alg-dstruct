#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define True 1
#define False (!True)

#define INITIAL_MAP_SIZE 10091 //first prime after 100000

typedef struct {
	char* data;
	char isFilled;
}mapData;

typedef struct {
	mapData* elements;
	int size;
}hashMap;

hashMap* hashMapInit(hashMap* map);

int BrentHash(hashMap* hashMap, char* data);

int findData(hashMap* hashMap, char* data);

void removeData(hashMap* hashMap, char* data);

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "BrentHash.h"

int main() {

	hashMap* hashMap = NULL;
	hashMap = hashMapInit(hashMap);
	char command = 0;
	char value[50] = { '\0' };
	while (scanf("%c", &command) >= 1) {

		getchar();
		fgets(value, sizeof(value), stdin);

		switch (command) {
		case 'a':
			BrentHash(hashMap, value);
			break;
		case 'r':
			removeData(hashMap, value);
			break;
		case 'f':
			if (findData(hashMap, value) == -1)
				puts("no");
			else
				puts("yes");
			break;
		}
	}
}

#include "BrentHash.h"


hashMap* hashMapInit(hashMap* map) {

	if (map != NULL)
		return NULL;

	map = (hashMap*)malloc(sizeof(hashMap));
	if (map == NULL)
		return NULL;

	map->size = INITIAL_MAP_SIZE;

	mapData* tempElements = (mapData*)malloc(INITIAL_MAP_SIZE * sizeof(mapData));
	if (tempElements == NULL)
		return NULL;

	map->elements = tempElements;

	for (int i = 0; i < INITIAL_MAP_SIZE; i++) {
		map->elements[i].data = (char*)malloc(50);
		map->elements[i].isFilled = False;
	}

	return map;
}

int BrentHash(hashMap* hashMap, char* data) {

	int start = hashStart(hashMap->size, data);
	int step = hashStep(hashMap->size, data);
	int prevPos = start;

	for (int N = 0; N < hashMap->size; N++) {
		for (int i = N; i >= 0; i--) {
			int newPos = (start + i * step) % hashMap->size;

			if (!hashMap->elements[newPos].isFilled) {
				strcpy(hashMap->elements[newPos].data, data);
				hashMap->elements[newPos].isFilled = True;
				return 1;
			}

			if (FreePosForNMoves(hashMap, prevPos, i)) {
				strcpy(hashMap->elements[prevPos].data, data);
				hashMap->elements[prevPos].isFilled = True;
				return 1;
			}

			prevPos = newPos;
		}
	}

	return 0;
}

int FreePosForNMoves(hashMap* hashMap, int pos, int N) {

	if (N == 0)
		return 0;

	int step = hashStep(hashMap->size, hashMap->elements[pos].data);
	int prevPos = pos;

	for (int i = 1; i <= N; i++) {
		int newPos = (pos + i * step) % hashMap->size;

		if (!hashMap->elements[newPos].isFilled) {
			strcpy(hashMap->elements[newPos].data, hashMap->elements[pos].data);
			hashMap->elements[pos].data = NULL;
			hashMap->elements[newPos].isFilled = True;
			hashMap->elements[pos].isFilled = False;
			return 1;
		}

		if (FreePosForNMoves(hashMap, prevPos, N - i)) {
			strcpy(hashMap->elements[prevPos].data, hashMap->elements[pos].data);
			hashMap->elements[pos].data = NULL;
			hashMap->elements[prevPos].isFilled = True;
			hashMap->elements[pos].isFilled = False;
			return 1;
		}

		prevPos = newPos;
	}

	return 0;
}

int hashStart(int size, char* data) {
	int number = 0;
	for (int i = 0; i < strlen(data); i++) {
		number += data[i];
	}
	return number % size;
}

int hashStep(int size, char* data) {
	int number = 0;
	for (int i = 0; i < strlen(data); i++) {
		number += data[i];
	}
	return (number / size) % size;
}

int findData(hashMap* hashMap, char* data) {

	for (int i = 0; i < hashMap->size; i++) {
		if (strcmp(hashMap->elements[i].data, data) == 0)
			if (hashMap->elements[i].isFilled)
				return i;
	}

	return -1;
}

void removeData(hashMap* hashMap, char* data) {

	int pos = findData(hashMap, data);

	if (pos != -1) {
		hashMap->elements[pos].isFilled = False;
	}
}