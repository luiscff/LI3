#include <time.h>
#include <string.h>
#include <stdio.h>

#include "parser.h"


#define MAX_PATH_SIZE 256


int main(int argc, char const *argv[]) {
    clock_t start = clock();
    if (argc != 3) {
        // parser só funciona se receber um folderPathDataset e inputPath ao executar programa
        printf("Usage: %s <folderPathDataset> <inputPath>\n", argv[0]); 
        return 1;
    }

    const char *folderPathDataset = argv[1];
    const char *folderPathInput = argv[2];  // Ainda n é usado o ficheiro de input

    char filePath[MAX_PATH_SIZE];

    // for users.csv
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "users.csv");
    parseCSV(filePath,1);

    // for flights.csv
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "flights.csv");
    parseCSV(filePath,2);

    // for passengers.csv
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "passengers.csv");
    parseCSV(filePath,3);

    // for reservations.csv
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "reservations.csv");
    parseCSV(filePath,4);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", time_spent);

    return 0;
}