#ifndef FLIGHT_CATALOG_H
#define FLIGHT_CATALOG_H


#include "flights.h"

typedef struct flights_catalog FLIGHTS_CATALOG;

FLIGHTS_CATALOG create_flights_catalog();

void insert_flight(FLIGHTS_CATALOG *catalog, FLIGHT *flight, gpointer key);

FLIGHT get_flight_by_id(FLIGHTS_CATALOG *catalog, int id);

FLIGHT get_flight_by_code(FLIGHTS_CATALOG *catalog, gpointer flight_code);

void free_flights_catalog(FLIGHTS_CATALOG *catalog);

#endif // FLIGHT_CATALOG_H