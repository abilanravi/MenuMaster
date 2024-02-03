#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"

void initResvList(ResvListType *list){
    list->head = NULL;
    list->nextId = RES_IDS;
}

void initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr, int min){
    *rt = malloc(sizeof(ResvTimeType));
    (*rt)->year = yr;
    (*rt)->month = mth;
    (*rt)->day = day;
    (*rt)->hours = hr;
    (*rt)->minutes = min;
}

void initResv(ResvType **r, PatronType *p, ResvTimeType *rt){
    *r = malloc(sizeof(ResvType));
    (*r)->id = rt->year * 100000 + rt->month * 10000 + rt->day * 1000 + rt->hours * 100 + rt->minutes * 10 + rt->minutes;
    (*r)->patron = p;
    (*r)->resvTime = rt;
}

int lessThan(ResvTimeType *r1, ResvTimeType *r2){
    if(r1->year < r2->year){
        return C_TRUE;
    }else if(r1->year > r2->year){
        return C_FALSE;
    }else{
        if(r1->month < r2->month){
            return C_TRUE;
        }else if(r1->month > r2->month){
            return C_FALSE;
        }else{
            if(r1->day < r2->day){
                return C_TRUE;
            }else if(r1->day > r2->day){
                return C_FALSE;
            }else{
                if(r1->hours < r2->hours){
                    return C_TRUE;
                }else if(r1->hours > r2->hours){
                    return C_FALSE;
                }else{
                    if(r1->minutes < r2->minutes){
                        return C_TRUE;
                    }else{
                        return C_FALSE;
                    }
                }
            }
        }
    }
}

void addResv(ResvListType *list, ResvType *r){
    NodeType *newNode = malloc(sizeof(NodeType));
    newNode->data = r;
    newNode->next = NULL;
    newNode->prev = NULL;
    if(list->head == NULL){
        list->head = newNode;
    }else{
        NodeType *curr = list->head;
        while(curr->next != NULL){
            if(lessThan(curr->data->resvTime, r->resvTime)){
                curr = curr->next;
            }else{
                break;
            }
        }
        if(curr->next == NULL){
            curr->next = newNode;
            newNode->prev = curr;
        }else{
            newNode->next = curr;
            newNode->prev = curr->prev;
            curr->prev->next = newNode;
            curr->prev = newNode;
        }
    }
}

void printReservation(ResvType *r){
    printf("  %d: %s, %d/%d/%d %d:%d\n", r->id, r->patron->name, r->resvTime->year, r->resvTime->month, r->resvTime->day, r->resvTime->hours, r->resvTime->minutes);
}

void printReservations(ResvListType *list){
    printf("Reservations:\n");
    NodeType *curr = list->head;
    while(curr != NULL){
        printReservation(curr->data);
        curr = curr->next;
    }
}

void cleanupResvList(ResvListType *list){
    NodeType *curr = list->head;
    while(curr != NULL){
        NodeType *temp = curr;
        curr = curr->next;
        free(temp->data->resvTime);
        free(temp->data);
        free(temp);
    }
}
