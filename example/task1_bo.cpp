// $Id$
/* COMIENZO DE DESCRIPCION
__USE_WIKI__

Diversas operaciones sobre un Arbol Ordenado Orientado (AOO)
[se asume que sus etiquetas son n\'umeros enteros positivos]:
altura          : calcula la altura;
#cta_hojas#      : cuenta el n\'umero de hojas;
#max_etiq_arbol#: obtiene la m\'axima etiqueta de todo el \'arbol;
#max_epar_arbol#: obtiene la m\'axima etiqueta par del \'arbol;
#max_etiq_hojas#: obtiene la m\'axima etiqueta de solo las hojas;
#sum_etiq_arbol#: obtiene la suma de todas las etiquetas;
#f_aplica#: ejemplo simple de {\bf programaci\'on funcional}
usando, una vez por vez, las funciones f\_duplica y f\_mitad
(ver en task1\_bb.cpp las equivalentes para \'arbol binario). 
Otras: es\_camino, is\_path, list\_if
#profundidad# : calcula la profundidad de un nodo. 
#get_node_by_pre_index# : busca un nodo dado su indice (en preorden). 

keywords: arbol orientado

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
// Ejemplo:
// +--(3)
//    |
//    +--(6)
//    +--(9)
//       |
//       +--(6)
//          |
//          +--(8)
// altura                      =  3
// nro de hojas                =  2
// max etiq. de todo el arbol  =  9
// max etiq. de las hojas      =  8
// suma de todas las etiquetas = 32
// -------------------------------------------------------------------
//
// Recordar que (errores tipicos en examen !!):
// 1) las funciones declaradas como "int" deben devolver en cualqueer 
//    caso un valor "int" y, por lo tanto, todo "return" debe devolver 
//    un "entero"; 
// 2) un razonamiento equivalente cuando en otros ejercicios
//    haya que devolver un "bool" o un "float";
// 3) solamente las funciones "void" NO devuelven explictamente
//    un valor y es la unica vez que el "return" no tendra argumentos 
// -------------------------------------------------------------------
#include <iostream>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
// Calcula la profundidad de un nodo. Notar que
// si tuvieramos la funcion `padre', entonces seria mucho
// mas facil ya que bastaria con seguir el camino desde
// el nodo a la raiz, usando `padre'. En este caso tenemos
// que hacer un codigo parecido a `find()' pero manteniendo
// en el estado la profundidad del nodo. 

// Calcula la profundidad del nodo `buscado' en el arbol
// `t' dentro del subarbol del nodo `raiz'. Sabiendo que la
// profundidad de `raiz' es `prof_raiz'. Retorna la
// profundidad del nodo y si no esta retorna `-1'. 
int  profundidad (tree <int> & t, node_t buscado, 
                 node_t raiz, int prof_raiz) {
  // Si el nodo esta en `raiz' entonces su profundidad
  // es `prof_raiz'
  if (buscado==raiz) return prof_raiz;
  else {
    // Si no, recorre los hijos, buscando el nodo
    // hasta que lo encuentra. Notar que la profundidad
    // de los hijos es `prof_raiz+1'
    node_t q = raiz.lchild();
    while (q!=t.end()) {
      int p = profundidad(t,buscado,q++,prof_raiz+1);
      // Sabemos que lo encontro cuando retorna una
      // profundidad no negativa.
      if (p>=0) return p;
    }
    return -1;
  }
}

int  profundidad (tree <int> & t, node_t buscado) {
  node_t raiz=t.begin();
  if (raiz==t.end()) return -1;
  return profundidad(t,buscado,t.begin(),0);
}

// -------------------------------------------------------------------
// Calcula la profundidad2 de un nodo. Notar que
// si tuvieramos la funcion `padre', entonces seria mucho
// mas facil ya que bastaria con seguir el camino desde
// el nodo a la raiz, usando `padre'. En este caso tenemos
// que hacer un codigo parecido a `find()' pero manteniendo
// en el estado la profundidad2 del nodo. 

// Calcula la profundidad del nodo `buscado' en el arbol
// `t' dentro del subarbol del nodo `raiz'. Sabiendo que la
// profundidad de `raiz' es `prof_raiz'. Retorna la
// profundidad del nodo y si no esta retorna `-1'. 
int  profundidad2 (tree <int> & t, node_t buscado, 
                 node_t raiz, int prof_raiz) {
  // Si el nodo esta en `raiz' entonces su profundidad
  // es `prof_raiz'
  if (buscado==raiz) return prof_raiz;
  else {
    // Si no, recorre los hijos, buscando el nodo hasta que
    // lo encuentra. Notar que la profundidad de los hijos
    // es `prof_raiz+1'. Primero prueba con los hijos lo
    // cual hace que solo revise los niveles superriores al
    // de `buscado'
    node_t q = raiz.lchild();
    // primero busca en las raices de los subarboles
    while (q!=t.end()) 
      if (q++==buscado) return prof_raiz+1;
    // No lo encontro en las raices, ahora busca en todos
    // los subarboles
    q = raiz.lchild();
    while (q!=t.end()) {
      int p = profundidad2(t,buscado,q++,prof_raiz+1);
      // Sabemos que lo encontro cuando retorna una
      // profundidad no negativa.
      if (p>=0) return p;
    }
    return -1;
  }
}

int  profundidad2 (tree <int> & t, node_t buscado) {
  node_t raiz=t.begin();
  if (raiz==t.end()) return -1;
  return profundidad2(t,buscado,t.begin(),0);
}

// -------------------------------------------------------------------
// Retorna el nodo cuyo indice (en preorder) es `index'. La
// busqueda se hace en el subarbol del nodo `n', sabiendo
// que su indice es `n_index'. Como side-effect, esta funcion
// actualiza el valor de `n_index' de manera que al salir contiene
// el indice del primer nodo _pasando_ el subarbol de `n'.
// (O sea que `n_index' es un argumento de entrada/salida. 
// Si el indice `index' no esta en el subarbol retorna `t.end()'
node_t get_node_by_pre_index(tree<int> &t, int index,
                            node_t n, int &n_index) {
  // Si el indice buscado es el de n, retorne `n'
  if (n_index==index) return n;
  n_index++;
  // Busca en los hijos, recusrivamente. Notar que
  // `get_node_by_pre_index' va a ir actualizando el valor
  // de `n_index'
  node_t q = n.lchild();
  while (q!=t.end()) {
    node_t w = get_node_by_pre_index(t,index,q++,n_index);
    if (w!=t.end()) return w;
  }
  return t.end();
}

node_t get_node_by_pre_index(tree<int> &t, int index) {
  int n_index=0;
  node_t n = t.begin();
  if (n==t.end()) return n;
  else 
    return get_node_by_pre_index(t,index,t.begin(),n_index);
}

// -------------------------------------------------------------------
int  altura (tree <int> & t, node_t n) {
  int     hmax, h ;
  node_t  c ;
  // la recursion finaliza cuando ingresan los hijos de las hojas
  if ( n == t.end () ) return -1 ;
  // altura por recursion de los sub-arboles del nodo "n"
  c = n.lchild () ;                  // inicia en hijo_mas_izquierdo 
  hmax = -1 ;                        // inicializa la mayor altura
  while ( c != t.end () ) {          // mientras haya descendientes
    h = altura (t,c++);              // recursion y pos-incremento
    if (h > hmax) hmax = h ;         // actualiza la mayor altura
  } // end while                     // fin lazo  
  return (1 + hmax) ;                // devuelve la mayor altura
} // end int

// -------------------------------------------------------------------
int  cta_hojas ( tree <int> & t, node_t n) {
  node_t c ;
  int    p ;
  // la recursion finaliza cuando ingresan los hijos de las hojas
  if ( n == t.end () ) return 0 ;
  c = n.lchild () ;                  // inicia en hijo_mas_izquierdo 
  if ( c == t.end () ) return 1 ;    // si el nodo es hoja retorna 1
  // cuenta por recursion las hojas de los sub-arboles del nodo "n"
  p = 0 ;                            // inicia acumulador
  while ( c != t.end () ) {          // mientras haya descendientes
    p = p + cta_hojas (t, c++) ;     // recursion y pos-incremento
  } // end while                     // fin lazo
  return p ;                         // devuelve la suma de hojas
} // end int

// -------------------------------------------------------------------
int  max_etiq_arbol (tree <int> & t, node_t n) {
  int    x, xmax ;
  node_t c ;
  // la recursion finaliza cuando ingresan los hijos de las hojas
  if (n == t.end () ) return -1;
  xmax = *n ;                        // inicia con la etiq del nod "n"
  // max etiqueta del arbol por recursion 
  c = n.lchild () ;                  // inicia en hijo_mas_izquierdo 
  while ( c != t.end () ) {          // mientras haya descendientes
    x = max_etiq_arbol (t, c++) ;    // llamada recursiva y pos-incr
    if ( x > xmax )  xmax = x ;      // actualiza el mayor
  } // end while  
  return xmax ;
} // end int

// -------------------------------------------------------------------
int max_epar_arbol (tree <int> & t, node_t n) {
  int x, xmax ;
  node_t c ;
  // la recursion finaliza cuando ingresa los hijos de las hojas
  if (n == t.end () ) return -1;     // retorna un valor fuera de rango
  if (*n % 2 == 0)                   // si es un numero par entonces
    xmax = *n ;                      // inicia "xmax" con *n
  else {                             // sino
    xmax = 0 ;                       // inicia con 0
  } // end if                        // fin "si"
  // max etiqueta par del arbol por recursion 
  c = n.lchild () ;                  // inicia en hijo_mas_izquierdo 
  while ( c != t.end () ) {          // mientras haya descendientes
    x = max_epar_arbol (t, c++) ;    // recursion y pos-incremento
    if (x > xmax)  xmax = x ;        // selecciona el mayor
  } // end while                     // fin lazo
  return xmax;                       // retorna max etiqueta
} // end int

// -------------------------------------------------------------------
int max_etiq_hojas (tree <int> & t, node_t n) {
  node_t c ;
  int    z, zmax ;
  // la recursion finaliza cuando ingresa los hijos de las hojas
  if ( n == t.end () ) return -1 ;
  c = n.lchild () ;                  // inicia en hijo_mas_izquierdo 
  if ( c == t.end () ) return *n ;   // si el nodo es hoja retorna *n
  // max etiqueta del arbol por recursion 
  zmax = 0 ;                         // inicia maxima etiqueta hojas
  c = n.lchild () ;                  // inicia en hijo_mas_izquierdo 
  while ( c != t.end () ) {          // mientras haya descendientes
    z = max_etiq_hojas (t, c++);     // recursion y pos-incremento
    if (z > zmax) zmax = z ;         // actualiza la mayor etiqueta
  } // end while                     // fin lazo
  return zmax;                       // retorna max etiqueta
} // end int

// -------------------------------------------------------------------
int sum_etiq_arbol (tree <int> &t, node_t n) {
  node_t c ;
  int    p ;
  // la recursion finaliza cuando ingresa los hijos de las hojas
  if (n == t.end ()) return 0 ;      // si el nodo es hoja retorna 0
  p = *n;                            // inicia "p" con *n
  c = n.lchild () ;                  // inicia en hijo_mas_izquierdo 
  while ( c != t.end () ) {          // mientras haya descendientes
    p = p + sum_etiq_arbol (t, c++); // recursion y pos-incremento
  } // end while                     // fin lazo
  return p ;                         // retorna suma
} // end int

// -------------------------------------------------------------------
// ejemplos *SIMPLES* de programacion funcional: 
// la funcion "aplica" es generica, es decir, la tarea que se haga 
// dependera de la funcion "f_usuario" que se ingrese cuando se 
// llame al "wrapper" desde, por ejemplo, el programa principal
int f_duplica (int i) {
 return (2*i) ;
}
int f_mitad (int i) {
 return (i/2) ;
}
void aplica (tree<int>           &T,
             tree<int>::iterator  n,
             int (*f_usuario) (int) ) {
 tree<int>::iterator c;
 if (n == T.end () ) return;
 *n = f_usuario (*n);
 c = n.lchild ();
 while ( c != T.end() ) {
   aplica (T, c, f_usuario);
   c++ ;
 }
}
void aplica (tree<int> &T, int (*f_usuario) (int) ) {
  aplica (T, T.begin (), f_usuario) ;
}

// -------------------------------------------------------------------
bool es_camino(tree<int> &t, node_t n,
	       list<int> &l,list<int>::iterator q) {
  if (q == l.end()) return true;
  if (n == t.end()) return false;
  if (*n != *q    ) return false;
  else {
    q++; 
    n = n.lchild();
    if (q== l.end()) return true;
    while (n != t.end()) {
      if (es_camino (t,n++,l,q)) return true;
    } // end while
    return false;
  } // end if
}
bool es_camino (tree<int> &t, list<int> &l) {
  return es_camino (t, t.begin(), l, l.begin());
}

// -------------------------------------------------------------------
typedef bool (*binary_pred) (int x,int y);

// -------------------------------------------------------------------
typedef bool (*unary_pred) (int x);

bool odd(int x) { return x % 2 != 0; }

// -------------------------------------------------------------------
bool is_path (tree <int> &t, node_t n,
	      list <int> &l, list <int>::iterator q,
	      binary_pred pred, list<int> &path) {
  if (q == l.end()) return true;
  if (n == t.end()) return false;
  if (!pred(*n,*q)) return false;
  else {
    path.insert (path.begin(),*n);
    q++; 
    n = n.lchild();
    if (q == l.end()) return true;
    while (n != t.end()) {
      if (is_path (t, n++, l, q, pred, path)) return true;
    } // end while
    path.erase (path.begin());
    return false;
  } // end if
}
bool is_path (tree<int> &t, list<int> &l,
	      binary_pred pred, list<int> &path) {
  return is_path (t, t.begin(), l, l.begin(), pred,path);
}

// -------------------------------------------------------------------
// Funcion recursiva: verifica si la suma de los elementos
// de algun subarbol del nodo "n" da "s".  Retorna la suma de
// los elementos del subarbol de "n". Se incluyen los "wrappers"
node_t encuentra_suma (int s,tree<int> &t,node_t n,int &suma) {
  node_t c, w ;
  int suma_hijo;
  if (n==t.end()) return t.end();
  c = n.lchild();
  suma = *n;
  while (c != t.end()) {
    w = encuentra_suma (s, t, c++, suma_hijo);
    if (w != t.end()) return w;
    suma += suma_hijo;
  }
  if (suma == s) 
    return n;
  else 
    return t.end();
}
node_t encuentra_suma (int s,tree<int> &t,node_t n) {
  int suma;
  return encuentra_suma (s, t, n, suma);
}
node_t encuentra_suma (int s,tree <int> &t) {
  return encuentra_suma (s, t, t.begin());
}

// -----------------------------------------------------------------
// un par de funciones predicado
bool  equal_pred (int x, int y) { return x==y; }
bool lesser_pred (int x, int y) { return x<=y; }

// -------------------------------------------------------------------
void tarea1 (tree<int> & T) {
  tree <int> U;
  node_t p ;
  int n1, n2, n3, n4, n5, n6 ;

  n1 = altura         ( T, T.begin () ) ;
  n2 = cta_hojas      ( T, T.begin () ) ;
  n3 = max_etiq_arbol ( T, T.begin () ) ;
  n4 = max_epar_arbol ( T, T.begin () ) ;
  n5 = max_etiq_hojas ( T, T.begin () ) ;
  n6 = sum_etiq_arbol ( T, T.begin () ) ;
  cout << "altura del arbol            = " << n1 << endl;
  cout << "nro de hojas del arbol      = " << n2 << endl;
  cout << "max etiq. de todo el arbol  = " << n3 << endl;
  cout << "max etiq. par en  el arbol  = " << n4 << endl;
  cout << "max etiq. de las hojas      = " << n5 << endl;
  cout << "suma de todas las etiquetas = " << n6 << endl;
  for (int k=5; k < 50; k += 5) {
    p = encuentra_suma (k,T);
    if (p != T.end()) 
     cout << "encuentra suma == " << k << " en nodo " << *p << endl;
  } // end k

  cout << endl ;
  cout << "ejemplos *SIMPLES* de programacion funcional: " << endl ;

  cout << endl ;
  cout << "1) devuelve el doble de las etiquetas de un AOO" << endl ;
  U = T ;
  cout << endl ;
  cout << "   AOO antes  : " ; U.lisp_print () ; cout << endl ;
  aplica (U, f_duplica) ;
  cout << endl ;
  cout << "   AOO despues: " ; U.lisp_print () ; cout << endl ;

  cout << endl ;
  cout << "2) devuelve la mitad de las etiquetas de un AOO" << endl ;
  U = T ;
  cout << endl ;
  cout << "   AOO antes  : " ; U.lisp_print () ; cout << endl ;
  aplica (U, f_mitad) ;
  cout << endl ;
  cout << "   AOO despues: " ; U.lisp_print () ; cout << endl ;

}

// -------------------------------------------------------------------
void tarea2 (tree<int> & E, list<int> & LP) {
  list <int> path;

  cout << "Es camino ? " 
       << (es_camino (E,LP) ? "si" : "no") << endl ;
  path.clear ();

  cout << "Is path   ? " 
       << (is_path (E, LP, equal_pred, path) ? "si" : "no") << endl;
  path.clear();
  cout << "Is path   ? " 
       << (is_path (E, LP, equal_pred, path) ? "si" : "no") << endl;
   
  cout << "lista: ";
  printl (LP);
  cout << "Es camino ? " 
       << (es_camino (E,LP) ? "si" : "no") << endl;
  path.clear();
  cout << "Is path   ? " 
       << (is_path (E, LP, equal_pred, path) ? "si" : "no") << "path: ";
  printl (path);

  cout << "Es un camino ? " 
       << (es_camino (E,LP) ? "si" : "no") << endl;
  path.clear();
  cout << "Is path      ? " 
       << (is_path (E,LP,equal_pred,path) ? "si" : "no") << endl;
}

// -------------------------------------------------------------------
// Escribir una funcion void `list_if(tree <int> &T, 
// list <int> &L, bool (*pred)(int x))' tal que
// dado un arbol ordenado orientado `T' retorna una lista de
// los elementos en orden previo que satisfacen el predicado
// `pred'. Por ejemplo, si T=`(1 (2 3 (4 5 6)))', entonces
// `list_if(T,L,odd)' debe retornar la lista (1 3 5).
void list_if(tree <int> &t, node_t n,
	     list <int> &l, unary_pred pred) {
  if (pred(*n)) l.insert(l.end(),*n);
  node_t c = n.lchild();
  while (c!=t.end()) list_if(t,c++,l,pred);
}

void list_if(tree <int> &t, list <int> &l, 
	     unary_pred pred) {
  l.clear();
  if (t.begin()!=t.end())
    list_if(t,t.begin(),l,pred);
}

// -------------------------------------------------------------------
int main () {
  const int BP=-1, EP=-2, NE=-3, EL=-4;
  int kaso = 5 ;

  cout << endl; 
  cout << "tareas varias en un Arbol Ordenado Orientado" << endl ;

  if (kaso == 1) {
    tree <int> T;
    for (int j = 0 ; j < 1 ; j++) {
      cout << endl ;
      T.clear ();
      make_random_tree (T, 10, 3); // 3.5
      print_tree (T);
      tarea1 (T);
    } // end j
  }
  else if (kaso == 2) {
    tree <int> A;
    list <int> LA;
    int la[] = {BP,4,3,2,BP,1,BP,9,BP,8,6,5,2,EP,BP,7,4,1,EP,EP,EP,EP,EL};
    insertl (LA,la,EL);
    list2tree (A,LA,BP,EP);
    cout << "arbol A: "; A.lisp_print(); cout << endl;
    tarea1 (A);
  }
  else if (kaso == 3) {
    tree <int> A;
    list <int> LA;
    list <int> LP1, LP2, LP3;

    int la[] = {BP,5,7,BP,8,BP,12,16,11,7,EP,15,EP,9,EP,EL};
    insertl (LA,la,EL);
    list2tree (A,LA,BP,EP);
    cout << "arbol A: "; A.lisp_print(); cout << endl;

    int lp1 [] = {5,8,12,11,EL};
    LP1.clear();
    insertl (LP1,lp1,EL);
    cout << "lista L1: "; printl (LP1);

    int lp2 [] = {5,8,12,9,EL};
    LP2.clear();
    insertl (LP2,lp2,EL);
    cout << "lista L2: "; printl (LP2);

    int lp3 [] = {5,9,EL};
    insertl (LP3,lp3,EL);
    cout << "lista L3: "; printl (LP3);

    tarea1 (A) ;

    tarea2 (A, LP1);
    tarea2 (A, LP2);
    tarea2 (A, LP3);

  }  else if (kaso == 4) {

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
    tree <int> T;
    list<int> L;
    make_random_tree (T, 10, 3); 
    print_tree(T);
    list_if(T,L,odd);
    printl(L);

  } else if (kaso == 5) {
    tree <int> A;
    list <int> LA;
    int la[] = {BP,4,3,2,BP,1,BP,9,BP,8,6,5,2,EP,BP,7,4,1,EP,EP,EP,EP,EL};
    insertl (LA,la,EL);
    list2tree (A,LA,BP,EP);
    cout << "arbol A: "; A.lisp_print(); cout << endl;
    // Retorna nodos de acuerdo a sus indices
    for (int j=0; j<20; j++) {
      node_t q = get_node_by_pre_index(A,j);
      if (q!=A.end()) printf("index %d, *node %d\n",j,*q);
      else printf("index %d, node==end()!!\n",j);
    }
    // Busca nodos aleatoriamente y calcula sus profundidades
    for (int j=0; j<12; j++) {
      node_t q = get_node_by_pre_index(A,j);
      printf("index %d, *node %d, profundidad %d\n",
             j,*q,profundidad2(A,q));
    }
    
  }

  cout << endl ;
  return 0;
}
// -------------------------------------------------------------------
