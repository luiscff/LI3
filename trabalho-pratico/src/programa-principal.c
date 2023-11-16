#include <time.h>
#include <string.h>
#include <stdio.h>

#include "parser.h"
#include "Catalog/flights_catalog.h"
#include "Catalog/passengers_catalog.h"


#define MAX_PATH_SIZE 256


int main(int argc, char const *argv[]) {
    clock_t start = clock();
    if (argc != 3) {
        // parser só funciona se receber um folderPathDataset e inputPath ao executar programa
        printf("Usage: %s <DatasetFolderPath> <InputFilePath>\n", argv[0]); 
        return 1;
    }

    const char *folderPathDataset = argv[1];
    const char *folderPathInput = argv[2];  // Ainda n é usado o ficheiro de input

    char filePath[MAX_PATH_SIZE];

    // // for users.csv
    // strcpy(filePath, folderPathDataset);
    // strcat(filePath, "users.csv");
    // parseCSV(filePath,1);

    // // for flights.csv
    // strcpy(filePath, folderPathDataset);
    // strcat(filePath, "flights.csv");
    // parseCSV(filePath,2);

    // // for passengers.csv
    // strcpy(filePath, folderPathDataset);
    // strcat(filePath, "passengers.csv");
    // parseCSV(filePath,3);

    // // for reservations.csv
    // strcpy(filePath, folderPathDataset);
    // strcat(filePath, "reservations.csv");
    // parseCSV(filePath,4);


    // TESTE DE FLIGHTS_CATALOG
    // Cria o catálogo de voos
    FLIGHTS_CATALOG* catalog = create_flights_catalog();

    // Cria novos voos
    FLIGHT* flight1 = create_flight();
    set_flight_id(flight1, "000123");
    set_airline(flight1, "Airline1");
    FLIGHT* flight2 = create_flight();
    set_flight_id(flight2, "000124");
    set_airline(flight2, "Airline2");
    FLIGHT* flight3 = create_flight();
    set_flight_id(flight3, "000125");
    set_airline(flight3, "Airline3");
    FLIGHT* flight4 = create_flight();
    set_flight_id(flight4, "000126");
    set_airline(flight4, "Airline4");

    // Adicione mais detalhes ao voo conforme necessário...

    // Insere os voos no catálogo
    insert_flight(catalog, flight1, GINT_TO_POINTER(get_flight_id(flight1)));
    insert_flight(catalog, flight2, GINT_TO_POINTER(get_flight_id(flight2)));
    insert_flight(catalog, flight3, GINT_TO_POINTER(get_flight_id(flight3)));
    insert_flight(catalog, flight4, GINT_TO_POINTER(get_flight_id(flight4)));


    // Recupera os voos do catálogo
    FLIGHT *retrieved_flight1 = get_flight_by_id(catalog, 123);
    FLIGHT *retrieved_flight2 = get_flight_by_id(catalog, 124);
    FLIGHT *retrieved_flight3 = get_flight_by_id(catalog, 125);
    FLIGHT *retrieved_flight4 = get_flight_by_id(catalog, 126);



    // Imprime alguns detalhes dos voos
    printf("Flight ID: %d, Airline: %s\n", get_flight_id(retrieved_flight1),get_airline(retrieved_flight1));
    printf("Flight ID: %d, Airline: %s\n", get_flight_id(retrieved_flight2),get_airline(retrieved_flight2));
    printf("Flight ID: %d, Airline: %s\n", get_flight_id(retrieved_flight3),get_airline(retrieved_flight3));
    printf("Flight ID: %d, Airline: %s\n", get_flight_id(retrieved_flight4),get_airline(retrieved_flight4));



    // Limpa
    free_flights_catalog(catalog);
    

    // // TESTE DE PASSENGERS_CATALOG
    // // Cria o catálogo de passageiros
    // PASSENGERS_CATALOG* catalog = create_passengers_catalog();

    // // Cria um novo passageiro
    // PASSENGER* passenger1 = create_passenger();
    // set_user_id2(passenger1, "000123");
    // set_flight_id2(passenger1, "000123");
    // // Adicione mais detalhes ao passageiro conforme necessário...

    // // Insere o passageiro no catálogo
    // insert_passenger(catalog, passenger1, GINT_TO_POINTER(get_user_id2(passenger1)));

    // // Recupera o passageiro do catálogo
    // PASSENGER *retrieved_passenger = get_passenger_by_id(catalog, 123);

    // // Imprime alguns detalhes do passageiro
    // printf("Passenger ID: %d\n", get_user_id2(retrieved_passenger));
    // printf("Flight ID: %d\n", get_flight_id2(retrieved_passenger));

    // // Limpa
    // free_passengers_catalog(catalog);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f seconds\n", time_spent);

    return 0;
}