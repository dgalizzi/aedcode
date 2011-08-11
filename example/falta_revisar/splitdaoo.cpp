// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dados dos enteros #M# y #n#, tales que #n<M# crear un AOO
   #T# tal que: 1) La suma de las hojas es #M#, pero cada
   una de ellas es #h<=n#. 2) Se satisface que para cada
   nodo #p# la suma de sus hijos es #*p#. 3) Cada nodo tiene
   a lo sumo #g# hijos, con #g>1# una constante dada.
   Ayuda: El arbol se puede construir poniendo inicialmente
   #M# en la raiz, y dividiendo el contenido #*n# de cada
   nodo en #g# valores aprox iguales hasta obtener valores
   #<=n#. [Tomado en el 2do parcial del 2009-10-27].
   keywords: arbol orientado

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
#include <cstdarg>
#include <cstdio>

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Esta funcion es auxiliar, divide el entero `m'
// en `g' partes menores (g>1) lo mas uniformes posibles.
// Si q = m/g, y r = m%g, entonces a los r primeros
// les toca q+1 y a los restantes q. 
void distrib(int m,int g, vector<int> &v) {
  v.clear();
  // A cada hijo le corresponde q o q+1,
  // dependiendo del resto. 
  int q = m/g, r = m%g, j=0, c;
  for (int j=0; j<g; j++) {
    // Notar que j<r da valores 1 para los r primeros
    // y 0 para el resto
    c = q+(j<r);
    // Solo pone los positivos
    if (c>0) v.push_back(c);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void split_down(tree<int> &T,node_t p,int n,int g) {
  // Si el valor en la raiz esta OK, entonces no hace falta
  // hacer nada. 
  if (*p <= n) return;
  // Llama a `distrib()' para ver como es la distribucion
  // del valor en el nodo `*p'
  vector<int> v; distrib(*p,g,v);
  // Va iterando, creando los nuevos nodos
  node_t c = p.lchild();
  for (unsigned int j=0; j<v.size(); j++) {
    c = T.insert(c,v[j]);
    // Aplica recursivamente la funcion
    split_down(T,c++,n,g);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void split_down(tree<int> &T,int M,int n,int g) {
  T.clear();
  T.insert(T.begin(),M);
  split_down(T,T.begin(),n,g);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  tree<int> T;
#define TRY(M,n,g)                              \
  split_down(T,M,n,g);                          \
  printf("M %d, n %d, g %d, T: ",M,n,g);        \
  T.lisp_print(); printf("\n");

  TRY(20,4,3);
  TRY(20,7,3);
  TRY(20,7,2);
  TRY(50,7,4);
  TRY(50,2,4);
  
  return 0;
}
