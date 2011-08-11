// $Id$

/* 
   COMIENZO DE DESCRIPCION 

   Escriba procedimientos para intercalar ({\it merge}): 
   (i) dos listas ordenadas {\tt L1} y {\tt L2} en una nueva lista 
   {\tt L}; (ii) un vector {\tt VL} de {\tt n} listas ordenadas 
   como nueva lista {\tt L}. Notar que {\it intercalar} ({\it merge}) 
   implica en ambos casos que la nueva lista {\tt L} debe resultar 
   tambi\'en {\it ordenada}.
   keywords: lista

   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c intercala.cpp
//        g++ -w -o intercala.exe util.o intercala.o
// INTEL: icc -w -c util.cpp
//        icc -w -c intercala.cpp
//        icc -w -o intercala.exe util.o intercala.o
// -----------------------------------------------------------------
#include <iostream>
#include <limits.h>
#include "./util.h"
using namespace std ;

// -----------------------------------------------------------------
// intercala (merge) dos listas ordenadas L1 y L2 como nueva lista L
template <typename t>
void intercala_2L (list<t> &L1,list<t> & L2 ,list<t> &L){ 
  typename list<t>::iterator p,q;
  t x1,x2;
  L.clear();         // reinicializa nueva lista L
  p=L1.begin();      // iterador para recorrer lista L1
  q=L2.begin();      // iterador para recorrer lista L2
  while (p!=L1.end() && q!=L2.end()) {
    x1=*p;
    x2=*q;
    if (x1<=x2) {
       L.insert(L.end(),x1);
       p++;}
    else {
       L.insert(L.end(),x2);
       q++; 
    } // end if
  } // end while
  while (p!=L1.end()) {L.insert(L.end(),*p++);} // eventual resto L1
  while (q!=L2.end()) {L.insert(L.end(),*q++);} // eventual resto L2
}

// -------------------------- --------------------------------------
// intercala el vector VL de "n" listas ordenadas como nueva lista L
template <typename t>
void intercala_vn (vector< list<t> > &VL, list<t> &L){ 
  typename list<t>::iterator p,q,z;
  int n;
  t x1,x2;
  L.clear();         // reincializa nueva lista L
  // copia la primera lista L_0 del vector VL en la lista L
  n=VL.size();
  q=VL[0].begin();   // iterador para la lista L_0
  z=VL[0].end();     // posicion del fin de la lista L_0
  while (q!=z) L.insert (L.end(),*q++); // notar: inserta al final
  // ahora intercala las restantes del vector en la lista L
  for (int i=1;i<n;i++) {
    p=L.begin();        // iterador para recorrer la nueva lista L
    q=VL[i].begin();    // iterador para recorrer la lista L_i
    z=VL[i].end();      // fin de la lista L_i
    while (p!=L.end() && q!=z) { 
      x1=*p;
      x2=*q;
      if (x1<=x2) {p++;}           // no inserta y avanza
      else {p=L.insert(p,x2);q++;} // inserta y refresca posicion 
    } // end while
    // pasa el remanente de la lista L_i a la nueva lista L
    while (q!=z) L.insert(L.end(),*q++); // notar: inserta al final
  } // end i
}

//--------------------------------------------------------------------
int main() {
  typedef int dato;
  typedef list<dato> lista;
  typedef vector<lista> vecto_l;
  int v0[]={2,4,6,8,11,13,14,-1};
  int v1[]={1,3,5,7,9,27,-1};
  int v2[]={2,4,6,8,42,50,-1};
  int n=3 ; // hay 3 listas
  lista L1,L2,L;
  cout << endl;
  cout << "intercala 2 listas ordenadas L1 y L1 como lista L " << endl;
  // arma lista ordenada L1
  insertl (L1,v1,-1);
  cout << "lista L1: ";
  printl(L1);
  // arma lista ordenada L2
  insertl (L2,v2,-1);
  cout << "lista L2: ";
  printl(L2);

  // intercala listas L1 y L2 en L
  intercala_2L(L1,L2,L); 
  cout << "lista L intercalada: ";
  printl(L);

  cout << endl;
  cout << "intercala un vector VL de N listas ordenadas " << endl;

  // numero de listas "n"
  cout << "numero de listas ; n = " << n << endl;
  vecto_l VL (n);  // constructor del vector de listas

  // arma lista ordenada L1
  insertl (VL[0],v0,-1);
  insertl (VL[1],v1,-1);
  insertl (VL[2],v2,-1);

  // imprime cada lista
  for (int i=0;i<n;i++) {
    cout << "lista L [" << i << "]: ";printl(VL[i]);
  } // end for
  // intercala las N listas en una unica lista
  intercala_vn (VL,L); 
  cout << "lista L intercalada: ";
  printl (L);

  cout << endl;
  return 0;
}
//--------------------------------------------------------------------
