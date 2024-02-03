#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"

void initRestaurant(RestaurantType *r, char *n){
    strcpy(r->name, n);
    initPatronArray(r->patrons);
    initResvList(&r->reservation);
}

int validateResvTime(int yr, int mth, int day, int hr, int min){
    if(yr < 2020 || yr > 2021){
        return C_FALSE;
    }
    if(mth < 1 || mth > 12){
        return C_FALSE;
    }
    if(day < 1 || day > 31){
        return C_FALSE;
    }
    if(hr < 0 || hr > 23){
        return C_FALSE;
    }
    if(min < 0 || min > 59){
        return C_FALSE;
    }
    return C_TRUE;
}

void createResv(RestaurantType *r, int pId, int yr, int mth, int day, int hr, int min) {
    if (validateResvTime(yr, mth, day, hr, min) == C_NOK) {
        fprintf(stderr, "Error: Invalid date or time for reservation.\n");
        return;
    }

    PatronType *foundPatron;
    if (findPatron(&r->patrons[0], pId, &foundPatron) == C_NOK) {
        printf("Error: Patron with ID %d not found\n", pId);
        return;
    }

    ResvTimeType *newResvTime;
    initResvTime(&newResvTime, yr, mth, day, hr, min);

    ResvType *newReservation;
    initResv(&newReservation, foundPatron, newResvTime);

    addResv(&r->reservation, newReservation);
}

void printResByPatron(RestaurantType *r, int id){
    PatronType *p;
    if(findPatron(r->patrons, id, &p) == C_FALSE){
        printf("Patron %d does not exist\n", id);
        return;
    }
    printf("Reservations for %s:\n", p->name);
    NodeType *curr = r->reservation.head;
    while(curr != NULL){
        if(curr->data->patron->id == id){
            printf("  %d: %d/%d/%d\n", curr->data->id, curr->data->resvTime->day, curr->data->resvTime->month, curr->data->resvTime->year);
        }
        curr = curr->next;
    }
}

void cleanupRestaurant(RestaurantType *r){
    cleanupPatronArray(r->patrons);
    cleanupResvList(&r->reservation);
}

