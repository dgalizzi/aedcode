// $Id$

/* 
   COMIENZO DE DESCRIPCION 

    Dadas dos correspondencias {\tt A} y {\tt B}, que asocian
    enteros con listas ordenada de enteros, escribir una
    funcion 
    {\tt void merge_map(map<int,list<int>> \&A, map<int,list<int>> \&B, map<int,list<int>> \&C)} que
    devuelve en {\tt C} una correspondencia que asigna al
    elemento {\tt x} la fusion ordenada de las dos listas {\tt A[x]}
    y {\tt B[x]}. Si {\tt x} no es clave de {\tt A}, entonces {\tt C[x]}
    debe ser {\tt B[x]} y viceversa. Por ejemplo:
    si {\tt M={(1,2),(2,5),(3,4),(4,6),(5,2)}} entonces {\tt cyclic(M,L)}
    debe dejar {\tt L=(1,2,5)}. 
    [Tomado en 1er parcial  25-SEP-2008].
    keywords: correspondencia, lista

    FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <cstdio>
#include <cassert>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

using namespace std ;

typedef list<int> list_t;
typedef list_t::iterator liter;
typedef map<int,list<int> > map_t;
typedef map_t::iterator miter;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Pone en C la fusion ordenada de 2 listas ordenadas
// A y B. Elementos repetidos aparecen tantas veces como
// en cada uno de los originales (i.e. preserva el numero
// de elementos). OJO L1, L2 y L deben ser
// objetos diferentes.
void merge(list_t &L1,list_t &L2,list_t &L) {
  liter 
    q1 = L1.begin(),
    q2 = L2.begin();
  // Avanza el menor y pone su valor al final de L
  while ((q1 != L1.end()) && (q2 != L2.end())) {
    if (*q1 <= *q2) L.insert(L.end(),*q1++);
    else L.insert(L.end(),*q2++);
  }
  // Inserta las colas de L1 y L2, notar
  // que no importa el orden ya que a esta altura
  // alguna de las dos esta vacia
  while (q1 != L1.end()) L.insert(L.end(),*q1++);
  while (q2 != L2.end()) L.insert(L.end(),*q2++);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

// Agrega las asignaciones de A a las de C.  Es decir si A
// asigna a x la lista La y C le asigna Lc, entonces despues
// de hacer add_map(A,C) en C[x] queda merge(La,Lc)
void add_map(map_t &A, map_t&C) {
  // Recorre las asignaciones de A
  miter qa = A.begin();
  while (qa!=A.end()) {
    // clave de la asignacion
    int ka = qa->first;
    // Busca si la clave esta asignada en C
    miter qc = C.find(ka);
    // Si la clave no esta asignada en C
    // crea una asignacion con la lista nula
    if (qc == C.end()) C[ka] = list_t();
    // A esta altura C *seguro* tiene una
    // asignacion para ka
    qc = C.find(ka);
    assert(qc != C.end());
    // hace la fusion de las listas en la lista
    // temporaria L. OJO, no se puede hacer in-place
    // es decir merge(qa->second,qc->second,qc->second);
    // ya que los argumentos de merge deben ser diferentes. 
    list_t L;
    merge(qa->second,qc->second,L);
    // Copia el resultado de merge en la asignacion de C
    qc->second = L;
    qa++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void merge_map(map_t &A, map_t &B, map_t&C) {
  C.clear();
  // Simplemente agrega las asignaciones de A y B en C
  add_map(A,C);
  add_map(B,C);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Genera un mapa aleatorio de `nk' claves en [0,NK)
// a listas de lingitud aleatoria (en promedio NL)
// de elementos en [0,M)
void rand_map(int nk,int NK, int nl, int NL, map_t &M) {
  // genera nk enteros diferentes en [0,NK)
  // para eso introduce los enteros de [0,NK)
  // en un vector, hace el random_shuffle() y
  // toma los nk primeros
  vector<int> v(NK);
  for (int j=0; j<NK; j++) v[j] = j;
  random_shuffle(v.begin(),v.end());

  // para cada clave asigna una lista aleatoria
  for (int j=0; j<nk; j++) {
    M[v[j]] = list_t();
    list_t &L = M[v[j]];
    int len = rand() % (2*nl);
    for (int j=0; j<len; j++) 
      L.insert(L.end(),rand()%NL);
    // Ordena la lista
    L.sort();
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Imprime la correspondencia
void print_map(map_t &M) {
  miter p = M.begin();
  while (p != M.end()) {
    printf("%d: ",p->first);
    list_t &L = p->second;
    liter q = L.begin();
    while (q != L.end()) 
      printf(" %d",*q++);
    printf("\n");
    p++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  // genera dos corresnpondencias aleatorias
  // A, B. Las concatena en C e imprime
  map_t A,B,C;
  rand_map(5,10,5,10,A);
  printf("A: --------\n");
  print_map(A);
  rand_map(5,10,5,10,B);
  printf("B: --------\n");
  print_map(B);

  merge_map(A,B,C);
  printf("C: --------\n");
  print_map(C);
}
