#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Tree {
    int nodes_amount;
    int value;
    struct Tree* left;
    struct Tree* right;
    struct Tree* parent;
} Node;

typedef struct list {
    Node* field;
    struct list* ptr;
}LIST;

typedef struct queue {
    LIST* first, * last;
}QUEUE;

LIST* create_new_list(Node* node) {
    LIST* list = (LIST*)malloc((sizeof(LIST)));
    list->field = node;
    list->ptr = NULL;
    return list;
}

int isempty(QUEUE* q) {
    if (q->first == 0) {
        return 1;
    }
    else
        return 0;
}

void insert(QUEUE* q, Node* x) {
    if ((q->first == NULL) && (q->last) == NULL) {
        q->first = q->last = create_new_list(x);
        return;
    }
    else {
        q->last->ptr = create_new_list(x);
        q->last = q->last->ptr;
    }
}

Node* pop(QUEUE* q) {
    Node* temp;
    if (q->first == NULL) {
        return NULL;
    }
    temp = q->first->field;
    if (q->first == q->last) {
        free(q->last);
        q->first = q->last = NULL;
    }
    else {
        LIST* tmp = q->first;
        q->first = q->first->ptr;
        free(tmp);
    }
    return temp;
}

void delete_queue(QUEUE* q) {
    while (q->first != NULL) {
        pop(q);

    }
}

Node* create(Node* root) {
    Node* tmp = (Node*)(malloc(sizeof(Node)));
    tmp->nodes_amount = 0;
    tmp->parent = NULL;
    tmp->left = tmp->right = NULL;
    root = tmp;
    return root;
}

void _add(Node* root, Node* new_Node) {
    if (root == NULL) {
        printf("%c", "Error in function create");
        return;
    }
    Node* unit = root;
    if (new_Node == NULL) {
        return;
    }
    while (unit != NULL) {

        if (unit->left == NULL) {
            unit->left = new_Node;
            unit->nodes_amount++;
            unit->left->parent = unit;
            unit->left->left = unit->left->right = NULL;
            return;
        }
        else if (unit->right == NULL) {
            unit->right = new_Node;
            unit->nodes_amount++;
            unit->right->parent = unit;
            unit->right->left = unit->right->right = NULL;
            return;
        }

        if (unit->left->nodes_amount <= unit->right->nodes_amount) {
            unit->nodes_amount += new_Node->nodes_amount + 1;

            unit = unit->left;
        }
        else {
            unit->nodes_amount += new_Node->nodes_amount + 1;

            unit = unit->right;
        }

    }

}

void PrintTree(Node* root, int n) {
    if (root != NULL) {
        PrintTree(root->right, n + 1);
        for (int i = 0; i < n; i++) {
            putchar('\t');
        }
        printf("%d", root->value);
        printf("\n");
        PrintTree(root->left, n + 1);


    }
}

Node* add(Node* root, int value) {
    Node* new_Node = (Node*)malloc(sizeof(Node));
    new_Node->nodes_amount = 0;
    new_Node->value = value;
    new_Node->parent = new_Node->right = new_Node->left = NULL;
    _add(root, new_Node);



}

Node* _search(Node* root, int value) {
    Node* node = NULL;
    QUEUE q;
    q.last = q.first = NULL;
    insert(&q, root);
    while ((root = pop(&q)) != NULL) {
        if (root->value == value) {
            delete_queue(&q);
            return root;
        }
        if (root->left != NULL) {
            insert(&q, root->left);

        }
        if (root->right != NULL) {
            insert(&q, root->right);
        }

    }
    return NULL;
}

int search(Node* root, int value) {
    if (_search(root, value) != NULL) {
        return 1;
    }
    return 0;
}

void delete(Node* root, int value) {
    Node* del = _search(root, value);
    if (!del) {
        return;
    }
    del->parent->nodes_amount -= del->nodes_amount;
    if (del->parent->left == del) {
        del->parent->left = NULL;
    }
    if (del->parent->right == del) {
        del->parent->right = NULL;
    }
    _add(root, del->left);
    _add(root, del->right);
    free(del);

}

int main() {
    Node* head = NULL;
    Node* root = create(head);
    for (int i = 0; i < 10; i++) {
        add(root, i);
    }


    PrintTree(root, 3);
    delete(root, 3);
    PrintTree(root, 3);

}