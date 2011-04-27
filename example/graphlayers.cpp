// $Id$

/* 
   COMIENZO DE DESCRIPCION 
   
   __USE_WIKI__
   Dado un grafo #vector<set<int>> G# y un vertice de
   partida #x# se desea determinar la estructuras de capas
   de vecinos de #G# alrededor de #x# definida de la
   siguiente forma: la capa 0 es #{x}#, la capa 1 son los
   vecinos de #x#. A partir de alli la capa #n>=2# esta
   formada por los vecinos de los nodos de la capa #n-1#
   (es decir la _adyacencia_ de la capa) pero que no estan
   en las capas anteriores (en realidad basta con verificar
   que no esten en las capas #n-1# ni #n-2#). 
   [Tomado en tercer parcial 22-NOV-2007].
   keywords: conjunto
    
   FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <iostream>
#include <vector>
#include <set>
#include "./util.h"
using namespace std ;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void mklayers(vector< set<int> > &graph,
            int x,
            vector< set<int> > &layers) {
  layers.clear();
  layers.push_back(set<int>());
  layers.back().insert(x);
  int jlay=0;
  while (1) {
    layers.push_back(set<int>());
    set<int> 
      &newlay = layers[jlay+1],
      &layer = layers[jlay];
    set<int>::iterator q = layer.begin();
    while (q!=layer.end()) {
      set<int> &ngbrs = graph[*q];
      set<int>::iterator r = ngbrs.begin();
      while (r!=ngbrs.end()) {
        if (layer.find(*r)!=layer.end()) continue;
        if (jlay==0) newlay.insert(*r);
        else {
          set<int> &inner = layers[jlay-1];
          if (inner.find(*r)==inner.end()) {
            newlay.insert(*r);
          }
        }
        r++;
      }
      q++;
    }
    if (newlay.empty()) break;
    jlay++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void mk_adjncy(vector< set<int> > &G,
               set<int> &front, set<int> &adjncy) {
  set<int>::iterator p = front.begin();
  adjncy.clear();
  set<int> tmp;
  while (p!=front.end()) {
    set_union(adjncy,G[*p++],tmp);
    adjncy = tmp;
  }
  set_difference(adjncy,front,tmp);
  adjncy = tmp;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void mklayers2(vector< set<int> > &G,
               int x,
               vector< set<int> > &layers) {
  layers.clear();
  layers.push_back(set<int>());
  layers.back().insert(x);
  
  layers.push_back(set<int>());
  layers[1] = G[x];

  int next=2;
  set<int> tmp,newlayer;
  while (1) {
    mk_adjncy(G,layers[next-1],tmp);
    set_difference(tmp,layers[next-2],newlayer);
    if (newlayer.empty()) break;
    layers.push_back(newlayer);
    next++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void print_layers(vector< set<int> > &layers) {
  for (int j=0; j<layers.size(); j++) {
    printf("layer[%d] = {",j);
    set<int> &lay = layers[j];
    set<int>::iterator q = lay.begin();
    while(q!=lay.end()) {
      printf("%d ",*q);
      q++;
    }
    printf("}\n");
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int modulo(int j,int n) {
  int k = j%n;
  if (k<0) k += n;
  return k;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  int N=10;
  vector< set<int> > G(N),layers;
  for (int j=0; j<N; j++) {
    G[j].insert((j+1)%N);
    G[j].insert((j+N-1)%N);
  }
  mklayers(G,0,layers);
  printf("---------------------\n");
  printf("1D cyclic grid, N %d, using algo: mklayers\n",N);
  print_layers(layers);

  mklayers2(G,0,layers);
  printf("---------------------\n");
  printf("1D cyclic grid, N %d, using algo: mklayers2\n",N);
  print_layers(layers);

  int Nvrtx = N*N;
  G.clear();
  G.resize(N*N);
  for (int j=0; j<N; j++) {
    for (int k=0; k<N; k++) {
      int vrtx=k*N+j, ngbr;
      set<int> &ngbrs = G[vrtx];
      if (k>0) {
        ngbr = modulo((k-1)*N+j,Nvrtx);
        ngbrs.insert(ngbr);
      }
      if (k<N-1) {
        ngbr = modulo((k+1)*N+j,Nvrtx);
        ngbrs.insert(ngbr);
      }
      if (j<N-1) {
        ngbr = modulo(k*N+j+1,Nvrtx);
        ngbrs.insert(ngbr);
      }
      if (j>0) {
        ngbr = modulo(k*N+j-1,Nvrtx);
        ngbrs.insert(ngbr);
      }
    }
  }

  mklayers(G,0,layers);
  printf("---------------------\n");
  printf("2D non-cyclic grid, N %d, usigng algo: mklayers\n",N);
  print_layers(layers);

  mklayers2(G,0,layers);
  printf("---------------------\n");
  printf("2D non-cyclic grid, N %d, usigng algo: mklayers2\n",N);
  print_layers(layers);

}
