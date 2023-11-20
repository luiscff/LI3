#ifndef QUERIES_H
#define QUERIES_H

#include "Catalog/flights_catalog.h"
#include "Catalog/users_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/passengers_catalog.h"


char * query1(USERS_CATALOG *ucatalog, FLIGHTS_CATALOG *fcatalog, RESERVATIONS_CATALOG *rcatalog,PASSENGERS_CATALOG *pcatalog, char *id);
double query3(RESERVATIONS_CATALOG* rcatalog, char* hotel_id);

char* query4 (RESERVATIONS_CATALOG* rcatalog, char *hotel_id);
char* query9 (USERS_CATALOG* ucatalog, char* token);
#endif