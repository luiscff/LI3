#ifndef USER_H
#define USER_H

enum Account_status
{
    active,
    inactive
};

enum Gender
{
    Male,
    Female
};

enum PaymentMethod
{
    debit_card,
    credit_card,
    cash
};

typedef struct user USER;

// Setters
void set_id(USER *user, int id);
void set_name(USER *user, const char *name);
void set_email(USER *user, const char *email);
void set_birth_date(USER *user, const char *birth_date);
void set_phone_number(USER *user, const char *phone_number);
void set_gender(USER *user, enum Gender gender);
void set_passport(USER *user, const char *passport);
void set_country_code(USER *user, const char *country_code);
void set_address(USER *user, const char *address);
void set_account_creation(USER *user, const char *account_creation);
void set_payment_method(USER *user, enum PaymentMethod payment_method);
void set_active_status(USER *user, enum Account_status active_status);

// Getters
int get_id(const USER *user);
const char *get_name(const USER *user);
const char *get_email(const USER *user);
const char *get_birth_date(const USER *user);
const char *get_phone_number(const USER *user);
enum Gender get_gender(const USER *user);
const char *get_passport(const USER *user);
const char *get_country_code(const USER *user);
const char *get_address(const USER *user);
const char *get_account_creation(const USER *user);
enum PaymentMethod get_payment_method(const USER *user);
enum Account_status get_active_status(const USER *user);

#endif // USER_H