#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>
#include "Header.h"



static void __SkiplistNodeFree(Node* node) {
	if (node != NULL) {
		if (node->next != NULL) {
			free(node->next);
		}
		free(node);
	}
}

Skiplist* SkiplistInit() {
	Skiplist* list = (Skiplist*)malloc(sizeof(Skiplist));
	if (list == NULL)
		return NULL;

	Node* header = (Node*)malloc(sizeof(Node));
	if (header == NULL) {
		free(list);

		return NULL;
	}

	list->header = header;
	header->key = INT_MAX;

	header->next = (Node**)malloc(sizeof(Node*) * MAX_LEVEL);
	if (header->next == NULL) {
		free(header);
		free(list);

		return NULL;
	}

	for (int i = 0; i < MAX_LEVEL; i++)
		header->next[i] = list->header;

	list->level = 1;

	return list;
}

Node* SkiplistSearch(Skiplist* list, int key) {
	if (list == NULL)
		return NULL;

	Node* element = list->header;

	for (int i = list->level; i >= 1; i--) {
		while (element->next[i] && element->next[i]->key < key) {
			element = element->next[i];
		}
	}

	if (element->next[1] && element->next[1]->key == key)
		return element->next[1];
	else
		return NULL;
}

int SkiplistDelete(Skiplist* list, int key) {
	int i;
	Node* update[MAX_LEVEL];
	Node* element = list->header;

	for (i = list->level; i >= 1; i--) {
		while (element->next[i]->key < key)
			element = element->next[i];

		update[i] = element;
	}

	element = element->next[1];

	if (element->key == key) {
		for (i = 1; i <= list->level; i++) {
			if (update[i]->next[i] != element)
				break;

			update[i]->next[i] = element->next[i];
		}

		__SkiplistNodeFree(element);

		while (list->level > 1 && list->header->next[list->level] == list->header)
			list->level--;

		return 0;
	}

	return 1;
}

int SkiplistInsert(Skiplist* list, int key, int value) {
	Node* update[MAX_LEVEL + 1];
	Node* element = list->header;
	int i, level;

	for (i = list->level; i >= 1; i--) {
		while (element->next[i]->key < key)
			element = element->next[i];
		update[i] = element;
	}

	element = element->next[1];

	if (key == element->key) {
		element->value = value;
		return 0;
	}
	else {
		level = rand() % MAX_LEVEL;

		if (level > list->level) {
			for (i = list->level + 1; i <= level; i++)
				update[i] = list->header;
			list->level = level;
		}

		element = (Node*)malloc(sizeof(Node));
		element->key = key;
		element->value = value;
		element->next = (Node**)malloc(sizeof(Node*) * (level + 1));

		for (i = 1; i <= level; i++) {
			element->next[i] = update[i]->next[i];
			update[i]->next[i] = element;
		}
	}

	return 0;
}


void SkiplistFree(Skiplist* list) {
	if (list == NULL)
		return;

	Node* current = list->header->next[1];

	while (current != list->header) {
		Node* forward = current->next[1];

		free(current->next);
		free(current);

		current = forward;
	}
	free(current->next);
	free(current);
	free(list);
}


void SkiplistPrint(Skiplist* list) {
	if (list == NULL) {
		printf("NULL\n");
		return;
	}

	Node* node = list->header;

	while (node && node->next[1] != list->header) {
		printf("%d[%d]->", node->next[1]->key, node->next[1]->value);
		node = node->next[1];
	}
}

Skiplist* test_skip_list_creation() {
	Skiplist* list;
	list = (Skiplist*)malloc(sizeof(Skiplist));
	Node* header = (Node*)malloc(sizeof(Node));
	list->header = header;
	header->key = INT_MAX;
	header->value = INT_MAX;
	header->next = (Node**)malloc(sizeof(Node*) * MAX_LEVEL);

	for (int i = 0; i < MAX_LEVEL; i++)
		header->next[i] = header;

	list->level = 1;
	return list;
}