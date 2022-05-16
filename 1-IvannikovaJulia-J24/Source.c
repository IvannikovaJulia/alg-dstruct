#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define size 1000

typedef struct {
    int key;
    char* str;
} table_h;

table_h* table;
char* delh;


void create_hash_table(void) {
    table = (table_h*)malloc(size * sizeof(table_h));
    if (table == NULL) {
        return;
    }
    delh = (char*)malloc(size * sizeof(char));
    if (delh == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        table[i].key = -1;
        table[i].str = NULL;
        delh[i] = 0;
    }
}


int search(int key) {
    int x = key % size;
    for (int i = 1; i <= size; i++) {
        if (table[x].key != -1) {
            if ((table[x].key == key) && !delh[x]) {
                return 1;
            }
            else {
                return 0;
            }
        }

    }
    return 0;
}

void insert(int key, char* str) {
    if (search(key))
        return;
    int x = key % size;
    for (int i = 1; i <= size; i++) {
        if ((table[x].key == -1) || delh[x]) {
            table[x].key = key;
            table[x].str = (char*)malloc((strlen(str) + 1) * sizeof(char));
            if (table[x].str == NULL)
                return;
            strcpy(table[x].str, str);
            table[x].str[strlen(str)] = '\0';
            delh[x] = 0;
            return;
        }
    }
}

void delete(int key) {
    if (!search(key)) {
        return;
    }
    int x = key % size;
    for (int i = 1; i <= size; i++) {
        if (table[x].key != -1) {
            if (table[x].key == key) {
                delh[x] = 1;
            }
            else {
                return;
            }
        }
    }
}

void destroy_hash_table(void) {
    if (table == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        free(table[i].str);
    }
    free(table);
    table = NULL;
    free(delh);
}

int main() {
    create_hash_table();
    char command;
    int key;
    while (scanf("%c", &command) >= 1) {
        scanf("%d", &key);
        switch (command) {
        case 'a':
            insert(key, "");
            break;
        case 'r':
            delete(key);
            break;
        case 'f':
            if (search(key)) {
                puts("yes");
            }
            else {
                puts("no");
            }
            break;
        }
    }
    destroy_hash_table();
    return 0;
}