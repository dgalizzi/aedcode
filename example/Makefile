all: junta orden_nivel random_shuffle intercala creciente ordenag cumsum cum_sum_cola particiona listarbo bilistado rejunta ascendente chunk-revert circulo encuentra reemplaza concatena refina print_back sorted_list1 sorted_list2 sorted_list3 inverse apply-map areinverse

junta: util.o junta.cpp
	g++ $^ -o bin/junta.out

areinverse: util.o areinverse.cpp
	g++ $^ -o bin/areinverse.out

apply-map: util.o apply-map.cpp
	g++ $^ -o bin/apply-map.out

inverse: util.o inverse.cpp
	g++ $^ -o bin/inverse.out

sorted_list1: util.o sorted_list1.cpp
	g++ $^ -o bin/sorted_list1.out

sorted_list2: util.o sorted_list2.cpp
	g++ $^ -o bin/sorted_list2.out

sorted_list3: util.o sorted_list3.cpp
	g++ $^ -o bin/sorted_list3.out

print_back: util.o print_back.cpp
	g++ $^ -o bin/print_back.out

refina: util.o refina.cpp
	g++ $^ -o bin/refina.out

concatena: util.o concatena.cpp
	g++ $^ -o bin/concatena.out

reemplaza: util.o reemplaza.cpp
	g++ $^ -o bin/reemplaza.out

encuentra: util.o encuentra.cpp
	g++ $^ -o bin/encuentra.out

circulo: util.o circulo.cpp
	g++ $^ -o bin/circulo.out

chunk-revert: util.o chunk-revert.cpp
	g++ $^ -o bin/chunk-revert.out

ascendente: util.o ascendente.cpp
	g++ $^ -o bin/ascendente.out

rejunta: util.o rejunta.cpp
	g++ $^ -o bin/rejunta.out

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
