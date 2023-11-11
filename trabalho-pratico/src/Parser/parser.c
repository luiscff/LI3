#define MAX_NAME 256
#define MAX_EMAIL 256
#define MAX_PHONE 12
#define MAX_ADDRESS 256
#define MAX_BIRTH_DATE 10
#define MAX_PASSPORT 8
#define MAX_COUNTRY_CODE 2
#define MAX_DATE_TIME 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseCSV(const char *filepath) {
    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Could not open file %s\n", filepath);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        char *token;

        // get the first token
        token = strtok(line, ";");

        // walk through other tokens
        while (token != NULL ) { //TODO dá print de um espaço vazio
            printf(" %s\n", token);
            token = strtok(NULL, ";");
        }
    }

    free(line);
    fclose(file);
}


//path do input é ignorado para já
int main(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filePath> <inputPath>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    parseCSV(filepath);

    return 0;
}
