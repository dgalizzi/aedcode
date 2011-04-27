// $Id$
/* COMIENZO DE DESCRIPCION

Diversas operaciones en un Arbol Binario (AB)
[se asume que sus etiquetas son n\'umeros enteros positivos]:
altura          : calcula la altura;
cta\_hojas      : cuenta el n\'umero de hojas;
max\_etiq\_arbol: obtiene la m\'axima etiqueta de todo el \'arbol;
max\_epar\_arbol: obtiene la m\'axima etiqueta par del \'arbol;
max\_etiq\_hojas: obtiene la m\'axima etiqueta de solo las hojas;
sum\_etiq\_arbol: obtiene la suma de todas las etiquetas;
f\_aplica: ejemplo simple de {\bf programaci\'on funcional}
usando, una vez por vez, las funciones f\_duplica y f\_mitad
(ver en task1\_bo.cpp las equivalentes para \'arbol orientado). 
keywords: arbol binario

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
// Recordar que (errores tipicos en examen !!):
// 1) las funciones declaradas como "int" deben devolver en cualqueer 
//    caso un valor "int" y, por lo tanto, todo "return" debe devolver 
//    un "entero"; 
// 2) un razonamiento equivalente cuando en otros ejercicios
//    haya que devolver un "bool" o un "float";
// 3) solamente las funciones "void" NO devuelven explictamente
//    un valor y es la unica vez que el "return" no tendra argumentos 
//
// -------------------------------------------------------------------
#include <iostream>
#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"
using namespace aed;
using namespace std;

// -------------------------------------------------------------------
int altura (btree<int> & T, btree<int>:: iterator n) {
  int h1, h2, hmax ;
  // la recursion finaliza cuando ingresa los hijos de las hojas
  if (n == T.end ()) return -1 ;
  // altura del sub-arbol izquierdo "h1" y derecho "h2" por recursion
  h1 = altura (T, n.left  () ) ;
  h2 = altura (T, n.right () ) ;
  // selecciona la mayor altura de los subarboles izquierdo y derecho
  if (h1 > h2) {
    hmax = h1 ; }
  else {
    hmax = h2 ; 
  } // end if
  // devuelve la mayor altura
  return (1 + hmax) ;
} // end int

// -------------------------------------------------------------------
int cta_hojas (btree<int> & T, btree<int>:: iterator n) {
  int  p1, p2, p ;
  bool b1, b2 ;
  // la recursion finaliza cuando ingresa los hijos de las hojas
  if ( n == T.end () ) return 0 ;
  // si el nodo "n" es hoja entonces devuelve 1
  b1 = ( n.left  () == T.end () ) ;
  b2 = ( n.right () == T.end () ) ;
  if ( b1 && b2 ) return 1 ;
  // cta hojas sub-arbol izquierdo "p1" y derecho "p2" por recursion
  p1 = cta_hojas ( T, n.left  () );
  p2 = cta_hojas ( T, n.right () );
  // devuelve la suma de las hojas de los sub-arboles izq. y der.
  p  = p1 + p2 ;
  return p ;
} // end int

// -------------------------------------------------------------------
int max_etiq_arbol (btree<int> & T, btree<int>:: iterator n) {
  int x1, x2, xmax ;
  // la recursion finaliza cuando ingresa los hijos de las hojas
  if (n == T.end ()) return -1;
  // max etiq. de los subarb. izq. "x1" y der. "x2" por recursion
  x1 = max_etiq_arbol (T, n.left  () ) ;
  x2 = max_etiq_arbol (T, n.right () ) ;
  // selecciona y devuelve "xmax" como el mayor de (*n, x1, x2)
  xmax = *n ;
  if (x1 > xmax) xmax = x1 ;
  if (x2 > xmax) xmax = x2 ;
  return xmax ;
} // end int

// -------------------------------------------------------------------
int max_etiq_hojas (btree<int> & T, btree<int>:: iterator n) {
  int  x, x1, x2, xmax ;
  bool b1, b2 ;
  // la recursion finaliza cuando ingresa los hijos de las hojas
  if (n == T.end ()) return -1 ;
  // si el nodo "n" es hoja entonces devuelve su etiqueta
  x = *n ;
  b1 = ( n.left  () == T.end () ) ;
  b2 = ( n.right () == T.end () ) ;
  if (b1 && b2) return x ;
  // max etiq_hojas de los subarb. izq. "x1" y der. "x2" por recursion
  x1 = max_etiq_hojas (T, n.left  ());
  x2 = max_etiq_hojas (T, n.right ());
  // selecciona y devuelve "xmax" como el mayor de (*n, x1, x2)
  xmax = 0 ;
  if  (x1 > xmax) xmax = x1 ;
  if  (x2 > xmax) xmax = x2 ;
  return xmax;
} // end int

// -------------------------------------------------------------------
int max_epar_arbol (btree<int> & T, btree<int>:: iterator n) {
  int x1, x2, xmax ;
  // la recursion finaliza cuando ingresa los hijos de las hojas
  if (n == T.end ()) return -1;
  // max etiq. par de los subarb. izq. "x1" y der. "x2" por recursion  
  x1 = max_epar_arbol (T, n.left  () ) ;
  x2 = max_epar_arbol (T, n.right () ) ;
  // selecciona y devuelve "xmax" como el mayor par de (*n, x1, x2)
  if (*n % 2 == 0) xmax = *n ; else xmax = 0 ;
  if (x1 > xmax && x1 % 2 == 0)  xmax = x1 ;
  if (x2 > xmax && x2 % 2 == 0)  xmax = x2 ;
  return xmax ;
} // end int

// -------------------------------------------------------------------
int  sum_etiq_arbol (btree<int> &T, btree<int>::iterator n) {
  int  s1, s2, suma ;
  // la recursion finaliza cuando ingresa los hijos de las hojas
  if (n == T.end ()) return 0 ;
  // suma recursiva de las etiq. de los subarb. izq. "s1" y der. "s2"
  s1 = sum_etiq_arbol (T, n.left  ());
  s2 = sum_etiq_arbol (T, n.right ());
  // devuelve "suma" como la suma de (*n, s1, s2)
  suma = *n + s1 + s2;
  return (suma) ;
} // end int

// -------------------------------------------------------------------
//
// Un par de ejemplos *SIMPLES* de Programacion Funcional:
//
// 1) Primero definimos una funcion "aplica" que hace el trabajo 
//    RECURSIVO. La tarea que haga dependera de la "f_usuario" que 
//    se defina cuando se llame al "wrapper" desde, por ejemplo, el 
//    programa principal;
//
// 2) Por didactica, la "f_usuario" la restringiremos: 
//    2.1) a ser de tipo entero;
//    2.2) con un unico argumento de tipo entero.
//
// 3) Luego, podremos implementar cualquier "f_usuario" que 
//    satisfaga tales restricciones. Como un par de ejemplos muy 
//    simples incluimos "f_duplica" y "f_mitad".
// -----------------------------------------------------------------
void aplica (btree<int>           &T,
             btree<int>::iterator  n,
             int (*f_usuario) (int) ) {
 if (n == T.end () ) return;
 *n = f_usuario (*n);
 aplica (T, n.left (), f_usuario);
 aplica (T, n.right(), f_usuario);
}
void aplica (btree<int> &T, int (*f_usuario) (int) ) {
  aplica (T, T.begin (), f_usuario) ;
}
int f_duplica (int i) {
 return (2*i) ;
}
int f_mitad (int i) {
 return (i/2) ;
}

// -------------------------------------------------------------------
void tareas (btree<int> & Q) {
  btree <int> U;
  int n1, n2, n3, n4, n5, n6 ;

  cout << endl ;
  cout << "Arbol binario: " ; Q.lisp_print () ; 
  cout << endl ;

  n1 = altura         ( Q, Q.begin () ) ;
  n2 = cta_hojas      ( Q, Q.begin () ) ;
  n3 = max_etiq_arbol ( Q, Q.begin () ) ;
  n4 = max_epar_arbol ( Q, Q.begin () ) ;
  n5 = max_etiq_hojas ( Q, Q.begin () ) ;
  n6 = sum_etiq_arbol ( Q, Q.begin () ) ;

  cout << "altura del arbol                  = " << n1 << endl;
  cout << "nro de hojas en el arbol          = " << n2 << endl;
  cout << "max etiqueta de todo el arbol     = " << n3 << endl;
  cout << "max etiqueta par de todo el arbol = " << n4 << endl;
  cout << "max etiqueta de las hojas         = " << n5 << endl;
  cout << "suma de todas las etiquetas       = " << n6 << endl;

  cout << endl ;
  cout << "ejemplos *SIMPLES* de programacion funcional: " << endl ;

  cout << endl ;
  cout << "1) devuelve el doble de las etiquetas de un AB " << endl ;
  U = Q ;
  cout << "   AB antes  : " ; U.lisp_print () ; cout << endl ;
  aplica (U, f_duplica) ;
  cout << "   AB despues: " ; U.lisp_print () ; cout << endl ;

  cout << endl ;
  cout << "2) devuelve la mitad de las etiquetas de un AB " << endl ;
  U = Q ;
  cout << "   AB antes  : " ; U.lisp_print () ; cout << endl ;
  aplica (U, f_mitad) ;
  cout << "   AB despues: " ; U.lisp_print () ; cout << endl ;
}

// -------------------------------------------------------------------
int main () {
  int kaso = 1 ;

  cout << endl; 
  cout << "tareas varias en un arbol ordenado binario" << endl ;

  if      (kaso == 1) {
    typedef int dato;
    const dato BP=-1, EP=-2, NE=-3, EL=-4;
    btree <dato> Q;
    //tareas (Q); 
    list <dato> L;
    dato l[]={BP,1,2,BP,8,BP,4,NE,BP,5,3,NE,EP,EP,BP,9,NE,6,EP,EP,EP,EL};
    insertl (L, l, EL);
    list2btree (Q, L, BP, EP, NE);
    tareas (Q); 
  }
  else if (kaso == 2) {
    btree <int> T;
    for (int j = 0 ; j < 1 ; j++) {
      T.clear ();
      make_random_btree (T, 10, 1.2); // 1.1
      tareas (T) ;
    } // end j
  } // end if

  cout << endl ;
  return 0 ;
} // end main
// -------------------------------------------------------------------
