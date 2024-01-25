#ifndef USERS_CATALOG_H
#define USERS_CATALOG_H

#include <glib.h>

#include "Entities/user.h"

typedef struct users_catalog USERS_CATALOG;

USERS_CATALOG *create_users_catalog();

void insert_user(USERS_CATALOG *catalog, USER *user, const char *key);

GHashTable *get_users_hash(USERS_CATALOG *catalog);

USER *get_user_by_id(USERS_CATALOG *catalog, char *id);

void free_users_catalog(USERS_CATALOG *catalog);

#endif  // USERS_CATALOG_H