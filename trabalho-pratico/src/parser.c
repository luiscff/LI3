#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"
#include "output.h"

bool isTrueOrFalse(const char *str) {
    if (strcasecmp(str, "f") == 0 || strcasecmp(str, "false") == 0 || strcasecmp(str, "0") == 0 || strcasecmp(str, "") == 0)
        return false;
    else if (strcasecmp(str, "t") == 0 || strcasecmp(str, "true") == 0 || strcasecmp(str, "1") == 0)
        return true;
    printf("Invalid input on parser.c\n");
    return false;
}

void parseLine_user(char *line, void *catalog) {
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
                    set_active_status(user, token);
                    break;
            }
        } else {
            writeToErrorFileUser(line, "Resultados/users_errors.csv");
            free(lineCopy);
            free_user(user);  // Adicione esta linha
            return;
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }

    if (fieldIndex == 13) {
        // adiciona o user ao catálogo
        insert_user(usersCatalog, user, get_id(user));
    } else {
        writeToErrorFileUser(line, "Resultados/users_errors.csv");
    }

    free(lineCopy);
}

void parseLine_flight(char *line, void *catalog) {
    FLIGHTS_CATALOG *flightsCatalog = (FLIGHTS_CATALOG *)catalog;
    char *token;
    int fieldIndex = 1;
    char *lineCopy = strdup(line);

    // Cria um novo voo
    FLIGHT *flight = create_flight();

    char *schedule_begin_date = NULL;
    char *real_begin_date = NULL;

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
            writeToErrorFileFlight(line, "Resultados/flights_errors.csv");
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

void parseLine_passenger(char *line, void *catalog) {
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
            writeToErrorFilePassenger(line, "Resultados/passengers_errors.csv");
            free(lineCopy);
            free_passenger(passenger);
            return;
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }

    if (fieldIndex == 3) {
        // adiciona o passageiro ao catálogo
        insert_passenger(passengersCatalog, passenger);
    } else {
        writeToErrorFilePassenger(line, "Resultados/passengers_errors.csv");
    }

    free(lineCopy);
}

void parseLine_reservation(char *line, void *catalog) {
    RESERVATIONS_CATALOG *reservationsCatalog = (RESERVATIONS_CATALOG *)catalog;
    char *token;
    int fieldIndex = 1;
    char *lineCopy = strdup(line);

    // Cria uma nova reserva
    RESERVATION *reservation = create_reservation();
    char *begin_date = NULL;

    token = strtok(lineCopy, ";");
    while (token != NULL) {
        if (begin_date != NULL) {
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
        // adiciona a reserva ao catálogo
        insert_reservation(reservationsCatalog, reservation, get_reservation_id(reservation));
    } else {
        writeToErrorFileReservation(line, "Resultados/reservations_errors.csv");
    }

    if (begin_date != NULL) free(begin_date);
    free(lineCopy);
}

void parseCSV(const char *filepath, int token, void *catalog) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filepath);
        return;
    }

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
            parseLine_user(line, catalog);
        }

    if (token == 2)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_flight(line, catalog);
        }

    if (token == 3)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_passenger(line, catalog);
        }

    if (token == 4)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_reservation(line, catalog);
        }

    free(line);
    fclose(file);
}
