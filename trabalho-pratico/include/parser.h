#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#define MAX_PHONE 12
#define MAX_PASSPORT 8
#define MAX_COUNTRY_CODE 2

void toUpperCase(char *str);
bool isValidAddress(const char *str);
bool isValidTime(const char *time);
bool isValidDate(const char *date);
bool isValidDate_Time(const char *dateTime); // isValidAccountCreation
bool isValidAccountStatus(const char *str);
bool isValidPaymentMethod(const char *str);
bool isValidCountryCode(const char *str);
bool isValidPassport(const char *str);
bool isGenderValid(const char *gender);
bool isValidEmail(const char *email);
void removeNonNumericChars(char *str);
bool isValidPhoneNumber(const char *phoneNumber);
bool isValidField_user(const char *value, int fieldIndex);
void parseLine_user(char *line);
bool isValidField_flight(const char *value, int fieldIndex);
void parseLine_flight(char *line);
bool isValidField_passenger(const char *value, int fieldIndex);
void parseLine_passenger(char *line);
bool isValidField_reservation(const char *value, int fieldIndex);
void parseLine_reservation(char *line);
void parseCSV(const char *filepath,int token);
void writeToFile(char *line, const char *filename);


#endif
