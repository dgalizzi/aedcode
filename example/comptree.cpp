//__INSERT_LICENSE__
// $Id$

#include <list>
#include <cstdio>
#include "./btree.h"
#include "./btreetools.h"
#include "./util.h"

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Se define una relaci\'on de orden
   entre \'arboles binarios de enteros de la siguiente forma: 
   #A<B# si #a<b#, o bien ({\tt a=b} y {\tt Ai < Bi}), o 
   bien ({\tt a=b} y #Ai=Bi# y {\tt Ad<Bd}), donde 
   #a#, #b# son las ra\'{\i}ces y #Ai#, #Ad#, #Bi#, #Bd# 
   son los sub\'arboles izquierdos y derechos de #A# y #B#. 
   Consigna: Escribir una funci\'on 
   #bool es_menor(tree<int> &A,tree<int> &B)# que retorna
   verdadero si #A < B#. 
   [Tomado en el 2do parcial 26/5/2005]. 
   keywords: arbol binario

   FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool es_menor(btree<int> &T1,btree<int>::iterator n1,
	      btree<int> &T2,btree<int>::iterator n2) {
  // Si los dos estan vacios, entonces no cae en
  // ninguno de los casos especificados y debe
  // retornar false. 
  if (n1==T1.end() && n2==T2.end()) return false;
  // Si `n1==end()' y `n2!=end()' entonces
  // `*n1<*n2' y debe retornar `true'. 
  if (n1==T1.end()) return true;
  // Si `n1!=end()' y `n2==end()' entonces
  // `*n1>*n2' y no entra en ninguno de los casos,
  // por lo tanto debe retornar `false'. 
  if (n2==T2.end()) return false;
  // Las dos raices son dereferenciables.
  // Si son distintas ya puede retornar un valor. 
  if (*n1 < *n2) return true;
  if (*n1 > *n2) return false;

  // Si llega aqui, las dos raices son dereferenciables
  // e iguales. Hay que comparar los arboles de los hijos. 

  // Si `Ai' y `Bi' son diferentes retornar un valor...
  if (es_menor(T1,n1.left(),T2,n2.left()))
    return true;
  if (es_menor(T2,n2.left(),T1,n1.left()))
    return false;
  // ... finalmente retorna el valor de comparacion
  // de los hijos derechos. 
  return es_menor(T1,n1.right(),T2,n2.right());
}

// `wrapper'
bool es_menor(btree<int> &T1,btree<int> &T2) {
  return es_menor(T1,T1.begin(),T2, T2.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Cuando se define una relacion de orden vimos que basta
// con definir <, >, <= o >=.  Una alternativa es una
// funcion `comp(a,b)' que retorna -1 si T1<T2, 0 si T1==T2,
// +1 si T1>T2. (En Perl es el operador `<=>').
// Esta funcion seria el operador `comp' para
// arboles binarios. Ademas, esta implementacion
// permite pasar una funcion de comparacion
// (programacion funcional)
int comp_btree(btree<int> &T1,btree<int>::iterator n1,
	    btree<int> &T2,btree<int>::iterator n2,
	    int (*comp)(int x,int y)) {
  // Si son Lambda => son iguales. 
  if (n1==T1.end() && n2==T2.end()) return 0;
  // Si `n1==end()' y `n2!=end()'
  // entonces `*n1<*n2'. 
  // debe retornar -1. 
  if (n1==T1.end()) return -1;
  // Si `n1!=end()' y `n2==end()'
  // entonces `*n1>*n2'. 
  if (n2==T2.end()) return +1;
  // Si `comp(*n1,*n2)!=0' entonces debe
  // retornar el valor de `comp'
  int v = comp(*n1,*n2);
  if (v) return v;
  // Si `comp_btree(Ai,Bi) != 0' entonces debe
  // retornar el valor.
  v = comp_btree(T1,n1.left(),T2,n2.left(),comp);
  if (v) return v;
  // Retorna el valor `comp_btree(Ai,Bi) != 0'
  return comp_btree(T1,n1.right(),T2,n2.right(),comp);
}

// `wrapper'
int comp_btree(btree<int> &T1, btree<int> &T2,
	    int (*comp)(int x,int y)) {
  comp_btree(T1,T1.begin(),T2,T2.begin(),comp);
}

// Funcion de comparacion para enteros. 
int comp(int x,int y) {
  return (y<x) - (x<y);
}

// Funcion de comparacion para enteros,
// correspondiente a la relacion de orden (debil)
// |a|<|b|
int comp_abs(int x,int y) {
  int yy = abs(y);
  int xx = abs(x);
  return (yy<xx) - (xx<yy);
}

int M=5;

int f(int x) { return x-M/2; }

bool equalp(btree<int> &A, btree<int>::iterator a, 
	    btree<int> &B, btree<int>::iterator b, 
	    bool (*eq)(int x,int y)) {
  if ((a == A.end()) != (b == B.end())) return false;
  if (a == A.end()) return true;
  if (!eq(*a,*b)) return false;
  return equalp(A,a.left(),B,b.left(),eq) &&
    equalp(A,a.right(),B,b.right(),eq);
}

bool equalp(btree<int> &A, btree<int> &B, 
	    bool (*eq)(int x,int y)) {
  return equalp(A,A.begin(),B,B.begin(),eq);
}

bool odd(int x) { return x %2; }
bool equal(int x,int y) { return x==y; }

int main() {
#if 1
  const int N=10000;
  typedef btree<int> tree_t;
  typedef tree_t::iterator node_t;
  typedef list<tree_t> list_t;
  typedef list_t::iterator iter_t;
  list_t L;
  tree_t A;
  // Genera una lista de `N' arboles.
  // La lista esta ordenada de aceuerdo
  // a `es_menor'
  for (int j=0; j<N; j++) {
    A.clear();
    double p=0.2;
    make_random_btree(A,M,p);
    apply(A,f);
    iter_t Q = L.begin();
    while (Q!=L.end() && !es_menor(A,*Q)) {
      // Se chequea consistencia entre `es_menor'
      // y `comp_btree'.
      assert(comp_btree(*Q,A,comp) == 
	     (es_menor(A,*Q)-es_menor(*Q,A)));
      Q++;
    }
    // Aqui se hace una copia 
    L.insert(Q,A);
  }
  
  // Imprime todos los arboles en forma ordenada
  iter_t Q = L.begin();
  while (Q!=L.end()) {
    Q->lisp_print();
    printf("\n");
    Q++;
  }

  // Verifica transitividad. 
  // Si `es_menor' y `comp_btree' representan
  // relaciones de orden, entonces se puede comparar
  // cualquier par de arboles Q,R tal que Q esta antes
  // que R en la lista y debe
  // ser Q <= R
  Q = L.begin();
  while (Q!=L.end()) {
    iter_t R = Q;
    R++;
    while (R!=L.end()) {

      if (es_menor(*R,*Q)) {
	printf("error!!!: Q>R segun es_menor()!! Q: ");
	Q->lisp_print();
	printf("\nQ: ");
	R->lisp_print();
	printf("\n");
      }

      if (comp_btree(*Q,*R,comp)>0) {
	printf("error!! Q>R segun comp_btree()!! Q: ");
	Q->lisp_print();
	printf("\nQ: ");
	R->lisp_print();
	printf("\n");
      }
      R++;
    }
    Q++;
  }

#else
  const int N=10;
  btree<int> A,B;
  for (int j=0; j<N; j++) {
    A.clear();
    B.clear();
    double p=0.2;
    make_random_btree(A,M,p);
    apply(A,f);
    make_random_btree(B,M,p);
    apply(B,f);
    printf("-----------------\nA, B: \n");
    A.lisp_print();
    printf("\n");
    B.lisp_print();
    printf("\n");
    printf("A==B? %d\n",equalp(A,B,equal));
  }
#endif
}
