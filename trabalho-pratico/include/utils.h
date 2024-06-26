#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

char* fix_flight_id(int num);
bool isDateTime1BeforeDateTime2(const char* date1, const char* date2);
bool isDate1BeforeDate2(const char* date1, const char* date2);

int isNumber(char s[]);
char* convert_to_upper_case(char* str);

int choose_entity(char* id);

char* bool_to_string(bool boolean);

int calc_idade(char* birth_date);

int verificaPrefixo(const char* string, const char* prefixo);

void convert_to_lower_case(char* str);
char* remove_accents(const char* str);
void removeAspas(char* str);

#endif