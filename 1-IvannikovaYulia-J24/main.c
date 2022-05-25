#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "BrentHash.h"

int main() {

    hashMap* hashMap = NULL;
    hashMap = hashMapInit(hashMap);
    char command = 0;
    char value[50] = {'\0'};
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