#ifndef QUERIES_H
#define QUERIES_H

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"


char* query1(USERS_CATALOG* ucatalog, FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, PASSENGERS_CATALOG* pcatalog, char* id);
char* query1F(USERS_CATALOG* ucatalog, FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, PASSENGERS_CATALOG* pcatalog, char* id);
char* query2_nocat(FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog,USERS_CATALOG *ucatalog, PASSENGERS_CATALOG* pcatalog, char* id, int flag);
char* query2_cat(FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog,USERS_CATALOG *ucatalog,PASSENGERS_CATALOG* pcatalog, char* token,char* catalog, int flag);
char* query3(RESERVATIONS_CATALOG* rcatalog, char* hotel_id);
char* query3F(RESERVATIONS_CATALOG* rcatalog, char* hotel_id);
char* query4(RESERVATIONS_CATALOG* rcatalog, char* hotel_id,int flag);
char* query7(FLIGHTS_CATALOG* fcatalog, char* token);
char* query9(USERS_CATALOG* ucatalog, char* token);
#endif