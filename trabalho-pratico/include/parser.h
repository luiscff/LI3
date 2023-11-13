#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#define MAX_PHONE 12
#define MAX_PASSPORT 8
#define MAX_COUNTRY_CODE 2

bool isValidAddress(const char *str);
bool isValidTime(const char *time);
bool isValidDate(const char *date);
bool isValidAccountCreation(const char *dateTime);
bool isValidAccountStatus(const char *str);
bool isValidPaymentMethod(const char *str);
bool isValidCountryCode(const char *str);
bool isValidPassport(const char *str);
bool isGenderValid(const char *gender);
bool isValidEmail(const char *email);
void removeNonNumericChars(char *str);
bool isValidPhoneNumber(const char *phoneNumber);
bool isValidField(const char *value, int fieldIndex);
void parseLine(char *line);
void parseCSV(const char *filepath);

#endif