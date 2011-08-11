// $Id$

/*
  COMIENZO DE DESCRIPCION

  Escribir una funci\'on {\tt void junta (list <int> &L, int n)}
  que, dada una lista {\tt L}, agrupa de a {\tt n} elementos
  dejando su suma IN PLACE. Por ejemplo, si la lista {\tt L} 
  contiene L=(1,3,2,4,5,2,2,3,5,7,4,3,2,2), entonces depu\'es de
  {\tt junta (L,3)} debe quedar L=(6,11,10,14,4). Prestar atenci\'on 
  a no usar posiciones inv\'alidas despu\'es de una supresi\'on. 
  El algoritmo debe tener un tiempo de ejecuci\'on {\tt O (m)}, 
  donde {\tt m} es el n\'umero de elementos en la lista original. 
  [Tomado en el examen final del 1/8/2002] 
  keywords: lista

  FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c junta.cpp
//        g++ -w -o junta.exe util.o junta.o
// INTEL: icc -w -c util.cpp
//        icc -w -c junta.cpp
//        icc -w -o junta.exe util.o junta.o
// -----------------------------------------------------------------
#include <list>
#include <iostream>
using namespace std;

// -----------------------------------------------------------------
void junta(list<int> &L,int n) {
  list<int>::iterator p;
  int suma;
  p=L.begin();
  while (p!=L.end()) {
    suma=0;
    // Suma de N elementos y los elimina 
    for (int j=0;j<n;j++) {
      suma=suma+(*p);
      p=L.erase(p);
      // Atencion podrian quedar menos de N elementos
      // en la lista. En tal caso llegamos a L.end () y
      // debemos salir del lazo 
      if (p==L.end()) break;
    } // end i
    // Inserta SUMA e incrementa P de manera de quedar apuntando
    // al comienzo de la siguiente subsecuencia. 
    p=L.insert(p,suma);p++;
  } // end while
}

// -----------------------------------------------------------------
// imprime en orden normal (directo)
void  printl(list<int> &l) {
  list<int>::iterator p;
  p=l.begin();
  while (p!=l.end()) cout << *p++ << " ";
  cout << endl;
}

// -----------------------------------------------------------------
int main () {
  int v[]={10,1,15,7,2,19,15,16,11,15,9,13,3,7,6,12,1,-1};
  int n=3;
  int *z;
  list<int> L;
  z=v;
  while (*z!=-1) {L.insert(L.end(),*z++);}
  cout << endl;
  cout << "Agrupa de a " << n << " elementos " << endl;
  cout << "Lista inicial : ";
  printl(L);
  junta (L,n);
  cout << "Lista agrupada: ";
  printl(L);
  cout << endl;
  return 0;
} // end main
// -----------------------------------------------------------------

