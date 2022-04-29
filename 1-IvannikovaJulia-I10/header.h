#pragma once
typedef struct tree_t {
    int size;
    int key[3];
    struct tree_t* one;
    struct tree_t* two;
    struct tree_t* three;
    struct tree_t* four;
    struct tree_t* parent;

} tree_t;

char find(int value, int* key, int size);
void swap(int* x, int* y);
void sort2(int* x, int* y);
void sort3(int* x, int* y, int* z);
void sortKeys(int size, int* key);
tree_t* createNode(int value);
tree_t* createNode2(int value, tree_t* one, tree_t* two, tree_t* three, tree_t* four, tree_t* parent);
void addKeyToNode(int value, tree_t* treeNode);
void removeKeyFromNode(int value, tree_t* treeNode);
void become_Node2(int value, int* key, tree_t* treeNode, tree_t* one, tree_t* two);
char isLeaf(tree_t* tree);
tree_t* split(tree_t* item);
tree_t* addNode(tree_t* tree, int value);
tree_t* search(tree_t* tree, int value);
tree_t* findMin(tree_t* tree);
tree_t* merge(tree_t* leaf);
tree_t* redistribute(tree_t* leaf);
tree_t* fix(tree_t* leaf);
tree_t* removeNode(tree_t* tree, int value);
void destroyTree(tree_t* t);
void printTree(tree_t* tree);