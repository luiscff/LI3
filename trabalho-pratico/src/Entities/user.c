#include "Entities/user.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {
    char *id;
    char *name;
    char *email;
    char *birth_date;  // formato é aaaa/mm/dd
    char *phone_number;
    char *gender;
    char *passport;
    char *country_code;
    char *address;
    char *account_creation;
    char *payment_method;
    char *active_status;
    double total_spent;
    int num_reservations;
    GList *reservations;
    GList *flights;
} USER;

USER *create_user() {
    USER *new_user = malloc(sizeof(struct user));
    if (new_user) {
        new_user->id = NULL;
        new_user->name = NULL;
        new_user->email = NULL;
        new_user->birth_date = NULL;
        new_user->phone_number = NULL;
        new_user->gender = NULL;
        new_user->passport = NULL;
        new_user->country_code = NULL;
        new_user->address = NULL;
        new_user->account_creation = NULL;
        new_user->payment_method = NULL;
        new_user->active_status = NULL;
        new_user->total_spent = 0;
        new_user->num_reservations = 0;
        new_user->reservations = NULL;
        new_user->flights = NULL;
    }
    return new_user;
}

void free_user(USER *user) {
    if (user->id) free(user->id);
    if (user->name) free(user->name);
    if (user->email) free(user->email);
    if (user->birth_date) free(user->birth_date);
    if (user->phone_number) free(user->phone_number);
    if (user->gender) free(user->gender);
    if (user->passport) free(user->passport);
    if (user->country_code) free(user->country_code);
    if (user->address) free(user->address);
    if (user->account_creation) free(user->account_creation);
    if (user->payment_method) free(user->payment_method);
    if (user->active_status) free(user->active_status);

    if (user->reservations) {
        g_list_foreach(user->reservations, (GFunc)free, NULL);
        g_list_free(user->reservations);
    }
    if (user->flights) {
        g_list_foreach(user->flights, (GFunc)free, NULL);
        g_list_free(user->flights);
    }
    if (user) free(user);
}

void set_id(USER *user, const char *id) {
    if (user->id) free(user->id);
    user->id = strdup(id);
}

void set_name(USER *user, const char *name) {
    if (user->name) free(user->name);
    user->name = strdup(name);
}

void set_email(USER *user, const char *email) {
    if (user->email) free(user->email);
    user->email = strdup(email);
}

void set_birth_date(USER *user, const char *birth_date) {
    if (user->birth_date) free(user->birth_date);
    user->birth_date = strdup(birth_date);
}

void set_phone_number(USER *user, const char *phone_number) {
    if (user->phone_number) free(user->phone_number);
    user->phone_number = strdup(phone_number);
}

void set_gender(USER *user, const char *gender) {
    if (user->gender) free(user->gender);
    user->gender = strdup(gender);
}

void set_passport(USER *user, const char *passport) {
    if (user->passport) free(user->passport);
    user->passport = strdup(passport);
}

void set_country_code(USER *user, const char *country_code) {
    if (user->country_code) free(user->country_code);
    user->country_code = strdup(country_code);
}

void set_address(USER *user, const char *address) {
    if (user->address) free(user->address);
    user->address = strdup(address);
}

void set_account_creation(USER *user, const char *account_creation) {
    if (user->account_creation) free(user->account_creation);
    user->account_creation = strdup(account_creation);
}

void set_payment_method(USER *user, const char *payment_method) {
    if (user->payment_method) free(user->payment_method);
    user->payment_method = strdup(payment_method);
}

void set_active_status(USER *user, const char *active_status) {
    if (user->active_status) free(user->active_status);
    user->active_status = strdup(active_status);
}

const char *get_birth_date(const USER *user) {
    return user->birth_date;
}

const char *get_phone_number(const USER *user) {
    return user->phone_number;
}

const char *get_gender(const USER *user) {
    return user->gender;
}

const char *get_passport(const USER *user) {
    return user->passport;
}

const char *get_country_code(const USER *user) {
    return user->country_code;
}

const char *get_address(const USER *user) {
    return user->address;
}

const char *get_account_creation(const USER *user) {
    return user->account_creation;
}

const char *get_payment_method(const USER *user) {
    return user->payment_method;
}

const char *get_active_status(const USER *user) {
    return user->active_status;
}

const char *get_id(const USER *user) {
    return user->id;
}

const char *get_name(const USER *user) {
    return user->name;
}

const char *get_email(const USER *user) {
    return user->email;
}

double get_total_spent(const USER *user) {
    return user->total_spent;
}

int get_num_reservations(const USER *user) {
    return user->num_reservations;
}

GList *get_reservations(const USER *user) {
    return user->reservations;
}

GList *get_flights(const USER *user) {
    return user->flights;
}

// STATS

// adiciona um valor ao total gasto pelo utilizador
void add_total_spent(USER *user, double total_spent) {
    user->total_spent += total_spent;
}

// adiciona uma reserva ao utilizador
void add_num_reservations(USER *user) {
    user->num_reservations++;
}

// adiciona um voo à lista de voos do utilizador
void add_flight(USER *user, char *flight_id) {
    user->flights = g_list_append(user->flights, strdup(flight_id));
    free(flight_id);
}

// remove um voo da lista de voos do utilizador
void remove_flight(USER *user, const char *flight_id) {
    user->flights = g_list_remove(user->flights, strdup(flight_id));
}

// adiciona uma reserva à lista de reservas do utilizador e adiciona 1 ao numero de reservas
void add_reservation(USER *user, const char *reservation_id) {
    user->reservations = g_list_append(user->reservations, strdup(reservation_id));
    user->num_reservations++;
}

// remove uma reserva da lista de reservas do utilizador
void remove_reservation(USER *user, const char *reservation_id) {
    user->reservations = g_list_remove(user->reservations, strdup(reservation_id));
}