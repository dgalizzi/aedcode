orden_nivel: util.o util_tree.o orden_nivel.cpp
	g++ $^ -o bin/orden_nivel.out

util.o: util.h util.cpp
	g++ -c util.cpp

util_tree.o: util_tree.h util_tree.cpp
	g++ -c util_tree.cpp

.PHONY: clean

clean:
	rm *.o bin/*.out
