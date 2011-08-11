// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dado un grafo #G#, y un arbol #T#, decimos que #T# "expande" a
   #G# si la raiz #n# de #T# es un vertice de #G#, y los caminos de
   #T# permiten llegar desde #n# hasta cualquier otro nodo de #G#.
   Escribir una funcion #bool is_spng_tree(G,T)# (por
   "is-spanning-tree") que determina si #T# expande a #G#.
   [Tomado en el 3er parcial del 2009-11-27].
   keywords: conjunto, correspondencia

   FIN DE DESCRIPCION */
// -------------------------------------------------------------------
#include <cstdarg>
#include <cstdio>

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

typedef map<int,set<int> > graph_t;

// Primero escribimos una tree_nodeset(tree<int> &T,set<int>
// &nodeset); que retorna true si todos los nodos de T son
// distintos y si ese es el caso retorna por !+nodeset+ el
// conjunto de nodos de !+T+. \emph{Ayuda:} Probablemente
// esto requiere hacerlo en forma recursiva sobre el arbol.
//   
// Despues escribimos una funcion !+void
// graph_vrtxset(map<int,set<int>> &G,set<int> &vrtxset);+
// que retorna por !+vrtxset+ el conjunto de vertices de
// !+G+.
//   
// Finalmente con la ayuda de las dos funciones auxiliares
// previas: 1) Comprobar que los nodos de !+T+ son
// unicos. (esto lo hace tree_nodeset).  2) Comprobar que el
// conjunto de nodos de !+T+ es igual al de vertices de
// !+G+. 3) Verificar que las aristas de !+T+ (es
// decir los pares padre-hijo) estan contenidos en
// !+G+. Para esto escribimos una funcion recursiva
// sobre el arbol check_edges(...)

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool tree_nodeset(tree<int> &T,tree<int>::iterator n,
                  set<int> &nodeset) {
  if (nodeset.find(*n)!=nodeset.end()) return false;
  nodeset.insert(*n);
  tree<int>::iterator q = n.lchild();
  while (q!=T.end()) 
    if (!tree_nodeset(T,q++,nodeset)) return false;
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool tree_nodeset(tree<int> &T,set<int> &nodeset) {
  nodeset.clear();
  if (T.begin()==T.end()) return true;
  return tree_nodeset(T,T.begin(),nodeset);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void graph_vrtxset(graph_t &G,set<int> &vrtxset) {
  vrtxset.clear();
  graph_t::iterator q = G.begin();
  while (q!=G.end()) vrtxset.insert(q++->first);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool check_edges(graph_t &G,tree<int> &T,
                 tree<int>::iterator p) {
  if (p==T.end()) return true;
  set<int> &ngbrs = G[*p];
  tree<int>::iterator q = p.lchild();
  while (q!=T.end())
    if (ngbrs.find(*q++)==ngbrs.end()
        || !check_edges(G,T,q)) return false;
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool is_spng_tree(graph_t &G,tree<int> &T) {
  set<int> nodeset, vrtxset;
  if (!tree_nodeset(T,nodeset)) return false;
  graph_vrtxset(G,vrtxset);
  if (nodeset!=vrtxset) return false;
  return check_edges(G,T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Esta es una segunda version que no usa funciones
// auxiliares, para esto solo usa un argumento auxiliar
// set<int> visited que trackea los nodos a medida que va
// recorriendo el arbol. De esta forma se hacen todos los
// chequeos al mismo tiempo.
bool is_spng_tree2(graph_t &G,tree<int> &T, 
                 tree<int>::iterator n,set<int> &visited) {
  // `n' ya fue visitado, asi que el arbol pasa dos veces
  // por el mismo nodo
  if (visited.find(*n)!=visited.end()) return false;
  visited.insert(*n);

  // Verifica que el nodo este en el grafo.
  // Si el nodo no tiene vecinos en el grafo
  // la entrada deberia estar, apuntando al
  // conjunto vacio.
  if (G.find(*n)==G.end()) return false;

  // Verifica que cada hijo de n este en su lista de
  // vecinos
  tree<int>::iterator c = n.lchild();
  set<int> &n_ngbrs = G[*n];
  while (c!=T.end()) 
    if (n_ngbrs.find(*c++)==n_ngbrs.end()) return false;

  // Verifica que el subarbol de cada uno de los
  // `c' este contenido en `G'
  c = n.lchild();  
  while (c!=T.end()) 
    if (!is_spng_tree2(G,T,c++,visited)) 
      return false;

  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
bool is_spng_tree2(graph_t &G,tree<int> &T) {
  printf("T size: %d\n",T.size());
  if (T.size()!=G.size()) return false;
  if (T.begin()==T.end()) return true;
  set<int> visited;
  return is_spng_tree2(G,T,T.begin(),visited);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void graph_print(graph_t &G) {
  graph_t::iterator q = G.begin();
  while (q!=G.end()) {
    printf("G[%d]: ",q->first);
    set<int> &qngbrs = q->second;
    set<int>::iterator r = qngbrs.begin();
    while (r!=qngbrs.end()) 
      printf("%d ",*r++);
    printf("\n");
    q++;
  }
}

//#define is_spng_tree is_spng_tree2
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#define BP -1
#define EP -2
#define TERM -3
int main() {
  // Load Graph
  graph_t G;
  //  0---1---2
  //  |   |   |
  //  3---4---5
  //  |   |   |
  //  6---7---8
  add_to_set(G[0],TERM,1,3,TERM);
  add_to_set(G[1],TERM,0,2,4,TERM);
  add_to_set(G[2],TERM,1,5,TERM);

  add_to_set(G[3],TERM,0,4,6,TERM);
  add_to_set(G[4],TERM,1,3,5,7,TERM);
  add_to_set(G[5],TERM,2,4,8,TERM);

  add_to_set(G[6],TERM,3,7,TERM);
  add_to_set(G[7],TERM,4,6,8,TERM);
  add_to_set(G[8],TERM,5,7,TERM);

  graph_print(G);
  printf("\n\n");

  // Load tree starting at 0, breadth-first
  // (0 (1 (2 5) (4 (7 8))) (3 6))
  tree<int> T;
  list2treev(T,TERM,BP,EP,
             BP,0,BP,1,BP,2,5,EP,BP,4,BP,7,8,EP,
             EP,EP,BP,3,6,EP,EP,TERM);
  printf("T: ");
  T.lisp_print();
  printf("\nis T a spanning tree for G? : %d\n\n",
         is_spng_tree(G,T));

  // Load tree traverse like list, starting as 0
  // (0 (1 (2 (5 (4 (3 (6 (7 (8)))))))))
  T.clear();
  list2treev(T,TERM,BP,EP,
             BP,0,BP,1,BP,2,BP,5,BP,4,BP,3,BP,
             6,BP,7,BP,8,EP,EP,EP,EP,EP,EP,EP,EP,EP,TERM);
  printf("T: ");
  T.lisp_print();
  printf("\nis T a spanning tree for G? : %d\n\n",
         is_spng_tree(G,T));

  // Load tree (should fail, because 4 is not connected to 0
  // (0 (3 6) (4 7 (5 8)) (1 2))
  T.clear();
  list2treev(T,TERM,BP,EP,
             BP,0,BP,3,6,EP,BP,4,7,BP,5,8,EP,EP,BP,1,2,EP,EP,TERM);
  printf("T: ");
  T.lisp_print();
  printf("\nis T a spanning tree for G? : %d\n\n",
         is_spng_tree(G,T));

  return 0;
}
