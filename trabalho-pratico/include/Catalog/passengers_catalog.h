#ifndef PASSENGERS_CATALOG_H
#define PASSENGERS_CATALOG_H

#include "Entities/passengers.h"

#include <glib.h>

typedef struct passengers_catalog PASSENGERS_CATALOG;

PASSENGERS_CATALOG* create_passengers_catalog();

void insert_passenger(PASSENGERS_CATALOG *catalog, PASSENGER *passenger, gpointer key);

PASSENGER* get_passenger_by_id(PASSENGERS_CATALOG *catalog, int id);

PASSENGER* get_passenger_by_code(PASSENGERS_CATALOG *catalog, gpointer code);

void free_passengers_catalog(PASSENGERS_CATALOG *catalog);

#endif // PASSENGERS_CATALOG_H