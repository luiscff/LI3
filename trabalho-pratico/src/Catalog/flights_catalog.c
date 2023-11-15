#include "catalogs/flights_catalog.h"

#include "entities/flights.h"

typedef struct flights_catalog {
    GHashTable *flights;
}FLIGHTS_CATALOG;

FLIGHTS_CATALOG create_flights_catalog() {
    FLIGHTS_CATALOG *new_catalog = malloc(sizeof(struct flights_catalog));

    new_catalog->flights = g_hash_table_new_full(NULL, g_direct_equal, NULL,
                                                 (GDestroyNotify)free_flight);

    return *new_catalog;
}

void insert_flight(FLIGHTS_CATALOG *catalog, FLIGHT *flight, gpointer key) {
    g_hash_table_insert(catalog->flights, key, flight);
}



FLIGHT get_flight_by_id(FLIGHTS_CATALOG *catalog, int id) {
    return g_hash_table_lookup(catalog->flights, GINT_TO_POINTER(id));
}

FLIGHT get_flight_by_code(FLIGHTS_CATALOG *catalog, gpointer flight_code) {
    return g_hash_table_lookup(catalog->flights, flight_code);
}

void free_flights_catalog(FLIGHTS_CATALOG *catalog) {
    g_hash_table_destroy(catalog->flights);
    free(catalog);
}