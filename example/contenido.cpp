// $Id$
/* COMIENZO DE DESCRIPCION

   Escribir una funci\'on predicado 
   {\tt bool contenido(btree<int> \&A, btree<int> \&B);}
   que retorna verdadero si la estructura del \'arbol binario {\tt A} 
   esta ``contenido'' dentro de la de {\tt B} y las etiquetas
   correspondientes de {\tt A} son menores que las de {\tt B+}. 
   [Tomado en el examen 2do parcial del 27/5/2004].
   keywords: arbol binario
  
  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
/* Por Ejemplo, si 
   T1=(1 (2 3 .) (5 2 4)), 
   T2=(0 2 (3 2 .)), 
   T3=(3 2 (3 2 .)) y 
   T4=(0 (2 . 3) (3 2 .)), 

   entonces

   contenido(T2,T1) retorna true
   contenido(T3,T1) retorna false
   contenido(T4,T1) retorna false

   En los casos que debe retornar false, el nodo que viola la condici\'on
   est\'a marcado. Se sugiere escribir una funci\'on auxiliar recursiva.
*/
// --------------------------!----------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_btree.cpp
//        icc -w -c contenido.cpp
//        icc -w -o contenido.exe contenido.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_btree.cpp
//        g++ -w -c contenido.cpp
//        g++ -w -o contenido.exe contenido.o util.o util_btree.o
//
// -------------------------------------------------------------------
#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
bool contenido(btree<int> &A,btree<int>::iterator na,
	       btree<int> &B,btree<int>::iterator nb) {
  if (na==A.end()) return true;
  if (nb==B.end()) return false;
  if (*na>*nb) return false;
  if (!contenido(A,na.left(),B,nb.left())) return false;
  if (!contenido(A,na.right(),B,nb.right())) return false;
  return true;
}
bool contenido(btree<int> &A,btree<int> &B) {
  return contenido(A,A.begin(),B,B.begin());
}

// -------------------------------------------------------------------
int main () {
  btree <int> A, B;
  
  for (int j=0; j<10; j++) {
    A.clear();
    make_random_btree (A, 10, 0.8);
    B=A;
    btree<int>::iterator n = B.begin();
    while(n!=B.end()) 
      n = (drand()>0.5 ? n.left() : n.right());
    B.insert(n,irand(10));
    cout << "A: " << endl;
    A.lisp_print();
    cout << endl;

    cout << "B: " << endl;
    B.lisp_print();
    cout << endl;

#define CONT(A,B) cout << #A " contenido en " #B \
    ": " << (contenido(A,B) ? "si" : "no") << endl;
    CONT(A,A);
    CONT(A,B);
    CONT(B,A);
    CONT(B,B);
  }

  cout << "-----------------------------" << endl;
  double prob=0.3;
  for (int j=0; j<10; j++) {
    cout << "-----\n";
    A.clear();
    make_random_btree (A, 3, prob);
    cout << "A: " << endl;
    A.lisp_print();
    cout << endl;
    B.clear();
    make_random_btree (B, 10, 3.0*prob);
    cout << "B: " << endl;
    B.lisp_print();
    cout << endl;    
    CONT (A,B);
  }

  cout << endl ;
  return 0 ;
} // end main
// -------------------------------------------------------------------
