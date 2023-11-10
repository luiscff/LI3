#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct flight {
    int id;                   // identificador do voo (se for 0 é inválido)
    char *airline;
    char *plain_model;
    int total_seats;            
    char *origin;
    char *destination;
    //Date schedule_departure_date;         TODO: ver formato de datas, fazer gets e sets
    // Date schedule_arrival_date;
    // Date real_arrival_date;
    // Date real_arrival_date;
    char *pilot;           
    char *copilot;
    char *notes;            
} FLIGHT;

FLIGHT *create_flight(void) {
    FLIGHT *new_flight = malloc(sizeof(struct flight));
    new_flight->id = 0;  // id 0 significa que é inválido
    return new_flight;
}

void free_flight(FLIGHT *flight) {
    free(flight);
}

// Getters
int get_id(const FLIGHT *f) { return f->id; }
const char *get_airline(const FLIGHT *f) { return f->airline; }
const char *get_plain_model(const FLIGHT *f) { return f->plain_model; }
int get_total_seats(const FLIGHT *f) { return f->total_seats; }
const char *get_origin(const FLIGHT *f) { return f->origin; }
const char *get_destination(const FLIGHT *f) { return f->destination; }
//Date
//Date
//Date
//Date
const char *get_pilot(const FLIGHT *f) { return f->pilot; }
const char *get_copilot(const FLIGHT *f) { return f->copilot; }
const char *get_notes(const FLIGHT *f) { return f->notes; }

// Setters
void set_id(FLIGHT *f, int id) {
    f->id = id;
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

//Date

//Date

//Date

// Date

void set_pilot(FLIGHT *f, const char *pilot) {
    f->pilot = strdup(pilot);
}

void set_copilot(FLIGHT *f, const char *copilot) {
    f->copilot = strdup(copilot);
}

void set_notes(FLIGHT *f, const char *notes) {
    f->notes = strdup(notes);
}
int main() {
    FLIGHT myFlight;

    // Setting the values for the flight
    set_id(&myFlight, 1);
    set_airline(&myFlight, "Airline XYZ");
    set_plain_model(&myFlight, "Model ABC");
    set_total_seats(&myFlight, 150);
    set_origin(&myFlight, "City A");
    set_destination(&myFlight, "City B");
    set_pilot(&myFlight, "John Doe");
    set_copilot(&myFlight, "Jane Doe");
    set_notes(&myFlight, "Additional notes for the flight");

    // Printing the details
    printf("Flight ID: %d\n", myFlight.id);
    printf("Airline: %s\n", myFlight.airline);
    printf("Plane Model: %s\n", myFlight.plain_model);
    printf("Total Seats: %d\n", myFlight.total_seats);
    printf("Origin: %s\n", myFlight.origin);
    printf("Destination: %s\n", myFlight.destination);
    printf("Pilot: %s\n", myFlight.pilot);
    printf("Co-pilot: %s\n", myFlight.copilot);
    printf("Notes: %s\n", myFlight.notes);

    // Freeing allocated memory
    free_flight(&myFlight);

    return 0;
}

