// $Id$

/* COMIENZO DE DESCRIPCION 

  __USE_WIKI__

  Escribir una funci\'on 
  #int ascendente1 (list <int> &L, list<list<int> > &LL)#
  que, dada una lista #L#, genera una lista de listas #LL# 
  de tal forma de que cada sublista es ascendente.
  [Tomado en el Parcial 1 20-ABR-2006].

  Escribir una funci\'on 
  #int ascendente2 (list <int> &L, vector < list<int> > &VL)#
  que, dada una lista #L#, genera un vector de listas #VL# 
  de tal forma de que cada sublista es ascendente.
  [Tomado en Examen Final 29-JUL-2004].
  keywords: lista
  FIN DE DESCRIPCION */

/*
 En ciertas aplicaciones interesa separar las corridas ascendentes 
 en una lista de n\'umeros $L=~(~a_1,~a_2,~...,~a_n~)$, donde 
 cada corrida ascendente es una sublista de n\'umeros consecutivos 
 $a_i$, $a_{i+1}$, ..., $a_{i+k}$, la cual termina cuando 
 $a_{i+k}>a_{i+k+1}$, y es ascendente en el sentido de que 
 $a_i \le a_{i+1} \le ... \le a_{i+k}$. Por ejemplo, si la 
 lista es L = (0,5,6,9,4,3,9,6,5,5,2,3,7), entonces hay 6 
 corridas ascendentes, a saber: (0,5,6,9), (4), (3,9), (6), 
 (5,5) y (2,3,7). 
 \emph{Consigna:}
 usando las operaciones de la clase lista, escribir una funci\'on
 {\tt int ascendente (list <int> &L, list < list<int> > &LL)}
 en la cual, dada una lista de enteros {\tt L}, almacena 
 cada corrida ascendente como una sublista en la lista de 
 listas {\tt LL}, devolviendo adem\'as el n\'umero $z$ de 
 corridas ascendentes halladas. \emph{Restricciones:} 
 a) El tiempo de ejecuci\'on del algoritmo debe ser $O(n)$, 
 b) La lista de listas {\tt LL} inicialmente est\'a vac\'{\i}a, 
 c) No usar otras estructuras auxiliares.
*/

// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c ascendente.cpp
//        g++ -w -o ascendente.exe util.o ascendente.o
// INTEL: icc -w -c util.cpp
//        icc -w -c ascendente.cpp
//        icc -w -o ascendente.exe  util.o ascendente.o
// -----------------------------------------------------------------
#include <cmath>
#include <list>
#include <iostream>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
double drand_a() {
  return double (rand())/double(RAND_MAX);
}
int irand_a(int m) {
  return int(double(m)*drand());
}

//--------------------------------------------------------------------
void  printa  (list<int> & L){
  list<int> :: iterator p, z;
  cout << endl ;
  cout << "lista ; L = " ;
  p = L.begin();
  while (p != L.end()) {
    cout << *p << " " ; p++;
  }
  cout << endl << "pausa ... " ; cin.get ();     
}

//--------------------------------------------------------------------
void  printa (list<list<int> > & LL){
  list<list<int> > :: iterator q;
  list<int> :: iterator p, z;
  int  n, h ;
  n = LL.size () ;
  q = LL.begin();
  h = 0 ;
  while (q != LL.end()) {
    p = q -> begin();         // comienzo de la sublista
    z = q -> end();           // fin      de la sublista
    cout << endl ;
    cout << "sublista " << h << " ; LL_h = " ;
    while (p != z) {cout << *p << " " ; p++;}
    cout << endl ;
    h++;
    q++;
  } // end while 
  cout << endl ;
  cout << "siza (LL) ; n = " << n << endl ;
  cout << endl << "pausa ... " ; cin.get ();     
}

//--------------------------------------------------------------------
void  printa (vector<list<int> > & VL){
  list<int> :: iterator p, z;
  int  n ;
  n = VL.size () ;
  for (int k = 0 ; k < n ; k++) {
    cout << "sublista c : " ; 
    p = VL [k].begin ();
    z = VL [k].end ();
    while (p != z) cout << *p++ << " " ;
    cout << endl ;
  } // end k
  cout << endl ;
  cout << "siza (LL) ; n = " << n << endl ;
  cout << endl << "pausa ... " ; cin.get ();     
}

//--------------------------------------------------------------------
void  genera_a (list<int> &L, int n, int maxval){
  list<int> :: iterator p;
  int  k;
  cout << endl ;
  cout << "llena aleatoriamente una lista L de enteros" << endl;
  p = L.begin ();
  for (int j=0 ; j<n ; j++) { 
    k = irand (maxval);          // valor aleatorio en [0,maxval)
    p = L.insert (p,k);          // inserta en la lista
  }
}

//--------------------------------------------------------------------
// Item 1: lista de listas 
//
// . los iteradores "p,q" recorren los numeros de la lista "L"
// . el iterador "r" va pasando de sublista en sublista, donde 
//   cada sublista es una corrida ascendente de la lista "L";
// . la lista vacia A es solo para inicializar cada nueva sublista.
int  ascendente1_a (list <int> &L, list < list<int> > &LL) {
  list < list<int> > :: iterator r;
  list <int> :: iterator p, q;
  list <int> A;
  p = L.begin ();
  while (p != L.end ()) {
    // inserta una nueva sublista vacia "A" en la lista de listas "L"
    r = LL.insert (LL.end(),A);
    // inserta el valor "*p" de la lista "L" en la nueva sublista
    r->insert (r->end(), *p) ;
    // mientras no sea fin de la lista "L" y se verifica la condicion 
    // de corrida ascendente, va copiando a la sublista actual
    q = p ; q++;
    while (q != L.end () && *p <= *q) {
      r->insert (r->end(), *q) ;
      p++;
      q++;
    } // end while
    p = q ;   // se posiciona al principio de la sgte corrida
  } // end while
  printa (LL) ;
  return LL.size() ;
}

//--------------------------------------------------------------------
// Item 1: lista de listas 
// Otra solucion
int  ascendente1_b (list<int> &L, list<list<int> > &LL) {
  list<int>::iterator p, q;
  list<list<int> >::iterator ql ;
  int x ;
  LL.clear();
  p = L.begin ();
  while (p != L.end ()) {
    ql = LL.insert(LL.end(),list<int>());
    while (1) {
      x = *p++;
      ql->insert(ql->end(),x);
      if (p==L.end() || *p<x) break;
    } // end while
  } // end while
  return LL.size();
}

//--------------------------------------------------------------------
// Item 2: vector de listas 
//
// el iterador "p" recorre la lista "L"
// el iterador "q" recorre cada corrida ascendente en "L"
// el contador "h" va contando las corridas ascendentes halladas
int ascendente2 (list <int> &L, vector < list<int> > &VL) {
  list <int> :: iterator p, q;
  int  h = 0 ;
  p = L.begin ();
  while (p != L.end ()) {
    // copia el elemento "p" de "L" como el primero de la sublista "h"
    VL [h].insert (VL [h].end (), *p) ;
    // mientras no sea fin de lista y se verifica la condicion de 
    // corrida ascendente, va copiando elementos a la sublista "h" 
    q = p ; q++;
    while (q != L.end () && *p <= *q) {
      VL [h].insert (VL [h].end (), *q) ;
      p++;
      q++;
    } // end while
    h++ ;     // para pasar a la eventual siguiente corrida ascendente
    p = q ;   // se posiciona al principio de la sgte corrida
  } // end while
  return (h) ;
}

//--------------------------------------------------------------------
void check(list<int> &L) {
  list<list<int> > LL;
  int nca = ascendente1_b (L,LL);
  list<list<int> >::iterator ql = LL.begin();
  while (ql!=LL.end()) {
    cout << "sublista ascendente: ";
    list<int>::iterator p = ql->begin();
    while (p!=ql->end()) {
      cout << " " << *p;
      p++;
    }
    ql++;
    cout << endl;
  }
}

//--------------------------------------------------------------------
int main() {
  list <int> L ;
  list <list<int> > LL ;
  int a [] = {3,7,0,0,3,4,6,4,2,7,-1};
  int opcion = 2 ;
  int h, n ;

  // Titulos
  cout << endl;
  cout << "encuentra todas las Corridas Ascendentes (CA) " << endl ;
  cout << "en una lista de numeros L " << endl;

  int kaso = 1 ;
  switch (kaso) {
  case 1:
    // Item 1: lista de listas "LL" 
    L.clear ();
    genera_a (L, 50, 99) ;      // Genera una lista "L" de numeros
    printa (L);
    h = ascendente1_a (L,LL) ;  // una solucion
    check (L);                  // otra solucion
    break;
  case 2:
    // Item 2: vector de listas "VL"
    if (opcion == 1) {
      L.clear ();
      insertl (L, a, -1) ;        // Construye una lista predefinida
      printa (L);
      n = L.size () ;             // alocamos para el peor caso: si las
      vector <list<int> > VL (n); // sublistas resultaran de longitud 1
      h = ascendente2 (L,VL) ;
      printa (VL) ;
      VL.clear ();
    } else {
      int const kmax = 20 ;
      for (int k = 0; k < kmax ; k++) {
        L.clear ();
        randl (L,10,5.0);
        printa (L);
        n = L.size () ;
        vector <list<int> > VL (n) ;
        h = ascendente2 (L,VL) ;
        printa (VL) ;
        VL.clear () ;
      } // end k
    } // end if
    break;
  default:
    cout << endl;
    cout << "no previsto " << endl ;
  } ;

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
