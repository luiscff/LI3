#include "Catalog/flights_catalog.h"
#include "Catalog/reservations_catalog.h"
#include "Catalog/users_catalog.h"
#include "Catalog/passengers_catalog.h"

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

void query1(USERS_CATALOG *ucatalog, FLIGHTS_CATALOG *fcatalog, RESERVATIONS_CATALOG *rcatalog, char *id){

    int entity = choose_entity(id);
    if (id == 1){ //
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

    /*if (id = 2){



    }

    if (id ==3){//aceder ao user catalog


-


    }
*/


}