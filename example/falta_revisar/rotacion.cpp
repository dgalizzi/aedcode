// $Id$

/* 
   COMIENZO DE DESCRIPCION 
   Escribir una funci\'on {\tt void rotacion (queue <int> &C)}, 
   la cual saca una cierta cantidad de enteros del frente de la 
   cola {\tt C} y los vuelve a insertar en fin de la misma, de 
   tal manera que quede en el frente de cola un n\'umero par. 
   Por ejemplo, si C = [1, 3, 5, 2, 4] entonces, despu\'es de 
   {\tt rotacion (C) }, debe quedar C = [2, 4, 1, 3, 5].
   Ejercicio tomado en el 1er parcial, 16/04/02.
   keywords: cola
   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// GNU:   g++ -c rotacion.cpp
//        g++ -o rotacion.exe rotacion.o
// INTEL: icc -v -c rotacion.cpp
//        icc -v -o rotacion.exe rotacion.o
// -----------------------------------------------------------------
#include "./util.h"
using namespace std;

// -----------------------------------------------------------------
void rotacion (queue <int> & C) {
  int x ;
  while ( !C.empty() ) {
    x = C.front () ;
    if  ( !(x % 2) ) return ;
    C.pop ();
    C.push (x);
  } // end while
}

// -----------------------------------------------------------------
int main () {
  queue<int> C ;
  int puso_par, j, x ;
  double z = 0.1 ;
  int n = 3 ;
  for (int i = 0 ; i < n ; i++) {
    puso_par = 0 ; 
    j = 0 ;
    while (true) { 
      x = 2 * irand (20) ;
      if ( drand () > z ) x = x + 1 ;
      C.push (x);
      if ( j++ > 20 && puso_par ) break;
      if ( !(x % 2) ) puso_par = 1;
    } // end while
    cout << endl ;
    cout << "antes de rotar ";
    printq (C);
    rotacion (C);
    cout << endl ;
    cout << "despues de rotar ";
    printq (C) ;
  } // end i
  cout << endl ;
  return 0 ;
}
// -----------------------------------------------------------------

