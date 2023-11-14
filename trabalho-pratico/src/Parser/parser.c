#include "parser.h"

#include <ctype.h>
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
// #define MAX_PASSPORT 8
#define MAX_COUNTRY_CODE 2
// #define MAX_DATE_TIME 20


//=========== VALIDATION =============
//geral
bool isValidNotNull(const char *str) {
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
    if ((!isdigit(date[0])||!isdigit(date[1]))||!isdigit(date[2])||!isdigit(date[3])) return false;

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

//users
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
    if (!isupper(str[0]) || !isupper(str[1])) {
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

//flights
bool isValidOriginAndDestination (const char *str) {
    return (strlen(str) == 3 && isalpha(str[0]) && isalpha(str[1]) && isalpha(str[2]));
};

//reservations
bool isValidHotelStars (const char *str) {
    int stars = atoi(str);
    return (stars >= 1 && stars <= 5);
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

bool isValidInclude_Breakfast(const char *str) { //strcasecmp is case insensitive
   return (strcasecmp(str,"f") == 0 || strcasecmp(str,"false") == 0 || strcasecmp(str,"0") == 0 || strcasecmp(str,"") == 0 || strcasecmp(str,"t") == 0 || strcasecmp(str,"true") == 0 || strcasecmp(str,"1") == 0);
}

bool isValidRating(const char *str) {
    if (str[0] == '\0') { // Allow empty strings
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
        case 1: // ID
            return isValidNotNull(value);
            break;
        case 2: // Nome
            return isValidNotNull(value);
            break;
        case 3: // Email
            return isValidEmail(value);
        case 4: // Número de telefone
            return isValidNotNull(value);
        case 5: // Data de nascimento
            return isValidDate(value);
        case 6: // Sexo
            return isGenderValid(value);
        case 7: // Passaporte
            return isValidNotNull(value);
        case 8: // Country Code
            return isValidCountryCode(value);
        case 9: // Morada
            return isValidNotNull(value);
        case 10: //Account creation
            return isValidDate_Time(value);
        case 11: // Método de pagamento
            return isValidNotNull(value);
        case 12: // Estado da conta
            return isValidAccountStatus(value);
        default:
            break;
    }
    return false;
}

void parseLine_user(char *line) {
    char *token;
    int fieldIndex = 1;
    int f = 1;
    char *lineCopy = strdup(line);

    FILE *errorFile = fopen("Resultados/users_errors.csv", "a");
    token = strtok(lineCopy, ";");
    while (token != NULL&&isValidField_user(token,fieldIndex)) {
        token = strtok(NULL, ";");
        fieldIndex++;
    }
    token = strtok(line,";");
    if (fieldIndex==13)
        {
            while(token!=NULL)
            {
            printf("%s", token);
            token = strtok(NULL, ";");
            }
        }
        else{
    while (f<13) {
        if(token!=NULL)
        fprintf(errorFile, ";%s", token);
        else fprintf(errorFile, " ;");
        token = strtok(NULL, ";");
        f++;}
    }
    fclose(errorFile);
    free(lineCopy);
    printf("\n");
}

bool isValidField_flight(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1: // ID
            return isValidNotNull(value);
        case 2: // Airline
            return isValidNotNull(value);
        case 3: // plain_model
            return isValidNotNull(value);
        case 4: // total_seats
            return true; //TODO O número de lugares de um voo (total_seats) não poderá ser inferior ao número de passageiros nesse voo;
        case 5: // origin
            return isValidOriginAndDestination(value);
        case 6: // destination
            return isValidOriginAndDestination(value);
        case 7: // schedule_departure_date
            return isValidDate_Time(value); //TODO ver se end_date é maior do que begin_date (vai ter que ser depois de haver hash tables feitas)
        case 8: // schedule_arrival_date
            return isValidDate_Time(value);
        case 9: // real_departure_date
            return isValidDate_Time(value); //TODO ver se end_date é maior do que begin_date (vai ter que ser depois de haver hash tables feitas)
        case 10: // real_arrival_date
            return isValidDate_Time(value);
        case 11: // pilot
            return isValidNotNull(value);
        case 12: // copilot
            return isValidNotNull(value);
        case 13:
            return true;
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
            return isValidNotNull(value);

        case 2: // flight_id
            return isValidNotNull(value);

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
        if (isValidField_passenger(token, fieldIndex)) {
            printf("%s", token);
        } else {
            FILE *errorFile = fopen("Resultados/passenger_errors.csv", "a");
            if (errorFile != NULL) {
                fprintf(errorFile, "%s", line);
                fclose(errorFile);
            } else {
                fprintf(stderr, "Erro ao abrir o arquivo passenger_errors.csv\n");
            }
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }
    printf("\n");
}



bool isValidField_reservation(const char *value, int fieldIndex) {
    switch (fieldIndex) {
        case 1: // ID
            return isValidNotNull(value);
        case 2: // user_id
            return isValidNotNull(value);
        case 3: // hotel_id
            return isValidNotNull(value);
        case 4: // hotel_name
            return isValidNotNull(value);
        case 5: // hotel_stars
            return isValidHotelStars(value);
        case 6: // city_tax
            return isValidCityTax(value);
        case 7: // address
            return isValidNotNull(value);
        case 8: // begin date
            return isValidDate(value);
        case 9: // end_date
            return isValidDate(value); //TODO ver se end_date é maior do que begin_date (vai ter que ser depois de haver hash tables feitas)
        case 10: // price_per_night
            return isValidPricePerNight(value);
        case 11: //include_breakfast
            return isValidInclude_Breakfast(value);
        case 12: // room_details
            return true;
        case 13: // rating
            return isValidRating(value);
        case 14: // comment
            return true;
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
            FILE *errorFile = fopen("/../../Resultados/reservation_errors.csv", "a");
            if (errorFile != NULL) {
                fprintf(errorFile, "%s", line);
                fclose(errorFile);
            } else {
                fprintf(stderr, "Erro ao abrir o arquivo reservation_errors.csv\n");
            }
        }
        token = strtok(NULL, ";");
        fieldIndex++;
    }
    printf("\n");
}



void parseCSV(const char *filepath,int token) {
    FILE *file = fopen(filepath, "r");
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


