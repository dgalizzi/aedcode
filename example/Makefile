all: junta orden_nivel random_shuffle intercala creciente ordenag

junta: util.o junta.cpp
	g++ $^ -o bin/junta.out

ordenag: util.o ordenag.cpp
	g++ $^ -o bin/ordenag.out

creciente: util.o creciente.cpp
	g++ $^ -o bin/creciente.out

intercala: util.o intercala.cpp
	g++ $^ -o bin/intercala.out

random_shuffle: util.o random_shuffle.cpp
	g++ $^ -o bin/random_shuffle.out

orden_nivel: util.o util_tree.o orden_nivel.cpp
	g++ $^ -o bin/orden_nivel.out

util.o: util.h util.cpp
	g++ -c util.cpp

util_tree.o: util_tree.h util_tree.cpp
	g++ -c util_tree.cpp

.PHONY: clean

clean:
	rm *.o bin/*.out
