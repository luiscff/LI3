#include "Entities/passengers.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct passenger {
    gpointer key;
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
    free(p);
}

//setters

//TODO implementar set_key()

void set_flight_id2(PASSENGER *p, int flight_id2) {
    p->flight_id2 = flight_id2;
}

void set_user_id2(PASSENGER *p, const char *user_id2) {
    p->user_id2 = strdup(user_id2);
}

//getters

//TODO implementar get_key()

 int get_flight_id2(const PASSENGER *p) {
    return p->flight_id2;
}

const char* get_user_id2(const PASSENGER *p) {
    return p->user_id2;
}