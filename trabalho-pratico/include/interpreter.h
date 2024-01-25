#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"
#include "output.h"
#include "queries.h"
#include "utils.h"

int inputParser(const char *inputPath, USERS_CATALOG *users_catalog, FLIGHTS_CATALOG *flights_catalog, RESERVATIONS_CATALOG *reservations_catalog, PASSENGERS_CATALOG *passengers_catalog, STATS *stats, bool isTestes);

#endif