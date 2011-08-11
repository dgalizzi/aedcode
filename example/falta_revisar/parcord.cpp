// $Id$

/* COMIENZO DE DESCRIPCION
   
  __USE_WIKI__

  Recordemos que un \'arbol es parcialmente ordenado si
  dados dos nodos #m#, #n# tal que #m# es hijo de #n#,
  entonces el valor de #m# es mayor o igual al de #n#.
  Consigna: Escribir un predicado 
  #bool es_parcialmente_ordenado(tree<int> &T,bool (*comp)(int,int)#, 
  que verifica si el \'arbol ordenado
  orientado #T# es parcialmente ordenado con respecto a la
  funci\'on de comparaci\'on #comp()#.
  [Tomado en el examen final 7/7/2005]. 
  keywords: arbol orientado

  FIN DE DESCRIPCION */

#include <cstdio>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool es_parcialmente_ordenado(tree<int> &T, tree<int>::iterator q,
			      bool (*comp)(int,int)) {
  tree<int>::iterator c;
  // Verifica que los valores nodales de los hijos sean mayores
  // o iguales que el de los padres y que los subarboles sean PO. 
  c = q.lchild();
  while (c!=T.end()) {
    if (comp(*c,*q) || 
	!es_parcialmente_ordenado(T,c,comp))
      return false;
    c++;
  }
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool es_parcialmente_ordenado(tree<int> &T,
			      bool (*comp)(int,int)) {
  if (T.begin()==T.end()) return true;
  return es_parcialmente_ordenado(T,T.begin(),comp);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool es_parcialmente_ordenado2(tree<int> &T, tree<int>::iterator q,
			      bool (*comp)(int,int)) {
  tree<int>::iterator c;
  // Verifica que los valores nodales de los hijos sean mayores
  // o iguales que el de los padres
  c = q.lchild();
  while (c!=T.end()) 
    if (comp(*c++,*q)) 
      return false;

  // Verifica que los subarboles de los hijos sean
  // (recursivamente) parc. ord.
  c = q.lchild();
  while (c!=T.end()) 
    if (!es_parcialmente_ordenado2(T,c++,comp)) 
      return false;

  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool es_parcialmente_ordenado2(tree<int> &T,
			      bool (*comp)(int,int)) {
  if (T.begin()==T.end()) return true;
  return es_parcialmente_ordenado2(T,T.begin(),comp);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool int_less(int x,int y) {
  return x < y;
}

bool int_greater(int x,int y) {
  return x > y;
}

bool int_less_abs(int x,int y) {
  return abs(x) < abs(y);
}

// -------------------------------------------------------------------
int main () {

  const int BP=INT_MAX, EP=INT_MAX-1, NE=INT_MAX-2, EL=INT_MAX-3;
  tree <int> A;
  list <int> LA;
  // (3 5 (7 9 10))   Es PO con respecto a <  (less)
  int la1[] = {BP,3,5,BP,7,9,10,EP,EP,EL};

  // (3 5 (-7 9 -10)) Es PO con respecto a |a|<|b|  (less_abs)
  int la2[] = {BP,3,5,BP,-7,9,-10,EP,EP,EL};

  // (7 5 (3 1 0))    Es PO con respecto a >  (greater)
  int la3[] = {BP,7,5,BP,3,1,0,EP,EP,EL};

  for (int j=0; j<3; j++) {
    LA.clear();
    insertl(LA,(j==0? la1 : j==1? la2 : la3),EL);
    A.clear();
    list2tree(A,LA,BP,EP);
    printf("arbol: "); A.lisp_print(); printf("\n");
    for (int k=0; k<3; k++) {
      // Aca `comp_p' es un puntero a funcion que
      // va tomando las diferentes funciones de comparacion
      // implementadas arriba. 
      bool (*comp_p)(int,int);
      comp_p = (k==0? int_less : k==1? int_greater : int_less_abs);
      const char *label = (k==0? "less" : k==1? "greater" : "less_abs");
      printf("parc. ord. con respecto a %s? %d, (usando version 2: %d)\n",
	     label, 
	     es_parcialmente_ordenado(A,comp_p),
	     es_parcialmente_ordenado2(A,comp_p));
    }
  }
}
// -------------------------------------------------------------------
