#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 typedef struct passanger {
    char* user_id;  //possivel key da hash
    int flight_id;
}PASSANGER;

struct passanger *create_passanger() {
    PASSANGER *new_passanger = malloc(sizeof(struct passanger));

    new_passanger->user_id = NULL;  // id NULL significa que é inválido
    new_passanger->flight_id=0;// id 0 significa que é inválido
    return new_passanger;
}

void set_flight_id(PASSANGER *p, int flight_id) {
    p->flight_id =flight_id;
}

void set_airline(PASSANGER *p, const char *user_id) {
    p->user_id = strdup(user_id);
}

int get_id(const PASSANGER *p) { return p->flight_id; }

const char *get_airline(const PASSANGER *p) { return p->user_id; }