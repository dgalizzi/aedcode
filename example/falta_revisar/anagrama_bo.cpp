// $Id$
/* COMIENZO DE DESCRIPCION

   Anagrama con Arbol Ordenado Orientado (AOO).
   keywords: arbol orientado

  FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_tree.cpp
//        icc -w -c anagrama_bo.cpp
//        icc -w -o anagrama_bo.exe anagrama_bo.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_tree.cpp
//        g++ -w -c anagrama_bo.cpp
//        g++ -w -o anagrama_bo.exe anagrama_bo.o util.o util_tree.o
//
// -------------------------------------------------------------------
#include <iostream>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
void  busca_igual ( node_t       p,
                    bool       & esta,
                    tree <int> & t, 
                    node_t       n) {
     node_t  c ;
    if      ( n == t.end () ) {
      return ; }
    else if ( *p == *n ) { 
      *n = - *n ;
      esta = true ;
      return ; }
    else {
      c = n.lchild () ;
      while ( c != t.end () ) busca_igual ( p, esta, t, c ++ ) ;
    } // end if
} // end bool

// -----------------------------------------------------------------
bool anagram (tree <int> & a, node_t p,
              tree <int> & b, node_t q) { 
  node_t  r, c, c1, c2 ;
  bool    z, esta ;
  if      ( p == a.end () xor q == b.end () ) { 
    return (false) ; }
  else if ( p == a.end () ) { 
    return (true)  ; }
  else if ( *p != *q ) {
    esta = false ;
    busca_igual ( p, esta, b, b.begin () );
    if (!esta) return (false) ; }
  else {
    c1 = p.lchild () ;
    c2 = q.lchild () ;
    z  = true ;
    while ( c != a.end () ) { z = z && anagram (a, c1++, b, c2++) ; }
    return ( z ) ;
  } // end if
} // end bool

// -------------------------------------------------------------------
int main () {
  tree <int> a, b ;
  bool       v0, v1, v2 ;

  cout << endl; 
  cout << "anagrama con arbol orientado " << endl ;

  a.clear ();
  b.clear ();
  v0 = anagram ( a, a.begin (), b, b.begin () ) ; 
  cout << endl ; cout << "anagram (a,a) = " << v0 << endl ;

  make_random_tree (a, 10, 3.5);
  make_random_tree (b,  8, 0.6);

  cout << endl ; cout << "a = " ; print_tree (a) ; cout << endl ;
  cout << endl ; cout << "b = " ; print_tree (b) ; cout << endl ;

  v1 = anagram ( a, a.begin (), a, a.begin () ) ; 
  v2 = anagram ( a, a.begin (), b, b.begin () ) ; 
  cout << endl ; cout << "anagram (a,a) = " << v1 << endl ;
  cout << endl ; cout << "anagram (a,b) = " << v2 << endl ;

  cout << endl ;
  return 0 ;
} // end main
// -------------------------------------------------------------------
