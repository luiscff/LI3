#include "Entities/user.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <glib.h>

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

typedef struct user
{
    int id;
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


void set_id(USER *user, int id) {
    user->id = id;
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

int get_id(const USER *user) {
    return user->id;
}

const char *get_name(const USER *user) {
    return user->name;
}

const char *get_email(const USER *user) {
    return user->email;
}

int main() {
    USER user1;
    char nome[256];
    char email[256];
    char data_nascimento[10];
    char telefone[12];
    enum Gender genero;
    int genero2;
    char passaporte[8];
    char codigo_pais[3];
    char endereco[256];
    char data_criacao[20];
    int paymentChoice;
    int statusChoice;

    printf("Nome: ");
    scanf("%s", nome);
    set_name(&user1, nome);

    printf("Email: ");
    scanf("%s", email);
    set_email(&user1, email);

    printf("Data de nascimento (aaaa/mm/dd): ");
    scanf("%s", data_nascimento);
    set_birth_date(&user1, data_nascimento);

    printf("Telefone: ");
    scanf("%s", telefone);
    set_phone_number(&user1, telefone);

    printf("Gênero (1 - Male, 2 - Female): ");
    scanf("%d", &genero2);
    set_gender(&user1, genero2 == 1 ? Male : Female);

    printf("Passaporte: ");
    scanf("%s", passaporte);
    set_passport(&user1, passaporte);

    printf("Código do país: ");
    scanf("%s", codigo_pais);
    set_country_code(&user1, codigo_pais);

    printf("Endereço: ");
    scanf("%s", endereco);
    set_address(&user1, endereco);

    printf("Data de criação: ");
    scanf("%s", data_criacao);
    set_account_creation(&user1, data_criacao);

    printf("Escolha um método de pagamento:\n");
    printf("1. Debit Card\n");
    printf("2. Credit Card\n");
    printf("3. Cash\n");
    printf("Digite o número correspondente ao método de pagamento: ");
    scanf("%d", &paymentChoice);

    switch (paymentChoice) {
        case 1:
            set_payment_method(&user1, debit_card);
            break;
        case 2:
            set_payment_method(&user1, credit_card);
            break;
        case 3:
            set_payment_method(&user1, cash);
            break;
        default:
            printf("Escolha inválida.\n");
            return 1; // Saída do programa com erro
    }

    printf("Escolha o status (1 - Active, 2 - Inactive): ");
    scanf("%d", &statusChoice);

    switch (statusChoice) {
        case 1:
            set_active_status(&user1, active);
            break;
        case 2:
            set_active_status(&user1, inactive);
            break;
        default:
            printf("Escolha inválida.\n");
            return 1; // Saída do programa com erro
    }

    // Teste das funções get para acessar os campos e imprimir os valores
    printf("User ID: %d\n", get_id(&user1));
    printf("User Name: %s\n", get_name(&user1));
    printf("User Email: %s\n", get_email(&user1));
    printf("User Birth Date: %s\n", get_birth_date(&user1));
    printf("User Phone Number: %s\n", get_phone_number(&user1));

    enum Gender gender = get_gender(&user1);
    printf("User Gender: %s\n", gender == Male ? "Male" : "Female");

    printf("User Passport: %s\n", get_passport(&user1));
    printf("User Country Code: %s\n", get_country_code(&user1));
    printf("User Address: %s\n", get_address(&user1));
    printf("User Account Creation: %s\n", get_account_creation(&user1));

    enum PaymentMethod payment_method = get_payment_method(&user1);
    printf("User Payment Method: %s\n", payment_method == debit_card ? "Debit Card" :
                                           payment_method == credit_card ? "Credit Card" : "Cash");

    enum Account_status active_status = get_active_status(&user1);
    printf("User Active Status: %s\n", active_status == active ? "Active" : "Inactive");

    return 0;
}