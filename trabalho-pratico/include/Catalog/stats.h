#ifndef STATS_H
#define STATS_H

#include "glib.h"

typedef struct stats STATS;
typedef struct hotel HOTEL;
typedef struct user_name USER_NAME;
typedef struct airportS AIRPORTS;

STATS* create_stats_catalog();
void free_stats(STATS *catalog);
void insert_or_update_hotel(STATS* catalog, char* hotel_id, int rating);
GHashTable *get_hotel_hash(STATS *catalog) ;
char* get_hotel_id_hash(HOTEL* hotel);
int get_hotel_sum_rating(HOTEL* hotel);
int get_hotel_num_reservations(HOTEL* hotel);

USER_NAME* create_user_name(const char* name, const char* user_id, const char* status);

void insert_user_name(STATS *catalog, USER_NAME *user_name);
GList *get_user_name_list(STATS *catalog);

const char *get_user_name_name(const USER_NAME *user);

const char *get_user_name_id(const USER_NAME *user);

const char *get_user_name_status(const USER_NAME *user);

void insert_airportS(STATS *catalog, AIRPORTS *airportS,const char* key);

void add_delay_to_airportS(AIRPORTS* airportS, int delay);

AIRPORTS* create_airportS(const char* origin, int delay);

void insert_or_update_airport(STATS* stats, const char* origin, int delay);

GHashTable *get_airportS_hash(STATS *catalog);
char* get_airport_name(const AIRPORTS* airportS);

GList* get_airport_delay_list (const AIRPORTS* airportS);



#endif // STATS_H