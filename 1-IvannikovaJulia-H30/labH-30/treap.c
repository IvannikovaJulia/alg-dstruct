#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	int value;
	struct node* l;
	struct node* r;
} node;

typedef struct nodePair
{
	struct node* r;
	struct node* l;
} nodePair;

node* Find(node* tree, int key)
{
	if (tree == NULL)
		return NULL;

	if (tree->key == key)
		return tree;

	if (tree->key > key)
	{
		node* newTree = Find(tree->l, key);
		return newTree;
	}
	else
	{
		node* newTree = Find(tree->r, key);
		return newTree;
	}
}

node* Merge(node* left, node* right)
{
	if (left == NULL)
		return right;

	if (right == NULL)
		return left;


	if (left->value > right->value)
	{
		left->r = Merge(left->r, right);
		return left;
	}
	else
	{
		right->l = Merge(left, right->l);
		return right;
	}
}

nodePair Split(node* tree, int key)
{
	if (tree == NULL)
	{
		nodePair nullTreap = { NULL, NULL };
		return nullTreap;
	}
	else if (key > tree->key)
	{
		nodePair tmpPair = Split(tree->r, key);
		tree->r = tmpPair.r;
		nodePair newTreap = { tree, tmpPair.l };
		return newTreap;
	}
	else
	{
		nodePair tmpPair = Split(tree->l, key);
		tree->l = tmpPair.l;
		nodePair newTreap = { tmpPair.r, tree };
		return newTreap;
	}
}

node* Add(node* tree, int key, int value)
{
	if (Find(tree, key) != NULL)
		return tree;


	node* newTree = (node*)malloc(sizeof(node));
	if (newTree == NULL)
	{
		printf("No memory allocated!");
		return 0;
	}

	if (newTree == NULL)
		return tree;


	newTree->key = key;
	newTree->value = value;
	newTree->r = NULL;
	newTree->l = NULL;

	nodePair newPair = Split(tree, key);
	newPair.r = Merge(newPair.r, newTree);

	return Merge(newPair.r, newPair.l);
}

node* Delete(node* tree, int key)
{
	if (Find(tree, key) == NULL)
		return tree;

	nodePair newPair = Split(tree, key);
	nodePair newTree = Split(newPair.l, key + 1);

	free(newTree.r);

	return Merge(newPair.r, newTree.l);
}

void Freee(node* tree)
{
	if (tree != NULL)
	{
		Freee(tree->l);
		Freee(tree->r);
		free(tree);
	}
	return;
}

int main(void)
{
	char command;
	int value;

	node* tree = NULL;

	while (fscanf(stdin, "%c %i", &command, &value) > 0)
	{
		switch (command)
		{
		case 'a':
			tree = Add(tree, value, rand());
			break;
		case 'r':
			tree = Delete(tree, value);
			break;
		case 'f':
			if (Find(tree, value))
				printf("yes\n");
			else
				printf("no\n");
			break;
		}
	}
	Freee(tree);
	return 0;
}