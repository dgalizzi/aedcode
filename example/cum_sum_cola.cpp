// $Id$

/* COMIENZO DE DESCRIPCION 

  __USE_WIKI__
  Escribir una funci\'on 
  #void cum_sum_cola (queue<int> &Q)# que modifica a la 
  cola #Q# dejando la suma acumulada de sus elementos, es 
  decir, si los elementos de #Q# antes de llamar a 
  #cum_sum_cola(Q)# son #Q = (a_0,a_1,...,a_{n-1})#, 
  entonces despu\'es de llamar a #cum_sum_cola(Q)# debe 
  quedar #Q = (a_0, a_0 + a_1, ..., a_0 + a_1 + ... + a_n)#. 
  [Tomado en el Primer Parcial 27-ABR-2004]
   keywords: cola

   FIN DE DESCRIPCION */

/*
  Por ejemplo, si {\tt Q = (1,3,2,4,2)} entonces despu\'es de hacer
  {\tt cum\_sum\_cola (Q)} debe quedar {\tt Q = (1,4,6,10,12)}. 
  Restricciones: (i) usar una cola auxiliar; (ii) usar la interfase 
  STL para colas ({\tt clear (), front (), pop (), push (T x)+, 
  size (), empty ()}); (iii) NO usar m\'as estructuras auxiliares 
  que la indicada ni otros algoritmos de STL; y (iv) el algoritmo 
  debe ser $O(n)$. 
*/
// -----------------------------------------------------------------
// INTEL: icc -v -w -c cum_sum_cola.cpp
//        icc -v -w -o cum_sum_cola.exe cum_sum_cola.o
//
// GNU:   g++ -w -c cum_sum_cola.cpp
//        g++ -w -o cum_sum_cola.exe cum_sum_cola.o
//
// -----------------------------------------------------------------
#include <iostream>
#include <queue>
#include <list>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
void cum_sum_cola (queue<int> & Q) {
  queue<int> C ;
  int x=0; 
  while ( !Q.empty() ) {
    x += Q.front (); Q.pop ();
    C.push (x) ;
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
  // cout << endl << endl << "lista L: "; printl (L);
  p = L.begin();
  while (p != L.end() ) Q.push (*p++) ;

  imprime_cola (Q);
  cum_sum_cola (Q);
  imprime_cola (Q);

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------

