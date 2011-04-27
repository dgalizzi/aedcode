// $Id$

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Dada una correspondencia #M# y asumiendo que es
   _invertible_ o _biunivoca_ (esto es, todos
   los valores del contradominio son distintos), la
   correspondencia `inversa' #N# es aquella
   tal que, si #y=M[x]#, entonces #x=N[y]#. Por
   ejemplo, si #M={(0,1),(1,2),(2,0)}#, entonces la
   inversa es #N={(1,0),(2,1,(0,2))}#. _Consigna:_
   Escribir una funci\'on 
   #bool inverse(map<int,int> &M,map<int,int> &N)# 
   tal que, si #M# es invertible,
   entonces retorna true y #N# es su inversa. En caso
   contrario retorna falso y #N# es la correspondencia
   `vacia' (sin asignaciones)
   [Tomado en el 1er parcial del 20/4/2006].
   keywords: lista, correspondencia

   FIN DE DESCRIPCION */
#include <iostream>
#include <map>
#include "./util.h"

using namespace std ;

bool inverse(map<int,int> &M,map<int,int> &N) {
  N.clear();
  map<int,int>::iterator q = M.begin();
  while (q!=M.end()) {
    if (N.find(q->second)!=N.end()) {
      N.clear();
      return false;
    }
    N[q->second] = q->first; 
    q++;
  }
  return true;
}

void print_map(map<int,int> &M) {
  map<int,int>::iterator q = M.begin();
  while (q!=M.end()) {
    cout << q->first << " -> " << q->second << endl;
    q++;
  }
}

void check(map<int,int> &M) {
  map<int,int> N;
  bool inversible = inverse(M,N);
  cout << "M:\n";
  print_map(M);

  cout << "inversible: " << inversible << endl;
  cout << "N:\n";
  print_map(N);
  cout << "--------------------\n";
}

//--------------------------------------------------------------------
int main() {
  map<int,int> M, N;

  // Light test
  M[0] = 1;
  M[1] = 2;
  M[2] = 0;
  check(M);

  M[0] = 1;
  M[1] = 2;
  M[2] = 1;
  check(M);

  // Test harness
  for (int j=0; j<10; j++) {
    M.clear();
    for (int k=0; k<10; k++) {
      int 
	x = rand() % 10,
	y = rand() % 20;
      M[x] = y;
    }
    check(M);
  }
}
// -----------------------------------------------------------------
// 
