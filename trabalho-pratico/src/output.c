#include <sys/stat.h>  // Adicionado para mkdir e stat
#include <stdio.h>
#include <string.h>

#include "output.h"


// cria o ficheiro de resultados com o conteúdo
void create_result_file(const char *folderPath, int lineNumber, const char *content) {
    char resultsFolderPath[MAX_PATH_SIZE];
    strcpy(resultsFolderPath, folderPath);

    struct stat st = {0};
    if (stat(resultsFolderPath, &st) == -1) {
        if (mkdir(resultsFolderPath, 0777) != 0) {
            printf("Error creating results folder\n");
            return;
        }
    }
    char filePath[MAX_PATH_SIZE];
    snprintf(filePath, MAX_PATH_SIZE, "%s/command%d.txt", resultsFolderPath, lineNumber);

    FILE *resultFile = fopen(filePath, "w");
    if (resultFile == NULL) {
        printf("Error creating result file for line %d\n", lineNumber);
        return;
    }

    if (content == NULL) fprintf(resultFile, ""); // Se o conteúdo for NULL, escreve uma linha vazia para não dar SEGFAULT
    else fprintf(resultFile, "%s", content); // Escreve o conteúdo no ficheiro
    fclose(resultFile);
}