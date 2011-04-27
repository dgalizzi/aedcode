//$Id$
/*
  COMIENZO DE DESCRIPCION
  Escribir una funcion SUMA_PAR_ANTEC (n:nodo; a:arbol):
  integer; que devuelve la suma de las etiquetas de los
  nodos tales que su etiqueta y la etiqueta de todos sus
  antecesores sea par. En forma recursiva SUMA_PAR_ANTEC
  es 0 si el arbol esta vacio o su etiqueta es impar y
  en otro caso es la suma de su etiqueta mas la
  SUMA_PAR_ANTEC de sus hijos.
  keywords: arbol orientado

  FIN DE DESCRIPCION
*/
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_tree.cpp
//        icc -w -c sumparantec.cpp
//        icc -w -o sumparantec.exe sumparantec.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_tree.cpp
//        g++ -w -c sumparantec.cpp
//        g++ -w -o sumparantec.exe sumparantec.o util.o util_tree.o
//
// -------------------------------------------------------------------
#include <iostream>
#include "./tree.h"
#include "./util.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
int sumaparantec (tree <int> &t,node_t n) {
  int s;
  node_t c;
  if ((n==t.end()) || (*n % 2 == 1)) s=0;
  else {
    s=*n;
    c=n.lchild();
    while (c!=t.end()) {
      s += sumaparantec(t,c);
      c++;
    } // end while
  } // end if
  return s;
} // end int

// -------------------------------------------------------------------
int main () {
  tree <int> t;
  int s ;
  for (int j=0;j<5;j++) {
    t.clear ();
    make_random_tree(t,10,2);
    print_tree (t);
    s = sumaparantec (t,t.begin() ); 
    cout << "suma de antecesores pares = " << s << endl;
  } // end for
  cout << endl;
  return 0;
} // end main
// -------------------------------------------------------------------
