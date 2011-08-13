//__INSERT_LICENSE__
// $Id$

/* COMIENZO DE DESCRIPCION 

  Escribir una funci\'on 
  {\tt void chunk_revert(list<int> \&L,int n);} que
  dada una lista {\tt L} y un entero {\tt n}, 
  invierte los elementos de la lista tomados de a {\tt n}. 
  Si la longitud de la lista no es m\'ultiplo de {\tt n} 
  entonces se invierte el resto tambi\'en. 
  Por ejemplo, si {\tt L={1,3,2,5,4,6,2,7}}
  entonces despu\'es de hacer {\tt chunk_revert(L,3)} debe 
  quedar {\tt L={2,3,1,6,4,5,7,2}}.
  Restricciones: Usar a lo sumo una estructura auxiliar.
  (En tal caso debe ser lista, pila o cola). 
   [Tomado en el 1er parcial 21/4/2005]. 
   keywords: lista

   FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c chunk-revert.cpp
//        g++ -w -o chunk-revert.exe util.o chunk-revert.o
// INTEL: icc -w -c util.cpp
//        icc -w -c chunk-revert.cpp
//        icc -w -o chunk-revert.exe util.o chunk-revert.o
// -----------------------------------------------------------------
#include <list>
#include <queue>
#include <stack>
#include "./util.h"
using namespace std;

// -------------------------------------------------------------------
// Version con pila
void chunk_revert (list<int> &L, int n) {
  stack<int> S;
  list<int>::iterator q;
  q = L.begin();
  while (q!=L.end()) {
    for (int j=0; j<n; j++) {
      if (q == L.end()) break;
      S.push(*q);
      q = L.erase(q);
    } // end for
    while (!S.empty()) {
      q = L.insert(q,S.top());
      q++;
      S.pop();
    } // end while
  } // end while
}

// -------------------------------------------------------------------
// Version con cola
void chunk_revert4 (list<int> &L, int n) {
  queue<int> Q;
  list<int>::iterator q;
  int m ;
  q = L.begin();
  while (q!=L.end()) {
    for (int j=0; j<n; j++) {
      if (q == L.end()) break;
      Q.push(*q);
      q = L.erase(q);
    } // end for
    m = Q.size();
    while (!Q.empty()) {
      q = L.insert(q,Q.front());
      Q.pop();
    } // end while
    for (int j=0; j<m; j++) q++;
  } // end while
}

// -------------------------------------------------------------------
// Version `in place'
void chunk_revert2 (list<int> &L, int n) {
  list<int>::iterator q, p;
  q = L.begin();
  int m, x;
  while (q!=L.end()) {
    p = q;
    for (m=0; m<n; m++)
      if (p++ == L.end()) break;
    for (int j=0; j<m; j++) {
      x = *q;
      q = L.erase(q);
      p = q;
      for (int k=0; k<m-j-1; k++) p++;
      p = L.insert(p,x);
    } // end for
    q = p;
    for (int j=0; j<m; j++) q++;
  } // end while
}

// -------------------------------------------------------------------
// Version `in place' 2 (sin suprimir ni insertar)
void chunk_revert3(list<int> &L,int n) {
  list<int>::iterator q, p, r;
  int m, x;
  q = L.begin();
  while (q!=L.end()) {
    p = q;
    for (m=0; m<n; m++)
      if (p++==L.end()) break;
    r = q;
    for (int j=0; j<m/2; j++) {
      x = *q;
      p = q;
      for (int k=0; k<m-2*j-1; k++) p++;
      *q = *p;
      *p = x;
    } // end for
    q = r;
    for (int j=0; j<m; j++) q++;
  } // end while
}

// -------------------------------------------------------------------
int main() {
  list<int> L,L1;
  for (int j=0; j<20; j++) L.push_back(j);
  L1 = L;
  printl(L);
  chunk_revert4(L,3);
  printl(L);
}
// -------------------------------------------------------------------
