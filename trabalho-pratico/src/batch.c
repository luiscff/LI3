#include "batch.h"

#include <stdio.h>

void batchMode(const char *folderPathDataset, const char *inputPath, void *users_catalog, void *flights_catalog, void *reservations_catalog, void *passengers_catalog, void *stats) {
    parseFiles(folderPathDataset, users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats);

    // Faz o parse do ficheiro de input
    if (!inputParser(inputPath, users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats)) {
        printf("Error parsing input file\n");
        return;
    }

    return;
}