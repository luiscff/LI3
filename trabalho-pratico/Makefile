CFLAGS=-Wall -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS=`pkg-config --libs glib-2.0`

.PHONY: clean_objs

all: programa-principal programa-testes clean_objs

programa-principal: src/programa-principal.o src/parser.o src/interpreter.o src/queries.o src/output.o src/validation.o src/Catalog/flights_catalog.o src/Catalog/passengers_catalog.o src/Catalog/users_catalog.o src/Catalog/reservations_catalog.o src/Catalog/stats.o src/Entities/flight.o src/Entities/passenger.o src/Entities/user.o src/Entities/reservation.o
	gcc -g $^ -lglib-2.0 -o $@
	

programa-testes: src/Tests/programa-testes.o src/Tests/interpreter-testes.o src/parser.o src/queries.o src/output.o src/validation.o src/Catalog/flights_catalog.o src/Catalog/passengers_catalog.o src/Catalog/users_catalog.o src/Catalog/reservations_catalog.o src/Catalog/stats.o src/Entities/flight.o src/Entities/passenger.o src/Entities/user.o src/Entities/reservation.o
	gcc -g $^ -lglib-2.0 -o $@
	

clean_objs:
	rm -f src/*.o src/Catalog/*.o src/Entities/*.o src/Tests/*.o

src/programa-principal.o: src/programa-principal.c
src/programa-testes.o: src/Tests/programa-testes.c
src/parser.o: src/parser.c
src/interpreter.o: src/interpreter.c
src/interpreter-testes.o: src/Tests/interpreter-testes.c
src/queries.o: src/queries.c
src/output.o: src/output.c
src/validation.o: src/validation.c
src/Catalog/flights_catalog.o: src/Catalog/flights_catalog.c
src/Catalog/passengers_catalog.o: src/Catalog/passengers_catalog.c
src/Catalog/users_catalog.o: src/Catalog/users_catalog.c
src/Catalog/reservations_catalog.o: src/Catalog/reservations_catalog.c
src/Catalog/stats.o: src/Catalog/stats.c
src/Entities/flight.o: src/Entities/flight.c
src/Entities/passenger.o: src/Entities/passenger.c
src/Entities/user.o: src/Entities/user.c
src/Entities/reservation.o: src/Entities/reservation.c

leaks: programa-principal
	valgrind --leak-check=full ./programa-principal ~/Desktop/dataset/data_clean ~/Desktop/dataset/input.txt

clean:
	rm -f programa-principal programa-testes src/*.o  src/Catalog/*.o src/Entities/*.o Resultados/*.txt
	> Resultados/users_errors.csv
	> Resultados/flights_errors.csv
	> Resultados/passengers_errors.csv
	> Resultados/reservations_errors.csv