#ifndef AED_BTREE_H
#define AED_BTREE_H

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <list>

using namespace std;

namespace aed {

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
template<class T>
class btree {
public:
	class iterator;
private:
	class cell {
		friend class btree;
		friend class iterator;
		T t;
		// Celdas al hijo derecho e hijo izquierdo respectivamente
		cell *right,*left;
		cell() : right(NULL), left(NULL)	{}
	};
	// Celda ficticia (placeholder, marcador de posición, sentinela)
	cell *header;
	// Indicador de si es un hijo derecho o izquierdo
	enum side_t {NONE,R,L};
public:
	static int cell_count_m;
	static int cell_count() { return cell_count_m; }
	class iterator {
	private:
		friend class btree;
		cell *ptr,*father;
		side_t side;
		iterator(cell *p,side_t side_a,cell *f_a) : ptr(p), side(side_a), father(f_a) { }
	public:
		iterator(const iterator &q) {
			ptr = q.ptr;
			side = q.side;
			father = q.father;
		}
		T &operator*() { return ptr->t; }
		T *operator->() { return &ptr->t; }
		bool operator!=(iterator q) { return ptr!=q.ptr; }
		bool operator==(iterator q) { return ptr==q.ptr; }
		iterator() : ptr(NULL), side(NONE), father(NULL) { }

		iterator left() { return iterator(ptr->left,L,ptr); }
		iterator right() { return iterator(ptr->right,R,ptr); }

	}; // End class iterator

	btree() {
		header = new cell;
		cell_count_m++;
		header->right = NULL;
		header->left = NULL;
	}

	// El constructor copia debe alocar
	// nueva memoria donde guardar todas las nuevas
	// celdas. No se puede utilizar el constructor copia
	// por defecto porque sólo copiaría punteros, y ambos árboles
	// apuntarían a los mismos elementos.
	btree<T>(const btree<T> &TT) { 
		if (&TT != this) {
			header = new cell;
			cell_count_m++;
			header->right = NULL;
			header->left = NULL;
			btree<T> &TTT = (btree<T> &) TT;
			if (TTT.begin()!=TTT.end()) 
				copy(begin(),TTT,TTT.begin()); 
		}
	}

	btree &operator=(btree<T> &TT) { 
		if (this != &TT) {
			clear();
			copy(begin(),TT,TT.begin()); 
		}
		return *this;
	}

	~btree() { clear(); delete header; cell_count_m--; }

	// Inserta un nodo en p, con dato t
	iterator insert(iterator p,T t) {
		assert(p==end());
		cell *c = new cell;
		cell_count_m++;
		c->t = t;
		if (p.side==R) p.father->right = c;
		else p.father->left = c;
		p.ptr = c;
		return p;
	}

	// Eliminar el nodo p, esto elimina también
	// todos los hijos de p, es decir, todo el
	// subárbol.
	iterator erase(iterator p) {
		if(p==end()) return p;
		erase(p.right());
		erase(p.left());
		if (p.side==R) p.father->right = NULL;
		else p.father->left = NULL;
		delete p.ptr;
		cell_count_m--;
		p.ptr = NULL;
		return p;
	}

	iterator splice(iterator to,iterator from) {
		if (from==end()) return to;
		cell *c = from.ptr;
		from.ptr = NULL;
		if (from.side==R) from.father->right = NULL;
		else from.father->left = NULL;

		if (to.side==R) to.father->right = c;
		else to.father->left = c;
		to.ptr = c;
		return to;
	}
	iterator copy(iterator nq,btree<T> &TT,iterator nt) {
		nq = insert(nq,*nt);
		iterator m = nt.left();
		if (m != TT.end()) copy(nq.left(),TT,m);
		m = nt.right();
		if (m != TT.end()) copy(nq.right(),TT,m);
		return nq;
	}
	iterator find(T t) { return find(t,begin()); }
	iterator find(T t,iterator p) {
		if(p==end() || p.ptr->t == t) return p;
		iterator l = find(t,p.left());
		if (l!=end()) return l;
		iterator r = find(t,p.right());
		if (r!=end()) return r;
		return end();
	}

	// Vaciar el arbol
	void clear() { erase(begin()); }
	iterator begin() { return iterator(header->left,L,header); }

#if 0
	void print_prev(iterator p) { 
		if (p==end()) return;
		cout << "(" << p.ptr << "," << p.ptr->t << ")" << endl;
		iterator c = p.lchild();
		while (c!=end()) print_prev(c++);
	}
	void print_prev() { print_prev(begin()); }

	void print_post(iterator p) { 
		if (p==end()) return;
		iterator c = p.lchild();
		while (c!=end()) print_post(c++);
		cout << "(" << p.ptr << "," << p.ptr->t << ")" << endl;
	}
	void print_post() { print_post(begin()); }
#endif

	// Mostrar el arbol con notación lisp
	void lisp_print(iterator n) {
		if (n==end()) { cout << "."; return; }
		iterator r = n.right(), l = n.left();
		bool is_leaf = r==end() && l==end();
		if (is_leaf) cout << *n;
		else {
			cout << "(" << *n << " ";
			lisp_print(l);
			cout << " ";
			lisp_print(r);
			cout << ")";
		}
	}
	void lisp_print() { lisp_print(begin()); }

	iterator end() { return iterator(); }
};

template<class T>
int btree<T>::cell_count_m = 0;
}
#endif
