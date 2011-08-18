/*
 * Implementación de una lista simplemente enlazada
 * mediante punteros.
 */
#ifndef AED_LIST_H 
#define AED_LIST_H

#include <cstddef>  
#include <iostream>  

namespace aed {

template<class T>
class list {
public:
	class iterator;
private:
	class cell {
		friend class list;
		friend class iterator;
		// El dato de la celda,
		// tener en cuenta que, a nivel estructura de datos,
		// este dato es en realidad el de la celda anterior.
		// (ver más abajo)
		T t;
		// Puntero a la celda siguiente, en una lista doblemente
		// enlazada se tiene además un puntero a la celda
		// anterior.
		cell *next;
		cell() : next(NULL) {}
	};
	// Celdas auxiliares (ver más abajo)
	cell *first, *last;
public:
	class iterator {
	private:
		friend class list;
		// La celda a la que apunta el iterador.
		cell* ptr;
	public:

		// IMPORTANTE: Esta es una parte muy importante
		// de esta implementación.
		// El valor del iterador, es decir, el dato/elemento
		// al que el iterador apunta, se encuentra en la
		// celda siguiente. 
		// Al pedir ptr->next->t estamos pidiendo el dato
		// de la siguiente celda. Esto se hace así para
		// que uno pueda insertar elementos detrás de un iterador.
		// Tener en cuenta que la lista es simplemente enlazada,
		// por lo tanto no se guarda un puntero a la celda anterior,
		// sólamente a la siguiente, por lo tanto no podríamos insertar
		// detrás de un iterador sin este 'truquito' (al menos no en O(1)).
		//
		// En las listas doblemente enlazadas, esto no se hace,
		// ya que sí se tiene un puntero a la celda anterior.
		T & operator*() { return ptr->next->t; }
		T *operator->() { return &ptr->next->t; }
		bool operator!=(iterator q) { return ptr!=q.ptr; }
		bool operator==(iterator q) { return ptr==q.ptr; }
		iterator(cell *p=NULL) : ptr(p) {}
		// Prefix:
		iterator operator++() {
			ptr = ptr->next;
			return *this;
		}
		// Postfix:
		iterator operator++(int) {
			iterator q = *this;
			ptr = ptr->next;
			return q;
		}
	};  

	list() {
		// Punteros auxiliares.
		// first es un puntero al primer elemento de la lista.
		// last es un puntero a un elemento _placeholder_, simplemente nos sirve
		// para marcar el final de la lista. En informática, a este tipo
		// de puntero se le llama 'centinela' (sentinel), se puede prescindir de él,
		// pero el centinela ayuda a reducir la complejidad de algunos métodos.
		// Para más información sobre centinelas ver http://en.wikipedia.org/wiki/Sentinel_(computer_science)
		// Si la lista está vacía, tanto first como last apuntan al mismo elemento.
		first = new cell;
		last = first;
	}

	// Inserta el elemento data justo detrás del elemento
	// al que apunta p. p puede ser end, en este caso
	// el elemento data se agregará al final de la lista.
	iterator insert(iterator p,T t) {
		cell *q = p.ptr->next;
		cell *c = new cell;
		p.ptr->next = c;
		c->next = q;
		c->t = t;
		if (q==NULL) last = c;
		return p;
	}

	// Elimina de la lista el elemento apuntado por p.
	// El iterador pasado como parámetro resulta inválido,
	// por lo tanto, no debe ser derreferenciado.
	// Devuelve el iterador que le sigue a p.
	iterator erase(iterator p) {
		cell *q = p.ptr->next;
		if (q==last) last = p.ptr;
		p.ptr->next = q->next;
		delete q;
		return p;
	}
	iterator erase(iterator p,iterator q) {
		cell *s, *r = p.ptr->next;
		p.ptr->next = q.ptr->next;
		if (!p.ptr->next) last = p.ptr;
		while (r!=q.ptr->next) {
			s = r->next;
			delete r;
			r = s;
		}
		return p;
	}
	void clear() { erase(begin(),end()); }
	iterator begin() { return iterator(first); }
	iterator end() { return iterator(last); }
	void print() {   
		iterator p = begin();
		while (p!=end()) std::cout << *p++ << " ";
		std::cout << std::endl;
	}
	void printd() {
		std::cout << "h(" << first << ")" << std::endl;
		cell *c = first->next;
		int j=0;
		while (c!=NULL) { 
			std::cout << j++ << "(" << c << ") :" << c->t << std::endl; 
			c = c->next;
		}
	}

	// Notar que este método es O(n), es decir,
	// de orden lineal.
	int size() {
		int sz = 0;
		iterator p = begin();
		while (p++!=end()) sz++;
		return sz;
	}
};

}
#endif
