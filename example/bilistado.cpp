//$Id$
/* COMIENZO DE DESCRIPCION

El bi-listado de un \'arbol ordenado orientado puede
pensarse como una combinacion de los listados previo y
posterior. Asumamos que las etiquetas tienen dos partes,
una etiqueta `derecha' y otra `izquierda', entonces el
bi-listado de un nodo n se define como:
BILISTADO (n) = (ETIQUETA-IZQUIERDA (n), BILISTADO (h1),
BILISTADO (h2), ...  ETIQUETA-DERECHA (n)),
donde h1, h2 ... son los hijos de n. Por ejemplo, si
A:1 ( 8 ( 3 2 ) 4 ( 9 2 ) ), y tomamos como etiqueta centro
a (100+etiqueta) y etiqueta izquierda como (200+etiqueta),
entonces debe listar (10 21 121 30 40 140 51 60 160 70 170
151 80 180 130 110).  
Para simplificar, en vez de tener 2 etiquetas tenemos una 
sola etiqeta entera "e" y la etiqueta derecha es 100+e. 
Por ejemplo si la etiqueta es 11 entonces
las etiquetas izquierda y derecha son [11,111].
[Tomado 2do parcial de 2003, 3-Jun-2003]
Keywords: arbol orientado

  FIN DE DESCRIPCION */

// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_tree.cpp
//        icc -w -c bilistado.cpp
//        icc -w -o bilistado.exe bilistado.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_tree.cpp
//        g++ -w -c bilistado.cpp
//        g++ -w -o bilistado.exe bilistado.o util.o util_tree.o
//
// -------------------------------------------------------------------
#include <iostream>
#include "util.h"
#include "../include/tree.h"
#include "util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
void  bilistado ( tree <int> & t, node_t n ) {
  node_t c ;  
  int    p ;
  if ( n == t.end () ) return ;
  // imprime etiqueta izquierda 
  cout << (* n)       << ' ' << endl ; 
  // aplica bilistado a los hijos
  c = n.lchild () ;
  while ( c != t.end () ) bilistado (t, c++) ;
  // imprime etiqueta derecha
  cout << (* n) + 100 << ' ' << endl ; 
} // end void

// -------------------------------------------------------------------
int main () {
  tree <int> t;
  for (int j = 0 ; j < 1 ; j++) {
    t.clear ();
    make_random_tree (t, 10, 2);
    cout << endl ;
    cout << "arbol orientado:"  << endl ; 
    print_tree (t);
    cout << endl ;
    cout << endl ;
    cout << "bilistado:"  << endl ; 
    bilistado ( t, t.begin () ) ; 
  } // end for
  cout << endl ;
  return 0 ;
} // end main
// -------------------------------------------------------------------
