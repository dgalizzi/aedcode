// $Id$
/* COMIENZO DE DESCRIPCION

   [Tomado en el 2do parcial del 27/5/2004].
   keywords: arbol orientado

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
#include <cstdarg>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
tree<int>::iterator 
graph2tree(map<int, list<int> > &G, int root,
           tree<int> &T, tree<int>::iterator n) {
  assert(n==T.end());
  n = T.insert(n,root);
  list<int> &sons = G[root];
  list<int>::iterator q = sons.begin();
  tree<int>::iterator p = n.lchild();
  while (q != sons.end()) {
    p = graph2tree(G,*q++,T,p);
    p++;
  }
  return n;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void graph2tree(map<int, list<int> > &G, 
                tree<int> &T) {
  // Buscar la raiz. Para eso recorremos los padres (claves
  // de G) y buscamos cual no esta en la lista de hijos
  set<int> fathers, sons, tmp;
  map<int, list<int> >::iterator q = G.begin();
  while (q!=G.end()) {
    fathers.insert(q->first);
    tmp.clear();
    set_union(q->second.begin(),q->second.end(),
              sons.begin(),sons.end(),
              inserter(tmp,tmp.end()));
    swap(tmp,sons);
    q++;
  }

  // Saca de `fathers' los hijos, el unico que deberia
  // quedar es la raiz
  tmp.clear();
  set_difference(fathers.begin(),fathers.end(),
                 sons.begin(),sons.end(),
                 inserter(tmp,tmp.end()));
  assert(tmp.size()==1);
  int root = *tmp.begin();
  // printf("root of tree is %d\n",root);

  graph2tree(G,root,T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void add_to_list(list<int> &l,int term,...) {
  va_list elems;
  va_start(elems,term);
  while (1) {
    int x = va_arg(elems, int);
    if (x==term) break;
    l.push_back(x);
  }
  va_end(elems);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  map<int, list<int> > G;
  list<int> tmp;
  // tree is (2 (7 12 (6 15 11)) (5 (9 4)))
  tmp.clear();
  add_to_list(tmp,-1,7,5,-1);
  G[2] = tmp;

  tmp.clear();
  add_to_list(tmp,-1,12,6,-1);
  G[7] = tmp;

  tmp.clear();
  add_to_list(tmp,-1,15,11,-1);
  G[6] = tmp;

  tmp.clear();
  add_to_list(tmp,-1,9,-1);
  G[5] = tmp;

  tmp.clear();
  add_to_list(tmp,-1,4,-1);
  G[9] = tmp;

  tree<int> T;
  graph2tree(G,T);
  
  T.lisp_print();
  printf("\n");
  return 0;
}
