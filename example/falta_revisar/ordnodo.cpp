// $Id$
/* COMIENZO DE DESCRIPCION

   __USE_WIKI__
   Escribir una funci\'on predicado 
   #bool ordnodo(tree<int> &A);# que verifica si cada secuencia de
   hermanos del sub\'arbol del nodo #n# (perteneciente
   al \'arbol ordenado orientado #A# est\'an ordenadas
   entre s\'\i{}, de izquierda a derecha. Por ejemplo, para
   el \'arbol #(3 5 (6 1 3) (7 4 5))# deber\'\i{}a
   retornar #true#, mientras que para 
   #(3 9 (6 1 3) (7 4 2))# deber\'\i{}a retornar #false#, ya que
   las secuencias de hermanos #(9 6 7)# y #(4 2)#
   NO est\'an ordenados. Se sugiere el siguiente algoritmo:
   para un dado nodo retornar false si: 1) sus hijos no
   estan ordenados o 2) algunos de sus hijos contiene en su
   sub\'arbol una secuencia de hermanos no ordenada. 
   (recursividad). Caso contrario retorna verdadero. 
   [Tomado en el final del 28/7/2005]. 
   keywords: arbol orientado
  
  FIN DE DESCRIPCION */
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#include <cstdio>
#include <queue>
#include "./tree.h"
#include "./util.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
bool ordnodo(tree<int> &t,tree<int>::iterator n) {
  tree<int>::iterator c = n.lchild(), d;
  // Buscar si hay dos hermanos c, d tales 
  // que *c>*d. 
  if (c==t.end()) return true;
  d = c; d++;
  while (d!=t.end()) {
    if (*d<*c) return false;
    c = d; d++;
  }
  // Verificar que el subarbol de cada hijo
  // satisfaga la condicion. 
  c = n.lchild();
  while (c!=t.end()) 
    if (!ordnodo(t,c++)) return false;
  // Si pasa todas las condiciones entonces
  // retorna verdadero. 
  return true;
}

// -------------------------------------------------------------------
// Funcion `wrapper' llama a la funcion
// rercursiva con los parametros apropiados. 
bool ordnodo(tree<int> &t) {
  if (t.begin()==t.end()) return true;
  return ordnodo(t,t.begin());
}

// -------------------------------------------------------------------
int main () {
  tree<int> A;
  // Genera arboles aleatorios y le aplica
  // el predicado, imprimiendo el resultado. 
  for (int j=0; j<100; j++) {
    A.clear();
    make_random_tree (A, 10, 2);
    printf("A: ");
    A.lisp_print();
    printf(", ordnodo(A) %d\n",ordnodo(A));
  }
}
// -------------------------------------------------------------------
