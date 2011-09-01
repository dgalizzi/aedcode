#ifndef AED_LIST_DOBLE
#define AED_LIST_DOBLE
#include <cassert>

// Lista doblemente enlazada
namespace aed {

template <class T>
class list {
public:
	// La clase iterator es pública, para que
	// se puedan crear iterators.
	// Como la clase iterator es una clase
	// anidada a la clase list, para crear un iterator
	// de lista se debe hacer:
	// list<TIPO>::iterator it;
	//
	// Se declara acá, porque cell (ver abajo) hace uso de esta clase,
	// por lo tanto debe estar declarada previamente.
	class iterator;
private:
	// La clase cell también es una clase anidada, pero
	// a diferencia de iterator, es privada y no puede ser
	// accedida desde afuera. Sólo puede ser accedida
	// desde dentro de la misma clase p.
	class cell {
		// Las clases list e iterator
		// pueden acceder a la parte privada de esta clase.
		friend class list;
		friend class iterator;

		// El dato en sí, notar que es del tipo T,
		// es decir, del tipo que se le indicó por medio de
		// la templatización a la clase list.
		T t;
		cell *prev, *next; // La celda anterior y la siguiente, respectivamente.
		cell() : prev(NULL), next(NULL) { } // Constructor por defecto.

		// Constructor por comodidad, de esta forma podemos crear una celda
		// e indicarle la celda anterior y siguiente directamente por medio
		// del constructor.
		cell(cell *_prev, cell *_next, T _t) : prev(_prev), next(_next), t(_t) { }
	};

	// head es un elemento _placeholder_, simplemente nos sirve
	// para marcar el principio/final de la lista.
	// En informática se lo suele denominar como 'centinela' (sentinel).
	cell head;

public:
	// Implementación de la clase iterator
	class iterator {
	private:
		// La lista puede acceder a los elementos privados de iterator.
		friend class list;
		
		// ptr es la celda a la que el iterator apunta. 
		// Notar que ptr es privado, por lo tanto no se puede acceder directamente
		// cuando uno crea un iterator. Para acceder al valor del elemento apuntado
		// por el iterator, se deben usar los operadores de derreferenciación (ver abajo).
		cell* ptr;
	public:

		// Operadores de derreferenciación.

		// El operador * se utiliza para obtener una
		// referencia del elemento de tipo T al que apunta
		// el iterator.
		T & operator*() { return ptr->t; }

		// El operador -> se utiliza para acceder directamente a los
		// métodos o miembros del objeto al que el iterador apunta.
		// De esta forma, (*foo).bar() es lo mismo que foo->bar().
		T *operator->() { return &ptr->t; }

		// Igualdad entre iteradores. Dos iteradores son iguales
		// si apuntan al mismo elemento.
		bool operator!=(iterator q) { return ptr!=q.ptr; }
		bool operator==(iterator q) { return ptr==q.ptr; }
		iterator(cell *p=NULL) : ptr(p) {}

		// Incremento prefijo.
		// Avanza el iterador y devuelve el iterador avanzado.
		iterator operator++() {
			assert(ptr != NULL);
			ptr = ptr->next;
			return *this;
		}

		// Incremento sufijo.
		// Avanza el iterador y devuelve el iterador sin avanzar.
		iterator operator++(int) {
			assert(ptr != NULL);
			iterator q = *this;
			ptr = ptr->next;
			return q;
		}

		// Decremento prefijo.
		// Retrocede el iterador y devuelve el iterador anterior.
		iterator operator--() {
			assert(ptr != NULL);
			ptr = ptr->prev;
			return *this;
		}

		// Decremento sufijo.
		// Retrocede el iterador pero devuelve el iterador sin retroceder.
		iterator operator--(int) {
			assert(ptr != NULL);
			iterator q = *this;
			ptr = ptr->prev;
			return q;
		}
	};

	// Constructor
	list() {
		// placeholder (marcador de posición)
		head.next = &head;
		head.prev = &head;
	}

	// Destructor
	~list() { 
		// Se vacía la lista. Notar que el clear culmina en varios erase
		// donde cada uno hace el delete correspondiente, liberando
		// correctamente la memoria alocada dinámicamente.
		clear();
	}

	// Devuelve un iterator al primer elemento de la lista.
	// Notar que dicho iterator se puede derreferenciar para obtener el valor
	// del primer elemento.
	iterator begin() { return iterator(head.next); } 

	// Devuelve un iterator al elemento *siguiente* al último de la lista.
	// Este iterator actúa como marcador de posición y no puede ser derreferenciado.
	iterator end()   { return iterator(&head); }

	T& front() { return head.next->t; }       // Devuelve una referencia al primer elemento.
	T& back()  { return head.prev->t ; }      // Devuelve una referencia al último elemento.
	bool empty() { return begin() == end(); } // Devuelve true si la lista está vacía.

	// Métodos auxiliares, notar que todos se pueden hacer
	// con un simple insert/erase.
	void push_front(T data) { insert(begin(), data); }      // Agrega un elemento al principio de la lista
	void push_back(T data)  { insert(end(), data); }        // Agrega un elemento al final de la lista
	void pop_front()        { erase(begin()); }             // Elimina el primer elemento de la lista
	void pop_back()         { erase(iterator(head.prev)); } // Elimina el último elemento de la lista

	// Inserta el elemento data justo detrás del elemento
	// al que apunta q. q puede ser end, en este caso
	// el elemento data se agregará al final de la lista.
	iterator insert(iterator q, const T &data) {
		// Se crea una nueva celda, donde su elemnto anterior
		// es el anterior a q. Y su elemento siguente es q.
		cell *c = new cell(q.ptr->prev, q.ptr, data);

		c->prev->next = c; // El siguiente del anterior, es la celda nueva
		c->next->prev = c; // El anterior del siguiente, es la celda nueva
		return iterator(c); // Se devuelve un iterador al elemento recién creado
	}

	// Elimina de la lista el elemento apuntado por q.
	// El iterador pasado como parámetro resulta inválido.
	// Devuelve el iterador que le sigue a q.
	iterator erase(iterator q) {
		assert(q != end());

		cell* p = q.ptr->prev; // Anterior
		cell* n = q.ptr->next; // Siguiente
		delete q.ptr;
		p->next = n; // El siguiente del anterior, es el anterior
		n->prev = p; // El anterior del siguiente, es el anterior
		return iterator(n); // Devolver el siguiente
	}

	// Eliminar el rango [p, q), es decir, elimina
	// p, y todos los que están entre p y q.
	// No elimina q.
	// Devuelve q, es decir, un iterator al último elemento
	// no eliminado.
	iterator erase(iterator p, iterator q) {
		while (p != q)
			p = erase(p);
		return p; // Notar que a esta altura, p y q son iguales
	}

	// Borra todos los elementos de la lista
	void clear() {
		erase(begin(), end());
	}
};

}

#endif
