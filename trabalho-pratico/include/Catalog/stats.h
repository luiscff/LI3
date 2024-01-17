#ifndef STATS_H
#define STATS_H

#include "Entities/reservation.h"
#include "Entities/flight.h"
#include "Entities/user.h"
#include "glib.h"

typedef struct stats STATS;
typedef struct hotel HOTEL;
typedef struct dictionary DICTIONARY;
typedef struct airportS AIRPORTS;

STATS* create_stats_catalog();
void free_stats(STATS *catalog);
void insert_or_update_hotel(STATS* catalog, char* hotel_id, int rating,RESERVATION* reservation);
GHashTable *get_hotel_hash(STATS *catalog) ;
char* get_hotel_id_hash(HOTEL* hotel);
int get_hotel_sum_rating(HOTEL* hotel);
int get_hotel_num_reservations(HOTEL* hotel);
GList *get_hotel_reservations_list(HOTEL* hotel);

//DICTIONARY

void insert_or_update_dictionary(STATS* catalog, char* letter, USER* user);
GHashTable *get_dictionary_hash(STATS *catalog);

GList *get_dictionary_values(const DICTIONARY* dictionary);



//AIRPORTS
void insert_airportS(STATS *catalog, AIRPORTS *airportS,const char* key);

void add_delay_to_airportS(AIRPORTS* airportS, int delay);
void add_flight_to_airportS(AIRPORTS* airportS, FLIGHT* flight);
GList* get_flights_list(AIRPORTS* airportS);
AIRPORTS* create_airportS(const char* origin, int delay,FLIGHT* flight);

void insert_or_update_airport(STATS* stats, const char* origin, int delay,FLIGHT* flight);

GHashTable *get_airportS_hash(STATS *catalog);
char* get_airport_name(const AIRPORTS* airportS);

GList* get_airport_delay_list (const AIRPORTS* airportS);
void calculate_and_set_median_for_all(GList* airport_list);
int get_mediana(const AIRPORTS* airportS);

void insert_or_update_pass(STATS* stats,const char* flight_id);



#endif // STATS_H