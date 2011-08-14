all: junta orden_nivel random_shuffle intercala creciente ordenag cumsum cum_sum_cola particiona listarbo bilistado rejunta ascendente chunk-revert circulo encuentra reemplaza concatena refina print_back sorted_list1 sorted_list2 sorted_list3 inverse apply-map areinverse cadena_pq cyclic intersecmap lista_cte map2list map_explora mergemap connected diffsym eqclass graphlayers incall incluido ismapset isspngtree propsubset es_biyectiva espermut nilpot

junta: util.o junta.cpp
	g++ $^ -o bin/junta.out

nilpot: util.o nilpot.cpp
	g++ $^ -o bin/nilpot.out

espermut: util.o espermut.cpp
	g++ $^ -o bin/espermut.out

es_biyectiva: util.o es_biyectiva.cpp
	g++ $^ -o bin/es_biyectiva.out

propsubset: util.o propsubset.cpp
	g++ $^ -o bin/propsubset.out

ismapset: util.o ismapset.cpp
	g++ $^ -o bin/ismapset.out

incluido: util.o incluido.cpp
	g++ $^ -o bin/incluido.out

incall: util.o incall.cpp
	g++ $^ -o bin/incall.out

graphlayers: util.o graphlayers.cpp
	g++ $^ -o bin/graphlayers.out

eqclass: util.o eqclass.cpp
	g++ $^ -o bin/eqclass.out

diffsym: util.o diffsym.cpp
	g++ $^ -o bin/diffsym.out

connected: util.o connected.cpp
	g++ $^ -o bin/connected.out

mergemap: util.o mergemap.cpp
	g++ $^ -o bin/mergemap.out

map_explora: util.o map_explora.cpp
	g++ $^ -o bin/map_explora.out

map2list: util.o map2list.cpp
	g++ $^ -o bin/map2list.out

lista_cte: util.o lista_cte.cpp
	g++ $^ -o bin/lista_cte.out

intersecmap: util.o intersecmap.cpp
	g++ $^ -o bin/intersecmap.out

cyclic: util.o cyclic.cpp
	g++ $^ -o bin/cyclic.out

cadena_pq: util.o cadena_pq.cpp
	g++ $^ -o bin/cadena_pq.out

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

isspngtree: util.o util_tree.o isspngtree.cpp
	g++ $^ -o bin/isspngtree.out

util.o: util.h util.cpp
	g++ -c util.cpp

util_tree.o: util_tree.h util_tree.cpp
	g++ -c util_tree.cpp

.PHONY: clean

clean:
	rm *.o bin/*.out
