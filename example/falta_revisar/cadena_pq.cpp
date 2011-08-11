// $Id$

/*
  COMIENZO DE DESCRIPCION

  Determinar si una cadena {\tt z} es de la forma {\tt z = x y}, 
  donde {\tt y} es la cadena inversa (o espejo) de la cadena 
  {\tt x}, ignorando los espacios en blanco. 
  Emplear una cola y una pila auxiliares.
  keywords: lista, pila, cola

  FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c cadena_pq.cpp
//        g++ -w -o cadena_pq.exe util.o cadena_pq.o
// INTEL: icc -w -c util.cpp
//        icc -w -c cadena_pq.cpp
//        icc -w -o cadena_pq.exe util.o cadena_pq.o
// -----------------------------------------------------------------
#include <iostream>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// -------------------------------------------------------------------
char fin_cadena ='#';
char blanco = ' ';

// -------------------------------------------------------------------
bool cadena_pq (list <char> & L1, list <char> & L2) {
  queue <char> Q;
  stack <char> S;
  list<char>::iterator p;
  list<char>::iterator q;
  char x, y ;
  bool b ;

  // verifica que las longitudes de las listas "L1" e "L2" sean iguales
  b = ( L1.size() == L2.size () ) ;
  if (!b) { 
    cout << endl ;
    cout << "error: listas de longitudes distintas" << endl; 
    return false ; 
  }
  cout << endl ;

  // pone cada caracter de la cadena "x" en la pila S
  p = L1.begin();
  while ( p != L1.end () ) {
    x = *p ;
    S.push (x) ;
    p++;
  } // end while

  // pone cada caracter de la cadena "y" en la cola Q
  q = L2.begin();
  while ( q != L2.end () ) {
    y = *q;
    Q.push (y) ;
    q++;
  } // end while

  // itera comparando el tope de la pila y el frente de la cola
  while (!S.empty () && !Q.empty () ) {
    x = S.top ()   ; S.pop (); // no olvidar "desapilar" !! 
    y = Q.front () ; Q.pop (); // no olvidar "descolar"  !!
    cout << "tope (pila) = " << x << " ; frente (cola) = " << y << endl;
    if (x != y) { return false ; } 
  } //
  return true ;
}

// -------------------------------------------------------------------
int main (){
  list <char> L1, L2 ;
  char x, y ;
  bool b ;

  // lee cada caracter de la cadena "x" y lo pone en la lista "L1"
  cout << endl ;
  cout << "lee cada caracter de la cadena x (# para salir)" << endl ;
  x = blanco ;
  while (x != fin_cadena) {
    cout << "cadena x : ? " ; cin >> x ;
    b = (x != fin_cadena && x != blanco) ;
    if (b) L1.insert (L1.end(), x);
  } ;

  // lee cada caracter de la cadena "x" y lo pone en la lista "L2"
  cout << endl ;
  cout << "lee cada caracter de la cadena y (# para salir)" << endl ;
  y = blanco ;
  while (y != fin_cadena) {
    cout << "cadena y : ? " ; cin >> y ;
    b = (y != fin_cadena && y != blanco) ;
    if (b) L2.insert (L2.end(), y);
  } ;

  // test
  b = cadena_pq (L1,L2) ;
  cout << endl ;
  if (b) cout << "la cadena 'y' es espejo de la cadena 'x' ";
  else   cout << "la cadena 'y' NO es espejo de la cadena 'x' ";
  cout << endl ;

  cout << endl ;
  return 0 ;
} // end main
// -------------------------------------------------------------------


