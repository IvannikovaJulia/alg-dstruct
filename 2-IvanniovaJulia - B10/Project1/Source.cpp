#include "memallocator.h"
#include <stdio.h>
#include <math.h>
#define MEMORY_FAIL -1
#define FREE 1
#define NOT_FREE 0

typedef struct descr_list {
    int size;
    struct descr_list* next;
    char is_free;
} descr_list;

descr_list* head = NULL;

int meminit(void* pMemory, int size) {
    if (head != NULL || pMemory == NULL || size < sizeof(descr_list)) {
        return MEMORY_FAIL;
    }
    head = (descr_list*)pMemory;
    head->size = size - sizeof(descr_list);
    head->next = NULL;
    head->is_free = FREE;
    return 0;
}

descr_list* Create_NewDescr(descr_list* descr, int size) {
    if (head == NULL || descr == NULL || descr->is_free == NOT_FREE)
        return NULL;
    if (descr->size - size > sizeof(descr_list)) {
        descr_list* new_descr = (descr_list*)((char*)(void*)((descr_list*)descr + 1) + size);
        new_descr->size = descr->size - size - sizeof(descr_list);
        new_descr->is_free = FREE;
        new_descr->next = descr->next;
        descr->next = new_descr;
    }
    descr->size = size;
    descr->is_free = NOT_FREE;
    return descr;
}

void* memalloc(int size) {
    if (head == NULL || size <= 0) {
        return NULL;
    }
    descr_list* descr = head;
    descr_list* new_descr = NULL;
    void* ptr = NULL;
    int flag = 0;
    while (descr != NULL) {
        if (descr->size >= size && descr->is_free == FREE) {
            flag = 1;
            break;
        }
        descr = descr->next;
    }
    if (flag != 0) {
        descr_list* needed_descr = Create_NewDescr(descr, size);
        if (needed_descr == NULL)
            return NULL;
        return (void*)((descr_list*)needed_descr + 1);;
    }
    else
        return NULL;
}

void memfree(void* p) {
    if (p == NULL)
        return;
    descr_list* descr = head;
    descr_list* prev_descr = NULL;
    descr_list* next_descr = NULL;
    while (descr != NULL) {
        if (((char*)p - (char*)(descr + 1)) > 0) {
            prev_descr = descr;
            descr = descr->next;
        }
        else
            if ((char*)(descr + 1) == (char*)p)
                break;
            else
                return;
    }
    if (descr == NULL)
        return;
    if (descr->is_free == FREE)
        return;
    descr_list* descr1 = descr;
    descr1->is_free = FREE;
    if (prev_descr != NULL && prev_descr->is_free == FREE) {
        prev_descr->size = prev_descr->size + sizeof(descr_list) + descr1->size;
        prev_descr->is_free = FREE;
        prev_descr->next = descr1->next;
    }
    next_descr = descr1->next;
    if (next_descr != NULL && next_descr->is_free == FREE) {
        if (prev_descr != NULL && prev_descr->is_free == FREE) {
            descr1 = prev_descr;
        }
        descr1->size = descr1->size + sizeof(descr_list) + next_descr->size;
        descr1->is_free = FREE;
        descr1->next = next_descr->next;
    }
}

int memgetminimumsize() {
    return sizeof(descr_list);
}

int memgetblocksize() {
    return sizeof(descr_list);
}

void memdone() {
    head = NULL;
}