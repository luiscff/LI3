#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h> // Adicionado para mkdir
#include <time.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "parser.h"

#define MAX_PATH_SIZE 256

void create_result_file(const char *folderPath, int lineNumber, const char *content) {
    char resultsFolderPath[MAX_PATH_SIZE];
    sprintf(resultsFolderPath, "%s/outputs", folderPath);
    struct stat st = {0};
    if (stat(resultsFolderPath, &st) == -1) {
        mkdir(resultsFolderPath, 0777);
    }
    char filePath[MAX_PATH_SIZE];
    sprintf(filePath, "%s/command%d.txt", resultsFolderPath, lineNumber);

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
    const char *folderPathInput = argv[2];

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

    
    printf("\n");
    //Cria o catálogo de passageiros
    PASSENGERS_CATALOG *passengers_catalog = create_passengers_catalog();

    // faz o parse do ficheiro de passageiros
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "passengers.csv");

    parseCSV(filePath, 3, passengers_catalog);

    // pesquisa de utilizadores por voo
    printf("Users on flight 1:\n");
    GList *users = find_users_by_flight(passengers_catalog, 1);
    for (GList *node = users; node != NULL; node = node->next) {
        printf("%s\n", (char *)node->data);
    }
    g_list_free(users);
    printf("\n");

    // pesquisa de voos por utilizador
    printf("Flights of user Tbranco:\n");
    GList *flights = find_flights_by_user(passengers_catalog, "TBranco");
    for (GList *node = flights; node != NULL; node = node->next) {
        printf("%d\n", GPOINTER_TO_INT(node->data));
    }
    g_list_free(flights);
    printf("\n");





    char filePathI[MAX_PATH_SIZE];
    strcpy(filePathI, folderPathInput);
    strcat(filePathI, "input.txt");
    char buffer[256];
    FILE *file = fopen(filePathI, "r");
    int lineNumber = 1;

    if (file == NULL) {
        printf("Error opening file\n");

        // Libera a memória antes de retornar
        free_users_catalog(users_catalog);
        free_flights_catalog(flights_catalog);
        free_reservations_catalog(reservations_catalog);
        free_passengers_catalog(passengers_catalog);

        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *token = strtok(buffer, " ");

        if (strcmp(token, "1") == 0) {
            create_result_file("Resultados", lineNumber, "Computador\n");
        } else if (strcmp(token, "2") == 0) {
            create_result_file("Resultados", lineNumber, "Livro\n");
        } else if (strcmp(token, "3") == 0) {
            create_result_file("Resultados", lineNumber, "pirata\n");
        } else if (strcmp(token, "4") == 0) {
            create_result_file("Resultados", lineNumber, "Animal\n");
        } else if (strcmp(token, "5") == 0) {
            create_result_file("Resultados", lineNumber, "Cão\n");
        } else if (strcmp(token, "6") == 0) {
            create_result_file("Resultados", lineNumber, "Gato\n");
        } else if (strcmp(token, "7") == 0) {
            create_result_file("Resultados", lineNumber, "Golfinho\n");
        } else if (strcmp(token, "8") == 0) {
            create_result_file("Resultados", lineNumber, "Tubarão\n");
        } else if (strcmp(token, "9") == 0) {
            create_result_file("Resultados", lineNumber, "Leão\n");
        } else if (strcmp(token, "10") == 0) {
            create_result_file("Resultados", lineNumber, "Luís\n");
        } else if (strcmp(token, "1F") == 0) {
            create_result_file("Resultados", lineNumber, "Luísa\n");
        } else if (strcmp(token, "2F") == 0) {
            create_result_file("Resultados", lineNumber, "Baleia\n");
        } else if (strcmp(token, "3F") == 0) {
            create_result_file("Resultados", lineNumber, "Livro\n");
        } else if (strcmp(token, "4F") == 0) {
            create_result_file("Resultados", lineNumber, "Biblio\n");
        } else if (strcmp(token, "5F") == 0) {
            create_result_file("Resultados", lineNumber, "Jesus\n");
        } else if (strcmp(token, "6F") == 0) {
            create_result_file("Resultados", lineNumber, "Teste\n");
        } else if (strcmp(token, "7F") == 0) {
            create_result_file("Resultados", lineNumber, "Exame\n");
        } else if (strcmp(token, "8F") == 0) {
            create_result_file("Resultados", lineNumber, "Frequência\n");
        } else if (strcmp(token, "9F") == 0) {
            create_result_file("Resultados", lineNumber, "Música\n");
        } else if (strcmp(token, "10F") == 0) {
            create_result_file("Resultados", lineNumber, "Nota\n");
        }

        lineNumber++;
    }

    fclose(file);

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
