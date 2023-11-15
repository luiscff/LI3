#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Entities/flights.h"

typedef struct flight {
    gpointer flight_id;                   // identificador do voo (se for 0 é inválido) || futura key
    char *airline;
    char *plain_model;
    int total_seats;            
    char *origin;
    char *destination;
    char *schedule_departure_date;
    char *schedule_arrival_date;
    char *real_departure_date;
    char *real_arrival_date;
    char *pilot;           
    char *copilot;
    char *notes;            
} FLIGHT;

FLIGHT *create_flight() {
    FLIGHT *new_flight = malloc(sizeof(struct flight));
    new_flight->flight_id = 0;  // id 0 significa que é inválido
    return new_flight;
}

void free_flight(FLIGHT *flight) {
    free(flight);
}

// Getters
int get_flight_id(const FLIGHT *flight) {
    int id = GPOINTER_TO_INT(flight->flight_id);
    return id;
}
const char *get_airline(const FLIGHT *f) { return f->airline; }
const char *get_plain_model(const FLIGHT *f) { return f->plain_model; }
int get_total_seats(const FLIGHT *f) { return f->total_seats; }
const char *get_origin(const FLIGHT *f) { return f->origin; }
const char *get_destination(const FLIGHT *f) { return f->destination; }

const char *schedule_departure_date(const FLIGHT *f) { return f->schedule_departure_date; }
const char *schedule_arrival_date(const FLIGHT *f) { return f->schedule_arrival_date; }
const char *real_departure_date(const FLIGHT *f) { return f->real_departure_date; }
const char *real_arrival_date(const FLIGHT *f) { return f->real_arrival_date; }

const char *get_pilot(const FLIGHT *f) { return f->pilot; }
const char *get_copilot(const FLIGHT *f) { return f->copilot; }
const char *get_notes(const FLIGHT *f) { return f->notes; }

// Setters

void set_flight_id(FLIGHT *flight, const char *flight_id_string) {
    int flight_id_int = atoi(flight_id_string);
    gpointer flight_id_int_pointer = GINT_TO_POINTER(flight_id_int);
    flight->flight_id = flight_id_int_pointer;
}

void set_airline(FLIGHT *f, const char *airline) {
    f->airline = strdup(airline);
}

void set_plain_model(FLIGHT *f, const char *plain_model) {
    f->plain_model = strdup(plain_model);
}

void set_total_seats(FLIGHT *f, int total_seats) {
    f->total_seats = total_seats;
}

void set_origin(FLIGHT *f, const char *origin) {
    f->origin = strdup(origin);
}
void set_destination(FLIGHT *f, const char *destination) {
    f->destination = strdup(destination);
}

void set_schedule_departure_date(FLIGHT *f, const char *schedule_departure_date) {
    f->schedule_departure_date = strdup(schedule_departure_date);
}

void set_schedule_arrival_date(FLIGHT *f, const char *schedule_arrival_date) {
    f->schedule_arrival_date = strdup(schedule_arrival_date);
}

void set_real_departure_date(FLIGHT *f, const char *real_departure_date) {
    f->real_departure_date = strdup(real_departure_date);
}

void set_real_arrival_date(FLIGHT *f, const char *real_arrival_date) {
    f->real_arrival_date = strdup(real_arrival_date);
            }
void set_pilot(FLIGHT *f, const char *pilot) {
    f->pilot = strdup(pilot);
}

void set_copilot(FLIGHT *f, const char *copilot) {
    f->copilot = strdup(copilot);
}

void set_notes(FLIGHT *f, const char *notes) {
    f->notes = strdup(notes);
}



