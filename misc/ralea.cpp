//__INSERT_LICENSE__
// $Id: ralea.cpp,v 1.1 2004/04/05 13:21:31 mstorti Exp $

/*
  COMIENZO DE DESCRIPCION

  Usando las operaciones de Lista, escribir una funcion `void
  random_shufle(list<int> &L)' que, dada una lista de enteros `L'
  reordena sus elementos en forma aleatoria.  Se sugiere el siguiente
  algoritmo: Usando una lista auxiliar Q, se van generando numeros
  enteros desde 0 a `length(L)-1'. Se extrae el elemento `j-esimo' de
  L y se inserta en Q. Finalmente, se vuelven a pasar todos los
  elementos de Q a L. 

  [Ejercicio tomado en el Ex\'amen Final del 05/07/01]
  keywords: lista
  
  FIN DE DESCRIPCION
*/

#include <time.h>
#include <cmath>
#include <sys/time.h>
#include <list>
#include <iostream>
#include <cassert>
#include <map>
#include "./util.h"

double gettod() {
 struct timeval tv;
 gettimeofday(&tv,0);
 return tv.tv_sec + 1e-6 * tv.tv_usec;
}

using namespace std;

void random_shuffle(list<int> &L) {
  // Cuenta el numero de elementos en L
  int n=0;
  list<int>::iterator p = L.begin();
  list<int> Q;
  while (p++!=L.end()) n++;
  for (int m=n; m>0; m--) {
    int k = irand(m);
    p = L.begin();
    for (int j=0; j<m-1; j++) p++;
    Q.insert(Q.end(),*p);
    L.erase(p);
  }
  list<int>::iterator q = Q.begin();
  while (q!=Q.end()) {
    L.insert(L.end(),*q);
    q = Q.erase(q);
  }
}

void random_shuffle2(list<int> &L) {
  // Dividir random entre dos sublistas
  list<int> L1,L2,*LL;
  list<int>::iterator p = L.begin();
  int n,n1=0,n2=0;
  while (p!=L.end()) {
    if (drand()>0.5) { LL = &L1; n1++; }
    else { LL = &L2; n2++; }
    LL->insert(LL->end(),*p);
    p = L.erase(p);
  }
  if (n1>1) random_shuffle2(L1);
  if (n2>1) random_shuffle2(L2);
  // Genera una lista random de dobles
  n = n1+n2;
  list<double> P;
  for (int j=0; j<n; j++) P.insert(P.end(),drand());
  // busca p tal que haya n1 elems. con prob. <p y n2 con prob. > p
  double pa=0., pb=1.,pc;
  int n1c;
  list<double>::iterator r;
  while (true) {
    pc = (pa+pb)/2.;
    n1c = 0;
    r = P.begin();
    while (r!=P.end()) 
      if (*r++<pc) n1c++;
    if (n1c==n1) break;
    else if (n1c<n1) pa = pc;
    else pb = pc;
  }
  r = P.begin();
  for (int j=0; j<n; j++) {
    LL = (*r++ < pc ? &L1 : &L2);
    list<int>::iterator q = LL->begin();
    assert(q!=LL->end());
    int w = *q;
    LL->erase(q);
    L.insert(L.end(),w);
  }
}

class stat_node {
private:
  void add(list<int> &L,list<int>::iterator p) {
    if (p==L.end()) count++;
    else {
      // level_t::iterator q = level.find(*p);
      // if (q==level.end()) level.insert[*p] = stat_node();
      int w = *p;
      level[w].add(L,++p);
    }
  }
  void print(list<int> &L) {
    if (count) {
      cout << "count: " << count << ", L: ";
      printl(L);
    }
    level_t::iterator q = level.begin();
    while (q!=level.end()) {
      // Esta version reusa L
      list<int>::iterator p = L.end();
      p = L.insert(L.end(),q->first);
      q->second.print(L);
      L.erase(p);
      q++;
    }
  }
public: 
  stat_node() : count(0) {}
  int count;
  typedef map<int,stat_node> level_t;
  level_t level;
  void add(list<int> &L) { add(L,L.begin()); }
  void print() { list<int> L; print(L); }
};

int main() {
  list<int> L;
  double l1=10., l2=1e5;
  double tries=l2*10.;
  int N = 10;
  double ll1 = log10(l1);
  double ll2 = log10(l2);
  for (int j=0; j<=N; j++) {
    double xi = double(j)/double(N);
    int len = int(pow(10,ll1+xi*(ll2-ll1)));
    int ntimes = int(tries/double(len))+1;
    double start = gettod();
    for (int j=0; j<ntimes; j++) {
      L.clear();
      for (int j=0; j<len; j++) L.insert(L.end(),j);
      random_shuffle(L);
    }
    double aver = (gettod()-start)/ntimes;
    printf("len %d, ntimes %d, aver time: %g\n",len,ntimes,aver);
  }

#if 0
  stat_node stat;
  for (int j=0; j<1000000; j++) {
    L.clear();
    for (int j=0; j<4; j++) L.insert(L.end(),j);
    cout << "Antes de random_shuffle(): ";
    printl(L);
    random_shuffle2(L);
    cout << "Despues de random_shuffle(): ";
    printl(L);
    stat.add(L);
  }
  stat.print();
#endif
}
