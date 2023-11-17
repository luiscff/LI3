#ifndef RESERVATION_H
#define RESERVATION_H

#include <stdbool.h>

typedef struct reservation RESERVATION;

RESERVATION *create_reservation(void);
void free_reservation(RESERVATION *reservation);

// Getters
const char* get_reservation_id(const RESERVATION *r);
const char* get_user_id(const RESERVATION *r);
const char* get_hotel_id(const RESERVATION *r) ;
const char *get_hotel_name(const RESERVATION *r);
int get_hotel_stars(const RESERVATION *r);
int get_city_tax(const RESERVATION *r);
const char *get_reservation_address(const RESERVATION *r);
const char *get_begin_date(const RESERVATION *r);
const char *get_end_date(const RESERVATION *r);
int get_price_per_night(const RESERVATION *r);
bool get_includes_breakfast(const RESERVATION *r);
const char *get_room_details(const RESERVATION *r);
int get_rating(const RESERVATION *r);
const char *get_comment(const RESERVATION *r);

// Setters
void set_reservation_id(RESERVATION *r, const char *id);
void set_user_id(RESERVATION *r, const char* user_id);
void set_hotel_id(RESERVATION *r, const char* hotel_id);
void set_hotel_name(RESERVATION *r, const char *hotel_name);
void set_hotel_stars(RESERVATION *r, int hotel_stars);
void set_city_tax(RESERVATION *r, int city_tax);
void set_reservation_address(RESERVATION *r, const char *address);
void set_begin_date(RESERVATION *r, const char *begin_date);
void set_end_date(RESERVATION *r, const char *end_date);
void set_price_per_night(RESERVATION *r, int price_per_night);
void set_includes_breakfast(RESERVATION *r, bool includes_breakfast);
void set_room_details(RESERVATION *r, const char *room_details);
void set_rating(RESERVATION *r, int rating);
void set_comment(RESERVATION *r, const char *comment);

// Func
double calc_total_price(RESERVATION *r);
int calc_nights(const char *begin ,const char *end);

#endif // RESERVATION_H