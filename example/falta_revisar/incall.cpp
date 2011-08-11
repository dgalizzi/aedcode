// $Id$

/* 
   COMIENZO DE DESCRIPCION 

    __USE_WIKI__
   Dados #n# conjuntos #A_0#, #A_1#, ... #A_{n-1}# determinar si 
   alguno de ellos (digamos #A_j# ) incluye a todos los otros. 
   Es decir #A_j\subset A_k# para todo #k#. En ese caso, 
   retornar el indice #j#, si no retornar -1. 
   #int includes_all(vector< set<int> > &setv);#
   [Tomado en tercer parcial 22-NOV-2007].
   keywords: conjunto

   FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include "./util.h"
using namespace std ;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int includes_all(vector< set<int> > &setv) {
  int j=0, n=setv.size();
  // Busca el conjunto candidato `j' con MAYOR cantidad de
  // elementos. Si algun conjunto satisface la condicion
  // del enunciado, entonces DEBE SER el `j'. 
  for (int k=0; k<n; k++) 
    if (setv[k].size()>setv[j].size()) j=k;

  // Para cada conjunto `k' verifica
  // que setv[k] este INCLUIDO en setv[j].
  // En este caso lo hace recorriendo todos
  // los elementos de setv[k]
  set<int> &sj = setv[j];
  for (int k=0; k<n; k++) {
    set<int> &s = setv[k];
    set<int>::iterator q = s.begin();
    while (q!=s.end()) {
      if (sj.find(*q)==sj.end()) return -1;
      q++;
    }
  }
  return j;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int included_in_all(vector< set<int> > &setv) {
  // Similar a `includes-all' pero ahora busca si uno de los
  // conjuntos esta INCLUIDO en todos los otros.
  
  // Busca el conjunto candidato `j' con MENOR cantidad de
  // elementos. Si algun conjunto satisface la condicion
  // del enunciado, entonces DEBE SER el `j'. 
  int j=0, n=setv.size();
  for (int k=0; k<n; k++) 
    if (setv[k].size()<setv[j].size()) j=k;

  // Para cada conjunto `k' verifica
  // que setv[k] INCLUYA A setv[j].
  // En este caso lo hace recorriendo todos
  // los elementos de setv[j]
  set<int> &sj = setv[j];
  for (int k=0; k<n; k++) {
    set<int> &sk = setv[k];
    set<int>::iterator q = sj.begin();
    while (q!=sj.end()) {
      if (sk.find(*q)==sk.end()) return -1;
      q++;
    }
  }
  return j;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int includes_all2(vector< set<int> > &setv) {
  // Esta version se basa en OPERACIONES BINARIAS
  // de conjuntos, esto es verifica que setv[k] este
  // incluido en setv[j] usando `set_difference'

  int j=0, n=setv.size();
  // Busca el conjunto candidato `j' con MAYOR cantidad de
  // elementos. Si algun conjunto satisface la condicion
  // del enunciado, entonces DEBE SER el `j'. 
  for (int k=0; k<n; k++) 
    if (setv[k].size()>setv[j].size()) j=k;

  // Para cada conjunto `k' verifica que `setv[j]' este
  // incluido en `setv[k]' usando `set_difference()'
  set<int> tmp;
  for (int k=0; k<n; k++) {
    set_difference(setv[k],setv[j],tmp);
    if (!tmp.empty()) return -1;
  }
  return j;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int included_in_all2(vector< set<int> > &setv) {
  // Similar a `includes-all' pero ahora busca si uno de los
  // conjuntos esta INCLUIDO en todos los otros.
  
  // Esta version se basa solamente en operaciones de
  // conjuntos, esto es verifica que setv[k] incluya 
  // a setv[j] usando `set_diference'

  // Busca el conjunto candidato `j' con MENOR cantidad de
  // elementos. Si algun conjunto satisface la condicion
  // del enunciado, entonces DEBE SER el `j'. 
  int j=0, n=setv.size();
  for (int k=0; k<n; k++) 
    if (setv[k].size()<setv[j].size()) j=k;

  // Para cada conjunto `k' verifica
  // que setv[k] incluya a setv[j].
  set<int> tmp;
  for (int k=0; k<n; k++) {
    set_difference(setv[j],setv[k],tmp);
    if (!tmp.empty()) return -1;
  }
  return j;
}

//--------------------------------------------------------------------
int main() {
  int N=10, m=4, NN=100, ok=0, okk=0, J, J2, JJ, JJ2;
  for (int l=0; l<NN; l++) {
    printf("------------------------\n");
    vector< set<int> > setv(N);
    // Genera `N' conjuntos aleatorios con `m' elementos
    // escogidos aleatoriamente en [0,m). Para eso
    // recorre todos  los elementos de [0,m) y "tira la moneda"
    // (rand()%2) para ver si lo incluye o no.
    for (int j=0; j<N; j++) {
      printf("setv[%d] = {",j);
      for (int k=0; k<m; k++) {
        if (rand()%2) {
          setv[j].insert(k);
          printf("%d ",k);
        }
      }
      printf("}\n");
    }

    J = includes_all(setv);
    J2 = includes_all2(setv);
    JJ = included_in_all(setv);
    JJ2 = included_in_all2(setv);
    printf("set[J] that includes all: J=%d, "
           "included by all JJ %d\n",
           J,JJ);

    // Verifica que los dos algoritmos den el mismo resultado
    assert(J==J2);
    assert(JJ==JJ2);
    ok += (J>=0);
    okk += (JJ>=0);
  }
  printf("total %d, had superset of all %d, rate %f\n",
         NN,ok,float(ok)/NN);
  printf("had subset of all %d, rate %f\n",
         okk,float(okk)/NN);
}
