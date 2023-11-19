#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "output.h"
#include "queries.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/flights_catalog.h"

int inputParser(const char *inputPath, USERS_CATALOG *users_catalog, FLIGHTS_CATALOG *flights_catalog, RESERVATIONS_CATALOG *reservations_catalog, PASSENGERS_CATALOG *passengers_catalog);


#endif