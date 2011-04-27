// $Id$
/* COMIENZO DE DESCRIPCION

Diversas ejemplos de Programaci\'on Funcional sobre un 
Arbol Binario(AB) [se asume que sus etiquetas 
son o bien n\'umeros enteros positivos o bien dobles] (ver en 
pfunc\_btree.cpp las equivalentes para \'arbol ordenado orientado). 
keywords: arbol binario.

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
//
// Programacion funcional
//
// Dados: 
//
//  . un arbol "T"
//  . una funcion asociativa  "z = f_asociat (x,y)", 
//  . con valor neutro        "v_ini"
//  . y una funcion predicado "f = f_predica (x)",
//
// entonces, la funcion de reduccion:
//
// "reduce (T, f_asociat, v_ini, f_predica)" 
//
// calcula
//
// "f_asociat (v_ini, f (n_1), f (n_2), ....,f (n_m))"
//  
// donde "m"     es el numero de nodos del arbol, 
//       "v_ini" es el elemento neutro para la funcion "f_asociat", 
//               es decir, tal que 
//               "f_asociat (u,v_ini) = f_asociat (u)" para todo "u".
//
// Algunas posibilidades mas frecuentes son:
//
// si "f_asociat (x,y) = x + y", con "v_ini = 0", entonces
//    "reduce (T, f_asociat)" da la suma de las etiquetas
//
// si "f_asociat (x,y) = x * y", con "v_ini = 1", entonces
//    "reduce (T, f_asociat)" da el producto de las etiquetas
//
// si "f_asociat (x,y) = max (x,y)", con "v_ini = -infty", entonces
//    "reduce (T, f_asociat)" da el maximo de las etiquetas
//
// si "f_asociat (x,y) = min (x,y)", con "v_ini = +infty", entonces
//    "reduce (T, f_asociat)" da el minimo de las etiquetas
//
// si "f_asociat (x,y) = |x| + |y|", con "v_ini = 0", entonces
//    "reduce (T, f_asociat)" 
//    da la suma de los valores absolutos de las etiquetas
//
// si "f_asociat (x,y) = sqrt (x*x + y*y)", con "v_ini = 0", entonces
//    "reduce (T, f_asociat)" da la norma euclidea de las etiquetas
//
// si "f_asociat (x,y) = x && y", con "v_ini = true", entonces
//    "reduce (T, f_asociat, f_predica)" da True/False segun si la 
//    funcion predicado "f_predica" es True/False para TODAS las etiquetas
//
// si "f_asociat (x,y) = x || y", con "v_ini = false", entonces
//    "reduce (T, f_asociat, f_predica)" da True/False segun si la 
//    funcion predicado "f_predica" es True/False para ALGUNA etiqueta
//
// si "f_asociat (x,y) = x + y", con "v_ini = 0" y 
//    "f_predica (x) = x^2, entonces
//    "reduce (T, f_asociat, f_predica)" da la suma de los cuadrados 
//     de las etiquetas
//
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_btree.cpp
//        icc -w -c progfunc_bb.cpp
//        icc -w -o progfunc_bb.exe progfunc_bb.o util.o util_btree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_btree.cpp
//        g++ -w -c progfunc_bb.cpp
//        g++ -w -o progfunc_bb.exe progfunc_bb.o util.o util_btree.o
//        progfunc_bb.exe
// -----------------------------------------------------------------
#include <iostream>
#include <math.h>     // tiene a "fmod (x,y)" (x mod y, para dobles)
#include "./util.h"
#include "./btree.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

// -----------------------------------------------------------------
// algunas funciones ASOCIATIVAS:
bool and_f (bool x, bool y) { return x && y; }
bool or_f  (bool x, bool y) { return x || y; }
template <class T> T suma (T x, T y) {return (x + y);}
template <class T> T max  (T x, T y) {return (x > y ? x : y);}
template <class T> T min  (T x, T y) {return (x < y ? x : y);}
template <class T> T root (T x, T y) {return T (sqrt(double(x*x+y*y)));}

// -----------------------------------------------------------------
// algunas funciones PREDICADOS:
bool oddp  (int    j) {return (j % 2      != 0);} // mod p/enteros
bool evenp (int    j) {return (j % 2      == 0);} // mod p/enteros
bool oddp  (double j) {return (fmod (j,2) != 0);} // mod p/dobles
bool evenp (double j) {return (fmod (j,2) == 0);} // mod p/dobles
template <class T> bool non_neg_p (T j) {return (j >= 0);}
template <class T> bool neg_p     (T j) {return (j <  0);}
template <class T> T f_iden (T x) {return x;  }   // la identidad
template <class T> T square (T x) {return x*x;}   // el cuadrado

// -----------------------------------------------------------------
// esta funcion de REDUCCION generica hace el trabajo RECURSIVO
template <class T, class U>
U reduce (btree<T> & Q, 
          typename btree<T>::iterator n,
	  U (*f_asociat) (U,U), 
          U   v_ini,
	  U (*f_predica) (T) ) {
  typename btree<T>::iterator c1, c2 ;
  U valor ;
  U h1, h2 ;
  if ( n == Q.end() ) return v_ini ;
  c1 = n.left  (); 
  c2 = n.right (); 
  h1 = reduce (Q, c1, f_asociat, v_ini, f_predica);
  h2 = reduce (Q, c2, f_asociat, v_ini, f_predica);
  valor = v_ini + (h1 + h2) ;
  valor = f_asociat (h1,valor);
  valor = f_asociat (h2,valor);
  return  f_asociat (f_predica (*n), valor);
}
// "wrapper" usual con ambas funciones asociativa y predicado
template <class T, class U>
U reduce (btree <T> & Q, 
          U (*f_asociat) (U,U), 
          U   v_ini,
          U (*f_predica) (T) ) {
 U z ;
 if (Q.begin() != Q.end ()) 
   z = reduce (Q, Q.begin(), f_asociat, v_ini, f_predica);
 else
   z = v_ini ;
 return z ;
}
// "wrapper" especial cuando el predicado se reduce a la identidad
template <class T>
T reduce (btree <T> & Q, 
          T (*f_asociat) (T,T), 
          T   v_ini) {
  T z ;
  if (Q.begin() != Q.end()) 
    z = reduce (Q, Q.begin (), f_asociat, v_ini, f_iden<T>);
  else
    z = v_ini;
  return z ; 
}

// -------------------------------------------------------------------
// auxiliar para las tareas
template <class T>
void tareas (btree <T> & Q) {  
  T     i ;
  T cero = 0 ;
  T semilla = INT_MAX ;
  bool  b ;

  cout << endl ;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++ " << endl ;
  cout << "Arbol ; Q: "; Q.lisp_print (); cout << endl;
 
  b = reduce (Q, and_f,  true, evenp) ;
  cout << endl ;
  cout << "todos pares   ? : " << (b ? "si" : "no") << endl;

  b = reduce (Q, and_f,  true,  oddp) ;
  cout << endl ;
  cout << "todos impares ? : " << (b ? "si" : "no") << endl;
  
  b = reduce (Q,  or_f, false, evenp) ;
  cout << endl ;
  cout << "alguno par    ? : " << (b ? "si" : "no") << endl;
  
  b = reduce (Q,  or_f, false, oddp) ;
  cout << endl ;
  cout << "alguno impar  ? : " << (b ? "si" : "no") << endl;
  
  i = reduce (Q, max, -semilla) ; 
  cout << endl ;
  cout << "max. etiquetas  = " << i << endl;
  
  i = reduce (Q, min, semilla) ; 
  cout << endl ;
  cout << "min. etiquetas  = " << i << endl;

  i = reduce (Q, suma, cero) ; 
  cout << endl ;
  cout << "suma etiquetas  = " << i << endl;
    
  i = reduce (Q, root, cero) ; 
  cout << endl ;
  cout << "norma L2        = " << i << endl;

  i = reduce (Q, suma, cero, square) ; 
  cout << endl ;
  cout << "suma cuadrados etiquetas = " << i << endl;

}

// -------------------------------------------------------------------
int main () {
  int kaso = 1 ;

  cout << endl ;
  cout << "Ejemplos de Programacion Funcional en   " << endl ;
  cout << "un Arbol Binario (AB) usando reduce ... " << endl ;

  if      (kaso == 1) { 
    typedef double dato;
    const dato BP=-1, EP=-2, NE=-3, EL=-4;
    btree <dato> Q;
    tareas (Q); 
    list <dato> L;
    dato l[] = {BP,5,BP,7,NE,3,EP,BP,8,NE,BP,9,6,2,EP,EP,EP,EL};
    insertl (L, l, EL);
    list2btree (Q, L, BP, EP, NE);
    tareas (Q); 
    }
  else if (kaso == 2) { 
    btree <int> Q;
    for (int j = 0 ; j < 1 ; j++) {
      cout << endl ;
      Q.clear ();
      make_random_btree (Q, 10, 3); // 3.5
      cout << "Q: "; Q.lisp_print (); cout << endl;
      tareas (Q);  
    } // end j
  } // end if

  cout << endl ;
  return 0 ;
} // end main
// -------------------------------------------------------------------
