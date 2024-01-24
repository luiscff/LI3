#include <ctype.h>
#include <stdio.h>

// para converter para minusculas e retirar acentos
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#include "queries.h"
#include "utils.h"

// aux q2

typedef struct aux_q2 {
    char* id;
    char* date;
    char* type;
} AUX_Q2;

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

int sort_function_q2_nocat(gconstpointer a, gconstpointer b) {
    const AUX_Q2* aux1 = a;
    const AUX_Q2* aux2 = b;

    // ordenadas por data de início (da mais recente para a mais antiga).
    char* date1 = strdup(aux1->date);
    char* date2 = strdup(aux2->date);

    int result = strcmp(date2, date1);

    free(date1);
    free(date2);

    if (result != 0) {
        return result;
    }
    // quando as datas são iguais
    // o identificador da reserva é o critério de desempate (de forma crescente).
    char* id1 = strdup(aux1->id);
    char* id2 = strdup(aux2->id);

    // compara os ids (strings) como num dicionario
    if (strcmp(id1, id2) < 0) {
        result = -1;
    } else if (strcmp(id1, id2) > 0) {
        result = 1;
    }
    free(id1);
    free(id2);

    if (result == 0)printf("ERRO no sort da query2: os voos têm a mesma data e o mesmo id\n");
    return result;
}

int sort_function_q2(gconstpointer a, gconstpointer b) {
    const FLIGHT* flight1 = a;
    const FLIGHT* flight2 = b;

    char* date1 = extractDate(get_schedule_departure_date(flight1));
    char* date2 = extractDate(get_schedule_departure_date(flight2));

    int result = strcmp(date2, date1);

    free(date1);
    free(date2);

    if (result != 0) {
        return result;
    }

    // If dates are equal, compare flight IDs
    return get_flight_id(flight1) - get_flight_id(flight2);
}


// aux 4
int sort_function_q4(gconstpointer a, gconstpointer b) {
    const RESERVATION* res1 = a;
    const RESERVATION* res2 = b;

    char* date1 = strdup(get_begin_date(res1));
    char* date2 = strdup(get_begin_date(res2));

    int result = strcmp(date2, date1);

    free(date1);
    free(date2);

    if (result != 0) {
        return result;
    }

    // If dates are equal, compare reservation IDs
    return strcmp(get_reservation_id(res1), get_reservation_id(res2));
}

// aux q5

void free_strings(char* date1, char* date2, char* airport1, char* airport2) {
    free(date1);
    free(date2);
    free(airport1);
    free(airport2);
}


int sort_function_q5(gconstpointer a, gconstpointer b) {
    const FLIGHT* flight1 = a;
    const FLIGHT* flight2 = b;

    // ordenadas por data de início (da mais recente para a mais antiga).
    char* date1 = strdup(get_schedule_departure_date(flight1));
    char* date2 = strdup(get_schedule_departure_date(flight2));
    int result = strcmp(date2, date1);

    free(date1);
    free(date2);

    if (result != 0) {
        return result;
    }

    // If dates are equal, compare reservation IDs
    return get_flight_id(flight1)- get_flight_id(flight2);
}

// aux q7

gint compare_ints(gconstpointer a, gconstpointer b) {
    int num1 = GPOINTER_TO_INT(a);
    int num2 = GPOINTER_TO_INT(b);

    if (num1 < num2) return -1;  // num1 é menor que num2
    if (num1 > num2) return 1;   // num1 é maior que num2

    return 0;  // os números são iguais
}

// Função para calcular a mediana de um GArray de inteiros
double calcula_mediana(GList* list) {
    GList* ordenada = g_list_sort(list, compare_ints);
    guint size = g_list_length(ordenada);
    if (size == 0) {
        // Array vazio, mediana indefinida
        return 0.0;
    }

    if (size % 2 == 0) {
        // Número par de elementos, calcular a média dos dois valores do meio
        int middle1 = GPOINTER_TO_INT(g_list_nth_data(ordenada, size / 2 - 1));
        int middle2 = GPOINTER_TO_INT(g_list_nth_data(ordenada, size / 2));
        return (middle1 + middle2) / 2.0;
    } else {
        // Número ímpar de elementos, a mediana é o valor do meio
        return GPOINTER_TO_INT(g_list_nth_data(ordenada, size / 2));
    }
}

// Função de comparação para ordenar aeroportos por mediana e desempatar pelo nome do aeroporto

int sort_function_q7(gconstpointer a, gconstpointer b) {
    const AIRPORTS* airport1 = (const AIRPORTS*)a;
    const AIRPORTS* airport2 = (const AIRPORTS*)b;

    GList* list_a = get_airport_delay_list(airport1);
    GList* list_b = get_airport_delay_list(airport2);

    char* name_a = strdup(get_airport_name(airport1));
    char* name_b = strdup(get_airport_name(airport2));

    double mediana_a = calcula_mediana(list_a);
    printf("\nA: %f\n", mediana_a);
    double mediana_b = calcula_mediana(list_b);
    printf("\nB: %f\n", mediana_b);

    if (mediana_a < mediana_b)
        return 1;
    else if (mediana_a > mediana_b)
        return -1;

    else
        return strcmp(name_a, name_b);
}

int sort_function_by_mediana(gconstpointer a, gconstpointer b) {
    const AIRPORTS* airport1 = (const AIRPORTS*)a;
    const AIRPORTS* airport2 = (const AIRPORTS*)b;

    int mediana1 = get_mediana(airport1);
    int mediana2 = get_mediana(airport2);
    // Compare mediana values
    if (mediana1 > mediana2) {
        return -1;
    } else if (mediana1 < mediana2) {
        return 1;
    }

    // When mediana values are equal, use the airport name as a tiebreaker
    return strcmp(get_airport_name(airport1), get_airport_name(airport2));
}
// aux 9
int sort_function_q9(gconstpointer a, gconstpointer b) {
    // formato das structs recebidas (a e b): id;name;status
    const USER* user = (const USER*)a;
    const USER* user2 = (const USER*)b;
    // saca os 2 tokens da string a
    char* id1 = strdup(get_id(user));
    char* name1 = strdup(get_name(user));
    // saca os 2 tokens da string b
    char* id2 = strdup(get_id(user2));
    char* name2 = strdup(get_name(user2));
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

//-------QUERIES-------

char* query1(USERS_CATALOG* ucatalog, FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, PASSENGERS_CATALOG* pcatalog, char* id, int flag) {
    char* aux = strdup(id);
    int entity = choose_entity(aux);
    if (entity == 1) {  // se for uma reserva
        RESERVATION* reservation = get_reservation_by_id(rcatalog, aux);
        if (reservation == NULL) {
            printf("Reservation not found\n");
            free(aux);
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
        if (flag == 1) sprintf(result, "%s;%s;%d;%s;%s;%s;%d;%.3f\n", hotel_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, num_nights, total_price);
        if (flag == 2) sprintf(result, "--- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %d\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n", hotel_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, num_nights, total_price);
        // frees
        free(aux);
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
            free(aux);
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

        GList* temp = find_users_by_flight(pcatalog, flight_id);
        num_passengers = g_list_length(temp);  // se find_users_by_flight retornar a lista com todos os users com este flight_id associado
        g_list_free(temp);

        delay = calc_departure_delay(schedule_departure, real_departure);

        // guarda os resultados todos numa string separados por ";" e retorna-a
        char* result = malloc(256 * sizeof(char));
        if (flag == 1) sprintf(result, "%s;%s;%s;%s;%s;%s;%d;%d\n", airline, plain_model, origin, destination, schedule_departure, schedule_arrival, num_passengers, delay);
        if (flag == 2) sprintf(result, "--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %d\n", airline, plain_model, origin, destination, schedule_departure, schedule_arrival, num_passengers, delay);
        // frees
        free(aux);
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
            free(aux);
            return NULL;
        }

        // verifica se o user está ativo, se não estiver, não faz nada
        char* active_status = strdup(get_active_status(user));
        if (strcasecmp(active_status, "inactive") == 0) {
            free(active_status);
            free(aux);
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
        if (flag == 1) sprintf(result, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", name, gender, age, country_code, passport, num_flight, num_reservations, total_gasto);
        if (flag == 2) sprintf(result, "--- 1 ---\nname: %s\nsex: %s\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n", name, gender, age, country_code, passport, num_flight, num_reservations, total_gasto);

        // frees
        free(aux);
        free(active_status);
        free(name);
        free(gender);
        free(birth_date);
        free(country_code);
        free(passport);

        return result;
    }
    free(aux);
    printf("Invalid ID on query1\n");
    return NULL;
}

// QUERY 2 SEM RECEBER TOKEN ESPECIFICO
char* query2_nocat(FLIGHTS_CATALOG* fcatalog, RESERVATIONS_CATALOG* rcatalog, USERS_CATALOG* ucatalog, PASSENGERS_CATALOG* pcatalog, char* token, int flag) {
    USER* user = get_user_by_id(ucatalog, token);
    if (user == NULL) {
        return NULL;
    }
    char* active_status = strdup(get_active_status(user));
    if (strcasecmp(active_status, "inactive") == 0) {
        free(active_status);
        return NULL;
    }

    char* output = malloc(1);
    output[0] = '\0';  // Start with an empty string

    GList* flights = get_flights(user);
    GList* reservations = get_reservations(user);

    GList* aux_list = NULL;
    // Process the list of flights and add new entities to aux_list
    while (flights != NULL) {
        char* flight_id = flights->data;
        FLIGHT* flight = get_flight_by_id(fcatalog, atoi(flight_id));
        char* id = fix_flight_id(get_flight_id(flight));
        char* date = extractDate(get_schedule_departure_date(flight));
        char* type = strdup("flight");

        AUX_Q2* aux = malloc(sizeof(AUX_Q2));
        aux->id = id;
        aux->date = date;
        aux->type = type;

        aux_list = g_list_append(aux_list, aux);

        flights = flights->next;
    }
    // Process the list of reservations and add new entities to aux_list
    while (reservations != NULL) {
        char* reservation_id = reservations->data;
        RESERVATION* reservation = get_reservation_by_id(rcatalog, reservation_id);
        char* id = strdup(get_reservation_id(reservation));
        char* date = strdup(get_begin_date(reservation));
        char* type = strdup("reservation");

        AUX_Q2* aux = malloc(sizeof(AUX_Q2));
        aux->id = id;
        aux->date = date;
        aux->type = type;

        aux_list = g_list_append(aux_list, aux);

        reservations = reservations->next;
        
    }

    GList* sorted_list = g_list_sort(aux_list, sort_function_q2_nocat);
    int tamanho = g_list_length(sorted_list);
    int reg_num = 1;
    // Write to the output the lines corresponding to reservations
    for (size_t i = 0; i < tamanho; i++) {
        char line[200];  // Current line
        AUX_Q2* curr_aux = g_list_nth_data(sorted_list, i);

        if (flag == 1) sprintf(line, "%s;%s;%s\n", curr_aux->id, curr_aux->date, curr_aux->type);
        if (flag == 2) sprintf(line, "--- %d ---\nid: %s\ndate: %s\ntype: %s\n\n", reg_num, curr_aux->id, curr_aux->date, curr_aux->type);
        reg_num++;
        // Reallocate to increase the size of the output string
        output = realloc(output, strlen(output) + strlen(line) + 1);
        // Concatenate the current line to the output string
        strcat(output, line);

        // Free memory for AUX_Q2 structure
        free(curr_aux->id);
        free(curr_aux->date);
        free(curr_aux->type);
        free(curr_aux);
    }

    // Free memory for the sorted list
    g_list_free(sorted_list);

    // Remove the last newline character
    if (flag == 2 && strlen(output) > 0 && output[strlen(output) - 1] == '\n') {
        output[strlen(output) - 1] = '\0';
    }

    // Free other resources
    free(active_status);
    return output;
}

// QUERY 2 A RECEBER TOKEN ESPECIFICO
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

    GList* aux = NULL;
    char* output = malloc(1);
    output[0] = '\0';  // Começa com uma string vazia
    GList* flights = get_flights(user);
    if (strcmp(catalog, "flights") == 0) {
        while (flights != NULL) {
            char* flight_id = flights->data;
            FLIGHT* flight = get_flight_by_id(fcatalog, atoi(flight_id));

            aux = g_list_append(aux, flight);

            flights = flights->next;
        }

        GList* sorted = g_list_sort(aux, sort_function_q2);
        int tamanho = g_list_length(sorted);
        int reg_num = 1;

        for (size_t i = 0; i < tamanho; i++) {
            char line[200];  // linha atual
            FLIGHT* curr_flight = g_list_nth_data(sorted, i);
            char* flight_id_char = fix_flight_id(get_flight_id(curr_flight));
            char* formated_date = extractDate(get_schedule_departure_date(curr_flight));

            if (flag == 1) sprintf(line, "%s;%s\n", flight_id_char, formated_date);
            if (flag == 2) sprintf(line, "--- %d ---\nid: %s\ndate: %s\n\n", reg_num, flight_id_char, formated_date);
            reg_num++;

            // realloc para aumentar o tamanho da string output
            output = realloc(output, strlen(output) + strlen(line) + 1);
            // concatena a linha atual à string de output
            strcat(output, line);
            free(flight_id_char);
            free(formated_date);
            
        }
        // tira o ultimo \n
        if (flag == 2) output[strlen(output) - 1] = '\0';

        free(active_status);
        return output;
    }

    if (strcmp(catalog, "reservations") == 0) {
        GList* reservations = get_reservations(user);
        while (reservations != NULL) {
            char* reservation_id = reservations->data;
            RESERVATION* reservation = get_reservation_by_id(rcatalog, reservation_id);

            aux = g_list_append(aux, reservation);

            reservations = reservations->next;
        }

        GList* sorted = g_list_sort(aux, sort_function_q4);
        int tamanho = g_list_length(sorted);
        int reg_num = 1;

        for (size_t i = 0; i < tamanho; i++) {
            char line[200];  // linha atual
            RESERVATION* curr_res = g_list_nth_data(sorted, i);

            if (flag == 1) sprintf(line, "%s;%s\n", get_reservation_id(curr_res), get_begin_date(curr_res));
            if (flag == 2) sprintf(line, "--- %d ---\nid: %s\ndate: %s\n\n", reg_num, get_reservation_id(curr_res), get_begin_date(curr_res));
            reg_num++;

            // realloc para aumentar o tamanho da string output
            output = realloc(output, strlen(output) + strlen(line) + 1);
            // concatena a linha atual à string de output
            strcat(output, line);
        }

        // tira o ultimo \n
        if (flag == 2) output[strlen(output) - 1] = '\0';

        free(active_status);
        return output;
    }

    free(active_status);
    return NULL;
}

// QUERY 3
char* query3(char* hotel_id, STATS* stats, int flag) {
    int res = 0;
    double total = 0;
    GHashTable* hotel_hash = get_hotel_hash(stats);
    HOTEL* hotel = g_hash_table_lookup(hotel_hash, hotel_id);

    total = get_hotel_sum_rating(hotel);
    res = get_hotel_num_reservations(hotel);

    if (res == 0) {
        printf("erro divisão por 0\n");
        return NULL;
    }
    double resultado = total / res;
    // guarda o resultado numa string e retorna-a
    char* output = malloc(256 * sizeof(char));
    if (flag == 1) sprintf(output, "%.3f\n", resultado);
    if (flag == 2) sprintf(output, "--- 1 ---\nrating: %.3f\n", resultado);
    return output;
}

// QUERY 4
char* query4(RESERVATIONS_CATALOG* rcatalog, char* hotel_id, STATS* stats, int flag) {
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
    int reg_num = 1;

    for (size_t i = 0; i < tamanho; i++) {
        double total_price = 0;
        char line[200];  // linha atual
        RESERVATION* curr_res = g_list_nth_data(sorted, i);
        total_price = calc_total_price(curr_res);

        if (flag == 1) sprintf(line, "%s;%s;%s;%s;%d;%.3f\n", get_reservation_id(curr_res), get_begin_date(curr_res), get_end_date(curr_res), get_user_id(curr_res), get_rating(curr_res), total_price);
        if (flag == 2) sprintf(line, "--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n\n", reg_num, get_reservation_id(curr_res), get_begin_date(curr_res), get_end_date(curr_res), get_user_id(curr_res), get_rating(curr_res), total_price);
        reg_num++;

        // realloc para aumentar o tamanho da string output
        output = realloc(output, strlen(output) + strlen(line) + 1);
        // concatena a linha atual à string de output
        strcat(output, line);
    }
    // tira os 1 ultimos \n
    if (flag == 2) output[strlen(output) - 1] = '\0';
    g_list_free(sorted);
    return output;
}

// QUERY 5

char* query5(char* token, char* dataI, char* dataF, STATS* stats, int flag) {
    GHashTable* airportS_hash = get_airportS_hash(stats);
    AIRPORTS* airportS = g_hash_table_lookup(airportS_hash, token);
    GList* flights_list = get_flights_list(airportS);
    GList* sorted = g_list_sort(flights_list, sort_function_q5);
    char* output = malloc(1);
    output[0] = '\0';
    int tamanho = g_list_length(sorted);
    int reg_num = 1;
    for (size_t i = 0; i < tamanho; i++) {
        FLIGHT* curr_flight = g_list_nth_data(sorted, i);
        char line[200] = {0};
        char* sch_dep = strdup(get_schedule_departure_date(curr_flight));
        char* sch_arr = strdup(get_schedule_arrival_date(curr_flight));
        if (get_flight_id(curr_flight) == 208) printf("\n%d\n", isDateTime1BeforeDateTime2(dataI, sch_dep) == true && isDateTime1BeforeDateTime2(sch_arr, dataF) == true);

        if (isDateTime1BeforeDateTime2(dataI, sch_dep) == true && isDateTime1BeforeDateTime2(sch_arr, dataF) == true) {
            if (flag == 1) sprintf(line, "%s;%s;%s;%s;%s\n", fix_flight_id(get_flight_id(curr_flight)), sch_dep, get_destination(curr_flight), get_airline(curr_flight), get_plain_model(curr_flight));
            if (flag == 2) sprintf(line, "--- %d ---\nid: %s\nschedule_departure_date: %s\ndestination: %s\nairline: %s\nplane_model: %s\n\n", reg_num, fix_flight_id(get_flight_id(curr_flight)), sch_dep, get_destination(curr_flight), get_airline(curr_flight), get_plain_model(curr_flight));
            reg_num++;
        }
        // realloc to increase the size of the output string
        output = realloc(output, strlen(output) + strlen(line) + 1);

        strcat(output, line);
        free(sch_dep);
        free(sch_arr);
    }
    
    if (flag == 2 && strlen(output) > 0) output[strlen(output) - 1] = '\0';

    return output;
}

// Q6
int in_year(int anoAlvo, char* data) {
    int ano, mes, dia, hora, min, sec;
    sscanf(data, "%d/%d/%d %d:%d:%d", &ano, &mes, &dia, &hora, &min, &sec);
    return anoAlvo == ano;
}

typedef struct query6 {
    char* airport;
    int passageiros;
} Q6;

void free_q6(void* data) {
    Q6* q6 = (Q6*)data;
        if (q6->airport) {
            free(q6->airport);
            q6->airport = NULL;
            }
        free(q6);
    }

Q6* create_q6_aux(char* airport, int passageiros) {
    Q6* curr = malloc(sizeof(Q6));
    curr->airport = strdup(airport);  // Duplicate only if necessary
    curr->passageiros = passageiros;
    return curr;
}

void insert_or_update_q6(GHashTable* curr, char* airport, int passageiros) {
    Q6* aux = g_hash_table_lookup(curr, airport);
    if (aux == NULL) {
        Q6* new_aux = create_q6_aux(airport, passageiros);
        g_hash_table_insert(curr, strdup(new_aux->airport), new_aux);
    } else {
        aux->passageiros += passageiros;
    }
}

int sort_function_q6(gconstpointer a, gconstpointer b) {
    const Q6* airport1 = (const Q6*)a;
    const Q6* airport2 = (const Q6*)b;

    // Compare com base no número de passageiros
    if (airport1->passageiros > airport2->passageiros) {
        return -1;
    } else if (airport1->passageiros < airport2->passageiros) {
        return 1;
    } else
        return strcmp(airport1->airport, airport2->airport);
}

char* query6(char* ano, char* top_n, STATS* stats, int flag) {
    int ano_alvo = atoi(ano);
    int teste = 0;

    GList* airportS_list = g_hash_table_get_values(get_airportS_hash(stats));
    int tamanho = g_list_length(airportS_list);
    // printf ("\n1 : %d\n",tamanho);
    GHashTable* q6_aux = g_hash_table_new_full(g_str_hash, g_str_equal, free,free_q6);

    for (int i = 0; i < tamanho; i++) {
        AIRPORTS* airportS = g_list_nth_data(airportS_list, i);
        GList* flights = get_flights_list(airportS);
        int tamanho2 = g_list_length(flights);
        // printf ("\nAiport %s : %d\n",get_airport_name(airportS),tamanho2);

        for (int j = 0; j < tamanho2; j++) {
            FLIGHT* flight = g_list_nth_data(flights, j);
            char* sch_dep = strdup(get_schedule_departure_date(flight));

            if (in_year(ano_alvo, sch_dep) == 1) {
                // logica que vai buscar o numero de passageiros de um voo e acrescenta ao de um aeroporto
                int curr_pass = get_passageiros(flight);
                char* airport_o = strdup(get_origin(flight));
                char* airport_d = strdup(get_destination(flight));
                insert_or_update_q6(q6_aux, airport_o, curr_pass);
                insert_or_update_q6(q6_aux, airport_d, curr_pass);
                free(airport_o);
                free(airport_d);
            }
            free(sch_dep);
        
        }
        
    }

    GList* q6_aux_list = g_hash_table_get_values(q6_aux);
    GList* sorted = g_list_sort(q6_aux_list, sort_function_q6);

    int tamanho_f = g_list_length(sorted);
    int reg_num = 1;
    char* output = malloc(1);
    output[0] = '\0';

    for (size_t h = 0; h < atoi(top_n) && h < tamanho_f; h++) {
        Q6* curr_airport = g_list_nth_data(sorted, h);
        char line[200];

        if (flag == 1) sprintf(line, "%s;%d\n", curr_airport->airport, curr_airport->passageiros);
        if (flag == 2) sprintf(line, "--- %d ---\nname: %s\npassengers: %d\n\n", reg_num, curr_airport->airport, curr_airport->passageiros);
        reg_num++;
        // realloc to increase the size of the output string
        output = realloc(output, strlen(output) + strlen(line) + 1);
        // concatena a linha atual à string de output
        strcat(output, line);
    }
    if (flag == 2) output[strlen(output) - 1] = '\0';
    //printf("\nTESTE : %d\n", teste);
    g_hash_table_destroy(q6_aux);
    g_list_free(sorted);
    //TODO arranjar de dar free a tudo sem dar erro (dificil porque as glists estao interligadas e a hash table tambem)
    return output;
}

// // QUERY 7 - Função principal para calcular e listar os top N aeroportosg
char* query7(char* token, STATS* stats, int flag) {
    GHashTable* airportS_hash = get_airportS_hash(stats);
    int top_n = atoi(token);
    // Calcular os atrasos para cada voo
    GList* airportS_list = g_hash_table_get_values(airportS_hash);
    calculate_and_set_median_for_all(airportS_list);

    char* output = malloc(1);
    output[0] = '\0';
    GList* sorted = g_list_sort(airportS_list, sort_function_by_mediana);
    int tamanho = g_list_length(sorted);
    int reg_num = 1;

    for (size_t i = 0; i < top_n && i < tamanho; i++) {
        AIRPORTS* curr_airport = g_list_nth_data(sorted, i);
        char line[200];

        if (flag == 1) sprintf(line, "%s;%d\n", get_airport_name(curr_airport), get_mediana(curr_airport));
        if (flag == 2) sprintf(line, "--- %d ---\nname: %s\nmedian: %d\n\n", reg_num, get_airport_name(curr_airport), get_mediana(curr_airport));
        reg_num++;
        // realloc to increase the size of the output string
        output = realloc(output, strlen(output) + strlen(line) + 1);
        // concatena a linha atual à string de output
        strcat(output, line);
    }
    if (flag == 2) output[strlen(output) - 1] = '\0';
    

    return output;
}

// Função para calcular a diferença em noites entre duas datas dentro de um intervalo
int calculate_nights_between_dates(const char* start_date1, const char* end_date1, const char* start_date_l, const char* end_date_l) {
    char* start_used;
    char* end_used;  // TODO:ver melhor logica

    if (isDate1BeforeDate2(end_date_l, start_date1) == 1 || isDate1BeforeDate2(end_date1, start_date_l) == 1) {
        return 0;
    }

    if (isDate1BeforeDate2(start_date1, start_date_l) == 1) {
        start_used = strdup(start_date_l);
    } else {
        start_used = strdup(start_date1);
    }

    if (isDate1BeforeDate2(end_date1, end_date_l) == 1) {
        end_used = strdup(end_date1);
    } else {
        end_used = strdup(end_date_l);
    }

    int nights = calc_nights(start_used, end_used);

    free(start_used);
    free(end_used);

    return nights;
}

// QUERY 8
char* query8(char* token, char* dataI, char* dataF, STATS* stats, int flag) {
    GHashTable* hotel_hash = get_hotel_hash(stats);
    HOTEL* hotel = g_hash_table_lookup(hotel_hash, token);
    GList* reservations_list = get_hotel_reservations_list(hotel);
    int tamanho = get_hotel_num_reservations(hotel);
    int revenue = 0;

    for (int i = 0; i < tamanho; ++i) {
        RESERVATION* curr_res = g_list_nth_data(reservations_list, i);
        printf("\n%s", get_hotel_id(curr_res));
        char* res_begin = strdup(get_begin_date(curr_res));
        char* res_end = strdup(get_end_date(curr_res));
        int ppn = get_price_per_night(curr_res);
        int nights = calculate_nights_between_dates(res_begin, res_end, dataI, dataF);
        printf("\n NOITES: %d\n", nights);
        printf("%d\n", ppn);
        revenue += nights;
    }

    char* output = malloc(256 * sizeof(char));
    if (flag == 1) sprintf(output, "%d\n", revenue);
    if (flag == 2) sprintf(output, "--- 1 ---\nrevenue: %d\n", revenue);
    return output;
}

// QUERY 9
char* query9(char* token, STATS* stats, int flag) {
    char* prefix = strdup(token);
    char* key = malloc(2);
    key[0] = prefix[0];
    key[1] = -'\0';
    GHashTable* dictionary = get_dictionary_hash(stats);
    DICTIONARY* page = g_hash_table_lookup(dictionary, key);
    if (page == NULL) {
        printf("NO USER FOUND WITH THAT PREFIX\n");
        return NULL;
    }

    GList* page_users = get_dictionary_values(page);
    GList* sorted = g_list_sort(page_users, sort_function_q9);  // dar fix a q9

    char* output = malloc(1);
    output[0] = '\0';
    int tamanho = g_list_length(sorted);
    int reg_num = 1;

    for (size_t i = 0; i < tamanho; i++) {
        USER* curr_user = g_list_nth_data(sorted, i);
        char* user_name = strdup(get_name(curr_user));
        char* user_id = strdup(get_id(curr_user));
        char* user_status = strdup(get_active_status(curr_user));
        char line[200];

        if ((verificaPrefixo(g_strdup(user_name), prefix) == 1) && strcmp(g_strdup(user_status), "active") == 0) {
            if (flag == 1) sprintf(line, "%s;%s\n", g_strdup(user_name), g_strdup(user_id));
            if (flag == 2) sprintf(line, "--- %d ---\nid: %s\nname: %s\n\n", reg_num, user_name, user_id);
            reg_num++;
            // realloc to increase the size of the output string
            output = realloc(output, strlen(output) + strlen(line) + 1);
            // concatena a linha atual à string de output
            strcat(output, line);
        }
        free(user_name);
        free(user_id);
        free(user_status);
    }

    if (flag == 2 && strlen(output) > 0) {
        output[strlen(output) - 1] = '\0';  // Avoid buffer overflow
    }
    free(key);
    return output;
}