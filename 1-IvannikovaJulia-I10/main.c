#include <stdio.h>
#include <stdlib.h>
//#include "header.h"
#pragma warning(disable : 4996)

typedef struct tree_t {
    int size;
    int key[3];
    struct tree_t* one;
    struct tree_t* two;
    struct tree_t* three;
    struct tree_t* four;
    struct tree_t* parent;

} tree_t;


tree_t* createNode(int value)
{
    tree_t* newNode = (tree_t*)malloc(sizeof(tree_t));
    if (newNode)
    {
        newNode->one = NULL;
        newNode->two = NULL;
        newNode->three = NULL;
        newNode->four = NULL;
        newNode->parent = NULL;
        newNode->key[0] = value;
        newNode->size = 1;
        return newNode;
    }

    return NULL;
}

tree_t* createNode2(int value, tree_t* one, tree_t* two, tree_t* three, tree_t* four, tree_t* parent)
{
    tree_t* newNode = (tree_t*)malloc(sizeof(tree_t));
    if (newNode)
    {
        newNode->one = one;
        newNode->two = two;
        newNode->three = three;
        newNode->four = four;
        newNode->parent = parent;
        newNode->key[0] = value;
        newNode->size = 1;
        return newNode;
    }

    return NULL;
}

int find(int value, int* key, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (key[i] == value)
            return 1;
    }

    return 0;
}

tree_t* search(tree_t* tree, int value)
{
    if (tree == NULL)
        return NULL;

    if (find(value, tree->key, tree->size))
        return tree;
    else if (value < tree->key[0])
        return search(tree->one, value);
    else if ((tree->size == 2) && (value < tree->key[1]) || (tree->size == 1))
        return search(tree->two, value);
    else if (tree->size == 2)
        return search(tree->three, value);
}




void swap(int* x, int* y)
{
    int r = (*x);
    (*x) = (*y);
    (*y) = r;
}

void sort2(int* x, int* y)
{
    if (*x > * y)
        swap(x, y);
}

void sort3(int* x, int* y, int* z)
{
    if (*x > * y)
        swap(x, y);

    if (*x > * z)
        swap(x, z);

    if (*y > * z)
        swap(y, z);
}

void sortKeys(int size, int* key)
{
    if (size == 1)
        return;

    if (size == 2)
        sort2(&key[0], &key[1]);

    if (size == 3)
        sort3(&key[0], &key[1], &key[2]);
}

void addKey(int value, tree_t* treeNode)
{
    if (treeNode == NULL)
        return;

    treeNode->key[treeNode->size] = value;
    treeNode->size++;
    sortKeys(treeNode->size, treeNode->key);
}

void removeKey(int value, tree_t* treeNode)
{
    if (treeNode == NULL)
        return;

    if (treeNode->size >= 1 && treeNode->key[0] == value)
    {
        treeNode->key[0] = treeNode->key[1];
        treeNode->key[1] = treeNode->key[2];
        treeNode->size--;
    }
    else if (treeNode->size == 2 && treeNode->key[1] == value)
    {
        treeNode->key[1] = treeNode->key[2];
        treeNode->size--;
    }
}

void become_Node2(int value, int* key, tree_t* treeNode, tree_t* one, tree_t* two)
{
    key[0] = value;
    treeNode->one = one;
    treeNode->two = two;
    treeNode->three = NULL;
    treeNode->four = NULL;
    treeNode->parent = NULL;
    treeNode->size = 1;
}

char isLeaf(tree_t* tree)
{
    if (tree == NULL)
        return 0;

    if ((tree->one == NULL) && (tree->two == NULL) && (tree->three == NULL))
        return 1;

    return 0;
}

tree_t* split(tree_t* item)
{
    if (item == NULL)
        return NULL;

    if (item->size < 3)
        return item;

    tree_t* x = createNode2(item->key[0], item->one, item->two, NULL, NULL, item->parent);
    tree_t* y = createNode2(item->key[2], item->three, item->four, NULL, NULL, item->parent);

    if (x->one)
        x->one->parent = x;

    if (x->two) {
        x->two->parent = x;
    }

    if (y->one)
        y->one->parent = y;

    if (y->two)
        y->two->parent = y;

    if (item->parent != NULL)
    {
        addKey(item->key[1], item->parent);

        if (item->parent->one == item)
            item->parent->one = NULL;
        else if (item->parent->two == item)
            item->parent->two = NULL;
        else if (item->parent->three == item)
            item->parent->three = NULL;

        if (item->parent->one == NULL)
        {
            item->parent->four = item->parent->three;
            item->parent->three = item->parent->two;
            item->parent->two = y;
            item->parent->one = x;
        }
        else if (item->parent->two == NULL)
        {
            item->parent->four = item->parent->three;
            item->parent->three = y;
            item->parent->two = x;
        }
        else
        {
            item->parent->four = y;
            item->parent->three = x;
        }

        tree_t* tmp = item->parent;
        free(item);
        return tmp;
    }
    else
    {
        x->parent = item;
        y->parent = item;
        become_Node2(item->key[1], item->key, item, x, y);
        return item;
    }
}

tree_t* addNode(tree_t* tree, int value)
{
    if (tree == NULL)
        return createNode(value);

    if (search(tree, value))
        return split(tree);

    if (isLeaf(tree))
        addKey(value, tree);
    else if (value <= tree->key[0])
        addNode(tree->one, value);
    else if ((tree->size == 1) || ((tree->size == 2) && value <= tree->key[1]))
        addNode(tree->two, value);
    else
        addNode(tree->three, value);

    return split(tree);
}

tree_t* findMin(tree_t* tree)
{
    if (tree == NULL)
        return tree;

    if ((tree->one) == NULL)
        return tree;
    else
        return findMin(tree->one);
}

tree_t* redistribute(tree_t* node)
{
    if (node == NULL)
        return NULL;

    tree_t* parent = node->parent;
    tree_t* first = parent->one;
    tree_t* second = parent->two;
    tree_t* third = parent->three;


    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2))
    {
        if (first == node)
        {
            parent->one = parent->two;
            parent->two = parent->three;
            parent->three = NULL;
            addKey(parent->key[0], parent->one);
            parent->one->three = parent->one->two;
            parent->one->two = parent->one->one;

            if (node->one != NULL)
                parent->one->one = node->one;
            else if (node->two != NULL)
                parent->one->one = node->two;

            if (parent->one->one != NULL)
                parent->one->one->parent = parent->one;

            removeKey(parent->key[0], parent);
        }
        else if (second == node)
        {
            addKey(parent->key[0], first);
            removeKey(parent->key[0], parent);
            if (node->one != NULL)
                first->three = node->one;
            else if (node->two != NULL)
                first->three = node->two;

            if (first->three != NULL)
                first->three->parent = first;

            parent->two = parent->three;
            parent->three = NULL;

            free(second);
        }
        else if (third == node)
        {
            addKey(parent->key[1], second);
            parent->three = NULL;
            removeKey(parent->key[1], parent);
            if (node->one != NULL)
                second->three = node->one;
            else if (node->two != NULL)
                second->three = node->two;

            if (second->three != NULL)
                second->three->parent = second;

            free(third);
        }
    }
    else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2)))
    {
        if (third == node)
        {
            if (node->one != NULL)
            {
                node->two = node->one;
                node->one = NULL;
            }

            addKey(parent->key[1], node);
            if (second->size == 2)
            {
                parent->key[1] = second->key[1];
                removeKey(second->key[1], second);
                node->one = second->three;
                second->three = NULL;

                if (node->one != NULL)
                    node->one->parent = node;

            }
            else if (first->size == 2)
            {
                parent->key[1] = second->key[0];
                node->one = second->two;
                second->two = second->one;
                if (node->one != NULL)
                    node->one->parent = node;

                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];
                removeKey(first->key[1], first);
                second->one = first->three;
                if (second->one != NULL)
                    second->one->parent = second;

                first->three = NULL;
            }
        }
        else if (second == node)
        {
            if (third->size == 2)
            {
                if (node->one == NULL)
                {
                    node->one = node->two;
                    node->two = NULL;
                }

                addKey(parent->key[1], second);
                parent->key[1] = third->key[0];
                removeKey(third->key[0], third);
                second->two = third->one;
                if (second->two != NULL)
                    second->two->parent = second;

                third->one = third->two;
                third->two = third->three;
                third->three = NULL;
            }
            else if (first->size == 2)
            {
                if (node->two == NULL)
                {
                    node->two = node->one;
                    node->one = NULL;
                }
                addKey(parent->key[0], second);
                parent->key[0] = first->key[1];
                removeKey(first->key[1], first);
                second->one = first->three;
                if (second->one != NULL)
                    second->one->parent = second;

                first->three = NULL;
            }
        }
        else if (first == node)
        {
            if (node->one == NULL)
            {
                node->one = node->two;
                node->two = NULL;
            }
            addKey(parent->key[0], first);
            if (second->size == 2)
            {
                parent->key[0] = second->key[0];
                removeKey(second->key[0], second);
                first->two = second->one;
                if (first->two != NULL)
                    first->two->parent = first;

                second->one = second->two;
                second->two = second->three;
                second->three = NULL;
            }
            else if (third->size == 2)
            {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];
                removeKey(third->key[0], third);
                first->two = second->one;
                if (first->two != NULL)
                    first->two->parent = first;

                second->one = second->two;
                second->two = third->one;
                if (second->two != NULL)
                    second->two->parent = second;

                third->one = third->two;
                third->two = third->three;
                third->three = NULL;
            }
        }
    }
    else if (parent->size == 1)
    {
        addKey(parent->key[0], node);

        if (first == node && second->size == 2)
        {
            parent->key[0] = second->key[0];
            removeKey(second->key[0], second);

            if (node->one == NULL)
                node->one = node->two;

            node->two = second->one;
            second->one = second->two;
            second->two = second->three;
            second->three = NULL;
            if (node->two != NULL)
                node->two->parent = node;
        }
        else if (second == node && first->size == 2)
        {
            parent->key[0] = first->key[1];
            removeKey(first->key[1], first);

            if (node->two == NULL)
                node->two = node->one;

            node->one = first->three;
            first->three = NULL;

            if (node->one != NULL)
                node->one->parent = node;
        }
    }
    return parent;
}

tree_t* merge(tree_t* node)
{
    if (node == NULL)
        return NULL;

    tree_t* parent = node->parent;

    if (parent->one == node)
    {
        addKey(parent->key[0], parent->two);
        parent->two->three = parent->two->two;
        parent->two->two = parent->two->one;

        if (node->one != NULL)
            parent->two->one = node->one;
        else if (node->two != NULL)
            parent->two->one = node->two;

        if (parent->two->one != NULL)
            parent->two->one->parent = parent->two;

        removeKey(parent->key[0], parent);
        free(parent->one);
        parent->one = NULL;
    }
    else if (parent->two == node)
    {
        addKey(parent->key[0], parent->one);

        if (node->one != NULL)
            parent->one->three = node->one;
        else if (node->two != NULL)
            parent->one->three = node->two;

        if (parent->one->three != NULL)
            parent->one->three->parent = parent->one;

        removeKey(parent->key[0], parent);
        free(parent->two);
        parent->two = NULL;
    }

    if (parent->parent == NULL)
    {
        tree_t* tmp = NULL;
        if (parent->one != NULL)
            tmp = parent->one;
        else
            tmp = parent->two;

        tmp->parent = NULL;
        free(parent);
        return tmp;
    }
    return parent;
}


tree_t* fix(tree_t* node)
{
    if (node == NULL)
        return NULL;

    if (node->size == 0 && node->parent == NULL)
    {
        free(node);
        return NULL;
    }

    if (node->size != 0)
    {
        if (node->parent)
            return fix(node->parent);
        else
            return node;
    }

    tree_t* parent = node->parent;
    if (parent->one->size == 2 || parent->two->size == 2 || parent->size == 2)
        node = redistribute(node);
    else if (parent->size == 2 && parent->three->size == 2)
        node = redistribute(node);
    else
        node = merge(node);

    return fix(node);
}
tree_t* removeNode(tree_t* tree, int value)
{
    if (tree == NULL)
        return NULL;

    tree_t* item = search(tree, value);

    if (item == NULL)
        return tree;

    tree_t* min = NULL;

    if (item->key[0] == value)
        min = findMin(item->two);
    else
        min = findMin(item->three);

    if (min != NULL)
    {
        int* z = (value == item->key[0] ? &(item->key[0]) : &(item->key[1]));
        swap(z, &min->key[0]);
        item = min;
    }

    removeKey(value, item);
    return fix(item);
}

void printTree(tree_t* tree)
{
    if (tree == NULL)
        return;

    printTree(tree->one);
    for (int i = 0; i < tree->size; i++)
        fprintf(stderr, "%d ", tree->key[i]);
    printTree(tree->two);
    printTree(tree->three);
}

void destroyTree(tree_t* tree)
{
    if (tree == NULL)
        return;

    destroyTree(tree->one);
    destroyTree(tree->two);
    destroyTree(tree->three);
    free(tree);
}


int main(void)
{
    char value;
    tree_t* prior = NULL;
    int key = 0;
    while (scanf("%c", &value) >= 1)
    {
        if (value != 'p' && value != 'q')
            scanf("%i", &key);

        switch (value)
        {
        case 'a':
            prior = addNode(prior, key);
            break;
        case 'r':
            prior = removeNode(prior, key);
            break;
        case 'f':
            if (search(prior, key))
                puts("yes");
            else
                puts("no");


            break;
        case 'p':
            printTree(prior);
            putchar('\n');
            break;
        case 'q':
            destroyTree(prior);
            return 0;
        }
    }
}