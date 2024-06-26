#include "Catalog/users_catalog.h"

#include <stdio.h>

typedef struct users_catalog {
    GHashTable *users;
} USERS_CATALOG;

USERS_CATALOG *create_users_catalog() {
    USERS_CATALOG *new_catalog = malloc(sizeof(USERS_CATALOG));

    new_catalog->users = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                               (GDestroyNotify)free_user);

    return new_catalog;
}

void insert_user(USERS_CATALOG *catalog, USER *user, const char *key) {
    g_hash_table_insert(catalog->users, strdup(key), user);
}

GHashTable *get_users_hash(USERS_CATALOG *catalog) {
    return catalog->users;
}

USER *get_user_by_id(USERS_CATALOG *catalog, char *id) {
    return g_hash_table_lookup(catalog->users, id);
}

void free_users_catalog(USERS_CATALOG *catalog) {
    g_hash_table_destroy(catalog->users);
    free(catalog);
}