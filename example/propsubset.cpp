// $Id$

/* COMIENZO DE DESCRIPCION
   
  __USE_WIKI__
   Dada una lista de conjuntos
  #list< set<int> > L#, escribir una funci\'on predicado 
  #bool proper_subset(list< set<int> > &L)#, que determina si los
  conjuntos de la lista #L# son subconjuntos propios en forma
  consecutiva. Es decir, si #L = (A_0, A_1, ...., A_{n-1})#, 
  determinar si #A_j# es subconjunto propio de #A_{j+1}#, 
  para #j=0,...,n-2#. 
  [Tomado en el examen final 7/7/2005]. 
  keywords: conjunto

  FIN DE DESCRIPCION */

#include <cstdio>
#include <cmath>
#include <set>
#include <list>
#include <algorithm>
#include "./util.h"

using namespace std;

typedef set<int> set_t;
typedef list<set_t> list_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void aed_set_union(set_t &a,set_t &b, set_t &c) {
  c.clear();
  set_union(a.begin(),a.end(),b.begin(),b.end(),
		 inserter(c,c.begin()));
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void aed_set_intersection(set_t &a,set_t &b, set_t &c) {
  c.clear();
  set_intersection(a.begin(),a.end(),b.begin(),b.end(),
		 inserter(c,c.begin()));
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void aed_set_difference(set_t &a,set_t &b, set_t &c) {
  c.clear();
  set_difference(a.begin(),a.end(),b.begin(),b.end(),
		 inserter(c,c.begin()));
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool proper_subset(list< set<int> > &L) {
  list_t::iterator p = L.begin();
  if (p == L.end()) return true;

  set_t tmp;
  while (p != L.end()) {
    // *p es A[j] y *q es A[j+1]
    list_t::iterator q = p; q++;

    // Aseguramos que p y
    // q son dereferenciables
    if (q==L.end()) break;

    // Verifica que A[j] incluido en A[j+1]
    // es decir, tmp = A[j]-A[j+1] es vacio
    aed_set_difference(*p,*q,tmp);
    if (!tmp.empty()) {
      // printf("NO incluye!!\n");
      return false;
    }

    // Verifica que la inclusion es propia
    // es decir, tmp = A[j+1]-A[j] NO es vacio
    aed_set_difference(*q,*p,tmp);
    if (tmp.empty()) {
      // printf("Inclusion NO propia!!\n");
      return false;
    }

    p=q;	   
  }
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Hace S un conjunto aleatorio con approx. m enteros en [0,n)
void make_random_set(set<int> &S,int m,int n) {
  S.clear();
  double lambda = 1.0/(m+1);
  while (drand() > lambda) 
      S.insert(rand() % n);
}

// Auxiliar function, prints set
void prints(set_t &S,const char *s=NULL) {
  // printf("size() %d\n",S.size());
  set_t::iterator q = S.begin();
  if (s) printf("%s: ",s);
  while (q != S.end()) printf(" %d",*q++);
  if (s) printf("\n");
}

// -------------------------------------------------------------------
int main () {

  list_t L;
  set_t S,DS,SS;

  // Prueba generando aleatoriamente listas
  // de vectores 
  for (int it=0; it<20; it++) {
    L.clear();
    S.clear();
    for (int j=0; j<3; j++) {
      // Agrega un conjunto aleatorio
      make_random_set(DS,3,100);
      aed_set_union(S,DS,SS);
      S = SS;

      // Quita un conjunto aleatorio
      make_random_set(DS,10,100);
      aed_set_difference(S,DS,SS);
      S = SS;

      L.push_back(S);
    }

    list_t::iterator q = L.begin();
    int j=0;
    while (q!=L.end()) {
      printf("L{%d} = (",j);
      set_t::iterator r = q->begin();
      while (r!=q->end()) 
	printf(" %d",*r++);
      printf(")\n");
      j++; q++;
    }
    printf("son subconjuntos propios? %s\n---------------\n",
	   (proper_subset(L)? "si" : "no"));
  }
}
// -------------------------------------------------------------------
