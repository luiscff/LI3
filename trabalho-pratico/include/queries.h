#ifndef QUERIES_H
#define QUERIES_H

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/stats.h"
#include "Catalog/users_catalog.h"

char* query1(USERS_CATALOG* ucatalog, FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, PASSENGERS_CATALOG* pcatalog, char* id, int flag);
char* query1F(USERS_CATALOG* ucatalog, FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, PASSENGERS_CATALOG* pcatalog, char* id);
char* query2_nocat(FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, USERS_CATALOG* ucatalog, PASSENGERS_CATALOG* pcatalog, char* id, int flag);
char* query2_cat(FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, USERS_CATALOG* ucatalog, PASSENGERS_CATALOG* pcatalog, char* token, char* catalog, int flag);
char* query3(char* hotel_id, STATS* stats, int flag);
char* query4(RESERVATIONS_CATALOG* rcatalog, char* hotel_id, STATS* stats, int flag);
char* query5(char* token, char* dataI, char* dataF, STATS* stats, int flag);
char* query6(char* ano, char* top_n, STATS* stats, int flag);
char* query7(char* token, STATS* stats, int flag);
char* query8(char* token, char* dataI, char* dataF, STATS* stats, int flag);
char* query9(char* token, STATS* stats, int flag);
#endif