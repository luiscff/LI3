#include "Entities/reservation.h"

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct reservation {
    char *reservation_id;  // identificador da reserva (se for 0 é inválido)
    char *user_id;              // identificador do utilizador (se for 0 é inválido)
    char *hotel_id;             // identificador do hotel (se for 0 é inválido)
    char *hotel_name;         // nome do hotel
    int hotel_stars;          // número de estrelas do hotel de 1 a 5
    int city_tax;             // percentagem do imposto da cidade (sobre o valor total)
    char *address;            // morada do hotel
    char *begin_date;         // data de início formato é aaaa/mm/dd
    char *end_date;           // data de fim formato é aaaa/mm/dd
    int price_per_night;      // preço por noite
    bool includes_breakfast;  // se a reserva inclui pequeno-almoço
    char *room_details;       // detalhes sobre o quarto
    int rating;               // classificação atribuída pelo utilizador de 1 a 5
    char *comment;            // comentário sobre a reserva
} RESERVATION;

RESERVATION *create_reservation(void) {
    RESERVATION *new_reservation = malloc(sizeof(struct reservation));
    if (new_reservation) {
        new_reservation->reservation_id = NULL;
        new_reservation->user_id = NULL;
        new_reservation->hotel_id = NULL;
        new_reservation->hotel_name = NULL;
        new_reservation->address = NULL;
        new_reservation->begin_date = NULL;
        new_reservation->end_date = NULL;
        new_reservation->room_details = NULL;
        new_reservation->comment = NULL;
        new_reservation->hotel_stars = 0;
        new_reservation->city_tax = 0;
        new_reservation->price_per_night = 0;
        new_reservation->includes_breakfast = false;
        new_reservation->rating = 0;
    }
    return new_reservation;
}

void free_reservation(RESERVATION *reservation) {
    if (reservation->reservation_id) free(reservation->reservation_id);
    if (reservation->user_id) free(reservation->user_id);
    if (reservation->hotel_id) free(reservation->hotel_id);
    if (reservation->hotel_name) free(reservation->hotel_name);
    if (reservation->address) free(reservation->address);
    if (reservation->begin_date) free(reservation->begin_date);
    if (reservation->end_date) free(reservation->end_date);
    if (reservation->room_details) free(reservation->room_details);
    if (reservation->comment) free(reservation->comment);
    if (reservation) free(reservation);
}

// Getters
const char* get_reservation_id(const RESERVATION *r) { return r->reservation_id; }
const char* get_user_id(const RESERVATION *r) { return r->user_id; }
const char* get_hotel_id(const RESERVATION *r) { return r->hotel_id; }
const char *get_hotel_name(const RESERVATION *r) { return r->hotel_name; }
int get_hotel_stars(const RESERVATION *r) { return r->hotel_stars; }
int get_city_tax(const RESERVATION *r) { return r->city_tax; }
const char *get_reservation_address(const RESERVATION *r) { return r->address; }
const char *get_begin_date(const RESERVATION *r) { return r->begin_date; }
const char *get_end_date(const RESERVATION *r) { return r->end_date; }
int get_price_per_night(const RESERVATION *r) { return r->price_per_night; }
bool get_includes_breakfast(const RESERVATION *r) { return r->includes_breakfast; }
const char *get_room_details(const RESERVATION *r) { return r->room_details; }
int get_rating(const RESERVATION *r) { return r->rating; }
const char *get_comment(const RESERVATION *r) { return r->comment; }

// Setters
void set_reservation_id(RESERVATION *r, const char *reservation_id_string) {
    if (r->reservation_id) free(r->reservation_id);
    r->reservation_id = strdup(reservation_id_string);
}
void set_user_id(RESERVATION *r, const char* user_id) { 
    if (r->user_id) free(r->user_id);
    r->user_id = strdup(user_id);
 }
void set_hotel_id(RESERVATION *r, const char* hotel_id) { 
    if (r->hotel_id) free(r->hotel_id);
    r->hotel_id = strdup(hotel_id);
 }
void set_hotel_name(RESERVATION *r, const char *hotel_name) {
    if (r->hotel_name) free(r->hotel_name);
    r->hotel_name = strdup(hotel_name);
}
void set_hotel_stars(RESERVATION *r, int hotel_stars) { r->hotel_stars = hotel_stars; }
void set_city_tax(RESERVATION *r, int city_tax) { r->city_tax = city_tax; }
void set_reservation_address(RESERVATION *r, const char *address) {
    if (r->address) free(r->address);
    r->address = strdup(address);
}
void set_begin_date(RESERVATION *r, const char *begin_date) {
    if (r->begin_date) free(r->begin_date);
    r->begin_date = strdup(begin_date);
}
void set_end_date(RESERVATION *r, const char *end_date) {
    if (r->end_date) free(r->end_date);
    r->end_date = strdup(end_date);
}
void set_price_per_night(RESERVATION *r, int price_per_night) { r->price_per_night = price_per_night; }
void set_includes_breakfast(RESERVATION *r, bool includes_breakfast) { r->includes_breakfast = includes_breakfast; }
void set_room_details(RESERVATION *r, const char *room_details) {
    if (r->room_details) free(r->room_details);
    r->room_details = strdup(room_details);
}
void set_rating(RESERVATION *r, int rating) { r->rating = rating; }
void set_comment(RESERVATION *r, const char *comment) {
    if (r->comment) free(r->comment);
    r->comment = strdup(comment);
}

double calc_total_price(RESERVATION *r){
    int tax = get_city_tax(r);
    int ppn = get_price_per_night(r);
    double total_price = 0;
    const char* begin = get_begin_date(r);
    const char* end = get_end_date(r);
    int num_nights = calc_nights(begin,end);
    
    total_price = ppn * num_nights * ((ppn * num_nights) /100) * tax;

    return total_price;
}

int calc_nights(const char *begin ,const char *end){
    int year1, month1, day1;
    int year2, month2, day2;
    sscanf(begin, "%4d/%2d/%2d", &year1, &month1, &day1);
    sscanf(end, "%4d/%2d/%2d", &year2, &month2, &day2);
    int m = month2 - month1;
    int y = year2 - year1;
    
    return 365 * y + 30 * m + day2 - day1;
}