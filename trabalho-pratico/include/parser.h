#ifndef PARSER_H
#define PARSER_H

#include <validation.h>
#include <stdbool.h>
#include "Catalog/stats.h"
#include "utils.h"


#define MAX_PHONE 12
#define MAX_PASSPORT 8
#define MAX_COUNTRY_CODE 2


void parseCSV(const char *filepath, int token, void *catalog, void *users_catalog, void *flights_catalog, STATS *stats);



#endif


