// $Id$

/* COMIENZO DE DESCRIPCION 

  __USE_WIKI__
  Escribir una funci\'on 
  #void cum_sum_pila (queue<int> &S)# que modifica a la 
  pila #S# dejando la suma acumulada de sus elementos, es 
  decir, si los elementos de #S# antes de llamar a 
  #cum_sum_pila(S)# son #S = (a_0,a_1,...,a_{n-1})#, 
  entonces despu\'es de llamar a #cum_sum_pila(S)# debe 
  quedar #S = (a_0, a_0 + a_1, ..., a_0 + a_1 + ... + a_n)#. 
  [Tomado en el Primer Parcial 27-ABR-2004]
   keywords: pila

   FIN DE DESCRIPCION */

/* 
  Escribir una funci\'on 
  {\tt void cum\_sum\_pila (stack<int> &S)} que modifica a la 
  pila {\tt S} dejando la suma acumulada de sus elementos, es 
  decir, si los elementos de {\tt S} antes de llamar a 
  {\tt cum\_sum\_pila (S)} son $ S = (a_0,a_1,\ldots,a_{n-1})$, 
  entonces despu\'es de llamar a {\tt cum\_sum\_pila (S)} debe 
  quedar $ S = (a_0,a_0+a_1,\ldots,a_0+a_1+\ldots+a_n)$. 
  Por ejemplo, si {\tt S = (1,3,2,4,2)} entonces despu\'es de hacer
  {\tt cum\_sum\_pila (S)} debe quedar {\tt S = (1,4,6,10,12)}. 
  Restricciones: (i) usar una pila auxiliar; (ii) usar la interfase 
  STL para pilas ({\tt clear (), top (), pop (), push (T x)+, 
  size (), empty ()}); (iii) NO usar m\'as estructuras auxiliares 
  que la indicada ni otros algoritmos de STL; y (iv) el algoritmo 
  debe ser $O(n)$. 
  [Tomado en el Primer Parcial 27-ABR-2004]
   keywords: pila
   FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -v -w -c cum_sum_pila.cpp
//        icc -v -w -o cum_sum_pila.exe cum_sum_pila.o
//
// GNU:   g++ -w -c cum_sum_pila.cpp
//        g++ -w -o cum_sum_pila.exe cum_sum_pila.o
//
// -----------------------------------------------------------------
#include <iostream>
#include <stack>
#include <list>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
void cum_sum_pila (stack<int> & S) {
  stack<int> C ;
  int x=0; 
  while ( !S.empty() ) {
    x += S.top (); S.pop ();
    C.push (x) ;
  } //
  while ( !C.empty() ) {
    x = C.top (); C.pop ();
    S.push (x) ;
  } //
}

//--------------------------------------------------------------------
void imprime_pila (stack<int> & S) {
  stack<int> C ;
  int x ; 
  cout << endl ;
  cout << "pila  S: " ;
  while ( !S.empty() ) {
    x = S.top (); 
    C.push (x) ;
    cout << x << " " ;
    S.pop (); // la unica forma de avanzar en la pila S
  } //
  cout << endl ;
  while ( !C.empty() ) {
    x = C.top (); 
    S.push (x) ;
    C.pop (); // la unica forma de avanzar en la pila S
  } //
}

//--------------------------------------------------------------------
int main() {
  int a [] = {1,3,5,4,2,3,7,3,5,-1};
  list<int> L ;
  list<int>::iterator p;
  stack<int> S;

  insertl (L, a, -1) ; 
  //cout << endl << endl << "lista L: "; printl (L);
  p = L.begin();
  while (p != L.end() ) S.push (*p++) ;

  imprime_pila (S);
  cum_sum_pila (S);
  imprime_pila (S);

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------

