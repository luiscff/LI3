#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Catalog/stats.h"

typedef struct stats {
    GHashTable *hotel_hash;
} STATS;

typedef struct hotel
{
   char* hotel_id;
   int sum_rating;
   int num_reservations;
}HOTEL;


void free_hotel(HOTEL *hotel) {
    if (hotel->hotel_id) free(hotel->hotel_id);
    if (hotel) free(hotel);
}

STATS* create_stats_catalog() {
    STATS *new_catalog = malloc(sizeof(STATS));

    new_catalog->hotel_hash = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                                 (GDestroyNotify)free_hotel);

    return new_catalog;
}

void free_stats(STATS *catalog) {
    g_hash_table_destroy(catalog->hotel_hash);
    free(catalog);
}

///HOTEL

HOTEL* create_hotel(char* hotel_id, int rating){
    HOTEL* hotel = malloc(sizeof(HOTEL));
    if(hotel){
        hotel->hotel_id = hotel_id;
        hotel->sum_rating = rating;
        hotel->num_reservations = 1;
    }
    return hotel;

}



void insert_hotel(STATS *catalog, HOTEL *hotel, char* key) {
    g_hash_table_insert(catalog->hotel_hash, strdup(key), hotel);
}

void update_hotel (STATS *catalog, char* hotel_id, int rating){
    HOTEL *curr = g_hash_table_lookup(catalog->hotel_hash,hotel_id);
    curr->sum_rating += rating;
    curr->num_reservations++;
}

void insert_or_update_hotel(STATS* catalog, char* hotel_id, int rating){
    HOTEL* hotel = g_hash_table_lookup(catalog->hotel_hash,hotel_id);
    if (hotel == NULL) {
                            HOTEL* hotel = create_hotel(hotel_id,rating);
                            insert_hotel(catalog,hotel,hotel_id);
                        }
    else  update_hotel(catalog,hotel_id,rating);
}

GHashTable *get_hotel_hash(STATS *catalog) {
    return catalog->hotel_hash;
}

void set_hotel_id_hash(HOTEL *hotel, const char *hotel_id) {
    if (hotel->hotel_id) free(hotel->hotel_id);
    hotel->hotel_id = strdup(hotel_id);
}

char* get_hotel_id_hash(HOTEL* hotel){
    return hotel->hotel_id;
}

int get_hotel_sum_rating(HOTEL* hotel){
    if (hotel == NULL) return 0;
    else return hotel->sum_rating;
}

int get_hotel_num_reservations(HOTEL* hotel){
    if (hotel == NULL) return 0;
    else return hotel->num_reservations;
}

HOTEL *get_hotel_by_hotel_id(STATS *catalog, const char *hotel_id) {
    HOTEL* res = g_hash_table_lookup(catalog->hotel_hash, hotel_id);
    return res;
}



