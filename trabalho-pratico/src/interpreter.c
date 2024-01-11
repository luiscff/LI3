#include "interpreter.h"

#include <stdio.h>

//função que vai tratar do input e chamar as queries respetivas para cada linha do ficheiro passado como argumento
int inputParser(const char *inputPath, USERS_CATALOG *u_catalog, FLIGHTS_CATALOG *f_catalog, RESERVATIONS_CATALOG *r_catalog, PASSENGERS_CATALOG *p_catalog, STATS* stats) {
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
            printf("Executando query 1 com token: %s\n",nextToken);
            char *result = query1(u_catalog, f_catalog, r_catalog, p_catalog, nextToken);
            create_result_file("Resultados", lineNumber, result);
            free(result);

        }  else if (strcmp(token, "2") == 0) {
            char *nextToken = strtok(NULL, " ");
            char *nextToken2 = strtok(NULL, " ");
            
            if (nextToken2 == NULL) {// se for chamada a query 2 com o 2º argumento nulo, chama a função responsável para produzir o output inteiro (voos e reservas)
                printf("Executando query 2 com token: %s\n",nextToken);
                char *result = query2_nocat(f_catalog, r_catalog, u_catalog,p_catalog, nextToken,1);
                create_result_file("Resultados", lineNumber, result); // escrita no ficheiro respetivo
                free(result);}
            else { // se a query 2 for chamada com um argumento, chama a função responsável para produzir o output do token dado (reserva ou voo)
                printf("Executando query 2 com tokens: %s %s\n",nextToken,nextToken2);
                char *result = query2_cat(f_catalog, r_catalog, u_catalog,p_catalog, nextToken, nextToken2,1);
                create_result_file("Resultados", lineNumber, result);

                free(result);}


           
        } else if (strcmp(token, "3") == 0) {// query3 e escrita numa linha no ficheiro
            char *nextToken = strtok(NULL, " ");
            printf("Executando query 3 com token: %s\n",nextToken);
            char *result = query3(r_catalog,nextToken,stats);
            create_result_file("Resultados", lineNumber, result);
            if (result != NULL) free(result);

        } else if (strcmp(token, "4") == 0) {// query4 e escrita numa linha no ficheiro
            char *nextToken = strtok(NULL, " ");
            printf("Executando query 4 com token: %s\n",nextToken);
            char *result = query4(r_catalog,nextToken,1);
            create_result_file("Resultados", lineNumber, result);
            free(result);

        } else if (strcmp(token, "5") == 0) {
            // ignora
        } else if (strcmp(token, "6") == 0) {
            // ignora
        } else if (strcmp(token, "7") == 0) {
            char *nextToken = strtok(NULL, " ");
            printf("Executando query 7 com token: %s\n",nextToken);
            char *result = query7(f_catalog,nextToken,stats,1);
            create_result_file("Resultados", lineNumber, result);
            free(result);

        } else if (strcmp(token, "8") == 0) {
            // ignora
        } else if (strcmp(token, "9") == 0) {
            char *nextToken = strtok(NULL, " ");
            printf("Executando query 9 com token: %s\n",nextToken);
            //char *result = query9(u_catalog,nextToken, stats, 1);
            //create_result_file("Resultados", lineNumber, result);
            //free(result);
            
        } else if (strcmp(token, "10") == 0) {
            // ignora
        } else if (strcmp(token, "1F") == 0) {// execução da query1 com a segunda formatação
            char *nextToken = strtok(NULL, " ");
            printf("Executando query 1F com token: %s\n",nextToken);
            char *result = query1F(u_catalog, f_catalog, r_catalog, p_catalog, nextToken);
            create_result_file("Resultados", lineNumber, result);
            free(result);

        } else if (strcmp(token, "2F") == 0) {
            char *nextToken = strtok(NULL, " ");
            char *nextToken2 = strtok(NULL, " ");
           
            
            if (nextToken2 == NULL) {
                printf("Executando query 2F com token: %s \n",nextToken);
                char *result = query2_nocat(f_catalog, r_catalog, u_catalog,p_catalog, nextToken,2);
                create_result_file("Resultados", lineNumber, result);
                free(result);
            }
            else {
                printf("Executando query 2F com tokens: %s %s\n",nextToken,nextToken2);
                char *result = query2_cat(f_catalog, r_catalog, u_catalog,p_catalog, nextToken, nextToken2,2);
                create_result_file("Resultados", lineNumber, result);
                free(result);
                }

        } else if (strcmp(token, "3F") == 0) {
            char *nextToken = strtok(NULL, " ");
            printf("Executando query 3F com token: %s\n",nextToken);
            char *result = query3F(r_catalog, nextToken,stats);
            create_result_file("Resultados", lineNumber, result);
            free(result);

        } else if (strcmp(token, "4F") == 0) {
           char *nextToken = strtok(NULL, " ");
            printf("Executando query 4F com token: %s\n",nextToken);
            char *result = query4(r_catalog,nextToken,2);
            create_result_file("Resultados", lineNumber, result);
            free(result);
        } else if (strcmp(token, "5F") == 0) {
            // ignora
        } else if (strcmp(token, "6F") == 0) {
            // ignora
        } else if (strcmp(token, "7F") == 0) {
            char *nextToken = strtok(NULL, " ");
            printf("Executando query 7 com token: %s\n",nextToken);
            char *result = query7(f_catalog,nextToken,stats,2);
            create_result_file("Resultados", lineNumber, result);
            free(result);
        } else if (strcmp(token, "8F") == 0) {
            // ignora
        } else if (strcmp(token, "9F") == 0) {
            char *nextToken = strtok(NULL, " ");
            printf("Executando query 9F com token: %s\n",nextToken);
            //char *result = query9(u_catalog,nextToken, stats, 2);
            //create_result_file("Resultados", lineNumber, result);
            //free(result);
        } else if (strcmp(token, "10F") == 0) {
            // ignora
        }

        lineNumber++;// incrementa o nº de linhas lidas para depois ser utilizado na criação do ficheiro commandX.txt
    }

    fclose(file);
    return 1;  // Success
}