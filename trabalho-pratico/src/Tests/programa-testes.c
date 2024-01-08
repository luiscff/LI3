#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"
#include "interpreter-testes.h"
#include "parser.h"

// Função que compara dois ficheiros linha a linha.
// Retorna o número da linha onde ocorreu a primeira diferença ou 0 se os ficheiros forem iguais
int compareFiles(const char *expectedResultsFolderPath, const char *actualResultPath) {
    FILE *expected = fopen(expectedResultsFolderPath, "r");
    FILE *actual = fopen(actualResultPath, "r");

    if (expected == NULL || actual == NULL) {
        // printf("Erro ao abrir os arquivos\n"); //TODO quando as queries estiverem todas prontas, tirar esta linha de comentário
        return -1;
    }

    char expectedLine[256];
    char actualLine[256];
    int lineNumber = 1;

    while (fgets(expectedLine, sizeof(expectedLine), expected) != NULL &&
           fgets(actualLine, sizeof(actualLine), actual) != NULL) {
        if (strcmp(expectedLine, actualLine) != 0) {
            // Fecha os arquivos antes de retornar
            fclose(expected);
            fclose(actual);
            return lineNumber;
        }
        lineNumber++;
    }

    // Fecha os arquivos antes de retornar
    fclose(expected);
    fclose(actual);

    // Se chegou até aqui, os arquivos são iguais
    return 0;
}

int main(int argc, char const *argv[]) {
    printf("Starting...\n\n");
    clock_t start = clock();

    if (argc != 4) {
        printf("Usage: %s <Dataset_Folder_Path> <Input_File_Path> <Expected_Results_Folder_Path\n", argv[0]);
        return 1;
    }

    const char *folderPathDataset = argv[1];
    const char *inputPath = argv[2];
    const char *expectedResultsFolderPath = argv[3];

    char filePath[MAX_PATH_SIZE];

    // Cria o catálogo de utilizadores
    USERS_CATALOG *users_catalog = create_users_catalog();

    // faz o parse do ficheiro de utilizadores
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "/users.csv");

    parseCSV(filePath, 1, users_catalog, NULL);

    // Cria o catálogo de voos
    FLIGHTS_CATALOG *flights_catalog = create_flights_catalog();

    // faz o parse do ficheiro de voos
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "/flights.csv");

    parseCSV(filePath, 2, flights_catalog, NULL);

    // Cria o catálogo de reservas
    RESERVATIONS_CATALOG *reservations_catalog = create_reservations_catalog();

    // faz o parse do ficheiro de reservas
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "/reservations.csv");

    parseCSV(filePath, 4, reservations_catalog, users_catalog);

    // Cria o catálogo de passageiros
    PASSENGERS_CATALOG *passengers_catalog = create_passengers_catalog();

    // faz o parse do ficheiro de passageiros
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "/passengers.csv");

    parseCSV(filePath, 3, passengers_catalog, users_catalog);

    // Faz o parse do ficheiro de input
    if (!inputParserTestes(inputPath, users_catalog, flights_catalog, reservations_catalog, passengers_catalog)) {
        printf("Error parsing input file\n");
        // Libera a memória antes de retornar
        free_users_catalog(users_catalog);
        free_flights_catalog(flights_catalog);
        free_reservations_catalog(reservations_catalog);
        free_passengers_catalog(passengers_catalog);
        return 1;
    }

    // Libera a memória no final do programa
    printf("Freeing memory...\n\n");
    free_users_catalog(users_catalog);
    free_flights_catalog(flights_catalog);
    free_reservations_catalog(reservations_catalog);
    free_passengers_catalog(passengers_catalog);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo de execução geral: %f segundos\n\n", time_spent);


    // Compara os resultados com os resultados esperados
    printf("Comparando resultados...\n\n");
    char actualResultPath[MAX_PATH_SIZE];
    char expectedResultPath[MAX_PATH_SIZE];
    int firstMismatch = -1;
    for (int i = 1; i <= 100; i++) {
        sprintf(actualResultPath, "Resultados/command%d_output.txt", i);
        sprintf(expectedResultPath, "%s/command%d_output.txt", expectedResultsFolderPath, i);
        int result = compareFiles(expectedResultPath, actualResultPath);
        if (result > 0) {
            printf("Incongruência encontrada no comando %d na linha %d\n", i, result);
            if (firstMismatch == -1) {
                firstMismatch = i;
            }
        }
    }

    if (firstMismatch == -1) {
        printf("Todos os testes passaram!\n");
    } else {
        printf("O primeiro teste que falhou foi o do comando %d\n", firstMismatch);
    }

    return 0;
}
