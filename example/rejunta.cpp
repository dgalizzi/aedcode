// $Id$

/*
  COMIENZO DE DESCRIPCION

  Usando las operaciones del TAD lista, escribir una funci\'on
  {\tt void rejunta (list<int> \&L, int A)} que, dada una lista 
  de enteros {\tt L}, agrupe elementos de tal manera que en la
  lista queden solo elementos mayores o iguales que {\tt A}. El 
  algoritmo recorre la lista y, cuando encuentra un elemento menor,
  empieza a agrupar el elemento con los siguientes hasta
  llegar a {\tt A} o hasta que se acabe la lista. Por ejemplo,
  si L=[3,4,2,4,1,4,4,3,2,2,4,1,4,1,4,4,1,4,4,2], entonces
  rejunta (L,10) da L=[13,12,13,10,10]. En la lista final
  NO deben quedar elementos menores que {\tt A} salvo,
  eventualmente, el \'ultimo.
  [Ejercicio tomado en el Ex\'amen Final del 05/07/01]
  keywords: lista
  
  FIN DE DESCRIPCION
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c rejunta.cpp
//        g++ -w -o rejunta.exe util.o rejunta.o
// INTEL: icc -w -c util.cpp
//        icc -w -c rejunta.cpp
//        icc -w -o rejunta.exe util.o rejunta.o
// -----------------------------------------------------------------
#include <list>
#include <iostream>
#include "./util.h"
using namespace std;

// -----------------------------------------------------------------
void rejunta (list<int> &L, int a) {
  list<int>::iterator p ; 
  int suma ;
  p = L.begin ();
  while ( p != L.end () ) {
    if (*p > a) 
      p++ ;
    else {
      suma = 0 ;
      while ( p != L.end () && suma < a) {
	suma = suma + (*p) ;
	p = L.erase (p);
      } // end while
      p = L.insert (p, suma);
      p++;
    } // end if
  } // end while
}

// -----------------------------------------------------------------
int main () {
  list <int> L ;
  int n = 10 ;
  for (int i = 0 ; i < n ; i++) {
    L.clear ();
    randl (L, 4, 10.0);
    cout << endl ;
    cout << "antes de rejunta: ";
    printl (L);
    rejunta (L, 3);
    cout << "Despues de rejunta: ";
    printl (L);
  } // end for
  cout << endl ;
  return 0 ;
} // end main
// -----------------------------------------------------------------
