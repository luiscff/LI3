#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  // Adicionado para mkdir e stat
#include <time.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"
#include "interpreter.h"
#include "parser.h"

// cria o ficheiro de resultados //TODO meter no ficheiro certo (algo tipo output.c)
void create_result_file(const char *folderPath, int lineNumber, const char *content) {
    char resultsFolderPath[MAX_PATH_SIZE];
    snprintf(resultsFolderPath, MAX_PATH_SIZE, "%s/outputs", folderPath);
    struct stat st = {0};
    if (stat(resultsFolderPath, &st) == -1) {
        mkdir(resultsFolderPath, 0777);
    }
    char filePath[MAX_PATH_SIZE];
    snprintf(filePath, MAX_PATH_SIZE, "%s/command%d.txt", resultsFolderPath, lineNumber);

    FILE *resultFile = fopen(filePath, "w");
    if (resultFile == NULL) {
        printf("Error creating result file for line %d\n", lineNumber);
        return;
    }

    fprintf(resultFile, "%s", content);

    fclose(resultFile);
}

int main(int argc, char const *argv[]) {
    clock_t start = clock();

    if (argc != 3) {
        printf("Usage: %s <DatasetFolderPath> <InputFilePath>\n", argv[0]);
        return 1;
    }

    const char *folderPathDataset = argv[1];
    const char *inputPath = argv[2];

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

    // Cria o catálogo de passageiros
    PASSENGERS_CATALOG *passengers_catalog = create_passengers_catalog();

    // faz o parse do ficheiro de passageiros
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "passengers.csv");

    parseCSV(filePath, 3, passengers_catalog);

    // Faz o parse do ficheiro de input
    if (!inputParser(inputPath, users_catalog, flights_catalog, reservations_catalog, passengers_catalog)) {
        printf("Error parsing input file\n");
        // Libera a memória antes de retornar
        free_users_catalog(users_catalog);
        free_flights_catalog(flights_catalog);
        free_reservations_catalog(reservations_catalog);
        free_passengers_catalog(passengers_catalog);
        return 1;
    }

    // Libera a memória no final do programa
    printf("Freeing memory...\n");
    printf("Users");
    free_users_catalog(users_catalog);
    printf("Flights");
    free_flights_catalog(flights_catalog);
    printf("Reservations");
    free_reservations_catalog(reservations_catalog);
    printf("Passengers");
    free_passengers_catalog(passengers_catalog);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", time_spent);

    return 0;
}
