// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dados dos enteros #M# y #n#, tales que #n<M# crear un
   arbol binario completo (ABC) #T# tal que: 1) La suma de
   las hojas es #M#, pero cada una de ellas es #h<=n#. 2) Se
   satisface que para cada nodo #n# la suma de sus dos hijos
   #l# y #r# es #n=l+r#. Ayuda: El arbol se puede construir
   poniendo inicialmente #M# en la raiz, y dividiendo cada nodo 
   por 2 hasta obtener valores #<=n#. 
   keywords: arbol binario

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
void split_down(btree<int> &T, btree<int>::iterator p,int n) {
  // Se supone que `p' es dereferenciable. Fijarse
  // que despues le aplica el `split_down()' solo a nodos
  // dereferenciables. 

  // Si el contenido del nodo es menor que `n' ya esta. 
  if (*p <= n) return;
  // Divide el contenido de `p' en `r' y `l'
  // de tal manera que son approx *p/2
  // (pero la suma se preserva)
  int r = *p/2, l = *p-r;

  // Inserta los nuevos nodos y les aplica
  // recursivamente el `split_down()'
  T.insert(p.left(),r);
  split_down(T,p.left(),n);

  T.insert(p.right(),l);
  split_down(T,p.right(),n);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void split_down(int M,btree<int> &T,int n) {
  T.clear();
  // Inicialmente inserta `M' en la raiz.
  // Notar que esto garantiza que despues
  // la `split_down()' recursiva se aplica solo
  // a nodos dereferenciables. 
  T.insert(T.begin(),M);
  split_down(T,T.begin(),n);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main () {
  btree<int> T;
  // Prueba con dos juegos de valores
  int M=10, n=2;
  split_down(M,T,n);
  printf("M %d, n %d, T: ",M,n);
  T.lisp_print();
  printf("\n");

  M=100; n=7;
  split_down(M,T,n);
  printf("M %d, n %d, T: ",M,n);
  T.lisp_print();
  printf("\n");
  
  return 0;
}
