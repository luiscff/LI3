#include "Entities/flight.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

typedef struct flight {
    gpointer flight_id;  // identificador do voo (se for 0 é inválido) || futura key
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
    int passageiros;
} FLIGHT;

FLIGHT *create_flight() {
    FLIGHT *new_flight = malloc(sizeof(struct flight));
    new_flight->flight_id = 0;  // id 0 significa que é inválido
    new_flight->airline = NULL;
    new_flight->plain_model = NULL;
    new_flight->origin = NULL;
    new_flight->destination = NULL;
    new_flight->schedule_departure_date = NULL;
    new_flight->schedule_arrival_date = NULL;
    new_flight->real_departure_date = NULL;
    new_flight->real_arrival_date = NULL;
    new_flight->pilot = NULL;
    new_flight->copilot = NULL;
    new_flight->notes = NULL;
    new_flight->passageiros = 0;
    return new_flight;
}

void free_flight(FLIGHT *flight) {
    if (flight->airline) free(flight->airline);
    if (flight->plain_model) free(flight->plain_model);
    if (flight->origin) free(flight->origin);
    if (flight->destination) free(flight->destination);
    if (flight->schedule_departure_date) free(flight->schedule_departure_date);
    if (flight->schedule_arrival_date) free(flight->schedule_arrival_date);
    if (flight->real_departure_date) free(flight->real_departure_date);
    if (flight->real_arrival_date) free(flight->real_arrival_date);
    if (flight->pilot) free(flight->pilot);
    if (flight->copilot) free(flight->copilot);
    if (flight->notes) free(flight->notes);
    if (flight) free(flight);
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

const char *get_schedule_departure_date(const FLIGHT *f) { return f->schedule_departure_date; }
const char *get_schedule_arrival_date(const FLIGHT *f) { return f->schedule_arrival_date; }
const char *get_real_departure_date(const FLIGHT *f) { return f->real_departure_date; }
const char *get_real_arrival_date(const FLIGHT *f) { return f->real_arrival_date; }

const char *get_pilot(const FLIGHT *f) { return f->pilot; }
const char *get_copilot(const FLIGHT *f) { return f->copilot; }
const char *get_notes(const FLIGHT *f) { return f->notes; }

// Setters

void set_flight_id(FLIGHT *flight, const char *id) {
    if (flight->flight_id) free(flight->flight_id);
    // convert to gpointer to store in GHashTable
    flight->flight_id = GINT_TO_POINTER(atoi(id));
}

void set_airline(FLIGHT *f, const char *airline) {
    if (f->airline) free(f->airline);
    f->airline = strdup(airline);
}

void set_plain_model(FLIGHT *f, const char *plain_model) {
    if (f->plain_model) free(f->plain_model);
    f->plain_model = strdup(plain_model);
}

void set_total_seats(FLIGHT *f, int total_seats) {
    f->total_seats = total_seats;
}

void set_origin(FLIGHT *f, const char *origin) {
    if (f->origin) free(f->origin);
    f->origin = convert_to_upper_case(strdup((origin)));
}
void set_destination(FLIGHT *f, const char *destination) {
    if (f->destination) free(f->destination);
    f->destination = convert_to_upper_case(strdup((destination)));
}

void set_schedule_departure_date(FLIGHT *f, const char *schedule_departure_date) {
    if (f->schedule_departure_date) free(f->schedule_departure_date);
    f->schedule_departure_date = strdup(schedule_departure_date);
}

void set_schedule_arrival_date(FLIGHT *f, const char *schedule_arrival_date) {
    if (f->schedule_arrival_date) free(f->schedule_arrival_date);
    f->schedule_arrival_date = strdup(schedule_arrival_date);
}

void set_real_departure_date(FLIGHT *f, const char *real_departure_date) {
    if (f->real_departure_date) free(f->real_departure_date);
    f->real_departure_date = strdup(real_departure_date);
}

void set_real_arrival_date(FLIGHT *f, const char *real_arrival_date) {
    if (f->real_arrival_date) free(f->real_arrival_date);
    f->real_arrival_date = strdup(real_arrival_date);
}
void set_pilot(FLIGHT *f, const char *pilot) {
    if (f->pilot) free(f->pilot);
    f->pilot = strdup(pilot);
}

void set_copilot(FLIGHT *f, const char *copilot) {
    if (f->copilot) free(f->copilot);
    f->copilot = strdup(copilot);
}

void set_notes(FLIGHT *f, const char *notes) {
    if (f->notes) free(f->notes);
    f->notes = strdup(notes);
}

int calc_departure_delay(char *schedule_departure, char *real_departure) {
    double delay = -1.0;
    struct tm schedule_departure_tm = {0};
    struct tm real_departure_tm = {0};

    if (sscanf(schedule_departure, "%4d/%2d/%2d %2d:%2d:%2d",
               &schedule_departure_tm.tm_year, &schedule_departure_tm.tm_mon, &schedule_departure_tm.tm_mday,
               &schedule_departure_tm.tm_hour, &schedule_departure_tm.tm_min, &schedule_departure_tm.tm_sec) != 6) return delay;

    if (sscanf(real_departure, "%4d/%2d/%2d %2d:%2d:%2d",
               &real_departure_tm.tm_year, &real_departure_tm.tm_mon, &real_departure_tm.tm_mday,
               &real_departure_tm.tm_hour, &real_departure_tm.tm_min, &real_departure_tm.tm_sec) != 6) return delay;

    // Adjust the year and month fields, because struct tm counts years since 1900 and months from 0
    schedule_departure_tm.tm_year -= 1900;
    schedule_departure_tm.tm_mon -= 1;
    real_departure_tm.tm_year -= 1900;
    real_departure_tm.tm_mon -= 1;

    time_t schedule_departure_time = mktime(&schedule_departure_tm);
    time_t real_departure_time = mktime(&real_departure_tm);

    delay = difftime(real_departure_time, schedule_departure_time);

    return (int)delay;
}
// STATS

int get_passageiros(FLIGHT *flight) {
    return flight->passageiros;
}

void add_passageiro(FLIGHT *flight) {
    flight->passageiros++;
}