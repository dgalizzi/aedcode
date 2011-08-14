// $Id$

/* COMIENZO DE DESCRIPCION 

   gado un grafo como {\tt map<int,set<int>> G} encontrar los subconjuntos del
   mismo {\tt list<set<int>> D} que estan desconectados. Por ejemplo, si 
   {\tt G={1->{2},2->{1},3->{4},4->{3}}}, 
   entonces debe retornar {\tt D=({1,2},{3,4})}. 
   La signatura de la funcion a implementar es
   {\tt void connected(map<int,set<int>> \&G, list<set<int>> \&D);}

   [Tomado en el 3er parcial 2008-11-20]. 
   keywords: conjunto

   FIN DE DESCRIPCION */

#include <time.h>
#include <sys/time.h>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include "./util.h"

using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void print_set(set<int> &s,const char *lab=NULL) {
  set<int>::iterator q = s.begin();
  if (lab) printf("%s: ",lab);
  while (q != s.end()) 
    printf("%d ",*q++);
  printf("\n");
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

// Busca la componente conexa #W# de un nodo #x# en el grafo
// #G#. Se mantenienen dos conjuntos #W# (los vertices ya
// visitados) y #F# el frente que esta avanzando. Inicialmente
// #W=F={x}#. Ahora para calcular el siguiente frente hacemos
// #Q  = \bigcup_{n\in  F} G[n]#, (vecinos de #F# )
// #F = Q-W#, (nuevo frente)
// #W = W \cup F#, (actualiza #Q#)
// El algoritmo termina cuando #F# queda vacio. 
void connected_to(map<int,set<int> > &G, 
                  int x,set<int> &W) {
  // Inicializa F y W
  set<int> F;
  F.insert(x);
  W.clear();
  W.insert(x);

  // Lazo principal, en cada ejecucion de este lazo el frente
  // avanza una capa de vecinos. 
  while(!F.empty()) {
    // Arma Q, el conjunto de los vecinos de los
    // nodos en F
    set<int> Q;
    set<int>::iterator n = F.begin();
    while (n!=F.end()) {
      set<int> &Gx = G[*n], tmp;
      set_union(Q.begin(),Q.end(),
                Gx.begin(),Gx.end(),
                inserter(tmp,tmp.end()));
      swap(Q,tmp);
      n++;
    }

    // Calcula el nuevo frente F = Q - W
    set<int> tmp;
    set_difference(Q.begin(),Q.end(),
                   W.begin(),W.end(),
                   inserter(tmp,tmp.end()));
    swap(tmp,F);
    
    // Calcula el nuevo acumulado W = W \cup F
    tmp.clear();
    set_union(W.begin(),W.end(),
              F.begin(),F.end(),
              inserter(tmp,tmp.end()));
    swap(tmp,W);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

// Otra version de `connected_to', mas simple pero menos
// eficiente. Tomamos inicialmente el acumulado `W={x}'.  A
// partir de ahi vamos calculando `Wnew' el conjunto de
// todos los vertices connectados a W y despues W=Wnew. El
// algoritmo termina cuando Wnew = W
void connected_to2(map<int,set<int> > &G, 
                   int x,set<int> &W) {
  // Inicializa `W'
  W.clear();
  W.insert(x);
  while(1) {
    // Calcula Wnew, recorriendo todos los elementos de `W'
    int m = W.size();
    set<int>::iterator q = W.begin();
    set<int> Wnew;
    while (q!=W.end()) {
      // Agrega todos los conectados a `*q' a `Wnew'
      set<int> &ngbq = G[*q++];
      set_union(W.begin(),W.end(),
                ngbq.begin(),ngbq.end(),
                inserter(Wnew,Wnew.end()));
    }
    // Verifica si el acumulado crecio o no. Si no crecio
    // quiere decir que ya tenemos en `W' toda la
    // componente conexa. 
    if (Wnew.size()==W.size()) break;
    swap(Wnew,W);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Determina todas las componentes conexas de G, en la lista
// de conjuntos D. Para esto inicializamos un conjunto
// not_visited=V, es decir con todos los vertices del grafo,
// e ir tomando un elemento `x' de `not_visited', calcular
// su componente conexa `vx' y eliminar `vx' de
// `not_visited'. El algoritmo termina cuando `not_visited'
// queda vacio.
void connected(map<int,set<int> > &G, 
               list<set<int> > &D) {
  // Conjuntos de los nos visitados. Inicialmente es igual al
  // conjunto de todos los vertices de `G', es decir de las claves
  // de la correspondencia. 
  set<int> not_visited;
  map<int,set<int> >::iterator q = G.begin();
  while (q!=G.end()) {
    not_visited.insert(q->first);
    q++;
  }
  // print_set(not_visited,"not_visited");

  // En cada ejecucion del lazo toma un element de
  // `not_visited' calcula su componente conexa `sx' y la
  // agrega a `D'. A su vez los elementos de `sx' son eliminados
  // de `V'. 
  while (!not_visited.empty()) {
    // Toma un elemento de `not_visited'
    int x = *not_visited.begin();
    // Inserta un conjunto vacio en `D'. Esta sera la
    // nueva componente conexa. 
    D.insert(D.begin(),set<int>());
    set<int> &sx = *D.begin();

    // Calcula la componente conexa con `connected_to()'
    connected_to(G,x,sx);

    // Saca los elementos de `sx' de `not_visited' 
    set<int> tmp;
    set_difference(not_visited.begin(),not_visited.end(),
                   sx.begin(),sx.end(),
                   inserter(tmp,tmp.end()));
    swap(tmp,not_visited);
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
#if 0
  map<int,set<int> > G;
  set<int> s;
  s.clear(); s.insert(2); G[1] = s;
  s.clear(); s.insert(1); G[2] = s;

  s.clear(); s.insert(4); G[3] = s;
  s.clear(); s.insert(3); G[4] = s;

  s.clear();
  connected_to(G,1,s);
  print_set(s,"connected to 1");

  s.clear();
  connected_to(G,1,s);
  print_set(s,"connected to 2");

  s.clear();
  connected_to(G,3,s);
  print_set(s,"connected to 3");

  s.clear();
  connected_to(G,4,s);
  print_set(s,"connected to 4");
#else
  int N = 10, M=5;
  map<int,set<int> > G;
  vector<int> v(N);
  for (int j=0; j<N; j++) v[j] = j;
  random_shuffle(v.begin(),v.end());

  int k=0, loop=0;
  while (k<N) {
    int m = 1+rand()%(2*M);
    if (k+m>N) m = N-k;
    // Next cycle is in range k+[0,n)
    printf("loop %d, vertices: ",loop++);
    for (int j=0; j<m; j++) {
      int k0 = k+j;
      printf(" %d",v[k0]);
      int km1 = k + (j-1+m) % m;
      int kp1 = k + (j+1) % m;
      set<int> &Gk = G[v[k0]];
      // printf("link %d -> {%d,%d}\n",v[k0],v[km1],v[kp1]);
      Gk.insert(v[km1]);
      Gk.insert(v[kp1]);
    }
    printf("\n");
    k += m;
  }

#endif

  map<int, set<int> >::iterator q = G.begin();
  while (q!=G.end()) {
    printf("%d -> ",q->first);
    print_set(q->second);
    q++;
  }

  list<set<int> > D;
  connected(G,D);
  list<set<int> >::iterator r = D.begin();
  while (r!=D.end()) {
    print_set(*r++,"disc graph");
  }
}
