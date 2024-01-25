#ifndef OUTPUT_H
#define OUTPUT_H

#define MAX_PATH_SIZE 256

// ficheiros de resultados
void create_result_file(const char *folderPath, int lineNumber, const char *content);

// ficheiros de erros
void writeToErrorFileUser(char *line, const char *filename);

void writeToErrorFileReservation(char *line, const char *filename);

void writeToErrorFileFlight(char *line, const char *filename);

void writeToErrorFilePassenger(char *line, const char *filename);

#endif
