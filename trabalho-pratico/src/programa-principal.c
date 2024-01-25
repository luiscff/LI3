#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wordexp.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/stats.h"
#include "Catalog/users_catalog.h"
#include "batch.h"
#include "interactive.h"

void end_program(USERS_CATALOG *users_catalog, FLIGHTS_CATALOG *flights_catalog, RESERVATIONS_CATALOG *reservations_catalog, PASSENGERS_CATALOG *passengers_catalog, STATS *stats) {
    printf("Freeing memory...\n");
    printf("Users\n");
    free_users_catalog(users_catalog);
    printf("Flights\n");
    free_flights_catalog(flights_catalog);
    printf("Reservations\n");
    free_reservations_catalog(reservations_catalog);
    printf("Passengers\n");
    free_passengers_catalog(passengers_catalog);
    printf("Stats\n");
    free_stats(stats);
}

int main(int argc, char const *argv[]) {
    clock_t start = clock();

    // Cria o catálogo de estatísticas
    STATS *stats = create_stats_catalog();
    // Cria o catálogo de utilizadores
    USERS_CATALOG *users_catalog = create_users_catalog();
    // Cria o catálogo de voos
    FLIGHTS_CATALOG *flights_catalog = create_flights_catalog();
    // Cria o catálogo de reservas
    RESERVATIONS_CATALOG *reservations_catalog = create_reservations_catalog();
    // Cria o catálogo de passageiros
    PASSENGERS_CATALOG *passengers_catalog = create_passengers_catalog();

    if (argc == 1) {
        printf("Inicializando o modo Interativo...\n");

        char folderPathDataset[MAX_PATH_SIZE];
        printf("Introduza o caminho para a pasta onde está o dataset:\n");

        fgets(folderPathDataset, MAX_PATH_SIZE, stdin);
        // Remove o caractere de nova linha no final da string
        folderPathDataset[strcspn(folderPathDataset, "\n")] = 0;

        // Expande o ~ para o diretório home do usuário (solução para um bug que acontecia quando se usava o caminho relativo)
        wordexp_t p;
        wordexp(folderPathDataset, &p, 0);
        strcpy(folderPathDataset, p.we_wordv[0]);
        wordfree(&p);

        interactiveMode(folderPathDataset, users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats);

    } else if (argc == 3) {
        printf("Inicializando o modo Batch...\n");

        batchMode(argv[1], argv[2], users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats);

    } else {
        printf("Command for Batch Mode: %s <DatasetFolderPath> <InputFilePath>\n", argv[0]);
        printf("Command for Interactive Mode: %s\n", argv[0]);
        return 1;
    }

    // Libera a memória no final do programa
    end_program(users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", time_spent);

    return 0;
}
