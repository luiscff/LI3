#include "Entities/user.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>


typedef struct user
{
    char *id;
    char *name;
    char *email;
    char *birth_date; // formato é aaaa/mm/dd
    char *phone_number;
    enum Gender gender;
    char *passport;
    char *country_code;
    char *address;
    char *account_creation;
    enum PaymentMethod payment_method;
    enum Account_status active_status;
} USER;


USER * create_user() {
    USER *new_user = malloc(sizeof(struct user));
    return new_user;
}

void free_user(USER *user) {
    free(user->id);
    free(user->name);
    free(user->email);
    free(user->birth_date);
    free(user->phone_number);
    free(user->passport);
    free(user->country_code);
    free(user->address);
    free(user->account_creation);
    free(user);
}



void set_id(USER *user, const char *id) {
    user->id = strdup(id);
}

void set_name(USER *user, const char *name) {
     user->name = strdup(name);
}

void set_email(USER *user, const char *email) {
     user->email = strdup(email);
}


void set_birth_date(USER *user, const char *birth_date) {
    user->birth_date = strdup(birth_date);
}

void set_phone_number(USER *user, const char *phone_number) {
     user->phone_number = strdup(phone_number);
}

void set_gender(USER *user, enum Gender gender) {
    user->gender = gender;
}

void set_passport(USER *user, const char *passport) {
     user->passport = strdup(passport);
}

void set_country_code(USER *user, const char *country_code) {
     user->country_code = strdup(country_code);
}

void set_address(USER *user, const char *address) {
     user->address = strdup(address);
}

void set_account_creation(USER *user, const char *account_creation) {
     user->account_creation = strdup(account_creation);
}

void set_payment_method(USER *user, enum PaymentMethod payment_method) {
    user->payment_method = payment_method;
}

void set_active_status(USER *user, enum Account_status active_status) {
    user->active_status = active_status;
}

const char *get_birth_date(const USER *user) {
    return user->birth_date;
}

const char *get_phone_number(const USER *user) {
    return user->phone_number;
}

enum Gender get_gender(const USER *user) {
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

enum PaymentMethod get_payment_method(const USER *user) {
    return user->payment_method;
}

enum Account_status get_active_status(const USER *user) {
    return user->active_status;
}

const char* get_id(const USER *user) {
    return user->id;
}

const char *get_name(const USER *user) {
    return user->name;
}

const char *get_email(const USER *user) {
    return user->email;
}

