// $Id$
/* COMIENZO DE DESCRIPCION

  Escribir una funci\'on int maxcota (tree <int> & t, node_t n, 
  const int & cota) que retorna el m\'aximo de las etiquetas de un 
  \'arbol ordenado orientado tales que son menores o iguales 
  que la cota dada. Por ejemplo, si las etiquetas del \'arbol 
  A son (1,3,7,4,2,10,13) y cota=8, entonces 
  maxcota (raiz (A), A, 8) debe retornar 7.
  keywords: arbol orientado

  FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_tree.cpp
//        icc -w -c maxcota_bo.cpp
//        icc -w -o maxcota_bo.exe maxcota_bo.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_tree.cpp
//        g++ -w -c maxcota_bo.cpp
//        g++ -w -o maxcota_bo.exe maxcota_bo.o util.o util_tree.o
//
// -------------------------------------------------------------------
#include <iostream>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
// esta version es una modificacion simple del "max_etiq_arbol"
int maxcota (tree <int> & T, node_t n, const int & cota) {
  int x, xmax ;
  node_t c ;
  if (n == T.end () ) return -1; // un valor fuera de rango
  // si la etiqueta del nodo es menor a la cota
  // entonces el maximo actual es la etiqueta del nodo
  xmax = 0 ;
  if ( *n <= cota ) xmax = *n ;
  // compara con los mascota de los hijos y actualiza
  c = n.lchild ();
  while ( c != T.end () ) {
    x = maxcota (T, c++, cota) ;
    if ( x > xmax && x <= cota )  xmax = x ;
  } // end while
  return xmax ;
}

// -------------------------------------------------------------------
int main () {
  tree <int> t1;
  list <int> l1;
  const int BP = -2, EP = -1, EL = -3 ;
  int  v1 [] = {BP,1,BP,3,7,4,2,EP,BP,10,13,
                BP,1,6,3,EP,0,EP,BP,2,3,EP,EP,EL};
  const int cota = 8 ;
  int xcota ;

  cout << endl; 
  cout << "maxcota en arbol orientado " << endl ;
  cout << endl; 

  l1.clear ();
  insertl (l1, v1, EL);
  t1.clear ();
  list2tree (t1, l1, BP, EP);
  print_tree (t1);
  xcota = maxcota ( t1, t1.begin (), cota ) ; 
  cout << "maxcota (t1) = " << xcota << endl ;

  cout << endl; 
  return 0 ;
} // end main
// -------------------------------------------------------------------
