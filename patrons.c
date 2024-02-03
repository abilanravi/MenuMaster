#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"

void initPatronArray(PatronArrayType *arr){
    arr->elements = calloc(MAX_CAP, sizeof(PatronType));
    arr->size = 0;
    arr->nextId = PATRON_IDS;
}

void addPatron(PatronArrayType *arr, char *n){
    PatronType *p = &arr->elements[arr->size];
    strcpy(p->name, n);
    p->id = arr->nextId;
    arr->size++;
    arr->nextId++; 
}

int findPatron(PatronArrayType *arr, int id, PatronType **p){
    for(int i = 0; i < arr->size; i++){
        if(arr->elements[i].id == id){
            *p = &arr->elements[i];
            return C_TRUE;
        }
    }
    return C_FALSE;
}

void printPatrons (PatronArrayType *arr){
    printf("Patrons:\n");
    for(int i = 0; i < arr->size; i++){
        printf("  %d: %s\n", arr->elements[i].id, arr->elements[i].name);
    }
}

void cleanupPatronArray(PatronArrayType *arr){
    free(arr->elements);
}