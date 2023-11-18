#ifndef QUERIES_H
#define QUERIES_H

#include "Catalog/flights_catalog.h"
#include "Catalog/users_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/passengers_catalog.h"


void query1(USERS_CATALOG *ucatalog, FLIGHTS_CATALOG *fcatalog, RESERVATIONS_CATALOG *rcatalog,PASSENGERS_CATALOG *pcatalog, char *id);


#endif