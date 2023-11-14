#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define MAX_NAME 256
// #define MAX_EMAIL 256
#define MAX_PHONE 12
// #define MAX_ADDRESS 256
// #define MAX_BIRTH_DATE 10
#define MAX_PASSPORT 8
#define MAX_COUNTRY_CODE 2
// #define MAX_DATE_TIME 20



bool isValidAddress(const char *str) {
    return (str != NULL);
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

bool isValidAccountStatus(const char *str) {
    return (strcmp(str, "active") == 0 || strcmp(str, "inactive") == 0);
}

bool isValidPaymentMethod(const char *str) {
    return (strcmp(str, "cash") == 0 || strcmp(str, "debit_card") == 0 || strcmp(str, "credit_card") == 0);
}

bool isValidCountryCode(const char *str) {
    if (strlen(str) != MAX_COUNTRY_CODE) {
        return false;
    }
    if (!isupper(str[0]) || !isupper(str[1])) {
        return false;
    }
    return true;
}

bool isValidPassport(const char *str) {
    if (strlen(str) != MAX_PASSPORT) {
        return false;
    }

    if (!isupper(str[0]) || !isupper(str[1])) {
        return false;
    }

    for (int i = 2; i < MAX_PASSPORT; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

bool isGenderValid(const char *gender) {
    return (gender[0] == 'M' || gender[0] == 'F') && strlen(gender) == 1;
}

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

void removeNonNumericChars(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ' || str[i] == '(' || str[i] == ')') {
            continue;
        }
        str[count++] = str[i];
    }
    str[count] = '\0';
}

bool isValidPhoneNumber(const char *phoneNumber) {
    char cleanedNumber[20];
    strcpy(cleanedNumber, phoneNumber);
    removeNonNumericChars(cleanedNumber);

    size_t len = strlen(cleanedNumber);
    for (int j = 0; j < len; j++) {
        if (!isdigit(cleanedNumber[j])) return false;
    }
    return len >= 9 && len <= MAX_PHONE;
}

bool isValidField_user(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1: // ID
            return isValidAddress(value);
            break;
        case 2: // Nome
            return isValidAddress(value);
            break;
        case 3: // Email
            return isValidEmail(value);
        case 4: // Número de telefone
            return isValidPhoneNumber(value);
        case 5: // Data de nascimento
            return isValidDate(value);
        case 6: // Sexo
            return isGenderValid(value);
        case 7: // Passaporte
            return isValidPassport(value);
        case 8: // Country Code
            return isValidCountryCode(value);
        case 9: // Morada
            return isValidAddress(value);
        case 10: // Método de pagamento
            return isValidPaymentMethod(value);
        case 11: // Estado da conta
            return isValidAccountStatus(value);
        default:
            break;
    }

    return false;
}

void parseLine_user(char *line) {
    char *token;
    int fieldIndex = 1;

    token = strtok(line, ";");

    while (token != NULL) {
        if (isValidField_user(token, fieldIndex)) {
            printf("%s", token);
        } else {
            printf("Erro no Campo %d", fieldIndex);// depois meter num ficheiro de erros em vez do printf
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }
        printf("\n");
}



bool isValidField_flight(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1: // ID
            return isValidAddress(value);
            break;
        case 2: // Airline
            return isValidAddress(value);
            break;
        case 3: // plain_model
            return isValidAddress(value);
        case 4: // total_seats
            return isValidAddress(value);
        case 5: // origin
            return isValidAddress(value);
        case 6: // destination
            return isValidAddress(value);
        case 7: // schedule_departure_date
            return isValidDate_Time(value);
        case 8: // schedule_arrival_date
            return isValidDate_Time(value);
        case 9: // real_departure_date
            return isValidDate_Time(value);
        case 10: // real_arrival_date
            return isValidDate_Time(value);
        case 11: // pilot
            return isValidAddress(value);
        case 12: // copilot
            return isValidAddress(value);
        default:
            break;
    }

    return false;
}

void parseLine_flight(char *line) {
    char *token;
    int fieldIndex = 1;

    token = strtok(line, ";");

    while (token != NULL) {
        if (isValidField_flight(token, fieldIndex)) {
            printf("%s", token);
        } else {
            printf("Erro no Campo %d", fieldIndex);// depois meter num ficheiro de erros em vez do printf
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }
    printf("\n");
}



bool isValidField_passenger(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1: // user_id
            return isValidAddress(value);

        case 2: // flight_id
            return isValidAddress(value);

        default:
            break;
    }
    return false;
}

void parseLine_passenger(char *line) {
    char *token;
    int fieldIndex = 1;

    token = strtok(line, ";");

    while (token != NULL) {
        if (isValidField_passenger(token, fieldIndex)) { // <- possivel mudança para melhorar codigo
            printf("%s", token);
        } else {
            printf("Erro no Campo %d", fieldIndex);// depois meter num ficheiro de erros em vez do printf
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }
    printf("\n");
}

bool isValidField_reservation(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1: // ID
            return isValidAddress(value);
        case 2: // user_id
            return isValidAddress(value);
        case 3: // hotel_id
            return isValidAddress(value);
        case 4: // hotel_name
            return isValidAddress(value);
        case 5: // hotel_stars
            return isValidAddress(value);
        case 6: // city_tax
            return isValidAddress(value);
        case 7: // address
            return isValidAddress(value);
        case 8: // begin date
            return isValidDate_Time(value);
        case 9: // end_date
            return isValidDate_Time(value);
        case 10: // price_per_night
            return isValidAddress(value);
        case 11: // room_details
            return isValidAddress(value);
        case 12: // rating
            return isValidAddress(value);
        case 13: // comment
            return isValidAddress(value); //?
        default:
            break;
    }
    return false;
}

void parseLine_reservation(char *line) {
    char *token;
    int fieldIndex = 1;

    token = strtok(line, ";");

    while (token != NULL) {
        if (isValidField_reservation(token, fieldIndex)) { // <- possivel mudança para melhorar codigo
            printf("%s", token);
        } else {
            printf("Erro no Campo %d", fieldIndex);// depois meter num ficheiro de erros em vez do printf
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }
    printf("\n");
}



void parseCSV(const char *filepath,int token) {
    FILE *file = fopen(filepath, "r");
    int opt = token;
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filepath);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    //gets rid of first line
    if ((read = getline(&line, &len, file)) != -1) {
        line = NULL;
        len = 0;
    }

    if (token == 1)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_user(line);
        }

    if (token == 2)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_flight(line);
        }

    if (token == 3)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_passenger(line);
        }

    if (token == 4)
        while ((read = getline(&line, &len, file)) != -1) {
            parseLine_reservation(line);
        }

    free(line);
    fclose(file);
}



