// $Id$
/*
  COMIENZO DE DESCRIPCION

  Escribir una funci\'on {\tt void ordenag (list <int> \&l, int m)} 
  que, dada una lista {\tt l}, va ordenando sus elementos de a grupos 
  de {\tt m} elementos. Por ejemplo si m=5, entonces {\tt ordenag} 
  ordena los primeros 5 elementos entre si, despues los siguientes 
  5 elementos, y asi siguiendo. Si la longitud {\tt n} de la lista 
  no es un m\'ultiplo de {\tt m}, entonces los \'ultimos 
  {\tt n mod m} elementos tambi\'en deben ser ordenados entre si. 
  Por ejemplo, si l = (10 1 15 7 2 19 15 16 11 15 9 13 3 7 6 12 1), 
  entonces despu\'es de {\tt ordenag (5)} debemos tener
  l = (1 2 7 10 15 11 15 15 16 19 3 6 7 9 13 1 12).  
  [Tomado en el examen final del 5-Dic-2002].  
  keywords: lista

  FIN DE DESCRIPCION
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c ordenag.cpp
//        g++ -w -o ordenag.exe util.o ordenag.o
// INTEL: icc -w -c util.cpp
//        icc -w -c ordenag.cpp
//        icc -w -o ordenag.exe util.o ordenag.o
// -----------------------------------------------------------------
#include <list>
#include <iostream>
#include "./util.h"
using namespace std;

// -----------------------------------------------------------------
void  ordenag (list<int> &L,int m) {
  list <int>::iterator p,q,z;
  int  k, x;
  p = L.begin();
  while (p != L.end()) {
    for (int k = m ; k > 0 ; k--) {
      // busca el menor elemento *z= min(*q) en el rango [p,p+k)
      q = p; 
      z = q;
      q++;
      for (int j = 1 ; j < k ; j++) {
	if (q == L.end()) break;
	if (*q < *z) z=q;
	q++;
      } // end j
      // lo inserta en L (p) y lo borra de R
      x =*z;
      if (z!=p) {
	L.erase(z);
	p=L.insert(p,x);
      } // end if
      p++;
      if (p == L.end()) break;
    } // end k
  } // end while
  p=L.begin();
  k=0;
  while (p!=L.end()) {
    cout << *p++ << " ";
    if (! (++k % m) ) cout << endl;
  } // enf while
  cout << endl;
} // end void

// -----------------------------------------------------------------
int main () {
  list<int> L;
  int n=3;
  int m= 5;
  cout << endl;
  for (int i=0;i<n;i++) {
    L.clear ();
    randl (L, 10, 3.0, 5);
    cout << "Antes de ordenar  : ";
    printl (L);
    ordenag (L, m);
    cout << "Despues de ordenar: ";
    printl (L);
    cout << endl;
  } // end i
  cout << endl;
  return 0;
} // end main
// -----------------------------------------------------------------


