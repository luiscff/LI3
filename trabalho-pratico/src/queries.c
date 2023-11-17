#include "Catalog/flights_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"
#include "Catalog/passengers_catalog.h"



#define current_date "2023/10/01"

// aux query 1

int choose_entity (char* id){
    char * id_aux = NULL;
    strncpy(id_aux,id,4);
    int entity = 0;
    
    if (strcmp(id_aux,"Book") == TRUE) entity = 1;
    else if (isnumber(id_aux) == TRUE) entity = 2;
    else entity = 3;
}

char* bool_to_string(bool boolean){
    if (boolean == true) return "true";
    else return "false";
}


int key_count(GHashTable *hash_table, char *searching_value) {
    GHashTableIter iter;
    char* current_key, *current_value;
    int counter = 0;

    g_hash_table_iter_init(&iter, hash_table);
   while (g_hash_table_iter_next(&iter, &current_key, &current_value)) { // percorre a hash a tentar encontrar o mesmo voo (searching value)
        if (g_strcmp0(current_value, searching_value) == 0) {
            counter++;
    }
    return counter;
}
}

int calc_idade(char* birth_date){
    int ano_nascimento, mes_nascimento, dia_nascimento;
    int ano_atual, mes_atual, dia_atual;

    sscanf(birth_date, "%d/%d/%d", &ano_nascimento, &mes_nascimento, &dia_nascimento);
    sscanf(current_date, "%d/%d/%d", &ano_atual, &mes_atual, &dia_atual);

    int idade = ano_atual - ano_nascimento;

    if (mes_atual < mes_nascimento || (mes_atual == mes_nascimento && dia_atual < dia_nascimento)) {
        idade--;
    }   // Ajustar a idade caso ainda nao tenha feito anos nesse mesmo ano
    return idade;

}


//

void query1(USERS_CATALOG *ucatalog, FLIGHTS_CATALOG *fcatalog, RESERVATIONS_CATALOG *rcatalog,PASSENGERS_CATALOG *pcatalog, char *id){

    int entity = choose_entity(id);
    if (entity == 1){ //
        RESERVATION *reservation = g_hash_table_lookup(rcatalog, id);
        char* output = malloc(144);
        char* hotel_id = strdup (get_hotel_id(reservation));
        char* hotel_name = strdup (get_hotel_name(reservation));
        int hotel_stars = get_hotel_stars(reservation);
        char* begin_date = strdup (get_begin_date(reservation));
        char* end_date = strdup (get_end_date(reservation));
        char* includes_breakfast = strdup(bool_to_string(get_includes_breakfast(reservation)));


        double total_price = calc_total_price(reservation);

        printf("%s;%s;%i;%s;%s;%s;%.2f\n", hotel_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, total_price);

    }

    if (entity == 2){
        FLIGHT *flight = g_hash_table_lookup(fcatalog, id);
        char* airline = strdup (get_airline(flight));
        char* plain_model = strdup (get_plain_model(flight));
        char* origin = strdup (get_origin(flight));
        char* destination = strdup (get_destination(flight));
        char* real_departure = strdup (get_real_departure_date(flight));
        char* real_arrival = strdup (get_real_arrival_date(flight));
        char* schedule_departure = strdup (get_schedule_departure_date(flight));
        char* schedule_arrival = strdup (get_schedule_arrival_date(flight));
        int num_passengers = 0; //necessario percorrer o ficheiro dos flights e ver quantos passageiros
        double delay = 0;

        

        delay = calc_delay(schedule_arrival,schedule_departure,real_arrival,real_departure);
        printf("%s;%s;%s;%s;%s;%s;%s,%s,%d,%f\n", airline,plain_model,origin,destination,schedule_departure,schedule_arrival,num_passengers,delay);



    }

    if (id ==3){
        USER *user = g_hash_table_lookup(ucatalog, id);
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

        //TODO: calc num_flight,num_reservations, total_gasto;

        printf("%s;%s;%s;%s;%s;%s;%s,%s,%d,%f\n", name,gender,age,country_code,passport,num_flight,num_reservations,total_gasto);


    }
}