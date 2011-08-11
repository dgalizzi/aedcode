// $Id$

/*
  COMIENZO DE DESCRIPCION

  Usando las operaciones del TAD lista, escribir una funci\'on 
  {\tt void random_shuffle (list <int> \&L)} que, dada una lista 
  de enteros {\tt L}, reordena sus elementos en forma aleatoria.  
  Se sugiere el siguiente algoritmo: usando una lista auxiliar 
  {\tt Q} se van generando n\'umeros enteros desde 0 a 
  {\tt length (L) - 1}. Se extrae el elemento j-\'esimo de
  {\tt l} y se inserta en {\tt Q}. Finalmente, se vuelven a 
  pasar todos los elementos de la cola {\tt Q} a la lista {\tt L}. 
  [Ejercicio tomado en el Ex\'amen Final del 05/07/01]
  keywords: lista
  
  FIN DE DESCRIPCION
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c ralea.cpp
//        g++ -w -o ralea.exe util.o ralea.o
// INTEL: icc -w -c util.cpp
//        icc -w -c ralea.cpp
//        icc -w -o ralea.exe util.o ralea.o
// -----------------------------------------------------------------
#include <list>
#include <iostream>
#include <cassert>
#include <map>
#include "./util.h"
using namespace std;

// -----------------------------------------------------------------
void random_shuffle(list<int> &L) {
  list<int>::iterator p,z; 
  list<int> q;
  int k,n;
  // Cuenta el numero de elementos en la lista L
  n=0;
  p=L.begin();
  while (p++!=L.end()) n++;
  // En cada iteracion del lazo se saca un elemento
  // al azar de la lista L y se lo inserta en la cola Q
  for (int h=n;h>0;h--) {
    // A esta altura la lista L tiene m elementos
    // asi que generamos un entero entre 0 y m-1
    k=irand(h);
    // nos posicionamos en el elemento k en la lista L
    p=L.begin();
    for (int j=0;j<h-1;j++) p++;
    // inserta el elemento k de la lista L al final de la cola Q
    // y lo elimina de la lista L
    q.insert(q.end(),*p);
    L.erase(p);
  } // end h
  // Vuelve a copiar todos los elementos de la cola a la lista
  z=q.begin();
  while (z!=q.end()) {
    L.insert(L.end(),*z);
    z=q.erase(z);
  } // end while
} 

// -----------------------------------------------------------------
int main() {
  list<int> L;
  int n=3;
  int m=10;
  for (int i=0;i<n;i++) {
    L.clear();
    randl(L,m,10.0);
    cout << endl;
    cout << "Antes de random_shuffle  : ";
    printl(L);
    random_shuffle (L);
    cout << endl;
    cout << "Despues de random_shuffle: ";
    printl(L);
  } // end i
  cout << endl;
  return 0;
}
// -----------------------------------------------------------------

