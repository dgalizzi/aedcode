// $Id$
/* COMIENZO DE DESCRIPCION

Dados dos \'arboles binarios {\tt A} y {\tt B}, escribir una funci\'on 
{\tt tree\_intersection(btree<int> \&A, btree<int> \&B, btree<int> \&C);} 
que devuelve el \'arbol cuya estructura es la intersecci\'on de
las estructuras de {\tt A} y {\tt B} y si adem\'as los valores
correspondientes son iguales. Por ejemplo, si 
{\tt A = (8 (3 6 (7 10 11)) (5 4 .))} y 
{\tt B = (8 (3 6 (9 . 3)) (5 7 .))}. Entonces debe quedar 
{\tt C = (8 (3 6 .) 5)}. 
keywords: arbol binario
FIN DE DESCRIPCION */

// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_btree.cpp
//        icc -w -c treeint.cpp
//        icc -w -o treeint.exe treeint.o util.o util_btree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_btree.cpp
//        g++ -w -c treeint.cpp
//        g++ -w -o treeint.exe treeint.o util.o util_btree.o
//
// -----------------------------------------------------------------
#include <iostream>
#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
// Introducimos una mejora inspirada en la programacion funcional.
// Pasamos un argumento que es una funcion que toma dos argumentos
// de entrada x,y y retorna bool. 
// La funcion retorna un bool que indica si el elemento
// correspondiente debe estar en C, y si es asi retorna
// por referencia en el argumento z el valor del elemento
// a insertar. 
void tree_intersection (btree<int> &A, btree<int>::iterator nA,
                        btree<int> &B, btree<int>::iterator nB,
                        btree<int> &C, btree<int>::iterator nC,
                        bool (*fun) (int x, int y, int &z)) {
  // Si habia algo en C limpiarlo
  nC = C.erase(nC);
  int w;
  // Solo hace algo si los dos nodos no son Lambda y si
  // `fun' retorna verdadero. 
  if (nA != A.end() && nB != B.end() && fun(*nA,*nB,w)) {
    // insertar 
    nC = C.insert(nC,w);
    // Llama recursivamente
    tree_intersection (A,nA.left(),B,nB.left(),
		       C,nC.left(),fun);
    tree_intersection (A,nA.right(),B,nB.right(),
		       C,nC.right(),fun);
  } // end if
} 
// Esta es la funcion "wrapper" correspondiente. 
void  tree_intersection(btree<int> &A, 
               	        btree<int> &B, 
		        btree<int> &C, 
                        bool (*fun) (int x,int y,int &z)) {
  tree_intersection (A, A.begin(),
		     B, B.begin(),
		     C, C.begin(),
		     fun);
}

// -------------------------------------------------------------------
// Esta es otra variante. La funcion `fun' ahora es llamada sobre 
// todos los pares correspondientes `x' en `A' e `y' en 'B'. En los 
// casos en que alguno de los dos es Lambda, entonces el valor pasado
// correspondiente es `undef'. 
void  tree_union (btree<int> &A, btree<int>::iterator nA,
	          btree<int> &B, btree<int>::iterator nB,
                  btree<int> &C, btree<int>::iterator nC,
	          bool (*fun)(int x,int y,int &z),
	          int undef=0) {
  nC = C.erase(nC);
  int w;
  if      (nA == A.end() && nB == B.end()) return;
  else if (nA != A.end() && nB != B.end() && fun (*nA,*nB,w)) {
    nC = C.insert (nC,w);
    tree_union (A, nA.left(), B, nB.left(), C, nC.left(), fun);
    tree_union (A, nA.right(),B,nB.right(), C, nC.right(),fun); } 
  else if (nA == A.end() && fun (undef,*nB,w)) {
    nC = C.insert(nC,w);
    tree_union (A, A.end(), B, nB.left() , C, nC.left(), fun);
    tree_union (A, A.end(), B, nB.right(), C, nC.right(),fun); } 
  else if (nB == B.end() && fun (*nA,undef,w)) {
    nC = C.insert (nC,w);
    tree_union (A, nA.left(), B, B.end(), C, nC.left(), fun);
    tree_union (A, nA.right(), B, B.end(), C, nC.right(), fun);
  } // end if
} 
void  tree_union (btree<int> &A, 
	          btree<int> &B, 
	          btree<int> &C, 
	          bool (*fun) (int x,int y,int &z),int undef=0) {
  tree_union (A, A.begin(), B, B.begin(),
	      C, C.begin(), fun, undef);
} 

// -------------------------------------------------------------------
// Este es el predicado apropiado para obtener
// la interseccion como se pide en el examen. 
bool are_equal (int x,int y,int &z) {
  z = x; 
  return x == y;
}

// -------------------------------------------------------------------
// Este da la interseccion (estructural)
// el minimo entre los valores de A y B
bool min (int x,int y,int &z) {
  z = (x < y ? x : y); 
  return true;
}

// -------------------------------------------------------------------
// Este da la interseccion (estructural)
// el maximo entre los valores de A y B
bool max (int x,int y,int &z) {
  z = (x < y ? y : x); 
  return true;
}

// -------------------------------------------------------------------
// Este filtra los valores de A con la estructura de B
bool mask(int x,int y,int &z) {
  z = x; 
  return true;
}

// -------------------------------------------------------------------
#define UNDEF -1
bool intersect (int x,int y,int &z) {
  z = x; 
  return x != UNDEF && y != UNDEF && x == y;
}

// -------------------------------------------------------------------
int main () {

  btree<int> A,B,C;
  list<int> LA, LB;
  const int BP=-1, EP=-2, NE=-3, EL=-4;

  int la[] = {BP,8,BP,3,6,BP,7,10,11,EP,EP,BP,5,4,NE,EP,EP,EL};
  insertl(LA,la,EL);
  list2btree(A,LA,BP,EP,NE);
  cout << "A: "; A.lisp_print(); cout << endl;

  int lb[] = {BP,8,BP,3,6,BP,9,NE,3,EP,EP,BP,5,7,NE,EP,EP,EL};
  insertl(LB,lb,EL);
  list2btree(B,LB,BP,EP,NE);
  cout << "B: "; B.lisp_print(); cout << endl;

  tree_intersection(A,B,C,are_equal);
  cout << "C = A intersec(=) B: "; C.lisp_print(); cout << endl;

  tree_intersection(A,B,C,min);
  cout << "C = A intersec(min) B: "; C.lisp_print(); cout << endl;

  tree_intersection(A,B,C,max);
  cout << "C = A intersec(max) B: "; C.lisp_print(); cout << endl;

  tree_intersection(A,B,C,mask);
  cout << "C = A intersec(mask) B: "; C.lisp_print(); cout << endl;

  tree_intersection(B,A,C,mask);
  cout << "C = B intersec(mask) A: "; C.lisp_print(); cout << endl;

  tree_union(B,A,C,max,UNDEF);
  cout << "C = B union(max) A: "; C.lisp_print(); cout << endl;

  tree_union(A,B,C,intersect,UNDEF);
  cout << "C = A union(intersect) B: "; C.lisp_print(); cout << endl;

  // Salida: 
  // A: (8 (3 6 (7 10 11)) (5 4 .))
  // B: (8 (3 6 (9 . 3)) (5 7 .))
  // C = A intersec(=) B: (8 (3 6 .) 5)
  // C = A intersec(min) B: (8 (3 6 (7 . 3)) (5 4 .))
  // C = A intersec(max) B: (8 (3 6 (9 . 11)) (5 7 .))
  // C = A intersec(mask) B: (8 (3 6 (7 . 11)) (5 4 .))
  // C = B intersec(mask) A: (8 (3 6 (9 . 3)) (5 7 .))
  // C = B union(max) A: (8 (3 6 (9 10 11)) (5 7 .))
  // C = A union(intersect) B: (8 (3 6 .) 5)

  return 0 ;
} // end main
// -------------------------------------------------------------------
