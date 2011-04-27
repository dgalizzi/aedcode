// $Id$
/* 
   COMIENZO DE DESCRIPCION 
   Escribir una funci\'on 
   {\tt void saca_de_cola (queue <int> & C, int n)}, 
   la cual elimina todas las ocurrencias del valor {\tt n} en la 
   cola {\tt C}
   Por ejemplo, si {\tt C = [1,3,5,4,2,3,7,3,5]}, despu\'es de 
   {\tt saca_de_cola (C, 3) } debe quedar {\tt C = [1,5,4,2,7,5]}.
   {\it Sugerencia: Usar una estructura auxiliar lista o cola}.
   {\it Restricciones:} el algoritmo debe tener un tiempo de 
   ejecuci\'on $O(n)$, donde $n$ es el n\'umero de los elementos
   en la cola original.
   Ejercicio tomado en el Ex\'amen Final 08/07/04.
   keywords: cola
   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// INTEL: icc -v -w -c saca_de_cola.cpp
//        icc -v -w -o saca_de_cola.exe saca_de_cola.o
//
// GNU:   g++ -w -c saca_de_cola.cpp
//        g++ -w -o saca_de_cola.exe saca_de_cola.o
//
// -----------------------------------------------------------------
#include "./util.h"

using namespace std;

// -----------------------------------------------------------------
void saca_de_cola (queue <int> & C, int n) {
  queue <int> Q ;
  int   x ;
  // pasa selectivamente a la cola auxiliar "Q"
  while ( !C.empty() ) {        // mientras "C" no este vacia
    x = C.front () ;            // extrae el frente de la cola "C"
    if  (x != n)  Q.push (x) ;  // si no es "n" lo encola en "Q"
    C.pop ();                   // avanza en la cola "C"
  } // end while
  // vuelve a la cola original
  while ( !Q.empty() ) {        // mientras "Q" no este vacia
    x = Q.front () ;            // extrae el frente de la cola "Q"
    C.push (x) ;                // lo encola en "C"
    Q.pop ();                   // avanza en la cola "Q"
  } // end while
} // end void

// -----------------------------------------------------------------
int main () {
  queue <int> C ;
  int    x ;
  int    n = 22 ;
  int    z =  1 ;
  for (int i = 0 ; i < n ; i++) {
    x = 2 * irand (20) ;
    C.push (x);
    if ( i == n/2 ) z = x ;
  } // end for
  cout << endl ;
  cout << "cola original   C1 : ";
  printq   (C);
  saca_de_cola (C,z);
  cout << endl ;
  cout << "a eliminar    ;  z = " << z << endl ;
  cout << "cola modificada C2 : ";
  printq (C) ;

  cout << endl ;
  return 0 ;
} // end main
// -----------------------------------------------------------------

