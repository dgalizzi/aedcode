// $Id$

/* 
  COMIENZO DE DESCRIPCION

  (a) Escriba una funci\'on
  void refina (list<double> &L, double delta) tal que dada una 
  lista inicial de reales clasificados de menor a mayor {\tt L}, 
  refina inserta elementos entre los de {\tt L}, de tal modo que 
  la diferencia m\'axima entre elementos de la lista final
  sea menor o igual que delta;
  (b) Escriba una funci\'on
  void desrefina (list<double> &L, double delta) tal que dada 
  una lista inicial de reales clasificados de menor a mayor
  {\tt L}, desrefina suprime elementos de {\tt L}, de tal modo 
  que la diferencia minima entre elementos de la lista final
  sea mayor o igual que delta.
  keywords: lista

  FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c refina.cpp
//        g++ -w -o refina.exe util.o refina.o
// INTEL: icc -w -c util.cpp
//        icc -w -c refina.cpp
//        icc -w -o refina.exe util.o refina.o
// -----------------------------------------------------------------
#include <list>
#include <iostream>
#include "./util.h"
using namespace std;

// -----------------------------------------------------------------
void refina (list<double> &L, double delta) {
  list<double>::iterator p;
  double x, y ;
  p = L.begin ();
  while (p != L.end () ) {
    x = (*p) + delta; p++ ;
    if (p == L.end () ) break;
    y = (*p) ;
    while (x < y) {
      p = L.insert (p,x); p++;
      x = x + delta ;
    } // end while
  } // end while
}

// -----------------------------------------------------------------
void desrefina (list<double> &L, double delta) {
  list <double> :: iterator p, q ;
  p = L.begin () ;
  while (p != L.end ()) {
    q = p ; q++ ;
    while (q != L.end () && (*q) < (*p) + delta ) {
      q = L.erase (q) ;
    } // end while
    p++;
  } // end while
}

// -----------------------------------------------------------------
int main () {
  list<double> L;
  double delta1 = 5.0, delta2 = 5.0 * delta1;
  int ni = 2, nj = 3 ;
  double x ;
  for (int i = 0 ; i < ni ; i++) {
    cout << endl;
    cout << "pasada i = " << i << endl ;
    L.clear ();
    x = 0.0 ;
    for (int j = 0 ; j < nj ; j++) {
      x = x + drand () * delta2 ;
      L.insert (L.end (), x);
    } // end for
    cout << endl;
    cout << "Antes de refinar     : ";
    printl (L);

    refina (L, delta1);
    cout << endl;
    cout << "Despues de refinar   : ";
    printl (L);

    cout << endl;
    cout << "Antes de desrefinar  : ";
    printl (L);
    desrefina (L, delta2);

    cout << endl;
    cout << "Despues de desrefinar: ";
    printl (L);

    cout << endl;
  } // end for
  return 0 ;
} // end main
// -----------------------------------------------------------------
