#include <stdio.h>

#include "Catalog/reservations_catalog.h"

typedef struct reservations_catalog {
    GHashTable *reservations;
} RESERVATIONS_CATALOG;

RESERVATIONS_CATALOG* create_reservations_catalog() {
    RESERVATIONS_CATALOG *new_catalog = malloc(sizeof(RESERVATIONS_CATALOG));

    new_catalog->reservations = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                                 (GDestroyNotify)free_reservation);

    return new_catalog;
}

void insert_reservation(RESERVATIONS_CATALOG *catalog, RESERVATION *reservation, const char *key) {
    g_hash_table_insert(catalog->reservations, strdup(key), reservation);
}

RESERVATION* get_reservation_by_id(RESERVATIONS_CATALOG *catalog, char *id) {
    return g_hash_table_lookup(catalog->reservations, id);
}

void free_reservations_catalog(RESERVATIONS_CATALOG *catalog) {
    g_hash_table_destroy(catalog->reservations);
    free(catalog);
}

