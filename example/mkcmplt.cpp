// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__ 
   Dados un arbol binario de enteros #T#, realizar las
   modificaciones necesarias para que sea completo, es decir
   un nodo dado o no tiene hijos o tiene los dos,
   manteniendo la suma total de sus nodos. Para esto si un
   nodo #n# tiene un solo hijo #p#, por ejemplo #(n (p R L) .)# 
   entonces sube los subarboles #R# y #L# de ese hijo
   #p#, como subarboles de #n#, es decir queda 
   #(n+p R L)#. 
   Ayuda: Usar la funcion #splice()#.

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
void make_complete(btree<int> &T,node_t n) {
  if (n==T.end()) return;
  // `nl,nr' son los hijos de `n'
  // `l,r' van bajando hasta encontrar un
  // nodo completo es decir para el cual `l,r'
  // son ambos dereferenciables o no. 
  node_t nl = n.left(), nr = n.right(),
    l = nl, r = nr;
  // `flag' indica si el nodo actual es completo
  // o no
  int flag = 0;
  while (l!=T.end() xor r!=T.end()) {
    // En este lazo va bajando hasta encontrar un nodo
    // que SI es completo
    flag = 1;
    // `p' indica cual de los nodos (l o r)
    // es el que es dereferenciable
    node_t p = (l!=T.end() ? l : r);
    // va acumulando el valor de `p' en `n' ya que despues
    // lo va a borrar
    *n += *p;
    l = p.left();
    r = p.right();
  }

  // Si `flag' es verdadero quiere decir que al menos habia
  // un nodo NO completo. `l' y `r' apuntan a las posiciones
  // que corresponden a los hijos del primer nodo completo.
  // OJO que pueden ser ambos no dereferenciables!!
  if (flag) {
    if (l!=T.end()) {
      // Caso que son dereferenciables. Hay que hacer
      // splice de `l,r' a arboles temporarios `L' y `R',
      // eliminar toda la cadena que iba desde el 
      btree<int> L,R;
      T.splice(L.begin(),l);
      T.splice(R.begin(),r);
      // Elimina toda la rama de `nl' o `nr' dependiendo
      // de cual de los dos es dereferenciable
      if (nl!=T.end()) nl = T.erase(nl);
      if (nr!=T.end()) nr = T.erase(nr);
      // Vuelve a hacer splice de los temporarios `L,R'
      nl = T.splice(nl,L.begin());
      nr = T.splice(nr,R.begin());
    } else {
      // Solo hay que hacer el erase, porque `l,r' son
      // no dereferenciables
      if (nl!=T.end()) nl = T.erase(nl);
      if (nr!=T.end()) nr = T.erase(nr);
    }
  }
  make_complete(T,nl);
  make_complete(T,nr);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void make_complete(btree<int> &T) {
  make_complete(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Predicado que determina si el arbol es completo o no.
// Se usa solo para verificar
bool is_complete(btree<int> &T,node_t n) {
  // El arbol vacio es completo
  if (n==T.end()) return true;
  node_t l=n.left(), r=n.right();
  // Si l y n son diferentes (en cuanto a
  // su dereferenciabilidad) entonces ya sabemos que
  // NO es completo
  if (l==T.end() xor r==T.end()) return false;
  // Ambos son `iguales' entonces si son no-dereferenciables
  // quiere decir que es completo
  if (l==T.end()) return true;
  // Si llegamos aca hay que verificar (recursivamente)
  // que ambos hijos son completos
  return is_complete(T,l) && is_complete(T,r);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
bool is_complete(btree<int> &T) {
  return is_complete(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Retorna la suma de los nodos de un arbol.
// Es solo para verificar
int sum(btree<int> &T, node_t n) {
  if (n==T.end()) return 0;
  // Lo hace por recursion, sumando el valor del nodo
  // y la suma de sus hijos.
  return *n + sum(T,n.left()) + sum(T,n.right());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
int sum(btree<int> &T) { return sum(T,T.begin()); }

#define WARN(cond,legend) if ((cond)) printf("!!!!%s!!!!\n",legend);

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main () {
  // Verifica tomando 10 arboles aleatorios.
  btree<int> T;
  for (int j=0; j<10; j++) {
    // Hace el arbol y lo imprime
    make_random_btree(T,10,1.4);
    printf("T: "); T.lisp_print(); printf("\n");
    int sum1 = sum(T);
    printf("is_complete %d, sum %d\n",is_complete(T),sum1);

    printf("makes T = mkcmplt(T)\n");
    make_complete(T);
    printf("T: "); T.lisp_print(); printf("\n");
    int sum2 = sum(T), ok=is_complete(T);
    printf("is_complete %d, sum %d\n",ok,sum2);
    WARN(!ok,"Arbol procesado no es completo");
    WARN(sum1!=sum2,"No se preservo la suma de los arboles");
    printf("--------\n");
  }
  return 0;
}
