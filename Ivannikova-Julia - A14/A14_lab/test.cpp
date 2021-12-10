#include "gtest/gtest.h"

extern "C" {
#include <stdlib.h>
#include "Header.h"
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



TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}



TEST(InitCase, SkiplistInitialisation) {
	Skiplist* list = SkiplistInit();
	ASSERT_TRUE(list != nullptr);
	ASSERT_TRUE(list->header != nullptr);
	ASSERT_TRUE(list->header->next != nullptr);
	ASSERT_TRUE(list->header->next[0] == list->header);
	EXPECT_TRUE(list->level == 1);
	EXPECT_TRUE(list->header->key == INT_MAX);
}



TEST(SearchCase, SkiplistSearchInEmptyList) {
	Skiplist* list;
	list = (Skiplist*)malloc(sizeof(Skiplist));
	Node* header = (Node*)malloc(sizeof(Node));
	list->header = header;
	header->key = INT_MAX;
	header->value = INT_MAX;
	header->next = (Node**)malloc(sizeof(Node*) * MAX_LEVEL);

	for (int i = 0; i < MAX_LEVEL; i++) {
		header->next[i] = NULL;
	}

	list->level = 1;

	Node* search_result = SkiplistSearch(list, 1);
	EXPECT_TRUE(search_result == nullptr);
}



TEST(SearchCase, SkiplistSearchInListWithOneElementInIt) {
	Skiplist* list = test_skip_list_creation();

	int key = 1;
	int value = 1;

	Node* update[MAX_LEVEL];
	Node* element = list->header;

	update[1] = element;
	element = element->next[1];

	update[2] = list->header;
	list->level = 2;

	element = (Node*)malloc(sizeof(Node));
	element->key = key;
	element->value = value;
	element->next = (Node**)malloc(sizeof(Node*) * 3);

	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;

	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;

	Node* search_result = SkiplistSearch(list, 1);
	ASSERT_TRUE(search_result != nullptr);
	EXPECT_TRUE(search_result->value == 1);
}



TEST(SearchCase, SkiplistSearchInListWithOneElementWithoutNeedValue) {
	Skiplist* list = test_skip_list_creation();

	int key = 1;
	int value = 1;

	Node* update[MAX_LEVEL];
	Node* element = list->header;

	update[1] = element;
	element = element->next[1];

	update[2] = list->header;
	list->level = 2;

	element = (Node*)malloc(sizeof(Node));
	element->key = key;
	element->value = value;
	element->next = (Node**)malloc(sizeof(Node*) * 3);

	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;

	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;

	Node* search_result = SkiplistSearch(list, 2);
	ASSERT_TRUE(search_result == nullptr);
}

TEST(DeleteCase, SkiplistDeleteElementFromEmptyList) {
	Skiplist* list = test_skip_list_creation();
	int res = SkiplistDelete(list, 1);
	ASSERT_TRUE(res == 1);
}



TEST(DeleteKeyCase, SkiplistDeleteElementFromNotEmptyListWithNeedValue) {
	Skiplist* list = test_skip_list_creation();

	int key = 1;
	int value = 1;

	Node* update[MAX_LEVEL];
	Node* element = list->header;

	update[1] = element;
	element = element->next[1];

	update[2] = list->header;
	list->level = 2;

	element = (Node*)malloc(sizeof(Node));
	element->key = key;
	element->value = value;
	element->next = (Node**)malloc(sizeof(Node*) * 3);

	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;

	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;

	int res = SkiplistDelete(list, 1);
	ASSERT_TRUE(res == 0);
}



TEST(DeleteKeyCase, SkiplistDeleteElementFromNotEmptyWithNotNeedValue) {
	Skiplist* list = test_skip_list_creation();

	int key = 1;
	int value = 1;

	Node* update[MAX_LEVEL];
	Node* element = list->header;

	update[1] = element;
	element = element->next[1];

	update[2] = list->header;
	list->level = 2;

	element = (Node*)malloc(sizeof(Node));
	element->key = key;
	element->value = value;
	element->next = (Node**)malloc(sizeof(Node*) * 3);

	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;

	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;

	int res = SkiplistDelete(list, 2);
	ASSERT_TRUE(res == 1);
}

TEST(DeleteListCase, DeleteNULLSkipList) {
	ASSERT_NO_FATAL_FAILURE(SkiplistFree(NULL));
}

TEST(DeleteListCase, DeleteEmptySkipList) {
	Skiplist* list = test_skip_list_creation();
	ASSERT_NO_FATAL_FAILURE(SkiplistFree(list));
}

TEST(DeleteListCase, DeleteNotEmptySkipList) {
	Skiplist* list = test_skip_list_creation();

	int key = 1;
	int value = 1;

	Node* update[MAX_LEVEL];
	Node* element = list->header;

	update[1] = element;
	element = element->next[1];

	update[2] = list->header;
	list->level = 2;

	element = (Node*)malloc(sizeof(Node));
	element->key = key;
	element->value = value;
	element->next = (Node**)malloc(sizeof(Node*) * 3);

	element->next[1] = update[1]->next[1];
	update[1]->next[1] = element;

	element->next[2] = update[2]->next[2];
	update[2]->next[2] = element;

	ASSERT_NO_FATAL_FAILURE(SkiplistFree(list));
}