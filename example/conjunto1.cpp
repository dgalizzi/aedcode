// $Id$

/*
  COMIENZO DE DESCRIPCION

Diversas operaciones con conjuntos:
purge            : purga elementos repetidos de una lista usando 
                   un conjunto como estructura auxiliar y con 
                   una implementacion tal que sea O (n).
set_intersection : interseccion de conjuntos;
prints           : imprime los elementos de un conjunto.
Keywords: conjunto, lista

  FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c conjunto1.cpp
//        g++ -w -o conjunto1.exe util.o conjunto1.o
// INTEL: icc -w -c util.cpp
//        icc -w -c conjunto1.cpp
//        icc -w -o conjunto1.exe util.o conjunto1.o
// -----------------------------------------------------------------
#include <iostream>
#include <list>
#include <set>
#include "./util.h"
using namespace std;

// -------------------------------------------------------------------
// Purgar los elementos repetidos de una lista usando un conjunto
// como estructura auxiliar y con una implementacion de O (n).
//
// Observaciones:
//
// 1) antes, en el tema "listas", vimos una implementacion que 
//    es O (n^2), la cual tambien esta en los apuntes;
//
// 2) aqui, en "conjuntos", usamos una implementacion de O (n)
//    siempre que las operaciones S.find () y S.insert () esten 
//    eficientemente implementadas como para ser de O (1)
template <class T>
void purge (list <T> & L) {
  typename list <T> :: iterator p;
  set <T> S;
  T  x ;
  p = L.begin ();
  while (p != L.end()) {
    x = *p;
    if ( S.find (x) != S.end () ) p = L.erase (p);
    else {
      S.insert(x);
      p++;
    } // end if
  } // end while
} // end void

// -------------------------------------------------------------------
template <class T>
void set_intersection (set <T> & A, set <T> & B,set <T> & C) {
  typename set <T> :: iterator p ;
  T x ;
  C.clear ();
  p = A.begin();
  while ( p != A.end () ) {
    x = *p++;
    if ( B.find (x) != B.end () ) C.insert (x);
  } // end while
} // end void

// -------------------------------------------------------------------
template <class T>
void prints (set <T> & S) {
  typename set <T> :: iterator p ;
  p = S.begin ();
  while (p != S.end ()) cout << *p++ << " ";
  cout << endl;
} // end void

// -----------------------------------------------------------------
int main () {
  list  <int> L;
  set   <int> A, B, C;

  for (int j = 0 ; j < 20 ; j++) L.insert ( L.end(), irand (20));

  cout << endl ;
  cout << "Antes de purge " << endl;
  printl (L);

  purge (L);

  cout << endl ;
  cout << "Despues de purge " << endl;
  printl (L);

  for (int j = 0 ; j < 20 ; j++) {
    A.insert (irand (40));
    B.insert (irand (40));
  } // end for

  set_intersection (A,B,C);

  cout << endl ; cout << "A: ";
  prints (A);

  cout << endl ; cout << "B: ";
  prints (B);

  cout << endl ; cout << "C = interseccion (A,B): ";
  prints (C);

  cout << endl ;
  return 0 ;
} // end main
// -----------------------------------------------------------------
