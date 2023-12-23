#include <ctype.h>
#include <stdio.h>

// para converter para minusculas e retirar acentos
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#include "queries.h"

#define current_date "2023/10/01"

// aux query 1

int isNumber(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (isdigit(s[i]) == 0)
            return 0;
    }
    return 1;
}

int choose_entity(char* id) {
    int entity = 0;
    if (strncmp(id, "Book", 4) == 0)
        // Se o ID começar por Book, é uma reserva
        entity = 1;
    else if (isNumber(id) == TRUE)
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
// aux q2

typedef struct aux_q2 {
    char* id;
    char* date;
    char* type;
}AUX_Q2;


void set_aux_id(AUX_Q2 *aux, const char *id) {
    if (aux->id!=NULL) free(aux->id);
    aux->id = strdup(id);
}

void set_aux_date(AUX_Q2 *aux, const char *date) {
    if (aux->date) free(aux->date);
    aux->date = strdup(date);
}

void set_aux_type(AUX_Q2 *aux, const char *type) {
    aux->type = strdup(type);
}


char* extractDate(const char* inputString) {
    char* datePart = malloc(11);
    if (datePart != NULL) {
        strncpy(datePart, inputString, 10);
        datePart[10] = '\0';
        return datePart;
    } else {
        return NULL;  // Memory allocation failed
    }
}

char* fix_flight_id(int num) {
    char* str = malloc(11);  // Allocate space for 10 digits and the null terminator
    if (str == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    sprintf(str, "%010d", num);  // Format the integer with leading zeros
    return str;
}

int sort_function_q2_nocat(gconstpointer a, gconstpointer b) {
    const AUX_Q2* aux1 = a;
    const AUX_Q2* aux2 = b;

    // ordenadas por data de início (da mais recente para a mais antiga).
    char* date1 = strdup(aux1->date);
    char* date2 = strdup(aux2->date);

    int ano1, mes1, dia1;
    sscanf(date1, "%d/%d/%d", &ano1, &mes1, &dia1);

    int ano2, mes2, dia2;
    sscanf(date2, "%d/%d/%d", &ano2, &mes2, &dia2);

    // compara anos
    if (ano1 > ano2) {
        return -1;
    } else if (ano1 < ano2) {
        return 1;
    }

    // compara meses
    if (mes1 > mes2) {
        return -1;
    } else if (mes1 < mes2) {
        return 1;
    }

    // compara dias
    if (dia1 > dia2) {
        return -1;
    } else if (dia1 < dia2) {
        return 1;
    }

    // quando as datas são iguais
    // o identificador da reserva é o critério de desempate (de forma crescente).
    char* id1 = strdup(aux1->id);
    char* id2 = strdup(aux2->id);

    // compara os ids (strings) como num dicionario
    if (strcmp(id1, id2) < 0) {
        return -1;
    } else if (strcmp(id1, id2) > 0) {
        return 1;
    }

    printf("ERRO no sort da query2: os voos têm a mesma data e o mesmo id\n");
    return 0;

}

int sort_function_q2(gconstpointer a, gconstpointer b) {
    const FLIGHT* flight1 = a;
    const FLIGHT* flight2 = b;

    // ordenadas por data de início (da mais recente para a mais antiga).
    char* date1 = strdup(extractDate(get_schedule_departure_date(flight1)));
    char* date2 = strdup(extractDate(get_schedule_departure_date(flight2)));

    int ano1, mes1, dia1;
    sscanf(date1, "%d/%d/%d", &ano1, &mes1, &dia1);

    int ano2, mes2, dia2;
    sscanf(date2, "%d/%d/%d", &ano2, &mes2, &dia2);

    // compara anos
    if (ano1 > ano2) {
        return -1;
    } else if (ano1 < ano2) {
        return 1;
    }

    // compara meses
    if (mes1 > mes2) {
        return -1;
    } else if (mes1 < mes2) {
        return 1;
    }

    // compara dias
    if (dia1 > dia2) {
        return -1;
    } else if (dia1 < dia2) {
        return 1;
    }

    // quando as datas são iguais
    // o identificador da reserva é o critério de desempate (de forma crescente).
    int id1 = get_flight_id(flight1);
    int id2 = get_flight_id(flight2);

    // compara os ids (strings) como num dicionario
    if (id1 < id2) {
        return -1;
    } else if (id1 > id2) {
        return 1;
    }

    printf("ERRO no sort da query2: os voos têm a mesma data e o mesmo id\n");
    return 0;
}

// aux 3

// aux 4
int sort_function_q4(gconstpointer a, gconstpointer b) {
    const RESERVATION* res1 = a;
    const RESERVATION* res2 = b;

    // ordenadas por data de início (da mais recente para a mais antiga).
    char* date1 = strdup(get_begin_date(res1));
    char* date2 = strdup(get_begin_date(res2));

    int ano1, mes1, dia1;
    sscanf(date1, "%d/%d/%d", &ano1, &mes1, &dia1);

    int ano2, mes2, dia2;
    sscanf(date2, "%d/%d/%d", &ano2, &mes2, &dia2);

    // compara anos
    if (ano1 > ano2) {
        return -1;
    } else if (ano1 < ano2) {
        return 1;
    }

    // compara meses
    if (mes1 > mes2) {
        return -1;
    } else if (mes1 < mes2) {
        return 1;
    }

    // compara dias
    if (dia1 > dia2) {
        return -1;
    } else if (dia1 < dia2) {
        return 1;
    }

    // quando as datas são iguais
    // o identificador da reserva é o critério de desempate (de forma crescente).
    char* id1 = strdup(get_reservation_id(res1));
    char* id2 = strdup(get_reservation_id(res2));

    // compara os ids (strings) como num dicionario
    if (strcmp(id1, id2) < 0) {
        return -1;
    } else if (strcmp(id1, id2) > 0) {
        return 1;
    }

    printf("ERRO no sort da query4: as reservas têm a mesma data e o mesmo id\n");
    return 0;
}

// aux q7

typedef struct aux_q7 {
    char* origin;
    GList* delays;  // Guarda os atrasos em segundos
}AUX_Q7;

char *get_aux_origin(const AUX_Q7 *aux) { return aux->origin; }

gboolean compare_origin(gconstpointer data, gconstpointer user_data) {
    const AUX_Q7 *element = (const AUX_Q7 *)data;
    const char *target_origin = (const char *)user_data;

    // Use strcmp para comparar as origens
    return strcmp(element->origin, target_origin) == 0;
}

gint compare_ints(gconstpointer a, gconstpointer b) {
    return GPOINTER_TO_INT(a) - GPOINTER_TO_INT(b);
}

// Função para calcular a mediana de um GArray de inteiros
int calcula_mediana(GList* list) {
    GList* ordenada = g_list_sort(list, compare_ints);

    guint size = g_list_length(list);
    if (size == 0) {
        // Array vazio, mediana indefinida
        return 0.0;
    }

    if (size % 2 == 0) {
        // Número par de elementos, calcular a média dos dois valores do meio
        int middle1 = GPOINTER_TO_INT(g_list_nth(ordenada, size / 2 - 1));
        int middle2 = GPOINTER_TO_INT(g_list_nth(ordenada,  size / 2));
        return (middle1 + middle2) / 2.0;
    } else {
        // Número ímpar de elementos, a mediana é o valor do meio
        return GPOINTER_TO_INT(g_list_nth(ordenada,  size / 2));
    }
}

// Função de comparação para ordenar aeroportos por mediana e desempatar pelo nome do aeroporto
gint compare_airports(gconstpointer a, gconstpointer b) {
    const AUX_Q7* airport1 = (const AUX_Q7*)a;
    const AUX_Q7* airport2 = (const AUX_Q7*)b;

    int mediana_a = calcula_mediana(airport1->delays);
    int mediana_b = calcula_mediana(airport2->delays);

    if (mediana_a > mediana_b) return 1;
    else if (mediana_a < mediana_b) return -1;
    
    else return strcmp(airport1->origin, airport2->origin); // Se as medianas forem iguais, use o nome do aeroporto como critério de desempate
        
}



// aux 9
int verificaPrefixo(const char* string, const char* prefixo) {
    size_t tamanhoPrefixo = strlen(prefixo);

    // Compara os primeiros 'tamanhoPrefixo' caracteres
    int resultadoComparacao = strncmp(string, prefixo, tamanhoPrefixo);

    // Se resultadoComparacao for 0, significa que o prefixo foi encontrado
    return (resultadoComparacao == 0);
}

void convert_to_lower_case(char* str) {
    if (str == NULL) {
        printf("String is NULL\n");
        return;
    }
    setlocale(LC_ALL, "");                // set the locale to the user's default locale
    size_t len = mbstowcs(NULL, str, 0);  // get the number of wide characters
    wchar_t* wstr = malloc((len + 1) * sizeof(wchar_t));
    if (wstr == NULL) {
        printf("Failed to allocate memory\n");
        return;
    }
    mbstowcs(wstr, str, len + 1);  // convert the string to a wide string

    for (size_t i = 0; i < len; i++) {
        wstr[i] = towlower(wstr[i]);  // convert to lowercase
    }

    wcstombs(str, wstr, len + 1);  // convert the wide string back to a multibyte string
    free(wstr);
}

void remove_accents(char* str) {
    setlocale(LC_ALL, "");                // set the locale to the user's default locale
    size_t len = mbstowcs(NULL, str, 0);  // get the number of wide characters
    wchar_t* wstr = malloc((len + 1) * sizeof(wchar_t));
    mbstowcs(wstr, str, len + 1);  // convert the string to a wide string

    for (size_t i = 0; i < len; i++) {
        switch (wstr[i]) {
            case L'ã':
            case L'á':
            case L'à':
            case L'â':
                wstr[i] = L'a';
                break;
            case L'é':
            case L'è':
            case L'ê':
                wstr[i] = L'e';
                break;
            case L'í':
            case L'ì':
            case L'î':
                wstr[i] = L'i';
                break;
            case L'ó':
            case L'ò':
            case L'ô':
                wstr[i] = L'o';
                break;
            case L'ú':
            case L'ù':
            case L'û':
                wstr[i] = L'u';
                break;
            case L'ç':
                wstr[i] = L'c';
                break;
        }
    }

    wcstombs(str, wstr, len + 1);  // convert the wide string back to a multibyte string
    free(wstr);
}

int sort_function_q9(gconstpointer a, gconstpointer b) {
    // formato das strings recebidas (a e b): "id;name"

    // saca os 2 tokens da string a
    char* aux1 = strdup(a);
    char* id1 = strtok(aux1, ";");
    char* name1 = strtok(NULL, ";");

    // saca os 2 tokens da string b
    char* aux2 = strdup(b);
    char* id2 = strtok(aux2, ";");
    char* name2 = strtok(NULL, ";");

    // se os nomes tiverem "-" mudar para " "

    for (int i = 0; name1[i] != '\0'; i++) {
        if (name1[i] == '-') {
            name1[i] = ' ';
        }
    }

    for (int i = 0; name2[i] != '\0'; i++) {
        if (name2[i] == '-') {
            name2[i] = ' ';
        }
    }

    // converter para minusculas e retirar acentos
    convert_to_lower_case(id1);
    convert_to_lower_case(id2);
    convert_to_lower_case(name1);
    convert_to_lower_case(name2);

    remove_accents(id1);
    remove_accents(id2);
    remove_accents(name1);
    remove_accents(name2);

    // ordenados por nome (de forma crescente).
    // compara os nomes (strings) como num dicionario

    int result = strcmp(name1, name2);
    if (result == 0) {
        // quando os nomes são iguais o identificador do utilizador é o critério de desempate (de forma crescente).
        // compara os ids (strings) como num dicionario
        result = strcmp(id1, id2);
    }

    if (result == 0) printf("ERRO no sort da query9: os utilizadores têm o mesmo nome e o mesmo id\n");

    return result;
}

//--------------

char* query1(USERS_CATALOG* ucatalog, FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, PASSENGERS_CATALOG* pcatalog, char* id) {
    char* aux = strdup(id);
    int entity = choose_entity(aux);
    if (entity == 1) {  // se for uma reserva
        RESERVATION* reservation = get_reservation_by_id(rcatalog, aux);
        if (reservation == NULL) {
            printf("Reservation not found\n");
            return NULL;
        }
        char* hotel_id = strdup(get_hotel_id(reservation));
        char* hotel_name = strdup(get_hotel_name(reservation));
        int hotel_stars = get_hotel_stars(reservation);
        char* begin_date = strdup(get_begin_date(reservation));
        char* end_date = strdup(get_end_date(reservation));
        char* includes_breakfast = strdup(bool_to_string(get_includes_breakfast(reservation)));

        int num_nights = calc_nights(begin_date, end_date);
        double total_price = calc_total_price(reservation);

        // guarda os resultados todos numa string separados por ";" e retorna-a
        char* result = malloc(256 * sizeof(char));
        sprintf(result, "%s;%s;%d;%s;%s;%s;%d;%.3f\n", hotel_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, num_nights, total_price);

        // frees
        free(hotel_id);
        free(hotel_name);
        free(begin_date);
        free(end_date);
        free(includes_breakfast);

        return result;
    }

    if (entity == 2) {  // se for um voo
        int flight_id = atoi(aux);
        FLIGHT* flight = get_flight_by_id(fcatalog, flight_id);
        if (flight == NULL) {
            printf("Flight not found\n");
            return NULL;
        }
        char* airline = strdup(get_airline(flight));
        char* plain_model = strdup(get_plain_model(flight));
        char* origin = strdup(get_origin(flight));
        char* destination = strdup(get_destination(flight));
        char* real_departure = strdup(get_real_departure_date(flight));
        char* real_arrival = strdup(get_real_arrival_date(flight));
        char* schedule_departure = strdup(get_schedule_departure_date(flight));
        char* schedule_arrival = strdup(get_schedule_arrival_date(flight));
        int num_passengers = 0;  // necessario percorrer o ficheiro dos flights e ver quantos passageiros
        int delay = 0;

        num_passengers = g_list_length(find_users_by_flight(pcatalog, flight_id));  // se find_users_by_flight retornar a lista com todos os users com este flight_id associado

        delay = calc_departure_delay(schedule_departure, real_departure);

        // guarda os resultados todos numa string separados por ";" e retorna-a
        char* result = malloc(256 * sizeof(char));
        sprintf(result, "%s;%s;%s;%s;%s;%s;%d;%d\n", airline, plain_model, origin, destination, schedule_departure, schedule_arrival, num_passengers, delay);

        // frees
        free(airline);
        free(plain_model);
        free(origin);
        free(destination);
        free(real_departure);
        free(real_arrival);
        free(schedule_departure);
        free(schedule_arrival);

        return result;
    }

    if (entity == 3) {  // se for um utilizador

        USER* user = get_user_by_id(ucatalog, aux);
        if (user == NULL) {
            printf("User not found\n");
            return NULL;
        }

        // verifica se o user está ativo, se não estiver, não faz nada
        char* active_status = strdup(get_active_status(user));
        if (strcasecmp(active_status, "inactive") == 0) {
            return NULL;
        }
        char* name = strdup(get_name(user));
        char* gender = strdup(get_gender(user));
        char* birth_date = strdup(get_birth_date(user));
        int age = 0;
        char* country_code = strdup(get_country_code(user));
        char* passport = strdup(get_passport(user));
        int num_flight = 0;
        int num_reservations = 0;
        double total_gasto = 0;

        age = calc_idade(birth_date);
        num_flight = g_list_length(find_flights_by_user(pcatalog, aux));  // se find_flight_by_user retornar a lista com todos os flights com este user_id associado
        num_reservations = get_num_reservations(user);
        total_gasto = get_total_spent(user);

        // guarda os resultados todos numa string separados por ";" e retorna-a
        char* result = malloc(256 * sizeof(char));
        sprintf(result, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", name, gender, age, country_code, passport, num_flight, num_reservations, total_gasto);

        // frees
        free(name);
        free(gender);
        free(birth_date);
        free(country_code);
        free(passport);

        return result;
    }
    printf("Invalid ID on query1\n");
    return NULL;
}

char* query1F(USERS_CATALOG* ucatalog, FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, PASSENGERS_CATALOG* pcatalog, char* id) {
    char* result = malloc(256 * sizeof(char));
    int entity = choose_entity(id);

    if (entity == 1) {  // se for uma reserva
        char* query1Result = query1(ucatalog, fcatalog, rcatalog, pcatalog, id);
        if (query1Result == NULL) {
            free(result);
            return NULL;
        }
        char* aux = strdup(query1Result);
        char* hotel_id = malloc(30);
        char* hotel_name = malloc(50);
        int hotel_stars = 0;
        char* begin_date = malloc(20);
        char* end_date = malloc(20);
        char* includes_breakfast = malloc(10);
        int num_nights = 0;
        double total_price = 0;

        char* token = strtok(aux, ";");
        if (token != NULL) {
            strcpy(hotel_id, token);
            token = strtok(NULL, ";");
            if (token != NULL) {
                strcpy(hotel_name, token);
                token = strtok(NULL, ";");
                if (token != NULL) {
                    hotel_stars = atoi(token);
                    token = strtok(NULL, ";");
                    if (token != NULL) {
                        strcpy(begin_date, token);
                        token = strtok(NULL, ";");
                        if (token != NULL) {
                            strcpy(end_date, token);
                            token = strtok(NULL, ";");
                            if (token != NULL) {
                                strcpy(includes_breakfast, token);
                                ;
                                token = strtok(NULL, ";");
                                if (token != NULL) {
                                    num_nights = atoi(token);
                                    token = strtok(NULL, ";");
                                    if (token != NULL) {
                                        total_price = atof(token);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        sprintf(result, "--- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %d\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n",
                hotel_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, num_nights, total_price);

        free(hotel_id);
        free(hotel_name);
        free(begin_date);
        free(end_date);
        free(includes_breakfast);
        free(aux);

        return result;
    }

    if (entity == 2) {  // se for um voo
        char* query1Result = query1(ucatalog, fcatalog, rcatalog, pcatalog, id);
        if (query1Result == NULL) {
            free(result);
            return NULL;
        }
        char* aux = strdup(query1Result);

        char* airline = malloc(30);
        char* plane_model = malloc(30);
        char* origin = malloc(30);
        char* destination = malloc(30);
        char* schedule_departure = malloc(20);
        char* schedule_arrival = malloc(20);
        int num_passengers = 0;
        int delay = 0;

        char* token = strtok(aux, ";");

        if (token != NULL) {
            strcpy(airline, token);
            token = strtok(NULL, ";");
            if (token != NULL) {
                strcpy(plane_model, token);
                token = strtok(NULL, ";");
                if (token != NULL) {
                    strcpy(origin, token);
                    token = strtok(NULL, ";");
                    if (token != NULL) {
                        strcpy(destination, token);
                        token = strtok(NULL, ";");
                        if (token != NULL) {
                            strcpy(schedule_departure, token);
                            token = strtok(NULL, ";");
                            if (token != NULL) {
                                strcpy(schedule_arrival, token);
                                token = strtok(NULL, ";");
                                if (token != NULL) {
                                    num_passengers = atoi(token);
                                    token = strtok(NULL, ";");
                                    if (token != NULL) {
                                        delay = atoi(token);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        sprintf(result, "--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %d\n",
                airline, plane_model, origin, destination, schedule_departure, schedule_arrival, num_passengers, delay);
        free(airline);
        free(plane_model);
        free(origin);
        free(destination);
        free(schedule_departure);
        free(schedule_arrival);
        free(aux);

        return result;
    }

    if (entity == 3) {  // se for um utilizador
        char* query1Result = query1(ucatalog, fcatalog, rcatalog, pcatalog, id);
        if (query1Result == NULL) {
            free(result);
            return NULL;
        }
        char* aux = strdup(query1Result);

        char* name = malloc(30);
        char* gender = malloc(5);
        int age = 0;
        char* country_code = malloc(30);
        char* passport = malloc(30);
        int num_flight = 0;
        int num_reservations = 0;
        double total_gasto = 0;

        char* token = strtok(aux, ";");
        if (token != NULL) {
            strcpy(name, token);
            token = strtok(NULL, ";");
            if (token != NULL) {
                strcpy(gender, token);
                token = strtok(NULL, ";");
                if (token != NULL) {
                    age = atoi(token);
                    token = strtok(NULL, ";");
                    if (token != NULL) {
                        strcpy(country_code, token);
                        token = strtok(NULL, ";");
                        if (token != NULL) {
                            strcpy(passport, token);
                            token = strtok(NULL, ";");
                            if (token != NULL) {
                                num_flight = atoi(token);
                                token = strtok(NULL, ";");
                                if (token != NULL) {
                                    num_reservations = atoi(token);
                                    token = strtok(NULL, ";");
                                    if (token != NULL) {
                                        total_gasto = atof(token);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        sprintf(result, "--- 1 ---\nname: %s\nsex: %s\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n", name, gender, age, country_code, passport, num_flight, num_reservations, total_gasto);
        free(name);
        free(gender);
        free(country_code);
        free(passport);
        free(aux);

        return result;
    }
    free(result);
    return " ";
}

char* query2_nocat(FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, USERS_CATALOG* ucatalog, PASSENGERS_CATALOG* pcatalog, char* token, int flag) {  
    GHashTable* users_hash = get_users_hash(ucatalog);
    USER* user = g_hash_table_lookup(users_hash, token);
    if (user == NULL) {
        return NULL;
    }
    char* active_status = strdup(get_active_status(user));
    if (strcasecmp(active_status, "inactive") == 0) {
        free(active_status);
        return NULL;
    }

    const char* type1 = strdup("flight");
    const char* type2 = strdup("reservation");

    gpointer key1, value1;  // flights
    GHashTableIter iter1;
    gpointer key2, value2;  // reservations
    GHashTableIter iter2;
    GList* aux_list = NULL;
    
    char* output = malloc(1);
    output[0] = '\0';  // Começa com uma string vazia
    GList* flight_ids = find_flights_by_user(pcatalog, token);

    // inserir a parte dos flights

    GHashTable* hash_flights = get_flights_hash(fcatalog);
    while (flight_ids != NULL) {
        int flight_id_by_user = GPOINTER_TO_INT(flight_ids->data);
        // printf("%d\n", flight_id_by_user);
        g_hash_table_iter_init(&iter1, hash_flights);

        while (g_hash_table_iter_next(&iter1, &key1, &value1)) {
            AUX_Q2* new_entidade = malloc(sizeof(AUX_Q2));
            FLIGHT* flight = value1;
            if (flight == NULL) {
                return NULL;
            }
            int curr_flight_id = get_flight_id(flight);

            if (flight_id_by_user == curr_flight_id) {
                set_aux_id(new_entidade, strdup(fix_flight_id(get_flight_id(flight))));
                printf("1 %s\n", new_entidade->id);
                set_aux_date(new_entidade, extractDate(get_schedule_departure_date(flight)));
                set_aux_type(new_entidade,type1);
                aux_list = g_list_append(aux_list, new_entidade);
            }   
        }
        flight_ids = flight_ids->next;
    }

    // inserir a parte das reservations

    GHashTable* hash_reservations = get_reservations_hash(rcatalog);
    g_hash_table_iter_init(&iter2, hash_reservations);

    while (g_hash_table_iter_next(&iter2, &key2, &value2)) {
        AUX_Q2* new_entidade = malloc(sizeof(AUX_Q2));
        RESERVATION* reservation = value2;
        char* curr_user_id = strdup(get_user_id(reservation));
        if (strcmp(token, curr_user_id) == 0){
            printf("2 %s\n",curr_user_id);
            const char *a = get_reservation_id(reservation);
            printf("SEGFAULT AQUI set_aux_id(new_entidade, %s)\n",a);
            set_aux_id(new_entidade, a);

            set_aux_date(new_entidade, strdup(get_begin_date(reservation)));
            set_aux_type(new_entidade,strdup(type2));
            aux_list = g_list_append(aux_list, new_entidade);      
    }
    free(curr_user_id);  
    }
    GList* sorted_aux= g_list_sort(aux_list, sort_function_q2_nocat);
    int tamanho = g_list_length(sorted_aux);

 if (flag == 1) { // 2 normal
    // escreve no output as linhas correspondentes as reservations
    for (size_t i = 0; i < tamanho; i++) {
        char line[200];  // linha atual
        AUX_Q2* curr_aux = g_list_nth_data(sorted_aux, i);

        sprintf(line, "%s;%s;%s\n", curr_aux->id, curr_aux->date, curr_aux->type);

        // realloc para aumentar o tamanho da string output
        output = realloc(output, strlen(output) + strlen(line) + 1);
        // concatena a linha atual à string de output
        strcat(output, line);
    }
}
     if (flag == 2) {  // 2F
            int reg_num = 1;
            for (size_t i = 0; i < tamanho; i++) {
                char line[200];  // linha atual
                AUX_Q2* curr_aux = g_list_nth_data(sorted_aux, i);

                sprintf(line, "--- %d ---\nid: %s\ndate: %s\ntype: %s\n", reg_num, curr_aux->id, curr_aux->date, curr_aux->type);
                reg_num++;
                // realloc para aumentar o tamanho da string output
                output = realloc(output, strlen(output) + strlen(line) + 1);
                // concatena a linha atual à string de output
                strcat(output, line);
            }
            // tira os 1 ultimos \n's
            output[strlen(output) - 1] = '\0';
        }

    free(active_status);
    return output;
}

char* query2_cat(FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, USERS_CATALOG* ucatalog, PASSENGERS_CATALOG* pcatalog, char* token, char* catalog, int flag) {
    USER* user = get_user_by_id(ucatalog, token);
    if (user == NULL) {
        return NULL;
    }
    char* active_status = strdup(get_active_status(user));
    if (strcasecmp(active_status, "inactive") == 0) {
        free(active_status);
        return NULL;
    }

    gpointer key, value;
    GHashTableIter iter;
    GList* aux = NULL;
    char* output = malloc(1);
    output[0] = '\0';  // Começa com uma string vazia
    GList* flight_ids = find_flights_by_user(pcatalog, token);
    if (strcmp(catalog, "flights") == 0) {
        GHashTable* hash = get_flights_hash(fcatalog);
        while (flight_ids != NULL) {
            int flight_id_by_user = GPOINTER_TO_INT(flight_ids->data);
            // printf("%d\n", flight_id_by_user);
            g_hash_table_iter_init(&iter, hash);

            while (g_hash_table_iter_next(&iter, &key, &value)) {
                FLIGHT* flight = value;
                int curr_flight_id = get_flight_id(flight);
                if (flight_id_by_user == curr_flight_id) aux = g_list_append(aux, flight);
            }
            flight_ids = flight_ids->next;
        }

        GList* sorted = g_list_sort(aux, sort_function_q2);
        int tamanho = g_list_length(sorted);

        if (flag == 1) {  // 2 normal

            for (size_t i = 0; i < tamanho; i++) {
                char line[200];  // linha atual
                FLIGHT* curr_flight = g_list_nth_data(sorted, i);

                sprintf(line, "%s;%s\n", fix_flight_id(get_flight_id(curr_flight)), extractDate(get_schedule_departure_date(curr_flight)));

                // realloc para aumentar o tamanho da string output
                output = realloc(output, strlen(output) + strlen(line) + 1);
                // concatena a linha atual à string de output
                strcat(output, line);
            }
        }
        if (flag == 2) {  // 2F
            int reg_num = 1;
            for (size_t i = 0; i < tamanho; i++) {
                char line[200];  // linha atual
                FLIGHT* curr_flight = g_list_nth_data(sorted, i);

                sprintf(line, "--- %d ---\nid: %s\ndate: %s\n\n", reg_num, fix_flight_id(get_flight_id(curr_flight)), extractDate(get_schedule_departure_date(curr_flight)));
                reg_num++;
                // realloc para aumentar o tamanho da string output
                output = realloc(output, strlen(output) + strlen(line) + 1);
                // concatena a linha atual à string de output
                strcat(output, line);
            }
            // tira os 1 ultimos \n's
            output[strlen(output) - 1] = '\0';
        }
        free(active_status);
        return output;
    }

    if (strcmp(catalog, "reservations") == 0) {
        GHashTable* hash = get_reservations_hash(rcatalog);
        g_hash_table_iter_init(&iter, hash);
        while (g_hash_table_iter_next(&iter, &key, &value)) {
            RESERVATION* reservation = value;
            char* curr_user_id = strdup(get_user_id(reservation));
            if (strcmp(token, curr_user_id) == 0) aux = g_list_append(aux, reservation);
            free(curr_user_id);
        }

        GList* sorted = g_list_sort(aux, sort_function_q4);
        int tamanho = g_list_length(sorted);

        if (flag == 1) {  // 2 normal
            for (size_t i = 0; i < tamanho; i++) {
                char line[200];  // linha atual
                RESERVATION* curr_res = g_list_nth_data(sorted, i);

                sprintf(line, "%s;%s\n", get_reservation_id(curr_res), get_begin_date(curr_res));

                // realloc para aumentar o tamanho da string output
                output = realloc(output, strlen(output) + strlen(line) + 1);
                // concatena a linha atual à string de output
                strcat(output, line);
            }
        }
        if (flag == 2) {  // 2F
            int reg_num = 1;
            for (size_t i = 0; i < tamanho; i++) {
                char line[200];  // linha atual
                RESERVATION* curr_res = g_list_nth_data(sorted, i);

                sprintf(line, "--- %d ---\nid: %s\ndate: %s\n\n", reg_num, get_reservation_id(curr_res), get_begin_date(curr_res));
                reg_num++;
                // realloc para aumentar o tamanho da string output
                output = realloc(output, strlen(output) + strlen(line) + 1);
                // concatena a linha atual à string de output
                strcat(output, line);
            }
            // tira os 1 ultimos \n's
            output[strlen(output) - 1] = '\0';
        }
        free(active_status);
        return output;
    }

    free(active_status);
    return NULL;
}

char* query3(RESERVATIONS_CATALOG* rcatalog, char* hotel_id) {
    int res = 0;
    double total = 0;
    gpointer key, value;
    GHashTableIter iter;
    GHashTable* hash = get_reservations_hash(rcatalog);
    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        RESERVATION* reservation = value;
        if (strcmp(hotel_id, get_hotel_id(reservation)) == 0) {
            res++;
            total += get_rating(reservation);
        }
    }

    if (res == 0) {
        printf("erro divisão por 0\n");
        return NULL;
    }
    double resultado = total / res;
    // guarda os resultados todos numa string separados por ";" e retorna-a
    char* output = malloc(256 * sizeof(char));
    sprintf(output, "%.3f\n", resultado);
    return output;
}

char* query3F(RESERVATIONS_CATALOG* rcatalog, char* hotel_id) {
    char* output = malloc(20);
    char* r = query3(rcatalog, hotel_id);
    if (r == NULL) {
        return NULL;
    }
    char* result = r;
    sprintf(output, "--- 1 ---\nrating: %s", result);
    return output;
}

char* query4(RESERVATIONS_CATALOG* rcatalog, char* hotel_id, int flag) {
    gpointer key, value;
    GList* aux = NULL;
    GHashTableIter iter;
    GHashTable* hash = get_reservations_hash(rcatalog);
    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        RESERVATION* reservation = value;
        if (strcmp(get_hotel_id(reservation), hotel_id) == 0) {
            aux = g_list_append(aux, reservation);
            if (aux == NULL) {
                printf("erro ao dar append\n");
                return NULL;
            }
        }
    }

    GList* sorted = g_list_sort(aux, sort_function_q4);
    int tamanho = g_list_length(sorted);
    char* output = malloc(1);
    output[0] = '\0';  // Começa com uma string vazia

    if (flag == 1) {  // query4

        for (size_t i = 0; i < tamanho; i++) {
            double total_price = 0;
            char line[200];  // linha atual
            RESERVATION* curr_res = g_list_nth_data(sorted, i);
            total_price = calc_total_price(curr_res);

            sprintf(line, "%s;%s;%s;%s;%d;%.3f\n", get_reservation_id(curr_res), get_begin_date(curr_res), get_end_date(curr_res), get_user_id(curr_res), get_rating(curr_res), total_price);

            // realloc para aumentar o tamanho da string output
            output = realloc(output, strlen(output) + strlen(line) + 1);
            // concatena a linha atual à string de output
            strcat(output, line);
        }
    }

    if (flag == 2) {  // query4F
        int reg_num = 1;
        for (size_t i = 0; i < tamanho; i++) {
            double total_price = 0;

            char line[200];  // linha atual
            RESERVATION* curr_res = g_list_nth_data(sorted, i);
            total_price = calc_total_price(curr_res);

            sprintf(line, "--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n\n", reg_num, get_reservation_id(curr_res), get_begin_date(curr_res), get_end_date(curr_res), get_user_id(curr_res), get_rating(curr_res), total_price);
            reg_num++;
            // realloc para aumentar o tamanho da string output
            output = realloc(output, strlen(output) + strlen(line) + 1);
            // concatena a linha atual à string de output
            strcat(output, line);
        }

        // tira os 1 ultimos \n
        output[strlen(output) - 1] = '\0';
    }

    return output;
}




// Função principal para calcular e listar os top N aeroportos
char* query7(FLIGHTS_CATALOG* fcatalog, char* token) {
    GHashTable* airport_delays_hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    int top_n = atoi(token);
    // Calcular os atrasos para cada voo
    
    gpointer key, value;
    GHashTableIter iter;
    GHashTable* hash = get_flights_hash(fcatalog);
    
    
    g_hash_table_iter_init(&iter, hash);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        FLIGHT* flight = value;

        char* origin = strdup(get_origin(flight));
        char* sch_departure = strdup(get_schedule_departure_date(flight));
        char* real_departure = strdup(get_real_departure_date(flight));
        int delay = calc_departure_delay(sch_departure, real_departure);

        AUX_Q7* airport_delay = g_hash_table_lookup(airport_delays_hash, origin);
        if (airport_delay == NULL) {
            airport_delay->origin = strdup(origin);
            airport_delay->delays = g_list_append(airport_delay->delays, GINT_TO_POINTER(delay));
            g_hash_table_insert(airport_delays_hash, airport_delay->origin, airport_delay);
        }
        else  airport_delay->delays = g_list_append(airport_delay->delays, GINT_TO_POINTER(delay));
    }

    GList* airport_list = g_hash_table_get_values(airport_delays_hash);
    GList* top_airports = g_list_sort(airport_list, compare_airports);

    int tamanho = g_list_length(top_airports);
    char* output = malloc(1);
    output[0] = '\0';  // Começa com uma string vazia

    for (size_t i = 0; (i < top_n) | (i < tamanho); i++) {
                char line[200];  // linha atual
                AUX_Q7* curr_aux = g_list_nth_data(top_airports, i);

                sprintf(line, "%s;%i\n", get_aux_origin(curr_aux),calcula_mediana(curr_aux->delays));

                // realloc para aumentar o tamanho da string output
                output = realloc(output, strlen(output) + strlen(line) + 1);
                // concatena a linha atual à string de output
                strcat(output, line);
            }
        
    g_hash_table_destroy(airport_delays_hash);

    return output;
}


char* query9(USERS_CATALOG* ucatalog, char* token) {
    char* prefix = strdup(token);
    gpointer key, value;
    GList* aux = NULL;
    GHashTableIter iter;
    GHashTable* hash = get_users_hash(ucatalog);
    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        USER* user = value;
        if (strcasecmp(get_active_status(user), "inactive") != 0) {  // se o user não for "inactive"
            char* id = strdup(get_id(user));
            if (id == NULL) {
                printf("Error: failed to allocate memory on id\n");
                free(prefix);
                return NULL;
            }

            char* name = strdup(get_name(user));
            if (name == NULL) {
                printf("Error: failed to allocate memory on name\n");
                free(id);
                free(prefix);
                return NULL;
            }
            if (verificaPrefixo(name, prefix)) {  // se tiver o prefixo, adiciona à lista
                char* idName = malloc(strlen(id) + strlen(name) + 2);
                if (idName == NULL) {
                    printf("Error: failed to allocate memory on idName\n");
                    free(id);
                    free(name);
                    free(prefix);
                    return NULL;
                }
                // concatena o id e o nome do user
                strcpy(idName, id);
                strcat(idName, ";");
                strcat(idName, name);

                aux = g_list_append(aux, idName);  // dá append à lista do "id;name"
                if (aux == NULL) {
                    printf("Error: failed to append to list\n");
                    free(idName);
                    free(id);
                    free(name);
                    free(prefix);
                    return NULL;
                }
            } else {  // se nao tiver o prefixo, liberta a memoria
            }
        }
    }

    GList* sorted = g_list_sort(aux, sort_function_q9);
    int tamanho = g_list_length(sorted);
    char* output = malloc(1);
    output[0] = '\0';  // começa com uma string vazia
    for (size_t i = 0; i < tamanho; i++) {
        char* curr_user = g_list_nth_data(sorted, i);

        // realloc to increase the size of the output string
        output = realloc(output, strlen(output) + strlen(curr_user) + 2);  // +2 para o "\n" e para o "\0"
        // concatena a linha atual à string de output
        strcat(output, curr_user);
        strcat(output, "\n");
    }

    // // frees
    // GList* l;
    // for (l = aux; l != NULL; l = l->next) {  // free de cada elemento da lista
    //     free(l->data);
    // }
    // g_list_free(aux);  // free da lista em si
    // free(prefix);

    // tira o \n do fim da string
    output[strlen(output) - 1] = '\0';
    return output;
}