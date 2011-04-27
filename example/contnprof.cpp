// $Id$

/*
  COMIENZO DE DESCRIPCION

  Escribir una funci\'on 
  {\tt int cant\_nodos\_prof(btree<int> \&A, int prof);}
  que retorna el n\'umero de nodos de una \'arbol binario {\tt A}
  que est\'an a profundidad {\tt prof} o mayor. 

  FIN DE DESCRIPCION
*/
// -------------------------------------------------------------------
//  Por ejemplo, 
//  en el caso del \'arbol: (1 (2 3 .) (5 (2 2 6) 4)), 
//
//  cant_nodos_prof(T,0) retorna 8
//  cant_nodos_prof(T,1) retorna 7
//  cant_nodos_prof(T,2) retorna 5
//  cant_nodos_prof(T,3) retorna 2
//  cant_nodos_prof(T,4) retorna 0
//  cant_nodos_prof(T,5) retorna 0
//
//  Se sugiere escribir una funci\'on auxiliar recursiva.
//  [Tomado en el examen 2do parcial del 27/5/2004].
//  keywords: arbol binario

// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_tree.cpp
//        icc -w -c contnprof.cpp
//        icc -w -o contnprof.exe contnprof.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_tree.cpp
//        g++ -w -c contnprof.cpp
//        g++ -w -o contnprof.exe contnprof.o util.o util_btree.o
//
// -------------------------------------------------------------------
#include <iostream>
#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
int cont_nod_prof(btree<int> &A,btree<int>::iterator n,
		  int prof) {
  if (n==A.end()) return 0;
  else return (prof<=0) 
	 + cont_nod_prof (A,n.left(),prof-1) 
	 + cont_nod_prof (A,n.right(),prof-1);
}
int cont_nod_prof(btree<int> &A,int prof) {
  return cont_nod_prof (A,A.begin(),prof);
}

// -------------------------------------------------------------------
int main () {
  btree <int> A, B;
  for (int j=0; j<10; j++) {
    A.clear();
    make_random_btree (A, 10, 0.8);
    cout << "A: " << endl;
    A.lisp_print();
    cout << endl;
    int prof=0;
    while (true) {
      int count = cont_nod_prof(A,prof);
      if (count==0) break;
      cout << count << " nodos a profundidad >= " << prof << endl;
      prof++;
    } // end while
  } // end j
  cout << endl ;
  return 0 ;
}
// -------------------------------------------------------------------
