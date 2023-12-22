#include "Entities/passenger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct passenger {
    int flight_id2;
    char *user_id2;
} PASSENGER;

PASSENGER *create_passenger() {
    PASSENGER *new_passenger = malloc(sizeof(struct passenger));
    new_passenger->user_id2 = NULL;  // id NULL significa que é inválido
    new_passenger->flight_id2 = 0;   // id 0 significa que é inválido
    return new_passenger;
}

void free_passenger(PASSENGER *p) {
    if (p->user_id2) free(p->user_id2);
    if (p) free(p);
}

void set_flight_id2(PASSENGER *p, int flight_id2) {
    p->flight_id2 = flight_id2;
}

void set_user_id2(PASSENGER *p, const char *user_id2) {
    if (p->user_id2) {  // Se user_id2 já foi definido, libertar memória para definir denovo
        free(p->user_id2);
    }
    p->user_id2 = strdup(user_id2);
}

int get_flight_id2(const PASSENGER *p) {
    return p->flight_id2;
}

const char *get_user_id2(const PASSENGER *p) {
    // retira o \n no final da string
    if (p->user_id2[strlen(p->user_id2) - 1] == '\n') {
        p->user_id2[strlen(p->user_id2) - 1] = '\0';
    }
    return p->user_id2;
}