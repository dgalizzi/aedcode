// $Id$

/*
  COMIENZO DE DESCRIPCION

  Usando las operaciones del TAD lista, escribir una funci\'on
  {\tt void particiona (list<int> &L, int a)} la cual, dada una lista 
  de enteros {\tt L}, reemplace aquellos que son mayores que {\tt a}
  por una sucesi\'on de elementos menores o iguales que {\tt a} 
  pero manteniendo la suma total constante.
  [Ejercicio tomado en el Ex\'amen Final del 05/07/01]
  keywords: lista
  
  FIN DE DESCRIPCION
*/
// -----------------------------------------------------------------
/*
  Se propone el siguiente algoritmo: recorrer la lista y, cada vez 
  que se encuentra un elemento "x>a" suprimirlo y reemplazarlo por 
  "a" tantas veces como entren en "x" y finalmente el resto, por ejemplo,
  si x=7 y `a=2', entonces se debe reemplazar ese 7 por la secuencia
  `2,2,2,1'. En la lista final NO deben quedar elementos mayores que
  `a'.  Por ejemplo, si L=[2,5,2,6,4,1,9,6,3,2], entonces particiona
  (l,4) debe retornar L=[2,4,1,2,4,2,4,1,4,4,1,4,2,3,2];
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c particiona.cpp
//        g++ -w -o particiona.exe util.o particiona.o
// INTEL: icc -w -c util.cpp
//        icc -w -c particiona.cpp
//        icc -w -o particiona.exe util.o particiona.o
// -----------------------------------------------------------------
#include <list>
#include <iostream>
#include "./util.h"
using namespace std;

// -----------------------------------------------------------------
void particiona (list<int> &L, int a) {
  list <int>::iterator p;
  int x;
  p = L.begin();
  while (p != L.end()) {
    // Despues de cada ejecucion del cuerpo de este lazo
    // si      *p <= a entonces p queda apuntando al siguiente
    // pero si *p >  a entonces *p es descompuesto en una serie
    // valores  y p queda apuntando al elemento siguiente
    // de la secuencia 
    x=*p;
    if (x>a) {
      p=L.erase(p); // Eliminamos el elemento
      // Este lazo inserta tantos valores de a como entren en *p
      while (x>a) { 
        p=L.insert(p, a); 
        p++; 
        x=x-a; 
      } // end while
      // Inserta el resto (si es x > 0)
      if (x>0) {p=L.insert(p,x); p++;}}
    else 
      p++;
  } // end while
}

// -----------------------------------------------------------------
int main () {
  list<int> L;
  randl(L,10,5.0);
  cout << endl;
  cout << "antes de particionar: ";
  printl(L);
  particiona(L, 3);
  cout << endl;
  cout << "despues de particionar: ";
  printl(L);
  cout << endl;
  cout << "imprime en orden inverso: ";
  printl_inv(L);
  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
