// $Id$
/*
  COMIENZO DE DESCRIPCION

  Resoluci\'on del problema de Josephus usando la clase <list> 
  de las STL.
  keywords: lista

  FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c josephus.cpp
//        g++ -w -o josephus.exe util.o josephus.o
// INTEL: icc -w -c util.cpp
//        icc -w -c josephus.cpp
//        icc -w -o josephus.exe util.o josephus.o
// -----------------------------------------------------------------
#include <list>
#include <iostream>
using namespace std;

// -----------------------------------------------------------------
// Debe retornar una lista con las numeros relativos de soldados de
// que van saliendo segun el algoritmo de Josephus, donde "n" es la 
// cantidad de soldados y "s" es el salto en el juego
// -----------------------------------------------------------------
void josephus (int n,int s,list<int> &L) {
  list <int> H;
  list <int> :: iterator p;
  // Inicialmente carga en lista auxiliar H con los enteros [0,n]
  for (int j=0;j<n;j++) H.insert(H.end(),j);
     p=H.begin();
    // Va simulando el algoritmos extrayendo soldados de H y
    // pasandolos a L. Como hay que extraer exactamente N soldados 
    // directamente hacemos un lazo de 0 a N-1
    for (int k = 0; k < n ; k++) {
    // Avanzamos S posiciones en sentido circular por lo que nunca 
    // debe quedar en H.end (). Para evitarlo, cuando llega a
    // ser H.end () pasamos a H.begin ().
    for (int j = 0 ; j < s-1; j++) 
      if (++p == H.end()) p = H.begin (); // Notar pre-incremento
      // Pasamos el soldado en P a la lista L
      L.insert (L.end(),*p);
      // Borra en sentido circular, es decir, si P es el
      // ultimo elemento, entonces al borrar queda en H.end(), 
      // en ese caso lo pasamos a H.begin ()
      p = H.erase(p);
      if (p == H.end () ) p = H.begin ();
    } // end j
} // end void

// -----------------------------------------------------------------
int main() {
  list<int>  L;
  list<int>::iterator p; 

  cout << endl;
  josephus (7,4,L);
  p = L.begin();
  while (p!=L.end()) cout << *p++ << " ";
  cout << endl;

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
