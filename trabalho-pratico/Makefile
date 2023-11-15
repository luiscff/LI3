CFLAGS=-Wall -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS=`pkg-config --libs glib-2.0`

programa-principal: src/programa-principal.o src/Parser/parser.o src/Catalog/flights_catalog.o src/Entities/flights.o
	gcc src/programa-principal.o src/Parser/parser.o src/Catalog/flights_catalog.o src/Entities/flights.o -lglib-2.0 -o programa-principal

flights_catalog: src/Catalog/flights_catalog.o src/Entities/flights.o
	gcc $(LDFLAGS) src/Catalog/flights_catalog.o src/Entities/flights.o -o flights_catalog

src/programa-principal.o: src/programa-principal.c
src/parser.o: src/Parser/parser.c
src/Catalog/flights_catalog.o: src/Catalog/flights_catalog.c
src/Entities/flights.o: src/Entities/flights.c

clean:
	rm -f programa-principal programa-testes src/*.o src/Parser/*.o src/Catalog/*.o src/Entities/*.o flights_catalog