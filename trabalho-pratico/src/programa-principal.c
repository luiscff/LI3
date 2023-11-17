#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/reservations_catalog.h"
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
    FLIGHTS_CATALOG *flights_catalog = create_flights_catalog();

    // faz o parse do ficheiro de voos

    strcpy(filePath, folderPathDataset);
    strcat(filePath, "flights.csv");

    parseCSV(filePath, 2, flights_catalog);

    // Cria o catálogo de reservas
    RESERVATIONS_CATALOG *reservations_catalog = create_reservations_catalog();

    // faz o parse do ficheiro de reservas
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "reservations.csv");

    parseCSV(filePath, 4, reservations_catalog);

    // print de um user, um flight e uma reservation
    USER *retrieved_user = get_user_by_id(users_catalog, "GusFreitas677");
    printf("User ID: %s\n", get_id(retrieved_user));

    FLIGHT *retrieved_flight = get_flight_by_id(flights_catalog, 1);
    printf("Flight ID: %d\n", get_flight_id(retrieved_flight));

    RESERVATION *retrieved_reservation = get_reservation_by_id(reservations_catalog, "Book0000000001");
    printf("Reservation ID: %s\n", get_reservation_id(retrieved_reservation));


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

    //frees
    free_users_catalog(users_catalog);
    free_flights_catalog(flights_catalog);
    free_reservations_catalog(reservations_catalog);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", time_spent);

    return 0;
}