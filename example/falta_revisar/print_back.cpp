// $Id$

/* 
   COMIENZO DE DESCRIPCION

   Escriba una funci\'on 
   {\tt void print_back (list<int> & L, list <int> :: iterator p)} que,
   en forma {\it recursiva}, imprima una lista en sentido inverso, 
   es decir, desde el final al principio de la lista.  Se le da 
   como dato el procedimiento a la primera posici\'on de la lista.  
   [Ejercicio 3 del final del 14/02/2002]
   keywords: lista

   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c print_back.cpp
//        g++ -w -o print_back.exe util.o print_back.o
// INTEL: icc -w -c util.cpp
//        icc -w -c print_back.cpp
//        icc -w -o print_back.exe util.o print_back.o
// -----------------------------------------------------------------
#include <list>
#include <iostream>
using namespace std;

// -----------------------------------------------------------------
// imprime en orden inverso (por recursion, de atras para adelante)
void print_back (list<int> &L,list<int>::iterator p) {
  list<int>::iterator q; 
  if (p==L.end()) return;
  q=p ; q++;
  print_back (L,q);
  cout << *p << " ";
}
void print_back (list<int> &L) { 
  print_back (L,L.begin()); 
  cout << endl;
}

// -----------------------------------------------------------------
// imprime en orden normal (de adelante para atras)
void  print (list<int> &L) {
  list<int>::iterator p;
  p=L.begin();
  while (p!=L.end()) cout << *p++ << " ";
  cout << endl;
}

// -----------------------------------------------------------------
int main() {
  int v[]={0,1,2,3,4,5,6,7,8,9,-1};
  int *z;
  list<int> L;
  list<int>::iterator p; 

  // construye lista
  z=v;
  while (*z!=-1) L.insert(L.end(),*z++);

  cout << endl;
  cout << "Lista : ";
  print (L);

  cout << "Lista inversa : ";
  print_back (L);

  cout << endl;
  return 0;
} // end main
// -----------------------------------------------------------------
