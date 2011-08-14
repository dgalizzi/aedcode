// $Id$

/* COMIENZO DE DESCRIPCION 

   Dada una lista de conjuntos de enteros 
   {\tt list< set<int> > l} escribir una funci\'on 
   {\tt void diffsym(list< set<int> > \&L, set<int> \&ad)} 
   que retorna en {\tt ad} el conjunto de los elementos que
   pertenecen a uno y s\'olo uno de los conjuntos de {\tt L}. 
   Por ejemplo, si {\tt L = ({1,2,3},{2,4,5},{4,6})} entonces
   {\tt ad} debe ser {\tt {1,3,5,6}}. Notar que si el n\'umero
   de conjuntos en {\tt l} es 2 y los llamamos {\tt A} y {\tt B}, 
   entonces debe retornar {\tt ad = (A-B) union (B-A)}. 
   [Tomado en el 3er parcial 23/6/2005]. 
   keywords: conjunto

   FIN DE DESCRIPCION */

#include <time.h>
#include <sys/time.h>
#include <cassert>
#include <cmath>
#include <set>
#include <list>
#include <algorithm>
#include <cstdio>
#include "./util.h"

using namespace std;

void print(const set<int> &s,
	   const char *t=NULL) {
  if (t) printf("%s",t);
  set<int>::iterator q = s.begin();
  while (q!=s.end()) printf("%d ",*q++);
  printf("\n");
}

// -----------------------------------------------------------------
// Obtiene el tiempo en segundos. 
// warning: `gettimeofday' is a GNU extension. 
double gettod() {
 struct timeval tv;
 gettimeofday (&tv,0);
 return tv.tv_sec + 1e-6 * tv.tv_usec;
}

//    Un algoritmo posible es recorrer todos los elementos
//    #x# que pertenecen a alg\'un conjunto de #l# y contar
//    en cuantos elementos de #l# est\'a (debe estar en al 
//    menos uno). El elemento es insertado en #ad# s\'olo
//    si el conteo da exactamente 1. 
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void diffsym(list< set<int> > &l,set<int> &ad) {
  list< set<int> >::iterator q = l.begin();
  while (q!=l.end()) {
    set<int> &s = *q;
    set<int>::iterator r = s.begin();
    while (r!=s.end()) {
      int count = 0;
      list< set<int> >::iterator w = l.begin();
      while (w!=l.end()) {
	if (w->find(*r) != w->end()) count++;
	if (count>=2) break;
	w++;
      }
      if (count==1) ad.insert(*r);
      r++;
    }
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Otro algoritmo, basado en funciones binarias
// Notar que en el caso de tres conjuntos si:
// S=diffsym(A,B) y
// U= A union B,
// entonces:
// diffsym(A,B,C) = (S-C) \cup (C-U). 
// Esto vale en general para cualquier n\'umero de conjuntos, de manera
// que podemos utilizar el siguiente lazo
// L = lista de conjuntos, S=U=<conjunto-vacio>
// FOR Q en la lista de conjuntos de L
// S = (S-Q) union (Q-U)
// U = U union Q
// Al terminar el lazo, S es la diferencia sim\'etrica buscada. 
void diffsym2(list< set<int> > &l,
		   set<int> &all_diff) {
  all_diff.clear();
  set<int> all_union,s1,s2;
  list< set<int> >::iterator 
    q = l.begin();
  while (q!=l.end()) {
    s2.clear();
    set_difference(all_diff.begin(),all_diff.end(),
		   q->begin(),q->end(),
		   inserter(s2,s2.begin()));
    all_diff = s2;

    set_difference(q->begin(),q->end(),
		   all_union.begin(),all_union.end(),
		   inserter(all_diff,all_diff.begin()));

    s1.clear();
    set_union(q->begin(),q->end(),
	      all_union.begin(),all_union.end(),
	      inserter(s1,s1.begin()));
    all_union = s1;
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Otra version: Hacemos all_diff = U - UI
// donde U = Union de todos los conjuntos
// donde UI = Union de las intersecciones de todos los
// pares de conjuntos.
void diffsym3(list< set<int> > &l,
              set<int> &all_diff) {
  set<int> U,UI,tmp1,tmp2;

  // Hace U = union de todos los conjuntos
  list< set<int> >::iterator q = l.begin(),r;
  while (q!=l.end()) {
    tmp2.clear();
    set_union(U.begin(),U.end(),
              q->begin(),q->end(),
              inserter(tmp2,tmp2.begin()));
    swap(U,tmp2);
    q++;
  }

  // Hace I = Union de todas las intersecciones de todos los
  // pares de conjuntos
  q = l.begin();
  while (q != l.end()) {
    // Poniendo r = siguiente de q
    // se gana un poco en eficiencia.
    // Se puede tambien verificar 
    r = q;
    r++;
    tmp1.clear();
    while (r!=l.end()) {
      set_intersection(q->begin(),q->end(),
                       r->begin(),r->end(),
                       inserter(tmp1,tmp1.begin()));
      r++;
      tmp2.clear();
      set_union(UI.begin(),UI.end(),
                tmp1.begin(),tmp1.end(),
                inserter(tmp2,tmp2.end()));
      swap(tmp2,UI);
    }
    q++;
  }

  // Hace all_diff = U - UI
  all_diff.clear();
  set_difference(U.begin(),U.end(),
                 UI.begin(),UI.end(),
                 inserter(all_diff,all_diff.begin()));
}

typedef list< set<int> > lset_t;
typedef lset_t::iterator lset_iter;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void diffsym4(lset_t &l, set<int> &all_diff, set<int> &all_union) {
  all_diff.clear();
  all_union.clear();

  if (l.size()==0) {
    return;
  } if (l.size()==1) {
    lset_iter q = l.begin();
    swap(all_diff,*q);
    l.erase(q);
    all_union = all_diff;
    return;
  }
  lset_t lodd, leven;
  lset_iter q = l.begin();
  int indx = 0;
  set<int> empty_set, 
    all_diff_odd, all_union_odd,
    all_diff_even, all_union_even,
    tmp1,tmp2;
    
  while (q != l.end()) {
    lset_t *lp = (indx % 2? &lodd : &leven);
    lset_iter r = lp->insert(lp->end(),empty_set);
    // printf("indx %d, *r: ",indx); print(*q);
    swap(*r,*q);
    q = l.erase(q);
    indx++;
  }
  
  diffsym4(lodd,all_diff_odd,all_union_odd);
  diffsym4(leven,all_diff_even,all_union_even);

#if 0
  printf("antes del merge--------\n");
  printf("all_diff_odd: "); print(all_diff_odd);
  printf("all_union_odd: "); print(all_union_odd);
  printf("all_diff_even: "); print(all_diff_even);
  printf("all_union_even: "); print(all_union_even);
#endif
  
  set_difference(all_diff_odd.begin(),all_diff_odd.end(),
                 all_union_even.begin(),all_union_even.end(),
                 inserter(tmp1,tmp1.begin()));
  swap(all_diff_odd,tmp1);
  tmp1.clear();

  set_difference(all_diff_even.begin(),all_diff_even.end(),
                 all_union_odd.begin(),all_union_odd.end(),
                 inserter(tmp1,tmp1.begin()));
  swap(all_diff_even,tmp1);
  tmp1.clear();

  all_diff.clear();
  set_union(all_diff_even.begin(),all_diff_even.end(),
            all_diff_odd.begin(),all_diff_odd.end(),
            inserter(all_diff,all_diff.end()));

  all_union.clear();
  set_union(all_union_even.begin(),all_union_even.end(),
            all_union_odd.begin(),all_union_odd.end(),
            inserter(all_union,all_union.end()));

#if 0
  printf("despues del merge--------\n");
  printf("all_diff: "); print(all_diff);
  printf("all_union: "); print(all_union);
#endif

  while (1) {
    lset_t *lp = (indx % 2? &lodd : &leven);
    if (lp->empty()) return;
    lset_iter r = lp->begin();
    q = l.insert(l.end(),empty_set);
    swap(*r,*q);
    lp->erase(r);
  }
}

void diffsym4(lset_t &l, set<int> &all_diff) {
  set<int> s;
  diffsym4(l,all_diff,s);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Este es similar al `diffsym4' pero se basa en lo
// siguiente. Si dividimos la lista de conjuntos l en
// dos partes l1 y l2, entonces podemos calcular
// por la diferencia simetrica de l1 all_diff_1
// y la union de todos sus conjuntos all_union_1.
// Lo mismo para l2. Ahora para hacer el `merge' (fusion) de
// los dos queda:
// 
// all_diff = (all_diff_1 - all_union_2) \cup  (all_diff_2 - all_union_1)
// all_union = all_union_1 \cup all_union_2
//
// Para calcular all_diff_1 aplicamos recursion. La recursion corta
// cuando la lista es vacia (en cuyo caso all_diff = all_union = empty-set)
// o tiene un solo conjunto en cuyo caso all_diff = all_union = s.
//
// La idea es que este algoritmo puede ser mas eficiente
// porque va agrupando los conjuntos en forma balanceada.
void diffsym4b(lset_t &l, set<int> &all_diff, 
               set<int> &all_union,
               lset_iter q1, lset_iter q2, int n) {
  all_diff.clear();
  all_union.clear();

  if (n == 0) {
    return;
  } if (n==1) {
    all_diff = *q1;
    all_union = *q1;
    return;
  }

  lset_t l1, l2;
  int n1 = n/2, n2 = n-n1;
  lset_iter qh = q1;
  for (int j=0; j<n1; j++) qh++;

  set<int> empty_set, 
    all_diff_1, all_union_1,
    all_diff_2, all_union_2,
    tmp1,tmp2;
    
  diffsym4b(l,all_diff_1,all_union_1,q1,qh,n1);
  diffsym4b(l,all_diff_2,all_union_2,qh,q2,n2);

#if 0
  printf("antes del merge--------\n");
  printf("all_diff_1: "); print(all_diff_1);
  printf("all_union_1: "); print(all_union_1);
  printf("all_diff_2: "); print(all_diff_2);
  printf("all_union_2: "); print(all_union_2);
#endif
  
  set_difference(all_diff_1.begin(),all_diff_1.end(),
                 all_union_2.begin(),all_union_2.end(),
                 inserter(tmp1,tmp1.begin()));
  swap(all_diff_1,tmp1);
  tmp1.clear();

  set_difference(all_diff_2.begin(),all_diff_2.end(),
                 all_union_1.begin(),all_union_1.end(),
                 inserter(tmp1,tmp1.begin()));
  swap(all_diff_2,tmp1);
  tmp1.clear();

  all_diff.clear();
  set_union(all_diff_2.begin(),all_diff_2.end(),
            all_diff_1.begin(),all_diff_1.end(),
            inserter(all_diff,all_diff.end()));

  all_union.clear();
  set_union(all_union_2.begin(),all_union_2.end(),
            all_union_1.begin(),all_union_1.end(),
            inserter(all_union,all_union.end()));

#if 0
  printf("despues del merge--------\n");
  printf("all_diff: "); print(all_diff);
  printf("all_union: "); print(all_union);
#endif

}

void diffsym4b(lset_t &l, set<int> &all_diff) {
  set<int> s;
  diffsym4b(l,all_diff,s,l.begin(),l.end(),l.size());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Crea un conjunto aleatorio `s' con
// `m' elements in average in range [0,N)
void make_random_set(set<int> &s,
		     int m,int N) {
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
  int ncases=10, vrbs = 1;

  for (int k=0; k<ncases; k++) {
#if 1
    int N = 20;		  // integers in sets are in range [0,N)
    int m = 10;           // Nbr of elements in each set
    int n = 5;            // nbr of sets
#elif 0
    int N = 600;      // integers in sets are in range [0,N)
    int m = 300;      // Nbr of elements in each set
    int n = 300;      // nbr of sets
#elif 0
    int ref=10;
    int N = 200*ref;      // integers in sets are in range [0,N)
    int m = 100*ref;      // Nbr of elements in each set
    int n = 100*ref;      // nbr of sets
#endif
    list< set<int> > l;
    double sav = 0.0;
    printf("----------------\n");
    for (int k=0; k<n; k++) {
      l.push_back(set<int>());
      set<int> &s = l.back();
      make_random_set(s,m,N);
      if (vrbs) {
        printf("set[%d]: ",k);
        print(s);
      }
      sav += s.size();
    }
    printf("average set size %f\n",sav/n);

    set<int> S1,S2,S3,S4,S4b;
    double start;

    start = gettod();
    diffsym(l,S1);
    printf("diffsym(): elapsed %.2f\n",gettod()-start);
    if (vrbs) print(S1,"using diffsym():");

    start = gettod();
    diffsym2(l,S2);
    printf("diffsym2(): elapsed %.2f\n",gettod()-start);
    if (vrbs) print(S2,"using diffsym2():");

    start = gettod();
    diffsym3(l,S3);
    printf("diffsym3(): elapsed %.2f\n",gettod()-start);
    if (vrbs) print(S3,"using diffsym3():");

    start = gettod();
    diffsym4(l,S4);
    printf("diffsym4(): elapsed %.2f\n",gettod()-start);
    if (vrbs) print(S4,"using diffsym4():");

    start = gettod();
    diffsym4b(l,S4b);
    printf("diffsym4b(): elapsed %.2f\n",gettod()-start);
    if (vrbs) print(S4b,"using diffsym4b():");

    printf("S2==S1 OK? %d\n",S2==S1);
    printf("S3==S1 OK? %d\n",S3==S1);
    printf("S4==S1 OK? %d\n",S4==S1);

    assert(S2==S1);
    assert(S3==S1);
    assert(S4==S1);
  }
}
