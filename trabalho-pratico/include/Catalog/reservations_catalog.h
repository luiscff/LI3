#ifndef RESERVATIONS_CATALOG_H
#define RESERVATIONS_CATALOG_H

#include <glib.h>
#include "Entities/reservation.h"

typedef struct reservations_catalog RESERVATIONS_CATALOG;

RESERVATIONS_CATALOG* create_reservations_catalog();

void insert_reservation(RESERVATIONS_CATALOG *catalog, RESERVATION *reservation, const char *key);

GHashTable *get_reservations_hash (RESERVATIONS_CATALOG *catalog);

RESERVATION* get_reservation_by_id(RESERVATIONS_CATALOG *catalog, char *id);

void free_reservations_catalog(RESERVATIONS_CATALOG *catalog);

int calc_total_spent_by_user_id(RESERVATIONS_CATALOG *catalog, char* user_id);



#endif// RESERVATIONS_CATALOG_H