//$Id$
/* COMIENZO DE DESCRIPCION

  Listado de \'arboles orientados en diferentes ordenes.
  keywords: arbol orientado

  FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_tree.cpp
//        icc -w -c listarbo.cpp
//        icc -w -o listarbo.exe listarbo.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_tree.cpp
//        g++ -w -c listarbo.cpp
//        g++ -w -o listarbo.exe listarbo.o util.o util_tree.o
//
// -------------------------------------------------------------------
#include <iostream>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
void  orden_prev ( tree <int> & t, node_t n) {
  node_t c ;  
  int    p ;
  if ( n == t.end () ) return ;
  cout << (* n) << ' ' ; 
  c = n.lchild () ;
  // notar el pos-incremento despues de la llamada recursiva
  while ( c != t.end () ) { orden_prev (t, c++) ; }
} // end void

// -------------------------------------------------------------------
void  orden_post ( tree <int> & t, node_t n) {
  node_t c ;  
  int    p ;
  if ( n == t.end () ) return ;
  c = n.lchild () ;
  // notar el pos-incremento despues de la llamada recursiva
  while ( c != t.end () ) { orden_post (t, c++) ; }
  cout << (* n) << ' ' ; 
} // end void

// -------------------------------------------------------------------
void  orden_sime ( tree <int> & t, node_t n) {
  node_t c ;  
  int    p ;
  if ( n == t.end () ) return ;
  c = n.lchild () ;
  orden_sime (t, c) ;
  cout << (* n) << ' ' ; 
  // notar el pre-incremento antes de la llamada recursiva
  while ( c != t.end () ) { orden_sime (t, ++c) ; }
} // end void

// -------------------------------------------------------------------
int main () {
  tree <int> t;

  cout << endl ;
  cout << "listados en un arbol ordenado y orientado "  << endl ; 

  for (int j = 0 ; j < 1 ; j++) {
    t.clear ();
    make_random_tree (t, 10, 2);
    cout << endl ;
    cout << "arbol ordenado:"  << endl ; 
    print_tree (t);
    cout << "orden_prev:"  << endl ; 
    orden_prev ( t, t.begin () ) ; 
    cout << endl ; 
    cout << "orden_post:"  << endl ; 
    orden_post ( t, t.begin () ) ; 
    cout << endl ; 
    cout << "orden_sime:"  << endl ; 
    orden_sime ( t, t.begin () ) ;
    cout << endl ;
  } // end for
  cout << endl ;
  return 0 ;
} // end main
// -------------------------------------------------------------------
