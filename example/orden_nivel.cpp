// $Id$
/* COMIENZO DE DESCRIPCION
  
  El listado en orden de nivel de los nodos de un \'arbol lista
  primero la raiz, luego todos los nodos de profundidad 1, despu\'es
  todos los de profundidad 2, y asi sucesivamente. Los nodos que
  est\'en en la misma profundidad se listan en orden de izquierda a
  derecha.  Escribir una funci\'on 
  {\tt void orden_de_nivel (tree <int> \&t)} para listar los nodos 
  de un \'arbol en orden de nivel. 
  keywords: arbol orientado
  
  FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_tree.cpp
//        icc -w -c orden_nivel.cpp
//        icc -w -o orden_nivel.exe orden_nivel.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_tree.cpp
//        g++ -w -c orden_nivel.cpp
//        g++ -w -o orden_nivel.exe orden_nivel.o util.o util_tree.o
//
// -------------------------------------------------------------------
#include <iostream>
#include <queue>
#include "../include/tree.h"
#include "util.h"
#include "util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
// También conocido como "recorrido a lo ancho"
void orden_de_nivel(tree<int> &t) {
  queue <node_t> q;
  node_t  n,n1,c;
  n=t.begin();
  if (n==t.end()) return;
  q.push(n);
  cout << *n << "  ";
  while (!q.empty()) {
    n1=q.front();
    q.pop();
    c=n1.lchild();
    while (c!=t.end()){
      cout << *c << "  ";
      q.push(c);
      c++;
    }
  }
}

// -------------------------------------------------------------------
int main () {
  tree<int> t;
  for (int j=0;j<1;j++) {
    t.clear();
    make_random_tree(t,10,2);
    cout << "Arbol inicial: "<< endl;
    print_tree(t);
    cout << "Listado en orden de nivel: " << endl;
    orden_de_nivel(t);
    cout << endl;
  }
  cout << endl;
  return 0;
}
// -------------------------------------------------------------------
