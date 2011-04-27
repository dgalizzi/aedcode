// $Id$

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Escribir un predicado
   #bool incluido(set<int> &A, set<int> &B);# que retorna verdadero
   si y solo si #A# esta incluido en #B#. 
   [Tomado en el 3er parcial 23/6/2005]. 
   keywords: conjunto

   FIN DE DESCRIPCION */

#include <cmath>
#include <set>
#include <list>
#include <algorithm>
#include "./util.h"

using namespace std;

void print(const set<int> &s,
	   const char *t=NULL) {
  if (t) printf("%s",t);
  set<int>::iterator q = s.begin();
  while (q!=s.end()) printf("%d ",*q++);
  printf("\n");
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// version 1: verifica que cada elemento de
// A este en B
bool incluido(set<int> &A, set<int> &B) {
  set<int>::iterator q = A.begin();
  while (q != A.end()) 
    if (B.find(*q++) == B.end()) return false;
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// A esta incluido en B si y solo si
// la diferencia A-B es vacia
bool incluido2(set<int> &A, set<int> &B) {
  set<int> C;
  set_difference(A.begin(),A.end(),B.begin(),B.end(),
		 inserter(C,C.begin()));
  return C.empty();
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void make_random_set(set<int> &s,
		     int m,int n,int N) {
  double lambda = 1.0/(m+1);	// Probability of stopping
  s.clear();
  while(1) {
    if (drand()<lambda) break;
    int w = rand() % N;
    s.insert(w);
  }
}

// -------------------------------------------------------------------
int main () {
  int N = 8;		  // Max nbr of elements in all sets
  int m = 5;			// Averg. nbr of elements in each set
  int n = 20;			// nbr of tries
  double lambda = 1.0/(m+1);	// Probability of stopping
  for (int k=0; k<n; k++) {
    set<int> a,b;
    make_random_set(a,m,n,N);
    printf("------\nA: ",k); print(a);

    make_random_set(b,m,n,N);
    printf("B: ",k); print(b);

    printf("A \\subset B (loop version) ? %d\n",
	   incluido(a,b));
    printf("A \\subset B (binary fun version) ? %d\n",
	   incluido2(a,b));
  }
}
