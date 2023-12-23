#ifndef USER_H
#define USER_H

typedef struct user USER;

USER * create_user();
void free_user(USER *user);

// Setters
void set_id(USER *user, const char *id);
void set_name(USER *user, const char *name);
void set_email(USER *user, const char *email);
void set_birth_date(USER *user, const char *birth_date);
void set_phone_number(USER *user, const char *phone_number);
void set_gender(USER *user, const char *gender);
void set_passport(USER *user, const char *passport);
void set_country_code(USER *user, const char *country_code);
void set_address(USER *user, const char *address);
void set_account_creation(USER *user, const char *account_creation);
void set_payment_method(USER *user, const char *payment_method);
void set_active_status(USER *user, const char *active_status);

// Getters
const char* get_id(const USER *user);
const char *get_name(const USER *user);
const char *get_email(const USER *user);
const char *get_birth_date(const USER *user);
const char *get_phone_number(const USER *user);
const char *get_gender(const USER *user);
const char *get_passport(const USER *user);
const char *get_country_code(const USER *user);
const char *get_address(const USER *user);
const char *get_account_creation(const USER *user);
const char *get_payment_method(const USER *user);
const char *get_active_status(const USER *user);
double get_total_spent(const USER *user);
int get_num_reservations(const USER *user);

// adiciona um valor ao total gasto pelo utilizador
void add_total_spent(USER *user, double total_spent);

// adiciona uma reserva ao utilizador
void add_reservation(USER *user);

#endif // USER_H