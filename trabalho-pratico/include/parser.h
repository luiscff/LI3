#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <validation.h>

#include "Catalog/stats.h"
#include "utils.h"

#define MAX_PHONE 12
#define MAX_PASSPORT 8
#define MAX_COUNTRY_CODE 2

// void parseCSV(const char *filepath, int token, void *catalog, void *users_catalog, void *flights_catalog, STATS *stats);
void parseFiles(const char *folderPathDataset, void *users_catalog, void *flights_catalog, void *reservations_catalog, void *passengers_catalog, void *stats);

#endif
