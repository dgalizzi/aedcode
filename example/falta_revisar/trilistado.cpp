// $Id$
/* COMIENZO DE DESCRIPCION

 El trilistado de un arbol ordenado binario puede pensarse 
 como una combinacion de los listados previo, posterior y 
 sim\'etrico. Asumamos que las etiquetas tienen
 tres partes: una etiqueta derecha, una izquierda y
 otra centro, entonces el trilistado de un nodo {\tt n} se
 define como:
 TRILISTADO (n) = ( ETIQ-IZQ (n), TRILISTADO (HIJO-IZQ (n) ),
 ETIQ-CENTRO (n), TRILISTADO ( HIJO-DER (n) ), ETIQ-DER (n) ).
 Por ejemplo, si A: 1 ( 8 ( 3 2 ) 4 ( 9 2 ) ), y tomamos como
 etiqueta derecha a (100+etiqueta) y etiqueta izquierda como
 (200+etiqueta), entonces debe listar (1 8 3 103 203 108 2
 102 202 208 101 4 9 109 209 104 2 102 202 204 201).  Para
 simplificar, en vez de tener 3 etiquetas tenemos una sola
 etiqeta entera e. La etiqueta del centro es (100+e) y la
 derecha es (200+e). Por ejemplo si la etiqueta es 11
 entonces las etiquetas izquierda, centro y derecha son
 [11,111,211]. [Tomado 2do parcial de 2003, 3-Jun-2003].
 Keywords: arbol binario

  FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_btree.cpp
//        icc -w -c trilistado.cpp
//        icc -w -o trilistado.exe trilistado.o util.o util_btree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_btree.cpp
//        g++ -w -c trilistado.cpp
//        g++ -w -o trilistado.exe trilistado.o util.o util_btree.o
//
// -----------------------------------------------------------------
#include <iostream>
#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
void  trilistado ( btree<int> &T, btree<int>::iterator n) {
  btree<int>:: iterator c1, c2 ;
  if ( n == T.end () ) return ;
  // imprime etiqueta izquierda 
  cout << (* n)       << ' ' << endl ; 
  // aplica trilistado_p al hijo izquierdo
  c1 = n.left () ;
  trilistado (T, c1) ;
  // imprime etiqueta centro
  cout << (* n) + 100 << ' ' << endl ; 
  // aplica trilistado_p al hijo derecho
  c2 = n.right  () ;
  trilistado (T, c2) ;
  // imprime etiqueta centro
  cout << (*n) + 200 << ' ' << endl ; 
} // end void

// -----------------------------------------------------------------
int main () {
  btree <int> T;
  for (int j = 0 ; j < 1 ; j++) {
    T.clear ();
    make_random_btree (T, 9, 1.3);
    cout << endl ;
    cout << "arbol binario:" << endl ; 
    T.lisp_print (); 
    cout << endl ;
    cout << endl ;
    cout << "trilistado:"    << endl ; 
    trilistado (T, T.begin () ) ; 
  } // end for
  cout << endl ;
  return 0 ;
} // end main
// -----------------------------------------------------------------
