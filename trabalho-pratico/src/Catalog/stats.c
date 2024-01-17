#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Catalog/stats.h"



typedef struct stats {
    GHashTable *hotel_hash;
    GHashTable *dictionary_hash;
    GHashTable *airports_hash;
    GHashTable *flight_passangers;
} STATS;

typedef struct hotel
{
   char* hotel_id;
   int sum_rating;
   int num_reservations;
   GList* reservations;
}HOTEL;


typedef struct airportS{
    char* origin;
    GList* delays;
    int mediana;
    GList* flights;
}AIRPORTS;

typedef struct flight_pass
{
   char* flight_id;
   int passageiros;
}FLIGHT_PASS;


typedef struct dictionary{
    char* letter;
    GList* users;
}DICTIONARY;
void free_hotel(HOTEL *hotel) {
    if (hotel->hotel_id) free(hotel->hotel_id);
    if (hotel->reservations) g_list_free(hotel->reservations);
    if (hotel) free(hotel);
}

void free_airportS(AIRPORTS *airportS) {
    if (airportS->origin) free(airportS->origin);
    if (airportS->delays) g_list_free(airportS->delays);
    if (airportS->flights) g_list_free(airportS->flights);
    if (airportS) free(airportS);
}

void free_passangers(FLIGHT_PASS *flight_pass) {
    if (flight_pass) free(flight_pass);
}

void free_dictionary(DICTIONARY* dictionary) {
    if (dictionary) {
        if (dictionary->letter) free(dictionary->letter);
        if (dictionary->users) free(dictionary->users);
        free(dictionary);
    }
}



STATS* create_stats_catalog() {
    STATS *new_catalog = malloc(sizeof(STATS));

    new_catalog->hotel_hash = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                                 (GDestroyNotify)free_hotel);
    new_catalog->dictionary_hash=  g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                                 (GDestroyNotify)free_dictionary);
    new_catalog->airports_hash = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                                 (GDestroyNotify)free_airportS);

    new_catalog->flight_passangers = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                                 (GDestroyNotify)free_passangers);

    return new_catalog;
}



void free_stats(STATS *catalog) {
    g_hash_table_destroy(catalog->hotel_hash);
    g_hash_table_destroy(catalog->dictionary_hash);
    g_hash_table_destroy(catalog->flight_passangers);
    g_hash_table_destroy(catalog->airports_hash);
    free(catalog);
}

///HOTEL

HOTEL* create_hotel(char* hotel_id, int rating,RESERVATION* reservation){
    HOTEL* hotel = malloc(sizeof(HOTEL));
    if(hotel){
        hotel->hotel_id = hotel_id;
        hotel->sum_rating = rating;
        hotel->num_reservations = 1;
        hotel->reservations = NULL;
        hotel->reservations = g_list_append(hotel->reservations,reservation);
    }
    return hotel;

}

void insert_hotel(STATS *catalog, HOTEL *hotel, char* key) {
    g_hash_table_insert(catalog->hotel_hash, strdup(key), hotel);
}

void update_hotel(STATS *catalog, char *hotel_id, int rating, RESERVATION *reservation) {
    HOTEL *curr = g_hash_table_lookup(catalog->hotel_hash, hotel_id);
    curr->sum_rating += rating;
    curr->reservations = g_list_append(curr->reservations, reservation);
    curr->num_reservations++;
    // Append the reservation to the list and update the HOTEL structure
   
}

void insert_or_update_hotel(STATS* catalog, char* hotel_id, int rating,RESERVATION* reservation){
    HOTEL* hotel = NULL;
    hotel = g_hash_table_lookup(catalog->hotel_hash,hotel_id);
    if (hotel == NULL) {
                            HOTEL* hotel = create_hotel(hotel_id,rating,reservation);
                            insert_hotel(catalog,hotel,hotel_id);
                        }
    else  update_hotel(catalog,hotel_id,rating,reservation);

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

GList *get_hotel_reservations_list(HOTEL* hotel) {
    
    GList* list = hotel->reservations;
    return list;
}


//Dictiniorary


DICTIONARY* create_page(const char* letter, USER* user){
    DICTIONARY* dictionary = malloc(sizeof(DICTIONARY));
    if(dictionary){
        dictionary->letter =strdup(letter);
        dictionary->users=NULL;
        dictionary->users = g_list_append(dictionary->users,user);
    }
    return dictionary;
}

void insert_page(STATS *catalog, char* letter,DICTIONARY *dictionary) {
    g_hash_table_insert(catalog->dictionary_hash , letter,dictionary);
}



GHashTable *get_dictionary_hash(STATS *catalog) {
    return catalog->dictionary_hash;
}

GList *get_dictionary_values(const DICTIONARY* dictionary) {
    return dictionary->users;
}

void insert_or_update_dictionary(STATS* catalog, char* letter, USER* user){
    DICTIONARY* curr = g_hash_table_lookup(catalog->dictionary_hash,letter);
    if (curr == NULL) {
                        DICTIONARY* new_page= create_page(letter,user);
                        insert_page(catalog,letter,new_page);

    }
    else {
        curr->users = g_list_append(curr->users,user);
    }

}

        
// AIRPORT

void insert_airportS(STATS *catalog, AIRPORTS *airportS,const char* key) {
    g_hash_table_insert(catalog->airports_hash, strdup(key), airportS);
}

void add_delay_to_airportS(AIRPORTS* airportS, int delay){
    airportS->delays = g_list_append(airportS->delays,GINT_TO_POINTER(delay));
}


void add_flight_to_airportS(AIRPORTS* airportS, FLIGHT* flight){
    airportS->flights = g_list_append(airportS->flights,flight);
}


GList* get_flights_list(AIRPORTS* airportS){
    return airportS->flights;
}

AIRPORTS* create_airportS(const char* origin, int delay,FLIGHT* flight){
    AIRPORTS* airportS = malloc(sizeof(AIRPORTS));
    if(airportS){
        airportS->origin = strdup(origin);
        airportS->delays = NULL;
        add_delay_to_airportS(airportS,delay);
        airportS->flights=NULL;
        add_flight_to_airportS(airportS,flight);
        airportS->mediana=0;
    }
    return airportS;
}

void insert_or_update_airport(STATS* stats, const char* origin, int delay,FLIGHT* flight){
    AIRPORTS* airportS = g_hash_table_lookup(stats->airports_hash, origin);
    if (airportS == NULL) {
        AIRPORTS* new_airportS = create_airportS(origin,delay,flight);
        insert_airportS(stats,new_airportS, origin);
    }
    else {
            add_delay_to_airportS(airportS,delay);
            //if (get_flight_id(flight) == 70 || get_flight_id(flight) == 938|| get_flight_id(flight) == 487||get_flight_id(flight) == 398) printf ("\n ESTA AQUI %d : %s \nDEPARTURE:%s\nARRIVAL: %s\n\n",get_flight_id(flight), get_origin(flight),get_schedule_departure_date(flight),get_schedule_arrival_date(flight));
            add_flight_to_airportS(airportS,flight);
         }
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


int compare_ints2(gconstpointer a, gconstpointer b) {
    int int_a = GPOINTER_TO_INT(a);
    int int_b = GPOINTER_TO_INT(b);

    if (int_a < int_b) {
        return -1;
    } else if (int_a > int_b) {
        return 1;
    } else {
        return 0;
    }
}

void calculate_and_set_median(AIRPORTS* airport) {
    // Ensure that the delays list is not empty
    if (airport->delays == NULL || g_list_length(airport->delays) == 0) {
        printf("Error: Delays list is empty.\n");
        return;
    }

    // Sort the delays list
    airport->delays = g_list_sort(airport->delays, compare_ints2);

    guint size = g_list_length(airport->delays);

    // Calculate the median
    if (size % 2 == 0) {
        // Número par de elementos, calcular a média dos dois valores do meio
        int middle1 = GPOINTER_TO_INT(g_list_nth_data(airport->delays, size / 2 - 1));
        int middle2 = GPOINTER_TO_INT(g_list_nth_data(airport->delays, size / 2));
        airport->mediana = (middle1 + middle2) / 2;
    } else {
        // Número ímpar de elementos, a mediana é o valor do meio
        airport->mediana = GPOINTER_TO_INT(g_list_nth_data(airport->delays, size / 2));
    }
}

void calculate_and_set_median_for_one(gpointer data, gpointer user_data) {
    AIRPORTS* airport = (AIRPORTS*)data;
    calculate_and_set_median(airport);
}

void calculate_and_set_median_for_all(GList* airport_list) {
    // Apply the callback function to each element in the list
    g_list_foreach(airport_list, calculate_and_set_median_for_one, NULL);
}

int get_mediana(const AIRPORTS* airportS){
    return airportS->mediana;
}



///PASSANGERS : struct que vai guardar todos os ids dos passageiros de um voo

FLIGHT_PASS* create_flight_pass(const char* flight_id){
    FLIGHT_PASS* flight_pass = malloc(sizeof(FLIGHT_PASS));
    if(flight_pass){
        flight_pass->flight_id = strdup(flight_id);
        flight_pass->passageiros = 1;
    }
    return flight_pass;
}


void insert_or_update_pass(STATS* stats,const char* flight_id){
    FLIGHT_PASS* curr = g_hash_table_lookup(stats->flight_passangers,flight_id);
    if (curr == NULL) {
        create_flight_pass(flight_id);
        g_hash_table_insert(stats->flight_passangers, strdup(flight_id), curr);
        printf("\nCREATED\n");
    }
    else {curr->passageiros++;
            printf("\nUPDATED\n");}
}
