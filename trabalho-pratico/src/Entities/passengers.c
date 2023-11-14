#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 typedef struct passenger {
    char* user_id;  //possivel key da hash
    int flight_id;
}PASSENGER;

struct passenger *create_passenger() {
    PASSENGER *new_passenger = malloc(sizeof(struct passenger));

    new_passenger->user_id = NULL;  // id NULL significa que é inválido
    new_passenger->flight_id=0;// id 0 significa que é inválido
    return new_passenger;
}

void free_passenger(PASSENGER *p) {
    free(p);
}


void set_flight_id(PASSENGER *p, int flight_id) {
    p->flight_id =flight_id;
}

void set_airline(PASSENGER *p, const char *user_id) {
    p->user_id = strdup(user_id);
}

int get_id(const PASSENGER *p) { return p->flight_id; }

const char *get_airline(const PASSENGER *p) { return p->user_id; }