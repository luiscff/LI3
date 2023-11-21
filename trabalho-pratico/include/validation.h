#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>

// Funções de validação de campos
bool isValidField_user(const char *value, int fieldIndex);

bool isValidField_flight(const char *value, int fieldIndex, char *schedule_begin_date, char *real_begin_date);

bool isValidField_passenger(const char *value, int fieldIndex);

bool isValidField_reservation(const char *value, int fieldIndex, char *begin_date);


#endif
