// $Id$

/* 
   COMIENZO DE DESCRIPCION 

   Una correspondencia es una _permutacion_ si el conjunto de
   los elementos del dominio (las claves) es igual al del contradominio
   (los valores). Consigna: escribir una funcion
   predicado {\tt bool es_permutacion(map<int,int> \&M)} que retorna
   {\tt true} si {\tt M} es una permutacion y {\tt false} si no lo es.
   [Tomado en Primer Parcial 27-SET-2007].
   keywords: correspondencia

   FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <iostream>
#include <map>
#include <cstdio>
using namespace std ;

bool es_permut(map<int,int> &M) {
  map<int,int> M2;
  map<int,int>::iterator q = M.begin(), q2;
  while (q!=M.end()) {
    M2[q->second] = q->first;
    q++;
  }

  if (M.size() != M2.size()) return false;
  q = M.begin();
  while (q!=M.end()) {
    q2 = M2.find(q->first);
    if (q2==M2.end()) return false;
    q++;
  }
  return true;
}

void print_map(map<int,int> &M) {
  map<int,int>::iterator q = M.begin();
  while (q!=M.end()) {
    printf("(%d -> %d) ",q->first,q->second);
    q++;
  }
  printf("\n");
}

//--------------------------------------------------------------------
int main() {
  map<int,int> M;
  int N=10;

  // Deberia retornar `true'
  for (int j=0; j<N; j++) M[j] = (j+3)%10;
  print_map(M);
  printf("is permutation ? %d\n",es_permut(M));

  // Deberia retornar `false'
  M.clear();
  for (int j=0; j<N; j++) M[j] = (j+3);
  print_map(M);
  printf("is permutation ? %d\n",es_permut(M));
}
// -----------------------------------------------------------------
