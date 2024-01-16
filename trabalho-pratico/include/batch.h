#ifndef BATCH_H
#define BATCH_H

#include "interpreter.h"
#include "parser.h"

void batchMode(const char *folderPathDataset, const char *inputPath, void *users_catalog, void *flights_catalog, void *reservations_catalog, void *passengers_catalog, void *stats);

#endif