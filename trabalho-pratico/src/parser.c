#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/stats.h"
#include "Catalog/users_catalog.h"
#include "output.h"
#include "utils.h"

// função responsável por tratar dos casos da include_breakfast, feita para aceitar tanto os chars f, como t, como os valores 0 ou 1
bool isTrueOrFalse(const char *str) {
    if (strcasecmp(str, "f") == 0 || strcasecmp(str, "false") == 0 || strcasecmp(str, "0") == 0 || strcasecmp(str, "") == 0 || strlen(str) == 0)
        return false;
    else if (strcasecmp(str, "t") == 0 || strcasecmp(str, "true") == 0 || strcasecmp(str, "1") == 0)
        return true;
    printf("Invalid input on parser.c\n");
    return false;
}
// função responsável por fazer o parse de cada linha do user, separando em tokens e colocando em cada campo o token o valor respetivo, ou, em caso de falha, vai escrever no ficheiro de erros dos users
void parseLine_user(char *line, void *catalog, STATS *stats) {
    USERS_CATALOG *usersCatalog = (USERS_CATALOG *)catalog;
    char *token;
    int fieldIndex = 1;
    char *lineCopy = strdup(line);

    // Cria um novo user
    USER *user = create_user();

    token = strtok(lineCopy, ";");
    while (token != NULL) {
        if (isValidField_user(token, fieldIndex)) {
            switch (fieldIndex) {
                case 1:
                    set_id(user, token);
                    break;
                case 2:
                    set_name(user, token);
                    break;
                case 3:
                    set_email(user, token);
                    break;
                case 4:
                    set_phone_number(user, token);
                    break;
                case 5:
                    set_birth_date(user, token);
                    break;
                case 6:
                    set_gender(user, token);
                    break;
                case 7:
                    set_passport(user, token);
                    break;
                case 8:
                    set_country_code(user, token);
                    break;
                case 9:
                    set_address(user, token);
                    break;
                case 10:
                    set_account_creation(user, token);
                    break;
                case 11:
                    set_payment_method(user, token);
                    break;
                case 12:
                    // tira o \n do final
                    token[strcspn(token, "\n")] = '\0';
                    set_active_status(user, token);
                    break;
            }
        } else {
            writeToErrorFileUser(line, "Resultados/users_errors.csv");  // função responável por escrever no ficheiro de erros dos users
            free(lineCopy);
            free_user(user);
            return;
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }

    if (fieldIndex == 13) {
        // adiciona conjunto nome e id as stats

        char *user_name = strdup(get_name(user));
        // remove_accents(user_name);
        // char *letter = malloc(2 * sizeof(wchar_t));
        // char *user_name_no_accents = remove_accents(strdup(user_name));

        // letter[0] = user_name_no_accents[0];
        // letter[1] = '\0';

        // insert_or_update_dictionary(stats, strdup(letter), user);
        // printf("NAME : %s\n",user_name_no_accents);
        // printf("LETTER : %s\n",letter);

        // adiciona o user ao catálogo
        insert_user(usersCatalog, user, get_id(user));

        // frees
        free(user_name);
        // free(letter);
        // free(user_name_no_accents);
    } else {
        writeToErrorFileUser(line, "Resultados/users_errors.csv");
    }

    free(lineCopy);
}
// função responsável por fazer o parse de cada linha dos flights, separando em tokens e colocando em cada campo o token o valor respetivo, ou, em caso de falha, vai escrever no ficheiro de erros dos flights
void parseLine_flight(char *line, void *catalog, STATS *stats) {
    FLIGHTS_CATALOG *flightsCatalog = (FLIGHTS_CATALOG *)catalog;
    char *token;
    int fieldIndex = 1;
    char *lineCopy = strdup(line);

    // Cria um novo voo
    FLIGHT *flight = create_flight();

    // são guardados os valores das datas schedule_departure_date e real_departure_date para mais tarde se poder comparar com as datas de arrival respetivas de modo a garantir que as datas de arrival são depois das de departure
    token = strtok(lineCopy, ";");
    while (token != NULL) {
        if (isValidField_flight(token, fieldIndex)) {
            switch (fieldIndex) {
                case 1:
                    set_flight_id(flight, token);
                    break;
                case 2:
                    set_airline(flight, token);
                    break;
                case 3:
                    set_plain_model(flight, token);
                    break;
                case 4:
                    set_total_seats(flight, atoi(token));
                    break;
                case 5:
                    set_origin(flight, token);
                    break;
                case 6:
                    set_destination(flight, token);
                    break;
                case 7:
                    set_schedule_departure_date(flight, token);
                    break;
                case 8:
                    set_schedule_arrival_date(flight, token);
                    break;
                case 9:
                    set_real_departure_date(flight, token);
                    break;
                case 10:
                    set_real_arrival_date(flight, token);
                    break;
                case 11:
                    set_pilot(flight, token);
                    break;
                case 12:
                    set_copilot(flight, token);
                    break;
                case 13:
                    set_notes(flight, token);
                    break;
            }
        } else {
            writeToErrorFileFlight(line, "Resultados/flights_errors.csv");  // função responsável por escrever no ficheiro de erros dos flights caso algum caso falhe
            free(lineCopy);
            free_flight(flight);
            return;
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }

    if (fieldIndex == 14) {
        // validaçao de datas
        char *schedule_departure_date = strdup(get_schedule_departure_date(flight));
        char *real_departure_date = strdup(get_real_departure_date(flight));
        char *schedule_arrival_date = strdup(get_schedule_arrival_date(flight));
        char *real_arrival_date = strdup(get_real_arrival_date(flight));
        bool errordata1 = isDateTime1BeforeDateTime2(schedule_arrival_date, schedule_departure_date);
        bool errordata2 = isDateTime1BeforeDateTime2(real_arrival_date, real_departure_date);
        if (errordata1 == true || errordata2 == true) {
            writeToErrorFileReservation(line, "Resultados/flights_errors.csv");
            free(schedule_departure_date);
            free(schedule_arrival_date);
            free(real_departure_date);
            free(real_arrival_date);
            free(lineCopy);
            return;
        }

        // funçoes para estatistica
        char *origin = strdup(get_origin(flight));
        int new_delay = calc_departure_delay(schedule_departure_date, real_departure_date);
        insert_or_update_airport(stats, origin, new_delay, flight);

        // adiciona o voo ao catálogo
        insert_flight(flightsCatalog, flight, GINT_TO_POINTER(get_flight_id(flight)));

        // frees
        free(origin);
        free(schedule_departure_date);
        free(schedule_arrival_date);
        free(real_departure_date);
        free(real_arrival_date);
    } else {
        writeToErrorFileFlight(line, "Resultados/flights_errors.csv");
        free(lineCopy);
        return;
    }
    free(lineCopy);
}
// função responsável por fazer o parse de cada linha dos passengers, separando em tokens e colocando em cada campo o token o valor respetivo, ou, em caso de falha, vai escrever no ficheiro de erros dos passengers
void parseLine_passenger(char *line, void *catalog, USERS_CATALOG *usersCatalog, FLIGHTS_CATALOG *flightCatalog, STATS *stats) {
    PASSENGERS_CATALOG *passengersCatalog = (PASSENGERS_CATALOG *)catalog;
    char *token;
    int fieldIndex = 1;
    char *lineCopy = strdup(line);

    // Cria um novo passageiro
    PASSENGER *passenger = create_passenger();

    token = strtok(lineCopy, ";");
    while (token != NULL) {
        if (isValidField_passenger(token, fieldIndex)) {
            switch (fieldIndex) {
                case 1:
                    set_flight_id2(passenger, atoi(token));
                    break;
                case 2:
                    set_user_id2(passenger, token);
                    break;
            }
        } else {
            writeToErrorFilePassenger(line, "Resultados/passengers_errors.csv");  // função responsável por escrever no ficheiro de erros dos passengers caso algum caso falhe
            free(lineCopy);
            free_passenger(passenger);
            return;
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }

    if (fieldIndex == 3) {
        // vai buscar o user associado a este passageiro ao users_catalog
        // adiciona o voo à lista de voos do user
        char *user_id = strdup(get_user_id2(passenger));
        USER *user = get_user_by_id(usersCatalog, user_id);
        if (user == NULL) {
            writeToErrorFilePassenger(line, "Resultados/passengers_errors.csv");
            free(user_id);
            free_passenger(passenger);
            free(lineCopy);
            return;
        }

        int flight_id = get_flight_id2(passenger);
        FLIGHT *flight = get_flight_by_id(flightCatalog, flight_id);

        if (flight == NULL) {
            writeToErrorFilePassenger(line, "Resultados/passengers_errors.csv");
            free(user_id);
            free_passenger(passenger);
            free(lineCopy);
            return;
        }

        char *flight_id_char = fix_flight_id(flight_id);
        add_flight(user, strdup(flight_id_char));

        add_passageiro(flight);

        free(user_id);
        free(flight_id_char);

        // adiciona o passageiro ao catálogo
        insert_passenger(passengersCatalog, passenger);

    } else {
        writeToErrorFilePassenger(line, "Resultados/passengers_errors.csv");
    }

    free(lineCopy);  // Release the memory allocated by strdup
}

char *custom_strtok(char *str, const char *delim) {
    static char *lastToken = NULL;

    if (str != NULL) {
        lastToken = str;
    }

    if (lastToken == NULL || *lastToken == '\0') {
        return NULL;
    }

    char *tokenStart = lastToken;
    while (*lastToken != '\0' && strchr(delim, *lastToken) == NULL) {
        lastToken++;
    }

    if (*lastToken != '\0') {
        *lastToken = '\0';
        lastToken++;
    }

    return tokenStart;
}
// função responsável por fazer o parse de cada linha das reservations, separando em tokens e colocando em cada campo o token o valor respetivo, ou, em caso de falha, vai escrever no ficheiro de erros dos reservations
void parseLine_reservation(char *line, void *catalog, USERS_CATALOG *usersCatalog, STATS *stats) {
    RESERVATIONS_CATALOG *reservationsCatalog = (RESERVATIONS_CATALOG *)catalog;
    char *token;

    int fieldIndex = 1;
    char *lineCopy = strdup(line);

    // Cria uma nova reserva
    RESERVATION *reservation = create_reservation();

    token = custom_strtok(lineCopy, ";");
    while (fieldIndex < 15) {
        if (isValidField_reservation(token, fieldIndex)) {
            switch (fieldIndex) {
                case 1:
                    set_reservation_id(reservation, token);
                    break;
                case 2:
                    set_user_id(reservation, token);
                    break;
                case 3:
                    set_hotel_id(reservation, token);
                    break;
                case 4:
                    set_hotel_name(reservation, token);
                    break;
                case 5:
                    set_hotel_stars(reservation, atoi(token));
                    break;
                case 6:
                    set_city_tax(reservation, atoi(token));
                    break;
                case 7:
                    set_reservation_address(reservation, token);
                    break;
                case 8:
                    set_begin_date(reservation, token);
                    break;
                case 9:
                    set_end_date(reservation, token);
                    break;
                case 10:
                    set_price_per_night(reservation, atoi(token));
                    break;
                case 11:
                    set_includes_breakfast(reservation, isTrueOrFalse(token));
                    break;
                case 12:
                    set_room_details(reservation, token);
                    break;
                case 13:
                    set_rating(reservation, atoi(token));
                    break;
                case 14:
                    set_comment(reservation, token);
                    break;
            }
        } else {
            writeToErrorFileReservation(line, "Resultados/reservations_errors.csv");
            free(lineCopy);
            free_reservation(reservation);  // Adicione esta linha
            return;
        }
        token = custom_strtok(NULL, ";");
        fieldIndex++;
    }

    if (fieldIndex == 15) {
        char *begin_date = strdup(get_begin_date(reservation));
        char *end_date = strdup(get_end_date(reservation));

        if (isDate1BeforeDate2(end_date, begin_date) == true) {
            writeToErrorFileReservation(line, "Resultados/reservations_errors.csv");
            free(lineCopy);
            return;
        }
        // vai buscar o user associado a esta reserva ao users_catalog
        char *user_id = strdup(get_user_id(reservation));
        USER *user = get_user_by_id(usersCatalog, user_id);
        free(user_id);
        if (user == NULL) {
            writeToErrorFileReservation(line, "Resultados/reservations_errors.csv");
            free(lineCopy);
            return;
        };

        // adiciona o total gasto ao respetivo user no users_catalog
        double price_reservation = calc_total_price(reservation);

        add_total_spent(user, price_reservation);

        // adiciona mais uma reserva ao respetivo user no users_catalog
        add_reservation(user, get_reservation_id(reservation));

        // adiciona ou da update as informaçoes de um hotel
        char *hotel_id = strdup(get_hotel_id(reservation));
        int hotel_rating = get_rating(reservation);
        insert_or_update_hotel(stats, hotel_id, hotel_rating, reservation);

        free(hotel_id);

        // adiciona a reserva ao catálogo
        insert_reservation(reservationsCatalog, reservation, get_reservation_id(reservation));

        free(begin_date);
        free(end_date);

    } else {
        writeToErrorFileReservation(line, "Resultados/reservations_errors.csv");
    }
    free(lineCopy);
}

// função responsável por fazer o parse de um ficheiro .csv inteiro, onde abre o ficheiro e chama as funções que leem cada linha do ficheiro para fazer o parse da linha
void parseCSV(const char *filepath, int flag, void *catalog, void *users_catalog, void *flights_catalog, STATS *stats) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filepath);
        return;
    }

    // casts para o tipo de catálogo que se pretende
    USERS_CATALOG *usersCatalog = (USERS_CATALOG *)users_catalog;
    FLIGHTS_CATALOG *flightsCatalog = (FLIGHTS_CATALOG *)flights_catalog;

    char *line = NULL;
    size_t len = 0;
    size_t read;

    // gets rid of first line
    if ((read = getline(&line, &len, file)) != -1) {
        free(line);
        line = NULL;
        len = 0;
    }

    if (flag == 1)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_user(line, catalog, stats);
        }

    if (flag == 2)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_flight(line, catalog, stats);
        }

    if (flag == 3)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_passenger(line, catalog, usersCatalog, flightsCatalog, stats);
        }

    if (flag == 4)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_reservation(line, catalog, usersCatalog, stats);
        }

    free(line);
    fclose(file);
}

// função responsável por fazer o parse de todos os ficheiros .csv do dataset, chamando a função parseCSV para cada um dos ficheiros
void parseFiles(const char *folderPathDataset, void *users_catalog, void *flights_catalog, void *reservations_catalog, void *passengers_catalog, void *stats) {
    char filePath[MAX_PATH_SIZE];

    // faz o parse do ficheiro de utilizadores
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "/users.csv");

    parseCSV(filePath, 1, users_catalog, NULL, NULL, stats);

    // faz o parse do ficheiro de voos
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "/flights.csv");

    parseCSV(filePath, 2, flights_catalog, NULL, NULL, stats);

    // faz o parse do ficheiro de reservas
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "/reservations.csv");

    parseCSV(filePath, 4, reservations_catalog, users_catalog, NULL, stats);

    // faz o parse do ficheiro de passageiros
    strcpy(filePath, folderPathDataset);
    strcat(filePath, "/passengers.csv");

    parseCSV(filePath, 3, passengers_catalog, users_catalog, flights_catalog, stats);
}