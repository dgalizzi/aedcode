// $Id$
/* COMIENZO DE DESCRIPCION

   Anagrama con \'arboles binario.
   keywords: arbol binario

   FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_btree.cpp
//        icc -w -c anagrama_bb.cpp
//        icc -w -o anagrama_bb.exe anagrama_bb.o util.o util_btree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_btree.cpp
//        g++ -w -c anagrama_bb.cpp
//        g++ -w -o anagrama_bb.exe anagrama_bb.o util.o util_btree.o
//
// -----------------------------------------------------------------
#include <iostream>
#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
void  busca_igual ( btree <int> :: iterator p,
               bool                  & esta,
               btree <int>           & t, 
               btree <int> :: iterator n) {
    if      ( n == t.end () ) {
      return ; }
    else if ( *p == *n ) { 
      *n = - *n ;    // lo "destruye" 
      esta = true ;
      return ; }
    else {
      busca_igual ( p, esta, t, n.left  () ) ;
      busca_igual ( p, esta, t, n.right () ) ;
    } // end if
} // end bool

// -----------------------------------------------------------------
bool anagram (btree <int> & a, btree <int> :: iterator p,
              btree <int> & b, btree <int> :: iterator q) { 
  btree <int> :: iterator r;
  bool b1, b2, esta ;
  if      ( p == a.end () xor q == b.end () ) { 
    return (false) ; }
  else if ( p == a.end () ) { 
    return (true)  ; }
  else if ( *p != *q ) {
    esta = false ;
    busca_igual ( p, esta, b, b.begin () );
    if (!esta) return (false) ; }
  else {
    b1 = anagram ( a, p.right (), b, q.right () ); 
    b2 = anagram ( a, p.left  (), b, q.left  () );
    return ( b1 && b2 ) ;
  } // end if
} // end bool

// -----------------------------------------------------------------
int main () {
  btree <int> a, b ;
  bool        v0, v1, v2 ;

  cout << endl; 
  cout << "anagrama  con arbol binarios " << endl ;

  a.clear ();
  b.clear ();
  v0 = anagram ( a, a.begin (), b, b.begin () ) ; 
  cout << endl ; cout << "anagram (a,a) = " << v0 << endl ;

  make_random_btree (a, 10, 1.4);
  make_random_btree (b,  8, 0.6);

  cout << endl ; cout << "a = " ; a.lisp_print () ; cout << endl ;
  cout << endl ; cout << "b = " ; b.lisp_print () ; cout << endl ;

  v1 = anagram ( a, a.begin (), a, a.begin () ) ; 
  v2 = anagram ( a, a.begin (), b, b.begin () ) ; 
  cout << endl ; cout << "anagram (a,a) = " << v1 << endl ;
  cout << endl ; cout << "anagram (a,b) = " << v2 << endl ;

  cout << endl;
  return 0 ;
} // end main
// -----------------------------------------------------------------
