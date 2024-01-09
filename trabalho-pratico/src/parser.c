#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"
#include "Catalog/stats.h"
#include "output.h"
#include "utils.h"

// função responsável por tratar dos casos da include_breakfast, feita para aceitar tanto os chars f, como t, como os valores 0 ou 1
bool isTrueOrFalse(const char *str) {
    if (strcasecmp(str, "f") == 0 || strcasecmp(str, "false") == 0 || strcasecmp(str, "0") == 0 || strcasecmp(str, "") == 0)
        return false;
    else if (strcasecmp(str, "t") == 0 || strcasecmp(str, "true") == 0 || strcasecmp(str, "1") == 0)
        return true;
    printf("Invalid input on parser.c\n");
    return false;
}
// função responsável por fazer o parse de cada linha do user, separando em tokens e colocando em cada campo o token o valor respetivo, ou, em caso de falha, vai escrever no ficheiro de erros dos users
void parseLine_user(char *line, void *catalog,STATS* stats) {
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

        //adiciona conjunto nome e id as stats

        USER_NAME* user_name = create_user_name(get_name(user), get_id(user), get_active_status(user));
        insert_user_name(stats,user_name);
        printf("user_name: %s;%s;%s\n",get_user_name_name(user_name), get_user_name_id(user_name), get_user_name_status(user_name));
        


        // adiciona o user ao catálogo

        
        insert_user(usersCatalog, user, get_id(user));
    } else {
        writeToErrorFileUser(line, "Resultados/users_errors.csv");
    }

    free(lineCopy);
}
// função responsável por fazer o parse de cada linha dos flights, separando em tokens e colocando em cada campo o token o valor respetivo, ou, em caso de falha, vai escrever no ficheiro de erros dos flights
void parseLine_flight(char *line, void *catalog, STATS* stats) {
    FLIGHTS_CATALOG *flightsCatalog = (FLIGHTS_CATALOG *)catalog;
    char *token;
    int fieldIndex = 1;
    char *lineCopy = strdup(line);

    // Cria um novo voo
    FLIGHT *flight = create_flight();

    char *schedule_begin_date = NULL;
    char *real_begin_date = NULL;
    // são guardados os valores das datas schedule_departure_date e real_departure_date para mais tarde se poder comparar com as datas de arrival respetivas de modo a garantir que as datas de arrival são depois das de departure
    token = strtok(lineCopy, ";");
    while (token != NULL) {
        if (schedule_begin_date != NULL) {
            free(schedule_begin_date);
            schedule_begin_date = NULL;
        }
        if (real_begin_date != NULL) {
            free(real_begin_date);
            real_begin_date = NULL;
        }
        if (get_schedule_departure_date(flight) != NULL) {
            schedule_begin_date = strdup(get_schedule_departure_date(flight));
        }
        if (get_real_departure_date(flight) != NULL) {
            real_begin_date = strdup(get_real_departure_date(flight));
        }

        if (isValidField_flight(token, fieldIndex, schedule_begin_date, real_begin_date)) {
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
            free(schedule_begin_date);
            free(real_begin_date);
            return;
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }

    if (fieldIndex == 14) {
        // adiciona o voo ao catálogo
        insert_flight(flightsCatalog, flight, GINT_TO_POINTER(get_flight_id(flight)));
    } else {
        writeToErrorFileFlight(line, "Resultados/flights_errors.csv");
    }

    free(schedule_begin_date);
    free(real_begin_date);
    free(lineCopy);
}
// função responsável por fazer o parse de cada linha dos passengers, separando em tokens e colocando em cada campo o token o valor respetivo, ou, em caso de falha, vai escrever no ficheiro de erros dos passengers
void parseLine_passenger(char *line, void *catalog, USERS_CATALOG *usersCatalog,STATS* stats) {
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
        char *user_id = strdup(get_user_id2(passenger));
        USER *user = get_user_by_id(usersCatalog, user_id);
        free(user_id);

        //adiciona o voo à lista de voos do user
        char* flight_id = fix_flight_id(get_flight_id2(passenger));
        add_flight(user, flight_id);

        // adiciona o passageiro ao catálogo
        insert_passenger(passengersCatalog, passenger);
    } else {
        writeToErrorFilePassenger(line, "Resultados/passengers_errors.csv");
    }

    free(lineCopy);
}

// função responsável por fazer o parse de cada linha das reservations, separando em tokens e colocando em cada campo o token o valor respetivo, ou, em caso de falha, vai escrever no ficheiro de erros dos reservations
void parseLine_reservation(char *line, void *catalog, USERS_CATALOG *usersCatalog, STATS* stats) {
    RESERVATIONS_CATALOG *reservationsCatalog = (RESERVATIONS_CATALOG *)catalog;
    char *token;

    int fieldIndex = 1;
    char *lineCopy = strdup(line);

    // Cria uma nova reserva
    RESERVATION *reservation = create_reservation();
    char *begin_date = NULL;

    token = strtok(lineCopy, ";");
    while (token != NULL) {
        if (begin_date != NULL) {  // é guardado o token da begin_date que mais tarde vai ser necessário para depois garantir que a segunda data é posterior à primeira
            free(begin_date);
            begin_date = NULL;
        }
        if (get_begin_date(reservation) != NULL) {
            begin_date = strdup(get_begin_date(reservation));
        }
        if (isValidField_reservation(token, fieldIndex, begin_date)) {
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
        token = strtok(NULL, ";");
        fieldIndex++;
    }

    if (fieldIndex == 15) {
        // vai buscar o user associado a esta reserva ao users_catalog
        char *user_id = strdup(get_user_id(reservation));
        USER *user = get_user_by_id(usersCatalog, user_id);
        free(user_id);

        // adiciona o total gasto ao respetivo user no users_catalog
        double price_reservation = calc_total_price(reservation);
        add_total_spent(user, price_reservation);

        // adiciona mais uma reserva ao respetivo user no users_catalog
        add_reservation(user, get_reservation_id(reservation));

        // adiciona ou da update as informaçoes de um hotel
        char *hotel_id = strdup(get_hotel_id(reservation));
        int hotel_rating = get_rating(reservation);
        
        insert_or_update_hotel(stats,hotel_id, hotel_rating);

        // adiciona a reserva ao catálogo
        insert_reservation(reservationsCatalog, reservation, get_reservation_id(reservation));
    } else {
        writeToErrorFileReservation(line, "Resultados/reservations_errors.csv");
    }

    if (begin_date != NULL) free(begin_date);
    free(lineCopy);
}

// função responsável por fazer o parse do ficheiro .csv inteiro, onde abre o ficheiro e chama as funções que leem cada linha do ficheiro para fazer o parse da linha
void parseCSV(const char *filepath, int token, void *catalog, void *users_catalog,STATS* stats) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filepath);
        return;
    }


    // casts para o tipo de catálogo que se pretende
    USERS_CATALOG *usersCatalog = (USERS_CATALOG *)users_catalog;

    char *line = NULL;
    size_t len = 0;
    size_t read;

    // gets rid of first line
    if ((read = getline(&line, &len, file)) != -1) {
        free(line);
        line = NULL;
        len = 0;
    }

    if (token == 1)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_user(line, catalog, stats);
        }

    if (token == 2)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_flight(line, catalog,stats);
        }

    if (token == 3)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_passenger(line, catalog, usersCatalog,stats);
        }

    if (token == 4)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_reservation(line, catalog, usersCatalog,stats);
        }

    free(line);
    fclose(file);
}
