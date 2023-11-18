#include "Catalog/passengers_catalog.h"
#include <string.h>

typedef struct passengers_catalog {
    GList *passengers;  // Lista de PASSENGER
} PASSENGERS_CATALOG;

PASSENGERS_CATALOG *create_passengers_catalog() {
    PASSENGERS_CATALOG *new_catalog = malloc(sizeof(PASSENGERS_CATALOG));
    new_catalog->passengers = NULL;  // Inicializar a lista como vazia
    return new_catalog;
}

void insert_passenger(PASSENGERS_CATALOG *catalog, PASSENGER *passenger) {
    // Adicionar o passageiro ao início da lista
    catalog->passengers = g_list_prepend(catalog->passengers, passenger);
}

GList *get_list(PASSENGERS_CATALOG *catalog) {
    return catalog->passengers;
}

// TODO testar
GList *find_flights_by_user(PASSENGERS_CATALOG *catalog, const char *user_id2) {
    GList *flights = NULL;
    // Percorrer a lista de passageiros
    for (GList *node = catalog->passengers; node != NULL; node = node->next) {
        PASSENGER *passenger = node->data;
        // Se o passageiro tiver o user_id2 pretendido, adicionar o seu flight_id2 à lista
        if (strcmp(get_user_id2(passenger), user_id2) == 0) {
            flights = g_list_prepend(flights, GINT_TO_POINTER(get_flight_id2(passenger)));
        }
    }
    return flights;
}

// TODO testar
GList *find_users_by_flight(PASSENGERS_CATALOG *catalog, int flight_id2) {
    GList *users = NULL;
    // Percorrer a lista de passageiros
    for (GList *node = catalog->passengers; node != NULL; node = node->next) {
        PASSENGER *passenger = node->data;
        // Se o passageiro tiver o flight_id2 pretendido, adicionar o seu user_id2 à lista
        if (get_flight_id2(passenger) == flight_id2) {
            char *copy = strdup(get_user_id2(passenger));
            users = g_list_prepend(users, copy);
        }
    }
    return users;
}

void free_passengers_catalog(PASSENGERS_CATALOG *catalog) {
    // Liberar cada PASSENGER na lista
    g_list_free_full(catalog->passengers, (GDestroyNotify)free_passenger);
    // Liberar o catálogo
    free(catalog);
}