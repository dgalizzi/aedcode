// $Id$

/* COMIENZO DE DESCRIPCION 
   
  __USE_WIKI__ 
  Escribir una funci\'on 
  #void elimina_valor(queue<int> &Q, int n);}# que elimina todos 
  las ocurrencias del valor #n# en la cola #Q#. Por ejemplo, 
  si #Q = { 1,3,5,4,2,3,7,3,5 }# y #n=3#, despu\'es de 
  #elimina_valor(Q,3)# debe quedar 
  #Q = {1,5,4,2,7,5}#. 
  Sugerencia: usar una estructura auxiliar lista o cola.
  Restricciones: el algoritmo debe tener un tiempo de ejecuci\'on 
  $O(n)$, donde $n$ es el n\'umero de elementos en la cola original.
  [Tomado en Ex\'amen Final 08-JUL-2004]
   keywords: cola
   FIN DE DESCRIPCION 
*/

// -----------------------------------------------------------------
// INTEL: icc -v -w -c elimina_valor.cpp
//        icc -v -w -o elimina_valor.exe elimina_valor.o
//
// GNU:   g++ -w -c elimina_valor.cpp
//        g++ -w -o elimina_valor.exe elimina_valor.o
//
// -----------------------------------------------------------------
#include <iostream>
#include <queue>
#include <list>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
void elimina_valor (queue<int> & Q, int n) {
  queue<int> C ;
  int x ; 
  while ( !Q.empty() ) {
    x = Q.front (); Q.pop ();
    if (x != n)  C.push (x) ;
  } //
  while ( !C.empty() ) {
    x = C.front (); C.pop ();
    Q.push (x) ;
  } //
}

//--------------------------------------------------------------------
void imprime_cola (queue<int> & Q) {
  queue<int> C ;
  int x ; 
  cout << endl ;
  cout << "cola  Q: " ;
  while ( !Q.empty() ) {
    x = Q.front (); 
    C.push (x) ;
    cout << x << " " ;
    Q.pop (); // la unica forma de avanzar en la cola Q
  } //
  cout << endl ;
  while ( !C.empty() ) {
    x = C.front (); 
    Q.push (x) ;
    C.pop (); // la unica forma de avanzar en la cola Q
  } //
}

//--------------------------------------------------------------------
int main() {
  int a [] = {1,3,5,4,2,3,7,3,5,-1};
  list<int> L ;
  list<int>::iterator p;
  queue<int> Q;
  int n ;

  insertl (L, a, -1) ; 
  //cout << endl << endl << "lista L: "; printl (L);
  p = L.begin();
  while (p != L.end() ) Q.push (*p++) ;

  imprime_cola (Q);
  n = 3 ;
  elimina_valor (Q,n);
  imprime_cola (Q);

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------

