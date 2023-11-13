CFLAGS=-Wall -Iinclude

programa-principal: src/programa-principal.o src/Parser/parser.o
	gcc $(LDFLAGS) src/programa-principal.o src/Parser/parser.o -o programa-principal

src/programa-principal.o: src/programa-principal.c
src/parser.o: src/Parser/parser.c


clean:
	rm -f programa-principal programa-testes src/*.o src/Parser/*.o