// $Id$

/* 
   COMIENZO DE DESCRIPCION 

    Dada una correspondecia {\tt M} y un elemento {\tt x0}, podemos
    generar una secuencia {\tt (x0,x1,x2,...)} de la forma
    {\tt x_{k+1}=M(x{k})}. La secuencia se detiene cuando uno de
    los valores {\tt x_k} generados no pertenece a las claves de
    {\tt M}. En ese caso la secuencia generada es finita. Por
    otra parte, puede ocurrir que un elemento de la
    secuencia se repita, es decir {\tt x_{k+m}=x_k} con
    {\tt m>0}. Es obvio que, a partir de alli la secuencia se va
    a repetir indefinidamente. _Consigna:_ escribir una
    Escribir una funcion 
    {\tt void cyclic(map<int,int> \&M,list<int> \&L);} 
    que extrae en {\tt L} todas aquellas
    claves de {\tt M} que generan una secuencia ciclica
    infinita. Por ejemplo, si
    {\tt M={(1,2),(2,5),(3,4),(4,6),(5,2)}} entonces
    {\tt cyclic(M,L)} debe retornar {\tt L=(1,2,5)}.
    [Tomado en 1er parcial  25-SEP-2008].
    keywords: correspondencia, lista

    FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <cstdio>
#include <list>
#include <map>
#include "util.h"
using namespace std ;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Predicado que determina si el elemento x
// esta en la lista L
int contains(list<int> &L,int x) {
  list<int>::iterator p = L.begin();
  while (p != L.end()) 
    if (x == *p++) return 1;
  return 0;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Verifica si la secuencia generada por x_{k+1} = M(x_k)
// es finita o no
int is_cyclic(map<int,int> &M, int x) {
  list<int> L;
  L.insert(L.end(),x);
  while (1) {
    // verifica si x tiene un valor asignado
    // o no. OJO: no se deben generar asociaciones
    // espurias. 
    map<int,int>::iterator p = M.find(x);
    // Si no tiene asignacion entonces es un terminador
    if (p==M.end()) return 0;
    // Genera el siquiente elemento de la secuencia
    x=p->second;
    // Verifica si ya esta en la lista o no.
    // Si ya esta entonces es ciclica
    if (contains(L,x)) return 1;
    L.insert(L.end(),x);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Extrae las claves ciclicas de M recorriendo
// las claves y aplicando el predicado `is_cyclic'. 
void cyclic(map<int,int> &M, list<int> &L) {
  map<int,int>::iterator q = M.begin();
  while (q != M.end()) {
    if (is_cyclic(M,q->first)) 
      L.insert(L.end(),q->first);
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  const int ntest = 20;
  // Repite el test ntest veces
  for (int j=0; j<ntest; j++) {    
    list<int> L;

    // Genera un mapa aleatorio
    // Las claves y valores en [0,N).
    map<int,int> M;
    const int N=20;
    for (int j=0; j<N; j++) {
      int k = rand() % N;
      int v = rand() % N;
      M[k] = v;
    }
    
    map<int,int>::iterator r = M.begin();
    while (r!=M.end()) {
      printf("M[%d] = %d\n",r->first,r->second);
      r++;
    }

    cyclic(M,L);
    list<int>::iterator q = L.begin();
    printf("cyclic keys: ");
    while (q!=L.end()) 
      printf(" %d",*q++);
    printf("\n");
    printf("cyclic %d, not cyclic %d\n",L.size(),N-L.size());
    printf("---------\n");
  }
}
