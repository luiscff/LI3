CFLAGS=-Wall -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS=`pkg-config --libs glib-2.0`

programa-principal: src/programa-principal.o src/Parser/parser.o src/Catalog/flights_catalog.o src/Catalog/passengers_catalog.o src/Entities/flights.o src/Entities/passengers.o
	gcc src/programa-principal.o src/Parser/parser.o src/Catalog/flights_catalog.o src/Catalog/passengers_catalog.o src/Entities/flights.o src/Entities/passengers.o -lglib-2.0 -o programa-principal


src/programa-principal.o: src/programa-principal.c
src/parser.o: src/Parser/parser.c
src/Catalog/flights_catalog.o: src/Catalog/flights_catalog.c
src/Catalog/passengers_catalog.o: src/Catalog/passengers_catalog.c
src/Entities/flights.o: src/Entities/flights.c
src/Entities/passengers.o: src/Entities/passengers.c

leaks: programa-principal
	valgrind --leak-check=full ./programa-principal ~/Desktop/dataset/data_clean/ palha

clean:
	rm -f programa-principal programa-testes src/*.o src/Parser/*.o src/Catalog/*.o src/Entities/*.o flights_catalog