// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dados un arbol binario #T# reordenarlo de forma de que si 
   un nodo tiene un solo hijo, entonces debe ser el izquierdo. 
   Ayuda: Usar la funcion #splice()#. 

  FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#include <cstdio>
#include <iostream>

#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void packleft(btree<int> &T,btree<int>::iterator n) {
  // Si el arbol esta vacio no hay que hacer nada
  if (n==T.end()) return;
  // `l,r' son los hijos
  btree<int>::iterator l = n.left(), r = n.right();
  // Solo en el caso de que `l' es vacio y `r'
  // no, entonces hay que hacer un splice.
  // Notar que hay que refrescar `l,r'
  if (l==T.end() && r!=T.end()) l = T.splice(l,r);
  r = n.right();
  // Aplica recursivamente a `l' y `r'
  packleft(T,l);
  packleft(T,r);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void packleft(btree<int> &T) { packleft(T,T.begin()); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main () {
  btree<int> T;
  for (int j=0; j<10; j++) {
    T.clear();
    make_random_btree(T,10,0.5);
    printf("T:           "); T.lisp_print(); printf("\n");
    packleft(T);
    printf("packleft(T): "); T.lisp_print(); printf("\n");
  }

  return 0;
}
