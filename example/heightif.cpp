// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__

   Dados un arbol binario #T# encontrar la maxima altura de
   un nodo tal que satisface un predicado dado. 

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
int height_if(btree<int> &T,btree<int>::iterator n,
              pred_t pred, int &h) {
  if (n==T.end()) { h = -1; return -1; }

  int hif,hifr,hifl,hr,hl;
  hifl = height_if(T,n.left(),pred,hl);
  hifr = height_if(T,n.right(),pred,hr);
  h = (hl>hr ? hl: hr) + 1;

  hif = (hifl>hifr ? hifl : hifr);
  if (pred(*n) && h>hif) hif=h;
  return hif;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
int height_if(btree<int> &T,pred_t pred) { 
  int h;
  return height_if(T,T.begin(),pred,h);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool even(int x) { return !(x%2); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main () {
  btree<int> T;
  for (int j=0; j<10; j++) {
    T.clear();
    make_random_btree(T,10,0.5);
    printf("T: "); T.lisp_print(); 
    printf(", height even: %d\n",height_if(T,even));
  }

  return 0;
}
