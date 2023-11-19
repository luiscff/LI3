CFLAGS=-Wall -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS=`pkg-config --libs glib-2.0`

programa-principal: src/programa-principal.o src/parser.o src/interpreter.o src/queries.o src/Catalog/flights_catalog.o src/Catalog/passengers_catalog.o src/Catalog/users_catalog.o src/Catalog/reservations_catalog.o src/Entities/flights.o src/Entities/passengers.o src/Entities/user.o src/Entities/reservation.o
	gcc -g $^ -lglib-2.0 -o $@

src/programa-principal.o: src/programa-principal.c
src/parser.o: src/parser.c
src/interpreter.o: src/interpreter.c
src/queries.o: src/queries.c
src/Catalog/flights_catalog.o: src/Catalog/flights_catalog.c
src/Catalog/passengers_catalog.o: src/Catalog/passengers_catalog.c
src/Catalog/users_catalog.o: src/Catalog/users_catalog.c
src/Catalog/reservations_catalog.o: src/Catalog/reservations_catalog.c
src/Entities/flights.o: src/Entities/flights.c
src/Entities/passengers.o: src/Entities/passengers.c
src/Entities/user.o: src/Entities/user.c
src/Entities/reservation.o: src/Entities/reservation.c

leaks: programa-principal
	valgrind --leak-check=full ./programa-principal ~/Desktop/smallDataset/ palha

clean:
	rm -f programa-principal programa-testes src/*.o  src/Catalog/*.o src/Entities/*.o Resultados/outputs/*.txt