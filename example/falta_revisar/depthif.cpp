// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Dados un arbol binario #T# encontrar la maxima profundidad de
   un nodo tal que satisface un predicado dado. 
   [Tomado en el 2do parcial del 2009-10-27].
   keywords: arbol binario

  FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#include <cstdio>
#include <iostream>

#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

typedef bool (* pred_t)(int);

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int depth_if(btree<int> &T,btree<int>::iterator n, pred_t pred) {
  if (n==T.end()) return -1;
  int dl,dr,dn,depth;
  dl = depth_if(T,n.left(),pred);
  dr = depth_if(T,n.right(),pred);
  depth = (dl>dr? dl : dr);
  return (depth>=0? depth+1 : pred(*n)? 0 : -1);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
int depth_if(btree<int> &T,pred_t pred) { 
  return depth_if(T,T.begin(),pred);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool odd(int x) { return x%2; }
bool even(int x) { return !odd(x); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main () {
  btree<int> T;
  for (int j=0; j<10; j++) {
    T.clear();
    make_random_btree(T,10,0.5);
    printf("T: "); T.lisp_print(); 
    printf(", depth even: %d, odd %d\n",
           depth_if(T,even), depth_if(T,odd));
  }

  return 0;
}
