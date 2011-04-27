// $Id$

#include <iostream>
#include "./util.h"
#include "./tree.h"
#include "./btree.h"
#include "./util_tree.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

/* COMIENZO DE DESCRIPCION 
   
   __USE_WIKI__
   Escribir una funci\'on 
   #void map_pre_post(tree<int> &T,list<int> &L, int (*fpre)(int),int (*fpost)(int))#
   que lista los valores nodales del \'arbol ordenado orientado
   #T# en una mezcla de orden previo y posterior, donde en orden 
   previo se listan los valores nodales aplicandoles #fpre()# y en 
   orden posterior los #fpost()#.   
   Por ejemplo, si #T=(1 3 (5 6 7 8))#, #f(x)=x# y #g(x)=x+1000#,
   entonces #map_pre_post(T,L,f,g)# debe dar 
   #L=(1,3,1003,5,6,1006,7,1007,8,1008,1005,1001)#. 
   [Tomado en el recup 30/6/2005]. 
   keywords: arbol orientado, lista

   FIN DE DESCRIPCION 

   La definicion recursiva es

   map_pre_post(n,f,g) = 
      si n=Lambda: lista vac\'\i{}a
      si n no es Lambda:  f(n),\mapprepost(n_1,f,g),
                                     ...,map_pre_post(n_m,f,g),g(n)  */

// Estas son las funciones de mapeo usadas en el
// enunciado
int f(int x) { return x; }
int g(int x) { return x+1000; }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void map_pre_post(tree<int> &T,tree<int>::iterator n,
		  list<int> &L, 
		  int (*fpre)(int),int (*fpost)(int)) {
  // Insertar primero el valor de `fpre()' aplicado al
  // valor nodal. 
  L.insert(L.end(),fpre(*n));
  // Insertar las secuencias generadas por los hijos
  tree<int>::iterator m = n.lchild();
  while (m!=T.end()) 
    map_pre_post(T,m++,L,fpre,fpost);
  // Insertar primero el valor de `fpost()' aplicado al
  // valor nodal. 
  L.insert(L.end(),fpost(*n));
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Wrapper
void map_pre_post(tree<int> &T,list<int> &L, 
		  int (*fpre)(int),int (*fpost)(int)) {
  L.clear();
  if (T.begin()!=T.end())
    map_pre_post(T,T.begin(),L,fpre,fpost);
}

// -------------------------------------------------------------------
int main () {

  // Crea el arbol 
  const int BP=-1, EP=-2, NE=-3, EL=-4;
  tree <int> A;
  list <int> LA;
  // Este es otro ejemplo
  // int la[] = {BP,4,3,2,BP,1,BP,9,BP,8,6,5,2,EP,BP,7,4,1,EP,EP,EP,EP,EL};

  /* Debe imprimir:
     [mstorti@minerva example]$ ./mapprepost.bin 
     arbol A: (1 3 (5 6 7 8))
     map-pre-post(A): 1 3 1003 5 6 1006 7 1007 8 1008 1005 1001 
     [mstorti@minerva example]$ 
  */
  int la[] = {BP,1,3,BP,5,6,7,8,EP,EP,EL};
  insertl (LA,la,EL);
  list2tree (A,LA,BP,EP);
  cout << "arbol A: "; A.lisp_print(); cout << endl;

  list<int> L;
  map_pre_post(A,L,f,g);
  list<int>::iterator q = L.begin();
  cout << "map-pre-post(A): ";
  while (q!=L.end())
    cout << *q++ << " ";
  cout << endl;
}
