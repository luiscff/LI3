#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_NAME 256
#define MAX_EMAIL 256
#define MAX_PHONE 12
#define MAX_ADDRESS 256
#define MAX_BIRTH_DATE 10
#define MAX_PASSPORT 8
#define MAX_COUNTRY_CODE 2
#define MAX_DATE_TIME 20

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

typedef struct users
{
    int id;
    char name[MAX_NAME];
    char email[MAX_EMAIL];
    char birth_date[MAX_BIRTH_DATE]; // formato é aaaa/mm/dd
    char phone_number[MAX_PHONE];
    enum Gender gender;
    char passport[MAX_PASSPORT];
    char country_code[MAX_COUNTRY_CODE];
    char address[MAX_ADDRESS];
    char account_creation[MAX_DATE_TIME];
    enum PaymentMethod payment_method;
    enum Account_status active_status;
} Users;


void set_id(Users *user, int id) {
    user->id = id;
}

void set_name(Users *user, const char *name) {
    strncpy(user->name, name, MAX_NAME);
    user->name[MAX_NAME - 1] = '\0'; // Certifica-se de que a string esteja terminada corretamente.
}

void set_email(Users *user, const char *email) {
    strncpy(user->email, email, MAX_EMAIL);
    user->email[MAX_EMAIL - 1] = '\0';
}


void set_birth_date(Users *user, const char *birth_date) {
    strncpy(user->birth_date, birth_date, MAX_BIRTH_DATE);
    user->birth_date[MAX_BIRTH_DATE - 1] = '\0';
}

void set_phone_number(Users *user, const char *phone_number) {
    strncpy(user->phone_number, phone_number, MAX_PHONE);
    user->phone_number[MAX_PHONE - 1] = '\0';
}

void set_gender(Users *user, enum Gender gender) {
    user->gender = gender;
}

void set_passport(Users *user, const char *passport) {
    strncpy(user->passport, passport, MAX_PASSPORT);
    user->passport[MAX_PASSPORT - 1] = '\0';
}

void set_country_code(Users *user, const char *country_code) {
    strncpy(user->country_code, country_code, MAX_COUNTRY_CODE);
    user->country_code[MAX_COUNTRY_CODE - 1] = '\0';
}

void set_address(Users *user, const char *address) {
    strncpy(user->address, address, MAX_ADDRESS);
    user->address[MAX_ADDRESS - 1] = '\0';
}

void set_account_creation(Users *user, const char *account_creation) {
    strncpy(user->account_creation, account_creation, MAX_DATE_TIME);
    user->account_creation[MAX_DATE_TIME - 1] = '\0';
}

void set_payment_method(Users *user, enum PaymentMethod payment_method) {
    user->payment_method = payment_method;
}

void set_active_status(Users *user, enum Account_status active_status) {
    user->active_status = active_status;
}

const char *get_birth_date(const Users *user) {
    return user->birth_date;
}

const char *get_phone_number(const Users *user) {
    return user->phone_number;
}

enum Gender get_gender(const Users *user) {
    return user->gender;
}

const char *get_passport(const Users *user) {
    return user->passport;
}

const char *get_country_code(const Users *user) {
    return user->country_code;
}

const char *get_address(const Users *user) {
    return user->address;
}

const char *get_account_creation(const Users *user) {
    return user->account_creation;
}

enum PaymentMethod get_payment_method(const Users *user) {
    return user->payment_method;
}

enum Account_status get_active_status(const Users *user) {
    return user->active_status;
}

int get_id(const Users *user) {
    return user->id;
}

const char *get_name(const Users *user) {
    return user->name;
}

const char *get_email(const Users *user) {
    return user->email;
}

int main() {
    Users user1;
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