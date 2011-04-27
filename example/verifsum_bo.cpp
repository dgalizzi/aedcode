// $Id$
/* COMIENZO DE DESCRIPCION

  En un programa de dise\~no asistido por computadora
  (tipo AutoCAD) se desea mantener las piezas de un sistema
  (por ejemplo un auto) clasificando sus partes en la forma
  de un \'arbol, donde sus nodos interiores representan
  sistemas del auto (planta motriz, direccion, carroceria),
  sus hijos subs-sistemas y asi siguiendo hasta las hojas
  que son los componentes indivisibles del automovil (por
  ej. el tornillo de fijaci\'on del espejo retrovisor
  izquierdo).
  Se quiere mantener en cada hoja el peso (en Kilogramos)
  del componente, y en los nodos interiores el peso total
  de todos los componentes del sub\'arbol que cuelga de ese
  nodo. Peri\'odicamente se quiere verificar que efectivamente
  las etiquetas del \'arbol verifican esta propiedad, es
  decir que la etiqueta de los nodos interiores es la
  suma de las hojas del sub\'arbol que cuelga de \'el.
  Escribir una funcion bool verif\_sum (tree <int> &T, node_t n) 
  que retorna true si el subarbol que cuelga del nodo verifica 
  la condicion dada y false en caso contrario. Usar las 
  primitivas del TAD Arbol Ordenado orientado.
  [Tomado en el segundo parcial del cursado 2002, 28/5/2002.]
  keywords: arbol orientado

  FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_tree.cpp
//        icc -w -c verifsum_bo.cpp
//        icc -w -o verifsum_bo.exe verifsum_bo.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_tree.cpp
//        g++ -w -c verifsum_bo.cpp
//        g++ -w -o verifsum_bo.exe verifsum_bo.o util.o util_tree.o
//
// -------------------------------------------------------------------
#include <iostream>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
bool  verif_sum ( tree <int> & T, node_t n ) { 
  node_t  c ;
  int     s ;
  // primero verifica si el nodo "n" no es lambda
  if ( n == T.end () ) return true ; 
  c = n.lchild () ;
  if ( c == T.end () ) 
    return true ; // si el nodo es hoja esta OK
  else { 
    s = 0 ;
    while ( c != T.end () ) {
      // llamada recursiva sobre cada hijo del nodo "n"
      // si no satisface la condicion aborta
      if ( !verif_sum (T,c) ) return false ;
      // acumula las etiquetas de los hijos
      s = s + *c ;
      c++;
    } // end while
    // verifica que la suma sea igual a la etiqueta del nodo
    return (s == *n ) ;
  } // end if
} // end bool

// -------------------------------------------------------------------
int main () {
  tree <int> t0, t1, t2, t3, t4 ;
  list <int>     l1, l2, l3, l4 ;
  const int BP = -2, EP = -1, EL = -3;
  int  v1 [] = {BP,3,1,2,EP,EL};
  int  v2 [] = {BP,6,4,5,EP,EL};
  int  v3 [] = {BP,21,BP,7,1,2,4,EP,BP,12,6,
                BP,5,3,2,EP,1,EP,BP,2,2,EP,EP,EL};
  int  v4 [] = {BP,1,BP,5,0,2,4,EP,BP,7,3,
                BP,1,6,9,EP,8,EP,BP,2,3,EP,EP,EL};
  bool b0, b1, b2, b3, b4 ;

  cout << endl; 
  cout << "verifica suma en arbol orientado " << endl ;
  cout << endl; 

  t0.clear ();
  b0 = verif_sum ( t0, t0.begin () ) ; 
  cout << "verif_sum (lambda) = " << b0 << endl ;
  cout << endl; 

  l1.clear ();
  insertl (l1, v1, EL);
  t1.clear ();
  list2tree (t1, l1, BP, EP);
  print_tree (t1);
  b1 = verif_sum ( t1, t1.begin () ) ; 
  cout << "verif_sum (t1) = " << b1 << endl ;
  cout << endl; 

  l2.clear ();
  insertl (l2, v2, EL);
  t2.clear ();
  list2tree (t2, l2, BP, EP);
  print_tree (t2);
  b2 = verif_sum ( t2, t2.begin () ) ; 
  cout << "verif_sum (t2) = " << b2 << endl ;
  cout << endl; 

  l3.clear ();
  insertl (l3, v3, EL);
  t3.clear ();
  list2tree (t3, l3, BP, EP);
  print_tree (t3);
  b3 = verif_sum ( t3, t3.begin () ) ; 
  cout << "verif_sum (t3) = " << b3 << endl ;
  cout << endl; 

  l4.clear ();
  insertl (l4, v4, EL);
  t4.clear ();
  list2tree (t4, l4, BP, EP);
  print_tree (t4);
  b4 = verif_sum ( t4, t4.begin () ) ; 
  cout << "verif_sum (t4) = " << b4 << endl ;
  cout << endl; 

  cout << endl ;
  return 0 ;
} // end main
// -------------------------------------------------------------------
