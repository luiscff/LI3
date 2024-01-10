#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Catalog/stats.h"

typedef struct stats {
    GHashTable *hotel_hash;
    GList *user_name;
    GHashTable *airports_hash;
} STATS;

typedef struct hotel
{
   char* hotel_id;
   int sum_rating;
   int num_reservations;
}HOTEL;

typedef struct user_name{
    char* name;
    char* id;
    char* status;
}USER_NAME;

typedef struct airportS{
    char* origin;
    GList* delays;
}AIRPORTS;


void free_hotel(HOTEL *hotel) {
    if (hotel->hotel_id) free(hotel->hotel_id);
    if (hotel) free(hotel);
}

void free_airportS(AIRPORTS *airportS) {
    if (airportS->origin) free(airportS->origin);
    if (airportS->delays) g_list_free(airportS->delays);
    if (airportS) free(airportS);
}



STATS* create_stats_catalog() {
    STATS *new_catalog = malloc(sizeof(STATS));

    new_catalog->hotel_hash = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                                 (GDestroyNotify)free_hotel);
    new_catalog->user_name = NULL;
    new_catalog->airports_hash = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                                 (GDestroyNotify)free_airportS);
    return new_catalog;
}

void free_user_name(USER_NAME *user_name) {
    if (user_name) {
        if (user_name->name) free(user_name->name);
        if (user_name->id) free(user_name->id);
        if (user_name->status) free(user_name->status);
        free(user_name);
    }
}

void free_stats(STATS *catalog) {
    g_hash_table_destroy(catalog->hotel_hash);
    g_list_free_full(catalog->user_name, (GDestroyNotify)free_user_name);
    g_hash_table_destroy(catalog->airports_hash);
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


//USER_NAME

USER_NAME* create_user_name(const char* name, const char* user_id, const char* status){
    USER_NAME* user_name = malloc(sizeof(USER_NAME));
    if(user_name){
        user_name->name =strdup(name);
        user_name->id = strdup(user_id);
        user_name->status = strdup(status);
    }
    return user_name;
}

void insert_user_name(STATS *catalog, USER_NAME *user_name) {
    catalog->user_name = g_list_append(catalog->user_name, user_name);
}



GList *get_user_name_list(STATS *catalog) {
    return catalog->user_name;
}

const char *get_user_name_name(const USER_NAME *user) {
    return user->name;
}

const char *get_user_name_id(const USER_NAME *user) {
    return user->id;
}

const char *get_user_name_status(const USER_NAME *user) {
    return user->status;
}

        
// AIRPORT

void insert_airportS(STATS *catalog, AIRPORTS *airportS,const char* key) {
    g_hash_table_insert(catalog->airports_hash, strdup(key), airportS);
}

void add_delay_to_airportS(AIRPORTS* airportS, int delay){
    airportS->delays = g_list_append(airportS->delays,GINT_TO_POINTER(delay));
}

AIRPORTS* create_airportS(const char* origin, int delay){
    AIRPORTS* airportS = malloc(sizeof(AIRPORTS));
    if(airportS){
        airportS->origin = strdup(origin);
        airportS->delays = NULL;
        airportS->delays = g_list_append(airportS->delays,GINT_TO_POINTER(delay));
    }
    return airportS;
}

void insert_or_update_airport(STATS* stats, const char* origin, int delay){
    AIRPORTS* airportS = g_hash_table_lookup(stats->airports_hash, origin);
    if (airportS == NULL) {
        AIRPORTS* new_airportS = create_airportS(origin,delay);
        insert_airportS(stats,new_airportS, origin);
    }
    else add_delay_to_airportS(airportS,delay);
}

GHashTable *get_airportS_hash(STATS *catalog) {
    return catalog->airports_hash;
}

char* get_airport_name(const AIRPORTS* airportS){
    return airportS->origin;
}

GList* get_airport_delay_list (const AIRPORTS* airportS){
    return airportS->delays;
}





