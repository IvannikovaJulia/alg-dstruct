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