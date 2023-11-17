#ifndef RESERVATIONS_CATALOG_H
#define RESERVATIONS_CATALOG_H

#include <glib.h>
#include "Entities/reservation.h"

typedef struct reservations_catalog RESERVATIONS_CATALOG;

RESERVATIONS_CATALOG* create_reservations_catalog(void);
void insert_reservation(RESERVATIONS_CATALOG *catalog, RESERVATION *reservation, const char *key);
RESERVATION* get_reservation_by_id(RESERVATIONS_CATALOG *catalog, char *id);
void free_reservations_catalog(RESERVATIONS_CATALOG *catalog);



#endif // RESERVATIONS_CATALOG_H