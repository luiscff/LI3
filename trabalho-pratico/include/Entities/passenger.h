#ifndef PASSENGERS_H
#define PASSENGERS_H

#include <glib.h>

typedef struct passenger PASSENGER;

PASSENGER *create_passenger();
void free_passenger(PASSENGER *p);

void set_flight_id2(PASSENGER *p, int flight_id2);
void set_user_id2(PASSENGER *p, const char *user_id2);

int get_flight_id2(const PASSENGER *p);
const char *get_user_id2(const PASSENGER *p);

#endif  // PASSENGERS_H