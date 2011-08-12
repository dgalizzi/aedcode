// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   El #cumsum(v)# de un vector #v# es la suma acumulada, es
   decir en la posicion #v[j]# debe quedar la suma de los
   elementos de #v[0..j]#. Para un arbol lo podemos extender
   diciendo que en cada nodo del arbol queda la suma de los
   valores de los nodos de su subarbol ANTES de la
   operacion. Por ejemplo si #T=(1 (2 (3 4 5 6))))# entonces
   despues de #cumsum(T)# debe quedar #T=(21 (2 (18 4 5
   6))))#. La version hacia abajo corresponde a que en cada camino
   #n0,n1,...,nk# queden los valores #cumsum[*n0,*n1,...,*nk]#. 
   keywords: arbol orientado

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
#include <cstdarg>
#include <cstdio>

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "util.h"
#include "../include/tree.h"
#include "util_tree.h"

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void cumsum(tree<int> &T,node_t p) {
  node_t c = p.lchild();
  while (c!=T.end()) {
    cumsum(T,c);
    *p += *c++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void cumsum(tree<int> &T) {
  if (!T.empty()) cumsum(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void cumsum_down(tree<int> &T,node_t n,int sumup) {
  *n += sumup;
  node_t c = n.lchild();
  while (c!=T.end()) cumsum_down(T,c++,*n);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void cumsum_down(tree<int> &T) {
  if (!T.empty()) cumsum_down(T,T.begin(),0);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  tree<int> T;
  for (int j=0; j<10; j++) {
    T.clear();
    make_random_tree(T,10,2.0);
    printf("T: "); T.lisp_print(); printf("\n"); 
    cumsum(T);
    printf("after cumsum(T)\n"); 
    printf("T: "); T.lisp_print(); printf("\n"); 
    printf("------------\n");
  }

  for (int j=0; j<10; j++) {
    T.clear();
    make_random_tree(T,10,2.0);
    printf("T: "); T.lisp_print(); printf("\n"); 
    cumsum_down(T);
    printf("after cumsum_down(T)\n"); 
    printf("T: "); T.lisp_print(); printf("\n"); 
    printf("------------\n");
  }

  return 0;
}
