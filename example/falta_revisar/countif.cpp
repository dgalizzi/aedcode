//__INSERT_LICENSE__
// $Id$

#include <list>
#include <cstdio>
#include "./tree.h"
#include "./util.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Escribir una funci\'on 
  #int count_if(tree<int> &T,bool (*pred)(int x));# que retorna
  el n\'umero de nodos del \'arbol #T# que satisfacen el
  predicado #pred#. Por ejemplo, si #T=(1 2 (3 5 7 6) 4)#,
  entonces #count_if(T,odd)# debe retornar 4. Escribir el
  predicado #bool odd(int x)# que determina si un entero es
  impar. 

  Escribir una funci\'on 
  #void list_if(tree<int> &T,list<int> &L,bool (*pred)(int x));# 
  que retorna en #L#
  la lista de valores nodales en orden previo de un \'arbol
  ordenado orientado #T# que satisfacen el predicado
  #pred#. Por ejemplo, si #T=(1 (-2 7 (8 -7) (3 -5 -6)))#,
  entonces despu\'es de #list_if(T,L,positive)#, debe quedar
  #L={1,7,8,3}#.  Escribir el predicado 
  #bool positive(int x)# que determina si un entero es mayor que 0.
  [Tomado en el 2do parcial 26/5/2005]. 
  keywords: arbol orientado

   FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int count_if(tree<int> &T,tree<int>::iterator n,
	     bool (*pred)(int)) {
  int count = pred(*n);
  tree<int>::iterator c = n.lchild();
  while (c!=T.end()) 
    count += count_if(T,c++,pred);
  return count;
}

int count_if(tree<int> &T,bool (*pred)(int)) {
  if (T.begin()!=T.end()) 
    count_if(T,T.begin(),pred);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void list_if(tree<int> &T,
	     tree<int>::iterator n,
	     list<int> &L,
	     bool (*pred)(int)) {
  if (pred(*n)) L.push_back(*n);
  tree<int>::iterator c = n.lchild();
  while (c!=T.end()) list_if(T,c++,L,pred);
}

int list_if(tree<int> &T,
	     list<int> &L,
	    bool (*pred)(int)) {
  L.clear();
  if (T.begin()!=T.end()) 
    list_if(T,T.begin(),L,pred);
}

bool odd(int x) { return x %2; }
bool positive(int x) { return x>0; }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void apply(tree<int> &T,tree<int>::iterator n,
	   int (*f)(int)) {
  *n = f(*n);
  tree<int>::iterator c = n.lchild();
  while (c!=T.end()) apply(T,c++,f);
}

void apply(tree<int> &T,int (*f)(int)) {
  apply(T,T.begin(),f);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int M = 5;
int f(int x) { return x-M/2; }

int main() {
  const int N=10;
  tree<int> A;
  list<int> L;
  for (int j=0; j<N; j++) {
    A.clear();
    make_random_tree(A,M,2);
    apply(A,f);
    printf("-----------------\nA: \n");
    A.lisp_print();
    printf("\n%d odd, %d positive\n",
	   count_if(A,odd),count_if(A,positive));

    printf("odd: ");
    list_if(A,L,odd);
    printl(L);

    printf("positive: ");
    list_if(A,L,positive);
    printl(L);
  }
}
