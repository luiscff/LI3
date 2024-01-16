#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define current_date "2023/10/01"
char* fix_flight_id(int num) {
    char* str = malloc(11);  // Allocate space for 10 digits and the null terminator
    if (str == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    sprintf(str, "%010d", num);  // Format the integer with leading zeros
    return str;
}

bool isDateTime1BeforeDateTime2(const char* date1, const char* date2) {
    // Convertendo strings de datas para inteiros
    char *begin = strdup(date1);
    char *end = strdup(date2);

    int year1, month1, day1, hours1, minutes1, seconds1;
    int year2, month2, day2, hours2, minutes2, seconds2;

    if (sscanf(begin, "%4d/%2d/%2d %2d:%2d:%2d", &year1, &month1, &day1, &hours1, &minutes1, &seconds1) != 6 ||
        sscanf(end, "%4d/%2d/%2d %2d:%2d:%2d", &year2, &month2, &day2, &hours2, &minutes2, &seconds2) != 6) {
        free(begin);
        free(end);
        printf("sscanf error\n");
        return false; // As datas não estão no formato correto
    }

    free(begin);
    free(end);

    // Comparando anos
    if (year1 < year2) {
        return true;
    } else if (year1 > year2) {
        return false;
    }

    // Comparando meses
    if (month1 < month2) {
        return true;
    } else if (month1 > month2) {
        return false;
    }

    // Comparando dias
    if (day1 < day2) {
        return true;
    } else if (day1 > day2) {
        return false;
    }

    // Comparando horas
    if (hours1 < hours2) {
        return true;
    } else if (hours1 > hours2) {
        return false;
    }

    // Comparando minutos
    if (minutes1 < minutes2) {
        return true;
    } else if (minutes1 > minutes2) {
        return false;
    }

    // Comparando segundos
    if (seconds1 < seconds2) {
        return true;
    } else if (seconds1 > seconds2) {
        return false;
    }

    return true; // As datas são iguais

}

bool isDate1BeforeDate2(const char *date1, const char *date2) {
    // Convertendo strings de datas para inteiros
    char *begin = strdup(date1);
    char *end = strdup(date2);

    int year1, month1, day1;
    int year2, month2, day2;

    if (sscanf(begin, "%4d/%2d/%2d", &year1, &month1, &day1) != 3 ||
        sscanf(end, "%4d/%2d/%2d", &year2, &month2, &day2) != 3) {
        free(begin);
        free(end);
        printf("sscanf error\n");
        return false; // As datas não estão no formato correto
    }

    free(begin);
    free(end);

    // Comparando anos
    if (year1 < year2) {
        return true;
    } else if (year1 > year2) {
        return false;
    }

    // Comparando meses
    if (month1 < month2) {
        return true;
    } else if (month1 > month2) {
        return false;
    }

    // Comparando dias
    if (day1 < day2) {
        return true; // A data 1 é menor
    } else if (day1 > day2) {
        return false; // A data 2 é menor
    }  
    return true; // As datas são iguais
}

int isNumber(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (isdigit(s[i]) == 0)
            return 0;
    }
    return 1;
}
char* convert_to_upper_case(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }

    return str;
}

int choose_entity(char* id) {
    int entity = 0;
    if (strncmp(id, "Book", 4) == 0)
        // Se o ID começar por Book, é uma reserva
        entity = 1;
    else if (isNumber(id) == true)
        // Se o ID for um número, é um voo
        entity = 2;
    else
        // Se não for nenhum dos anteriores, é um utilizador
        entity = 3;

    // free(id_aux);
    return entity;
}

char* bool_to_string(bool boolean) {
    if (boolean == true)
        return "True";
    else
        return "False";
}

int calc_idade(char* birth_date) {
    int ano_nascimento, mes_nascimento, dia_nascimento;
    int ano_atual, mes_atual, dia_atual;

    sscanf(birth_date, "%d/%d/%d", &ano_nascimento, &mes_nascimento, &dia_nascimento);
    sscanf(current_date, "%d/%d/%d", &ano_atual, &mes_atual, &dia_atual);

    int idade = ano_atual - ano_nascimento;

    if (mes_atual < mes_nascimento || (mes_atual == mes_nascimento && dia_atual < dia_nascimento)) {
        idade--;
    }  // Ajustar a idade caso ainda nao tenha feito anos nesse mesmo ano
    return idade;
}