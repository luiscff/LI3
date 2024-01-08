#ifndef STATS_H
#define STATS_H

#include "glib.h"

typedef struct stats STATS;
typedef struct hotel HOTEL;

STATS* create_stats_catalog();
void free_stats(STATS *catalog);
void insert_or_update_hotel(STATS* catalog, char* hotel_id, int rating);
GHashTable *get_hotel_hash(STATS *catalog) ;
char* get_hotel_id_hash(HOTEL* hotel);

int get_hotel_sum_rating(HOTEL* hotel);
int get_hotel_num_reservations(HOTEL* hotel);



#endif // STATS_H