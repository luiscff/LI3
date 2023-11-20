#include <ctype.h>
#include <stdio.h>

#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"

#define current_date "2023/10/01"

// aux query 1

int calc_total_spent_by_user_id(RESERVATIONS_CATALOG* catalog, char* user_id) {
    int total = 0;
    gpointer key, value;
    GHashTableIter iter;
    GHashTable* hash = get_reservations_hash(catalog);
    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        RESERVATION* reservation = value;
        if ((strcmp(user_id, get_user_id(reservation)) == 0)) {
            total += calc_total_price(reservation);
        }
    }
    return total;
}

int calc_num_reservations(RESERVATIONS_CATALOG* rcatalog, char* user_id) {
    int res = 0;
    gpointer key, value;
    GHashTableIter iter;
    GHashTable* hash = get_reservations_hash(rcatalog);
    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        RESERVATION* reservation = value;
        if (strcmp(user_id, get_user_id(reservation)) == 0) {
            res++;
        }
    }

    return res;
}

int isNumber(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (isdigit(s[i]) == 0)
            return 0;
    }
    return 1;
}

int choose_entity(char* id) {
    // char* id_aux = malloc((strlen(id) + 1) * sizeof(char)); //aloca memoria para o id_aux do tamanho do id + 1
    // strncpy(id_aux, id, 4);
    int entity = 0;
    // printf("id_aux: %s\n", id_aux);
    printf("id: %s\n", id);
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
        return "true";
    else
        return "false";
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

// aux 3

int verificaPrefixo(const char *string, const char *prefixo) {
    size_t tamanhoPrefixo = strlen(prefixo);

    // Compara os primeiros 'tamanhoPrefixo' caracteres
    int resultadoComparacao = strncmp(string, prefixo, tamanhoPrefixo);

    // Se resultadoComparacao for 0, significa que o prefixo foi encontrado
    return (resultadoComparacao == 0);
}

//aux 4
int sort_function_q4(gconstpointer a, gconstpointer b){
    
    int ano1, mes1, dia1;
    sscanf(a, "%d/%d/%d", &ano1, &mes1, &dia1);

    int ano2, mes2, dia2;
    sscanf(b, "%d/%d/%d", &ano2, &mes2, &dia2);

    //compara anos
    if (ano1 < ano2) {
        return -1;
    } else if (ano1 > ano2) {
        return 1;
    }

    //compara meses
    if (mes1 < mes2) {
        return -1;
    } else if (mes1 > mes2) {
        return 1;
    }

    // compara dias
    if (dia1 < dia2) {
        return -1;
    } else if (dia1 > dia2) {
        return 1;
    }

    return 0;//iguais
}

// aux 9
int sort_function_q8(gconstpointer a, gconstpointer b){
    return strcmp(a,b);
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
        
        //frees
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
        double delay = 0;

        num_passengers = g_list_length(find_users_by_flight(pcatalog, flight_id));  // se find_users_by_flight retornar a lista com todos os users com este flight_id associado

        delay = calc_delay(schedule_arrival, schedule_departure, real_arrival, real_departure);

        // guarda os resultados todos numa string separados por ";" e retorna-a
        char* result = malloc(256 * sizeof(char));
        sprintf(result, "%s;%s;%s;%s;%s;%s;%d;%.3f\n", airline, plain_model, origin, destination, schedule_departure, schedule_arrival, num_passengers, delay);
        
        //frees
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
        char* name = strdup(get_name(user));
        char* gender = strdup(get_gender(user));
        char* birth_date = strdup(get_birth_date(user));
        int age = 0;
        char* country_code = strdup(get_country_code(user));
        char* passport = strdup(get_passport(user));
        int num_flight = 0;
        int num_reservations = 0;
        int total_gasto = 0;

        age = calc_idade(birth_date);
        num_flight = g_list_length(find_flights_by_user(pcatalog, aux));  // se find_flight_by_user retornar a lista com todos os flights com este user_id associado
        num_reservations = calc_num_reservations(rcatalog, aux);
        total_gasto = calc_total_spent_by_user_id(rcatalog, aux);

        // guarda os resultados todos numa string separados por ";" e retorna-a
        char* result = malloc(256 * sizeof(char));
        sprintf(result, "%s;%s;%d;%s;%s;%d;%d;%d\n", name, gender, age, country_code, passport, num_flight, num_reservations, total_gasto );
        
        //frees
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

double query3(RESERVATIONS_CATALOG* rcatalog, char* hotel_id) { //TODO: testar
    int res = 0;
    int total = 0;
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
    free(hash);
    return total/res;
}


char* query4 (RESERVATIONS_CATALOG* rcatalog, char *hotel_id){
    gpointer key, value;
    GList *aux = NULL;
    GHashTableIter iter;
    GHashTable* hash = get_reservations_hash(rcatalog);
    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        RESERVATION* reservation = value;
        if (strcmp(get_hotel_id(reservation), hotel_id)){
            g_list_append(aux,reservation);
        }
        
    }

    GList* sorted = g_list_sort(aux,sort_function_q4);//TODO: sort_function_q4
    int tamanho = g_list_length(sorted);
    char* output;
    for (size_t i = 0; i < tamanho; i++) {
        int total_price = 0;
        output = malloc(sizeof(char[30]));
        RESERVATION* curr_res = g_list_nth_data(sorted, i);
        calc_total_price(curr_res);
        sprintf(output," %s; %s; %s, %s, %d, %d\n", get_reservation_id(curr_res), get_begin_date(curr_res),get_end_date(curr_res),get_user_id(curr_res), get_rating(curr_res),total_price);
    }

    return output;





}

char* query9 (USERS_CATALOG* ucatalog, char* token){
    char* prefix = strdup(token);
    gpointer key, value;
    char* current = malloc(30);
    GList *aux = NULL;
    GHashTableIter iter;
    char* output;
    GHashTable* hash = get_users_hash(ucatalog);
    g_hash_table_iter_init(&iter, hash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        USER* user = value;
        current = strdup(get_id(user));
        if (verificaPrefixo(current,prefix)) g_list_append(aux,current);
    }

    GList* sorted = g_list_sort(aux,sort_function_q8);
    int tamanho = g_list_length(sorted);
    for (size_t i = 0; i < tamanho; i++) {
        USER* curr_user = g_list_nth_data(sorted, i);
        output = malloc(sizeof(char[30]));
        sprintf(output,"%s;%s;\n", get_id(curr_user),get_name(curr_user));
    }

    //free(hash); TODO:ver como dar free a isto
    free(current);
    free(aux);
    free(sorted);

    return output;
}


