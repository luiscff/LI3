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
    snprintf(filePath, MAX_PATH_SIZE, "%s/command%d_output.txt", resultsFolderPath, lineNumber);

    FILE *resultFile = fopen(filePath, "w");
    if (resultFile == NULL) {
        printf("Error creating result file for line %d\n", lineNumber);
        return;
    }

    if (content == NULL) fputs("",resultFile); // Se o conteúdo for NULL, escreve uma linha vazia para não dar SEGFAULT
    else fprintf(resultFile, "%s", content); // Escreve o conteúdo no ficheiro
    fclose(resultFile);
}

void writeToErrorFileFlight(char *line, const char *filename) {
    char *token = strtok(line, ",");
    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == 0) { // Se o ficheiro estiver vazio, escreve o cabeçalho
        fprintf(file, "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes\n");
    }
    while (token != NULL) {
        fprintf(file, "%s", token);
        token = strtok(NULL, ",");
        if (token != NULL) {
            fprintf(file, ";");
        }
    }
    fclose(file);
}


void writeToErrorFilePassenger(char *line, const char *filename) {
    char *token = strtok(line, ",");
    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == 0) {
        fprintf(file, "flight_id;user_id\n");
    }
    while (token != NULL) {
        fprintf(file, "%s", token);
        token = strtok(NULL, ",");
        if (token != NULL) {
            fprintf(file, ";");
        }
    }
    fclose(file);
}

void writeToErrorFileReservation(char *line, const char *filename) {
    char *token = strtok(line, ",");
    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == 0) {
        fprintf(file, "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment;\n");
    }
    while (token != NULL) {
        fprintf(file, "%s", token);
        token = strtok(NULL, ",");
        if (token != NULL) {
            fprintf(file, ";");
        }
    }
    fclose(file);
}

void writeToErrorFileUser(char *line, const char *filename) {
    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size == 0) {
        fprintf(file, "id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status\n");
    }

    fprintf(file, "%s", line);  // Write the whole line to the file

    fclose(file);
}