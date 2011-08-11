// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Un arbol binario #T# es balanceado, si para cada nodo #n#
   del arbol la diferencia entre la altura de la rama
   izquierda y derecha es a lo sumo 1. Ademas se puede
   definir el desbalance maximo es la maxima diferencia (en
   valor absoluto) sobre todos los nodos de las alturas de
   sus dos hijos. Escribir una funcion 
   #int max_disbalance(btree<int> &T);#
   que calcula el desbalance maximo del arbol #T#. 

  FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#include <cstdio>
#include <iostream>

#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

typedef btree<int>::iterator node_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int max_disbalance(btree<int> &T,node_t n,int &height) {
  // Esta es la funcion recursiva. Retorna el maximo
  // desbalance para el subarbol del nodo `n' y su
  // altura por `height'
  if (n==T.end()) {
    // El arbol vacio tiene altura -1
    // y desbalance 0
    height = -1;
    return 0;
  }
  // `hl,hr' son las alturas de los hijos
  // y `mdl,mdr' sus desbalances. 
  int hl, hr, mdl, mdr, md;
  mdl = max_disbalance(T,n.left(),hl);
  mdr = max_disbalance(T,n.right(),hr);

  // La altura de `n' es el maximo de las alturas
  // de los hijos + 1
  height = (hl>hr ? hl : hr) + 1;
  
  // El maximo desbalance se puede deber al desbalance de
  // este nodo abs(hr-hl), o de los subarboles de sus hijos.
  // Hay que tomar el maximo de los 3. 
  md = abs(hl-hr);
  if (mdl>md) md = mdl;
  if (mdr>md) md = mdr;

  return md;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
int max_disbalance(btree<int> &T) {
  int height;
  return max_disbalance(T,T.begin(),height);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main () {
  btree<int> T;
  // Genera 10 arboles aleatorios y les
  // calcula el desbalance
  for (int j=0; j<20; j++) {
    make_random_btree(T,10,0.7);
    printf("T: ");
    T.lisp_print();
    printf(", max disbalance %d\n----------\n",max_disbalance(T));
  }
}
