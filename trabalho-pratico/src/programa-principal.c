#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/users_catalog.h"
#include "parser.h"

#define MAX_PATH_SIZE 256

int main(int argc, char const *argv[]) {
    clock_t start = clock();
    if (argc != 3) {
        // parser só funciona se receber um folderPathDataset e inputPath ao executar programa
        printf("Usage: %s <DatasetFolderPath> <InputFilePath>\n", argv[0]);
        return 1;
    }

    const char *folderPathDataset = argv[1];
    const char *folderPathInput = argv[2];  // Ainda n é usado o ficheiro de input

    char filePath[MAX_PATH_SIZE];

    // Cria o catálogo de utilizadores
    USERS_CATALOG *users_catalog = create_users_catalog();

    // faz o parse do ficheiro de utilizadores
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "users.csv");

    parseCSV(filePath, 1, users_catalog);


    // Cria o catálogo de voos
    FLIGHTS_CATALOG *catalog = create_flights_catalog();

    // faz o parse do ficheiro de voos

    strcpy(filePath, folderPathDataset);
    strcat(filePath, "flights.csv");

    parseCSV(filePath, 2, catalog);

    // // TESTE DE PASSENGERS_CATALOG
    // // Cria o catálogo de passageiros
    // PASSENGERS_CATALOG* catalog = create_passengers_catalog();

    // // Cria um novo passageiro
    // PASSENGER* passenger1 = create_passenger();
    // set_user_id2(passenger1, "000123");
    // set_flight_id2(passenger1, "000123");
    // // Adicione mais detalhes ao passageiro conforme necessário...

    // // Insere o passageiro no catálogo
    // insert_passenger(catalog, passenger1, GINT_TO_POINTER(get_user_id2(passenger1)));

    // // Recupera o passageiro do catálogo
    // PASSENGER *retrieved_passenger = get_passenger_by_id(catalog, 123);

    // // Imprime alguns detalhes do passageiro
    // printf("Passenger ID: %d\n", get_user_id2(retrieved_passenger));
    // printf("Flight ID: %d\n", get_flight_id2(retrieved_passenger));

    // // Limpa
    // free_passengers_catalog(catalog);

    // // TESTE DE USERS_CATALOG
    // // cria catalogo
    // USERS_CATALOG *catalog = create_users_catalog();

    // // cria user
    // USER *user = create_user();

    // // dá fields ao user
    // set_id(user, strdup("1"));
    // set_name(user, strdup("João"));
    // set_email(user, strdup("joao@example.com"));
    // set_birth_date(user, strdup("1990-01-01"));
    // set_phone_number(user, strdup("123456789"));
    // set_passport(user, strdup("AB123456"));
    // set_country_code(user, strdup("PT"));
    // set_address(user, strdup("Rua Exemplo, 123"));
    // set_account_creation(user, strdup("2020-01-01"));

    // // insere user no catalogo
    // insert_user(catalog, user, "1");

    // // recupera user do catalogo
    // USER *retrieved_user = get_user_by_id(catalog, "1");

    // // imprime alguns detalhes do user
    // printf("User ID: %s\n", get_id(retrieved_user));
    // printf("Adress: %s\n", get_address(retrieved_user));

    // // limpa
    // free_users_catalog(catalog);

    return 0;

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", time_spent);

    return 0;
}