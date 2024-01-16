#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "interpreter.h"
#include "parser.h"

void interactiveMode(const char *folderPathDataset, void *users_catalog, void *flights_catalog, void *reservations_catalog, void *passengers_catalog, void *stats);

#endif