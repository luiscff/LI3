#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct reservation {
    int id;                   // identificador da reserva (se for 0 é inválido)
    int user_id;              // identificador do utilizador (se for 0 é inválido)
    int hotel_id;             // identificador do hotel (se for 0 é inválido)
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
    new_reservation->id = 0;  // id 0 significa que é inválido
    return new_reservation;
}

void free_reservation(RESERVATION *reservation) {
    free(reservation);
}

// Getters
int get_id(const RESERVATION *r) { return r->id; }
int get_user_id(const RESERVATION *r) { return r->user_id; }
int get_hotel_id(const RESERVATION *r) { return r->hotel_id; }
const char *get_hotel_name(const RESERVATION *r) { return r->hotel_name; }
int get_hotel_stars(const RESERVATION *r) { return r->hotel_stars; }
int get_city_tax(const RESERVATION *r) { return r->city_tax; }
const char *get_address(const RESERVATION *r) { return r->address; }
const char *get_begin_date(const RESERVATION *r) { return r->begin_date; }
const char *get_end_date(const RESERVATION *r) { return r->end_date; }
int get_price_per_night(const RESERVATION *r) { return r->price_per_night; }
bool get_includes_breakfast(const RESERVATION *r) { return r->includes_breakfast; }
const char *get_room_details(const RESERVATION *r) { return r->room_details; }
int get_rating(const RESERVATION *r) { return r->rating; }
const char *get_comment(const RESERVATION *r) { return r->comment; }

// Setters
void set_id(RESERVATION *r, int id) { r->id = id; }
void set_user_id(RESERVATION *r, int user_id) { r->user_id = user_id; }
void set_hotel_id(RESERVATION *r, int hotel_id) { r->hotel_id = hotel_id; }
void set_hotel_name(RESERVATION *r, const char *hotel_name) {
    r->hotel_name = strdup(hotel_name);
}
void set_hotel_stars(RESERVATION *r, int hotel_stars) { r->hotel_stars = hotel_stars; }
void set_city_tax(RESERVATION *r, int city_tax) { r->city_tax = city_tax; }
void set_address(RESERVATION *r, const char *address) {
    r->address = strdup(address);
}
void set_begin_date(RESERVATION *r, const char *begin_date) {
    r->begin_date = strdup(begin_date);
}
void set_end_date(RESERVATION *r, const char *end_date) {
    r->end_date = strdup(end_date);
}
void set_price_per_night(RESERVATION *r, int price_per_night) { r->price_per_night = price_per_night; }
void set_includes_breakfast(RESERVATION *r, bool includes_breakfast) { r->includes_breakfast = includes_breakfast; }
void set_room_details(RESERVATION *r, const char *room_details) {
    r->room_details = strdup(room_details);
}
void set_rating(RESERVATION *r, int rating) { r->rating = rating; }
void set_comment(RESERVATION *r, const char *comment) {
    r->comment = strdup(comment);
}

int main() {
    RESERVATION *r = create_reservation();
    set_id(r, 1);
    set_hotel_name(r, "Hotel California");
    set_address(r, "123 Main St");
    set_begin_date(r, "2022/01/01");
    set_end_date(r, "2022/01/05");
    set_price_per_night(r, 100);
    set_includes_breakfast(r, true);
    set_room_details(r, "King bed, ocean view");

    printf("Reservation ID: %d\n", get_id(r));
    printf("Hotel name: %s\n", get_hotel_name(r));
    printf("Address: %s\n", get_address(r));
    printf("Check-in date: %s\n", get_begin_date(r));
    printf("Check-out date: %s\n", get_end_date(r));
    printf("Price per night: %d\n", get_price_per_night(r));
    printf("Includes breakfast: %s\n", get_includes_breakfast(r) ? "yes" : "no");
    printf("Room details: %s\n", get_room_details(r));

    free_reservation(r);
    return 0;
}