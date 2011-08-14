// $Id$

/* COMIENZO DE DESCRIPCION 

   Escribir una funci\'on {\tt bool es_biyectiva (map <int,int> \&A)}
   que retorna true si la misma representa una funci\'on biyectiva,
   esto es, si la correspondencia {\tt A} describe una relaci\'on
   {\it uno a uno}. Por ejemplo, supongamos el conjunto 
   {\tt X = (0,1,2,3,4,5)} y consideremos las correspondencias
   {\tt A1 = { (0,2), (1,5), (2,0), (3,3), (4,4), (5,1) }} y
   {\tt A2 = { (0,2), (1,1), (2,0), (3,3), (4,3), (5,1) }}. 
   En el primer caso, cada elemento (de 0 a 5) tiene preimagen, 
   por lo que {\tt es_biyectiva (A1)} debe retornar {\tt true}.
   En cambio, en el segundo caso, los elementos 4 y 5 no tienen 
   preimagen, por lo que {\tt es_biyectiva (A2)} debe retornar 
   {\tt false}.
   keywords: correspondencia

   FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c es_biyectiva.cpp
//        icc -w -o es_biyectiva.exe es_biyectiva.o
//
// GNU:   g++ -w -c es_biyectiva.cpp
//        g++ -w -o es_biyectiva.exe es_biyectiva.o
//
// -----------------------------------------------------------------
#include <iostream>
#include <map>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
void imprime (map <int,int> & M) {
  map <int,int> :: iterator p;
  int x_dominio ;
  int y_rango;
  cout << "mapeo actual (x_dominio, y_rango):" << endl ;
  p = M.begin ();
  while (p != M.end () ) {
    x_dominio = p->first;
    y_rango   = p->second;
    cout << "x_dominio = "     <<    x_dominio  << "  " ;
    cout << "M [x_dominio] = " << M [x_dominio] << endl ;
    p++;
  } // end while
}

//--------------------------------------------------------------------
bool es_biyectiva (map <int,int> & A) {
  map <int,int> B ;
  map <int,int> :: iterator p, q;
  int x_dominio ;
  int y_rango;
  p = A.begin ();
  while ( p != A.end () ) {
    x_dominio = p->first;
    y_rango   = p->second;
    q = B.find (y_rango);
    if ( q == B.end () ) B [y_rango] = x_dominio ;
    p++;
  } // end while
  return B.size() == A.size() ;
}

//--------------------------------------------------------------------
int main() {
  map <int,int> A1, A2 ;
  bool b1, b2;

  // mapeo 1
  cout << endl;
  cout << "mapeo 1:" << endl;
  A1.clear ();
  A1 [0] = 2;
  A1 [1] = 5;
  A1 [2] = 0;
  A1 [3] = 3;
  A1 [4] = 4;
  A1 [5] = 1;
  imprime (A1);
  b1 = es_biyectiva (A1);
  cout << endl;
  cout << "es_inyectiva (A1) = " << b1 << endl;

  // mapeo 2
  cout << endl;
  cout << "mapeo 2:" << endl;
  A2.clear ();
  A2 [0] = 3;
  A2 [1] = 1;
  A2 [2] = 0;
  A2 [3] = 2;
  A2 [4] = 3;
  A2 [5] = 1;
  imprime (A2);
  b2 = es_biyectiva (A2);
  cout << endl;
  cout << "es_inyectiva (A2) = " << b2 << endl;

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
// 
