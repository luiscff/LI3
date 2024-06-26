#include "validation.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Entities/reservation.h"

#define MAX_PHONE 12
#define MAX_COUNTRY_CODE 2

//=========== VALIDATION IN-PARSER =============
// geral
bool isValidNotNull(const char *str) {
    return (str != NULL && strcmp(str, "\0") != 0);
}
// verifica se uma string é apenas composta por digitos
bool isdigitAll(const char *string) {
    if (strlen(string) == 0) return isValidNotNull(string);
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])) {
            return false;
        }
    }
    return true;
}

bool isValidTime(const char *time) {
    int hours, minutes, seconds;

    if (sscanf(time, "%2d:%2d:%2d", &hours, &minutes, &seconds) != 3) {
        return false;
    }
    if ((hours < 10 && time[0] != '0') || (minutes < 10 && time[3] != '0') || (seconds < 10 && time[6] != '0')) {
        return false;
    }
    return (hours >= 0 && hours <= 23) && (minutes >= 0 && minutes <= 59) && (seconds >= 0 && seconds <= 59);
}

bool isValidDate(const char *date) {
    int year, month, day;

    if (sscanf(date, "%4d/%2d/%2d", &year, &month, &day) != 3) {
        return false;
    }
    if ((!isdigit(date[0]) || !isdigit(date[1])) || !isdigit(date[2]) || !isdigit(date[3])) return false;

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    if (month < 10 && date[5] != '0') {
        return false;
    }

    if (day < 10 && date[8] != '0') {
        return false;
    }

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[2] = 29;
    }

    return day <= daysInMonth[month];
}

bool isValidDate_Time(const char *dateTime) {
    int year, month, day, hours, minutes, seconds;
    if (sscanf(dateTime, "%4d/%2d/%2d %2d:%2d:%2d", &year, &month, &day, &hours, &minutes, &seconds) != 6) {
        return false;
    }

    char date[11], time[9];
    sscanf(dateTime, "%10s %8s", date, time);

    return isValidDate(date) && isValidTime(time);
}

// users
bool isValidEmail(const char *email) {
    const char *atSymbol = strchr(email, '@');

    if (atSymbol == NULL || atSymbol == email || atSymbol[1] == '\0') {
        return false;
    }

    const char *lastDot = strrchr(atSymbol, '.');
    if (lastDot == NULL || lastDot[1] == '\0') {
        return false;
    }

    return true;
}

bool isGenderValid(const char *gender) {
    return (gender[0] == 'M' || gender[0] == 'F') && strlen(gender) == 1;
}

bool isValidCountryCode(const char *str) {
    if (strlen(str) != MAX_COUNTRY_CODE) {
        return false;
    }
    if (!isalpha(str[0]) || !isalpha(str[1])) {
        return false;
    }
    return true;
}

void toUpperCase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

bool isValidAccountStatus(const char *str) {
    return (strcasecmp(str, "active\n") == 0 || strcasecmp(str, "inactive\n") == 0);
}

bool isValidPaymentMethod(const char *str) {
    return (strcmp(str, "cash") == 0 || strcmp(str, "debit_card") == 0 || strcmp(str, "credit_card") == 0);
}

// flights
bool isValidOriginAndDestination(const char *str) {
    return (strlen(str) == 3 && isalpha(str[0]) && isalpha(str[1]) && isalpha(str[2]));
};

// reservations
bool isValidHotelStars(const char *str) {
    double stars = atoi(str);
    return (stars >= 1 && stars <= 5 && (stars - (int)stars) == 0);
}

bool isValidCityTax(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return false;
        }
    }
    int tax = atoi(str);
    return (tax >= 0);
}

bool isValidPricePerNight(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return false;
        }
    }
    int price = atoi(str);
    return (price > 0);
}

bool isValidInclude_Breakfast(const char *str) {
    return (strlen(str) == 0 || strcasecmp(str, "f") == 0 || strcasecmp(str, "false") == 0 || strcasecmp(str, "0") == 0 || strcasecmp(str, "t") == 0 || strcasecmp(str, "true") == 0 || strcasecmp(str, "1") == 0);
}

bool isValidRating(const char *str) {
    if (str[0] == '\0') {  // Allow empty strings
        return true;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return false;
        }
    }
    int rating = atoi(str);
    return (rating >= 1 && rating <= 5);
}

bool isValidField_user(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1:  // ID
            return isValidNotNull(value);
            break;
        case 2:  // Nome
            return isValidNotNull(value);
            break;
        case 3:  // Email
            return isValidEmail(value);
        case 4:  // Número de telefone
            return isValidNotNull(value);
        case 5:  // Data de nascimento
            return isValidDate(value);
        case 6:  // Sexo
            return isGenderValid(value);
        case 7:  // Passaporte
            return isValidNotNull(value);
        case 8:  // Country Code
            return isValidCountryCode(value);
        case 9:  // Morada
            return isValidNotNull(value);
        case 10:  // Account creation
            return isValidDate_Time(value);
        case 11:  // Método de pagamento
            return isValidNotNull(value);
        case 12:  // Estado da conta
            return isValidAccountStatus(value);
        default:
            break;
    }
    return false;
}

bool isValidField_flight(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1:  // ID
            return isValidNotNull(value);
        case 2:  // Airline
            return isValidNotNull(value);
        case 3:  // plain_model
            return isValidNotNull(value);
        case 4:  // total_seats
            return isdigitAll(value);
        case 5:  // origin
            return isValidOriginAndDestination(value);
        case 6:  // destination
            return isValidOriginAndDestination(value);
        case 7:  // schedule_departure_date
            return isValidDate_Time(value);
        case 8:  // schedule_arrival_date
            return isValidDate_Time(value);
        case 9:  // real_departure_date
            return isValidDate_Time(value);
        case 10:  // real_arrival_date
            return isValidDate_Time(value);
        case 11:  // pilot
            return isValidNotNull(value);
        case 12:  // copilot
            return isValidNotNull(value);
        case 13:
            return true;
        default:
            break;
    }

    return false;
}

bool isValidField_passenger(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1:  // user_id
            return isValidNotNull(value);

        case 2:  // flight_id
            return isValidNotNull(value);

        default:
            break;
    }
    return false;
}

bool isValidField_reservation(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1:  // ID
            return isValidNotNull(value);
        case 2:  // user_id
            return isValidNotNull(value);
        case 3:  // hotel_id
            return isValidNotNull(value);
        case 4:  // hotel_name
            return isValidNotNull(value);
        case 5:  // hotel_stars
            return (isValidHotelStars(value) && isdigitAll(value));
        case 6:  // city_tax
            return isValidCityTax(value);
        case 7:  // address
            return isValidNotNull(value);
        case 8:  // begin date
            return isValidDate(value);
        case 9:  // end_date
            return isValidDate(value);
        case 10:  // price_per_night
            return isdigitAll(value);
        case 11:  // include_breakfast
            return isValidInclude_Breakfast(value);
        case 12:  // room_details
            return true;
        case 13:  // rating
            return isValidRating(value);
        case 14:  // comment
            return true;
        default:
            break;
    }
    return false;
}