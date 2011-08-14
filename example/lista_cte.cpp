// $Id$
/* COMIENZO DE DESCRIPCION 

   Dada una lista {\tt L} de enteros escribir una funci\'on 
   {\tt bool es_constante (list <int> \&L)}
   que retorna true solo si todos sus elementos son iguales.
   Hacerlo con (i) s\'olo operaciones del TAD lista y (ii) 
   mediante una correspondencia.
   Escriba un procedimiento {\tt void imprime (map <int,int> \&M);}
   para imprimir una correspondencia.
   keywords: lista, correspondencia

   FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c lista_cte.cpp
//        g++ -w -o lista_cte.exe util.o lista_cte.o
// INTEL: icc -w -c util.cpp
//        icc -w -c lista_cte.cpp
//        icc -w -o lista_cte.exe util.o lista_cte.o
// -----------------------------------------------------------------
#include <iostream>
#include <list>
#include <map>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
void imprime (list <int> & L) {
  list <int> :: iterator p, z;
  cout << "lista : " ; 
  p = L.begin ();
  z = L.end ();
  while (p != z) cout << *p++ << " " ;
  cout << endl ;
}

//--------------------------------------------------------------------
void imprime (map <int,int> & M) {
  map <int,int> :: iterator p;
  int x_dominio ;
  int y_rango;
  cout << endl ;
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
// version con iteradores sobre lista
bool es_constante1 (list <int> & L) {
  list <int> :: iterator p, q;
  p = L.begin ();
  q = p;
  while (q != L.end () && *p == *q) q++; 
  if (q == L.end ()) return true ; 
  else               return false ;
}

//--------------------------------------------------------------------
// version "larga" con iteradores sobre mapeo
bool es_constante2 (list <int> & L) {
  map <int,int> M ;
  map <int,int> :: iterator q;
  list <int> :: iterator p;
  int x ;
  p = L.begin ();
  while ( p != L.end () ) {
      x = *p;
      q = M.find (x);
      if ( q == M.end () ) M [x] = 1 ;
      p++;
  } // end while
  return M.size() == 1 ;
}

//--------------------------------------------------------------------
// version "breve" con iteradores sobre mapeo pero con mas operaciones
bool es_constante3 (list <int> & L) {
  map <int,int> M ;
  list <int> :: iterator p = L.begin ();
  while ( p != L.end () ) M [*p++] = 1 ; // puede hacer varias reasign
  return M.size() == 1 ;
}

//--------------------------------------------------------------------
int main() {
  list <int> L ;
  int  v1 [] = {7,7,7,7,-1};
  int  v2 [] = {8,2,5,7,-1};
  bool b1, b2, b3;

    // construye una lista prefijada
    cout << endl;
    cout << "Construye una lista prefijada:" << endl;
    L.clear ();
    insertl (L,v1,-1); 
    cout << "lista L: "; printl (L);
    b1 = es_constante1 (L);
    b2 = es_constante2 (L);
    b3 = es_constante3 (L);
    cout << endl;
    cout << "es_constante1 (L) = " << b1 << endl;
    cout << "es_constante2 (L) = " << b2 << endl;
    cout << "es_constante3 (L) = " << b3 << endl;

    // construye una lista prefijada
    cout << endl;
    cout << "Construye una lista prefijada:" << endl;
    L.clear ();
    insertl (L,v2,-1); 
    cout << "lista L: "; printl (L);
    b1 = es_constante1 (L);
    b2 = es_constante2 (L);
    b3 = es_constante3 (L);
    cout << endl;
    cout << "es_constante1 (L) = " << b1 << endl;
    cout << "es_constante2 (L) = " << b2 << endl;
    cout << "es_constante3 (L) = " << b3 << endl;

    // construye una lista aleatoria
    cout << endl;
    cout << "Construye una lista aleatoria:" << endl;
    L.clear ();
    randl (L, 13, 111.0);
    cout << "lista L: "; printl (L);
    cout << endl;
    cout << "es_constante1 (L) = " << b1 << endl;
    cout << "es_constante2 (L) = " << b2 << endl;
    cout << "es_constante3 (L) = " << b3 << endl;

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
// 
