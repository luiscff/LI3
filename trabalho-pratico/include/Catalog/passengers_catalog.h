#ifndef PASSENGERS_CATALOG_H
#define PASSENGERS_CATALOG_H

#include "Entities/passengers.h"

#include <glib.h>

typedef struct passengers_catalog PASSENGERS_CATALOG;

PASSENGERS_CATALOG* create_passengers_catalog();
void insert_passenger(PASSENGERS_CATALOG *catalog, PASSENGER *passenger);
GList *get_list(PASSENGERS_CATALOG *catalog);

GList *find_flights_by_user(PASSENGERS_CATALOG *catalog, const char *user_id2);

GList *find_users_by_flight(PASSENGERS_CATALOG *catalog, int flight_id2);

void free_passengers_catalog(PASSENGERS_CATALOG *catalog);

#endif // PASSENGERS_CATALOG_H