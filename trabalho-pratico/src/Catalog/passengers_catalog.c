#include "Catalog/passengers_catalog.h" 

typedef struct passengers_catalog {
    GHashTable *passengers;
}PASSENGERS_CATALOG;

PASSENGERS_CATALOG* create_passengers_catalog() {
    PASSENGERS_CATALOG *new_catalog = malloc(sizeof(struct passengers_catalog));

    new_catalog->passengers = g_hash_table_new_full(NULL, g_direct_equal, NULL,
                                                    (GDestroyNotify)free_passenger);

    return new_catalog;
}

void insert_passenger(PASSENGERS_CATALOG *catalog, PASSENGER *passenger, gpointer key) {
    g_hash_table_insert(catalog->passengers, key, passenger);
}

PASSENGER* get_passenger_by_id(PASSENGERS_CATALOG *catalog, int id) {
    return g_hash_table_lookup(catalog->passengers, GINT_TO_POINTER(id));
}

PASSENGER* get_passenger_by_code(PASSENGERS_CATALOG *catalog, gpointer code) {
    return g_hash_table_lookup(catalog->passengers, code);
}

void free_passengers_catalog(PASSENGERS_CATALOG *catalog) {
    g_hash_table_destroy(catalog->passengers);
    free(catalog);
}
 