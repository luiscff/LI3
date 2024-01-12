#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

char* fix_flight_id(int num);
bool isDateTime1BeforeDateTime2(const char* date1, const char* date2);
bool isDate1BeforeDate2(const char *date1, const char *date2);

#endif