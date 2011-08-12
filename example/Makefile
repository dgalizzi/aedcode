all: junta orden_nivel random_shuffle intercala creciente ordenag cumsum cum_sum_cola particiona listarbo bilistado

junta: util.o junta.cpp
	g++ $^ -o bin/junta.out

particiona: util.o particiona.cpp
	g++ $^ -o bin/particiona.out

cum_sum_cola: util.o cum_sum_cola.cpp
	g++ $^ -o bin/cum_sum_cola.out

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

cumsum: util.o util_tree.o cumsum.cpp
	g++ $^ -o bin/cumsum.out

listarbo: util.o util_tree.o listarbo.cpp
	g++ $^ -o bin/listarbo.out

bilistado: util.o util_tree.o bilistado.cpp
	g++ $^ -o bin/bilistado.out

util.o: util.h util.cpp
	g++ -c util.cpp

util_tree.o: util_tree.h util_tree.cpp
	g++ -c util_tree.cpp

.PHONY: clean

clean:
	rm *.o bin/*.out
