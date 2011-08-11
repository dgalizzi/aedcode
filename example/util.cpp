//__INSERT_LICENSE__
// $Id$
/* 
   COMIENZO DE DESCRIPCION 
   Utilitarios varios. 
keywords: lista, cola
FIN DE DESCRIPCION 
*/
#include <cmath>
#include <cstdlib>
#include <list>
#include <iostream>
#include "util.h"

using namespace std;

// -----------------------------------------------------------------
double drand() {
	return double(rand())/double(RAND_MAX);
}
// -----------------------------------------------------------------
int irand(int m) {
	return int(double(m)*drand());
}
// -----------------------------------------------------------------
void randl(list<int> &l,int m,int n) {
	for (int j=0;j<n;j++) l.insert(l.end(),irand(m));
}
// -----------------------------------------------------------------
void randl (list<int> &l,int m,double n) {
	// define una probabilidad de detenerse
	double lambda=1.0/(n+1.0);
	while (true) {
		if (drand()<lambda) break;
		l.insert(l.end(),irand(m));
	} 
} 
// -----------------------------------------------------------------
// Similar al anterior, pero asegurando una cantidad mínima de 
// elementos. La función anterior, cuando uno busca listas chicas,
// suele tirar listas vacías o de un elemento, donde muchos ejemplos
// no se llegan a apreciar.
void randl (list<int> &l,int m,double n, int min_n) {
	// Asegura una cantidad min_n de elementos
	while (min_n-- > 0)
		l.insert(l.end(),irand(m));

	// define una probabilidad de detenerse
	double lambda=1.0/(n+1.0);
	while (true) {
		if (drand()<lambda) break;
		l.insert(l.end(),irand(m));
	} 
} 

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// llena un vector "vl" de "n" listas con listas "l_i" de longitudes 
// aleatorias "n_i" y contenidos tambien aleatorios (numeros enteros)
template <typename t>
void generar_vl(vector< list <t> > &vl) {
	typename  list< list<t> >::iterator p;
	int  k,z,n;
	n=vl.size();
	for (int i=0;i<n;i++) {
		z=irand(10);
		for (int j=0;j<z;j++) {
			k=irand(100);
			vl[i].insert(vl[i].end(),k);      
		}
	}
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// imprime vector de listas
template <typename t>
void imprime_vl(vector< list <t> > &vl) {
	typename list<t>::iterator q,z;
	int n;
	n=vl.size();
	// imprime cada lista
	for (int i=0;i<n;i++) {
		cout << "lista l [" << i << "]: "; printl(vl[i]);
	}
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void add_to_list(list<int> &L,int term,va_list elems) {
	int count=0;
	while (1) {
		int x = va_arg(elems, int);
		if (x==term) break;
		count++;
		L.push_back(x);
	}
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void add_to_list(list<int> &L,int term,...) {
	// Funcion auxiliar que carga elementos hasta llegar al
	// terminador `term'. Usa macros `variadicos'
	// http://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html#Variadic-Functions
	va_list elems;
	va_start(elems,term);
	add_to_list(L,term,elems);
	va_end(elems);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void add_to_set(set<int> &s,int term,va_list elems) {
	int count=0;
	while (1) {
		int x = va_arg (elems, int);
		if (x==term) break;
		count++;
		s.insert(x);
	}
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void add_to_set(set<int> &s,int term,...) {
	// Funcion auxiliar que carga elementos hasta llegar al
	// terminador `term'. Usa macros `variadicos'
	// http://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html#Variadic-Functions
	va_list elems;
	va_start (elems,term);
	add_to_set(s,term,elems);
}
