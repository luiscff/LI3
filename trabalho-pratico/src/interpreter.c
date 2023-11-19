#include "interpreter.h"

#include <stdio.h>

int inputParser(const char *inputPath, USERS_CATALOG *u_catalog, FLIGHTS_CATALOG *f_catalog, RESERVATIONS_CATALOG *r_catalog, PASSENGERS_CATALOG *p_catalog) {
    char buffer[256];
    FILE *file = fopen(inputPath, "r");
    int lineNumber = 1;

    if (file == NULL) return 0;  // Error

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *token = strtok(buffer, " ");

        if (strcmp(token, "1") == 0) {
            // executa query 1
            char *nextToken = strtok(NULL, " ");
            printf("Execuntando query 1 com token: %s\n",nextToken);
            query1(u_catalog, f_catalog, r_catalog, p_catalog, nextToken);
            //TODO fazer a query 1 chamar o futuro ficheiro output.c que vai criar o ficheiro com o resultado da query
            //ou fazer a query 1 retornar o resultado e chama-se o output.c aqui
        } else if (strcmp(token, "2") == 0) {
            // ignora

        } else if (strcmp(token, "3") == 0) {
            // ignora
        } else if (strcmp(token, "4") == 0) {
            // ignora
        } else if (strcmp(token, "5") == 0) {
            // ignora
        } else if (strcmp(token, "6") == 0) {
            // ignora
        } else if (strcmp(token, "7") == 0) {
            // ignora
        } else if (strcmp(token, "8") == 0) {
            // ignora
        } else if (strcmp(token, "9") == 0) {
            // ignora
        } else if (strcmp(token, "10") == 0) {
            // ignora
        } else if (strcmp(token, "1F") == 0) {
            // ignora
        } else if (strcmp(token, "2F") == 0) {
            // ignora
        } else if (strcmp(token, "3F") == 0) {
            // ignora
        } else if (strcmp(token, "4F") == 0) {
            // ignora
        } else if (strcmp(token, "5F") == 0) {
            // ignora
        } else if (strcmp(token, "6F") == 0) {
            // ignora
        } else if (strcmp(token, "7F") == 0) {
            // ignora
        } else if (strcmp(token, "8F") == 0) {
            // ignora
        } else if (strcmp(token, "9F") == 0) {
            // ignora
        } else if (strcmp(token, "10F") == 0) {
            // ignora
        }

        lineNumber++;
    }

    fclose(file);
    return 1;  // Success
}