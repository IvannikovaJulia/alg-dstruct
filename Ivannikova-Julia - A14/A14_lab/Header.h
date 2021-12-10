#pragma once

#define MAX_LEVEL 5

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

typedef struct Node
{
	int key;
	int value;
	struct Node** next;
} Node;

typedef struct Skiplist
{
	int level;
	struct Node* header;
} Skiplist;

Skiplist* SkiplistInit();
Node* SkiplistSearch(Skiplist* list, int key);
int SkiplistDelete(Skiplist* list, int key);
int SkiplistInsert(Skiplist* list, int key, int value);
void SkiplistFree(Skiplist* list);
void SkiplistPrint(Skiplist * list); 
