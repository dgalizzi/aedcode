// $Id$
/* COMIENZO DE DESCRIPCION

  Ejemplos de programacion funcional con arboles ordenados orientados, 
  apply, remove\_if, reduce, any, all, reduce\_up, copy\_if, sort, 
  height\_if. keywords: arbol orientado

  FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c util_tree.cpp
//        icc -w -c treeprogf.cpp
//        icc -w -o treeprogf.exe treeprogf.o util.o util_tree.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c util_tree.cpp
//        g++ -w -c treeprogf.cpp
//        g++ -w -o treeprogf.exe treeprogf.o util.o util_tree.o
//
// -----------------------------------------------------------------
#include <iostream>
#include "./tree.h"
#include "./util.h"
#include "./util_tree.h"

using namespace std;
using namespace aed;

// -----------------------------------------------------------------
// Dado un arbol T y una funcion escalar T f(t), apply(T,f)
// modifica los valores del arbol de forma de que los
// valores nodales pasan a ser `*n = f(*n)'. 
template <class T> 
void apply (tree<T> & Q, typename tree<T>::iterator n,
            T (*f) (T)) {
  typename tree<T>::iterator c ;
  *n = f (*n);
  c = n.lchild ();
  while (c != Q.end()) apply (Q, c++, f);
}
template <class T> 
void apply (tree<T> & Q, T (*f)(T)) {
  if (Q.begin() != Q.end()) apply (Q, Q.begin(), f);
}

// -----------------------------------------------------------------
// Dado un arbol `T' y una funcion predicado `bol pred(t)', 
// elimina aquellas ramas del arbol cuya raiz satisface
// el predicado `pred'. 
template<class T>
typename tree<T>::iterator 
remove_if (tree <T> & Q, typename tree<T>::iterator n,
	   bool (*pred_fun) (T) ) {
  typename tree<T>::iterator c ;
  if (pred_fun (*n) ) 
    n = Q.erase(n);
  else {
    c = n.lchild();
    while (c != Q.end()) c = remove_if (Q, c, pred_fun);
    n++;
  } // end if
  return n;
}
template<class T>
void remove_if (tree<T> & Q, bool (*pred_fun) (T) ) {
  if (Q.begin() != Q.end()) remove_if (Q, Q.begin(), pred_fun);
}

// -----------------------------------------------------------------
// Aqui f = id (es la identidad):
template<class T> T id (T t) { return t; }

// -----------------------------------------------------------------
// Dado un arbol "T", una funcion asociativa "z=afun(x,y)" con valor
// nulo "init_val" y una funcion de mapeo "w = f (x)",
// "reduce (T, afun, init_val, f)" calcula
// "afun (init_val, f(n_1), f(n_2), ....,f(n_m))", donde "m" es el 
// numero de nodos del arbol, "init_val" es el elemento neutro para 
// la funcion "afun", es decir, tal que 
// "afun (w,init_val) = afun (w)" para todo "w".
//
// Algunas posibilidades comunes son:
// afun (x,y) = x + y, init_val = 0, 
//    reduce (T, afun, f) -> suma de los valores nodales, 
// afun (x,y) = x * y, init_val = 1, 
//    reduce (T, afun, f) -> producto de los valores nodales, 
// afun (x,y) = max (x,y), init_val = -infty
//    reduce (T, afun, f) -> maximo de los valores nodales, 
// afun (x,y) = min (x,y), init_val = +\infty
//    reduce (T, afun, f) -> minimo de los valores nodales, 
// afun (x,y) = |x| + |y|, init_val = 0, 
//    reduce (T, afun, f) -> suma de los valores absolutos nodales, 
// afun (x,y) = sqrt (x*x + y*y), init_val = 0, 
//    reduce (T, afun, f) -> norma euclidea de los valores nodales
// afun (x,y) = sqrt{x^2 + y^2}, init_val = 0, 
//    reduce (T, afun, f) -> norma euclidea de los valores nodales
// afun (x,y) = x && y, init_val = true, f = pred (1 funcion predicado)
//    reduce (T, afun, f) -> all (pred)
// afun (x,y) = x || y, init_val = false, f = pred
//    reduce (T, afun, f) -> any (pred)
// afun (x,y) = x + y, init_val = 0, f (x) = x^2
//    reduce (T, afun, f) -> suma de los cuadrados
//
// -----------------------------------------------------------------
template <class T, class U>
U reduce (tree <T> & Q, typename tree<T>::iterator n,
	  U (*assoc_fun) (U,U), U init_val,
	  U (*f) (T) ) {
  U val = init_val;
  U u ;
  typename tree<T>::iterator c ;
  c = n.lchild ();
  while (c != Q.end()) {
    u = reduce (Q, c++, assoc_fun, init_val, f);
    val = assoc_fun (u,val);
  } // end while
  return assoc_fun ( f (*n), val );
}
template <class T, class U>
 U reduce (tree <T> & Q, U (*assoc_fun) (U,U), U init_val,
 U (*f) (T)) {
 if (Q.begin() != Q.end ()) 
    return reduce (Q, Q.begin(), assoc_fun, init_val, f);
}

// -----------------------------------------------------------------
// Este es un caso particular en el cual la funcion de mapeo es
// la identidad. 
template <class T>
T reduce (tree <T> & Q, T (*assoc_fun) (T,T), T init_val) {
  if (Q.begin() != Q.end()) 
    return reduce (Q, Q.begin (), assoc_fun, init_val, id <T> );
}

// -----------------------------------------------------------------
// Verifica si algunos de los valores nodales satisface `pred'
template<class T>
bool any (tree <T> & Q, typename tree<T>::iterator n,
	  bool (*pred_fun) (T)) {
  typename tree<T>::iterator c ;
  if ( pred_fun (*n) ) return true;
  c = n.lchild ();
  while (c != Q.end()) if (pred_fun (*c++)) return true;
  return false;
}
template <class T>
bool any (tree <T> & Q, bool (*pred_fun) (T)) {
  if (Q.begin() == Q.end()) 
    return false;
  else 
    return any (Q, Q.begin(), pred_fun);
}

// -----------------------------------------------------------------
// Verifica si todos los valores nodales satisface `pred'
// Debe siempre valer all(T,pred) == !any(T,not_pred);
// donde `not_pred' es el predicado negado de `pred'.
template<class T>
 bool all (tree<T> &Q,typename tree<T>::iterator n,
	  bool (*pred_fun)(T j)) {
  if (!pred_fun(*n)) return false;
  typename tree<T>::iterator c = n.lchild();
  while (c!=Q.end()) if (!pred_fun(*c++)) return false;
  return true;
}
template<class T>
bool all(tree<T> &Q,bool (*pred_fun)(T)) {
  if (Q.begin()==Q.end()) return true;
  else return all(Q,Q.begin(),pred_fun);
}

// -----------------------------------------------------------------
// Hace que el valor de un nod interior sea el resultado de aplicar
// la funcion asociativa a los hijos, es decir
// `*n = afun(init_val,s_1,s_2,...,s_m)',
// donde `s_j' son los hijos de `n'
template<class T> void
reduce_up (tree<T> & Q, typename tree<T>::iterator n,
	  T (*afun) (T,T), T init_val) {
  typename tree<T>::iterator c ;
  T val ;
  c = n.lchild();
  if (c == Q.end()) return;
  val = init_val;
  while (c != Q.end()) {
    reduce_up (Q, c, afun, init_val);
    val = afun (val,*c);
    c++;
  }
  *n = val;
}
template <class T> void 
reduce_up (tree<T> & Q,T (*afun)(T,T), T init_val) {
  reduce_up (Q, Q.begin(), afun, init_val);
}

// -----------------------------------------------------------------
// Copia el arbol `R' en `Q' pero excluyendo las ramas
// que satisface `pred'. Deberia ser equivalente a `Q=R' seguido
// de `remove_if(Q,not_pred)'
template<class T>
typename tree<T>::iterator 
copy_if (tree<T> &Q,typename tree<T>::iterator nq,
	 tree<T> &R,typename tree<T>::iterator nr,
	 bool (*pred_fun)(T)) {
  if (pred_fun(*nr)) {
    nq = Q.insert(nq,*nr);
    typename tree<T>::iterator 
      cr = nr.lchild(),
      cq = nq.lchild();
    while (cr != R.end()) cq = copy_if(Q,cq,R,cr++,pred_fun);
    nq++;
  }
  return nq;
}
template<class T>
void copy_if (tree<T> & Q, tree<T> & R, bool (*pred_fun)(T j)) {
  if (R.begin() != R.end()) 
    copy_if (Q, Q.begin(), R, R.begin(), pred_fun);
}

// -----------------------------------------------------------------
// Ordena los hijos del arbol usando la funcion de comparacion
// `comp'. `comp(x,y)' debe retornar 1 si `x<y', -1 si `x>y'
// y 0 si `x==y'. 
template<class T> void
sort(tree<T> &Q,typename tree<T>::iterator n,
     int (*comp)(T,T)) {
  typedef tree<T> tree_t;
  typedef typename tree<T>::iterator node_t;
  typedef list< tree<T> > list_t;
  typedef typename list_t::iterator pos_t;
  list_t L;
  T tmin ;
  node_t cmin ;
  pos_t p = L.begin();
  while (true) {
    node_t c = n.lchild();
    if (c == Q.end()) break;
    cmin = c;
    tmin = *c;
    c++;
    while (c!=Q.end()) {
      if (comp(*c,tmin)==1) {
	cmin = c;
	tmin = *c;
      }
      c++;
    }
    p = L.insert(p,tree_t());
    p->splice(p->begin(),cmin);
    p++;
  }
  p = L.begin();
  node_t c = n.lchild();
  while (p != L.end()) {
    c = Q.splice (c,p->begin());
    sort (Q,c,comp);
    p = L.erase (p);
    c++;
  }
}
template<class T> 
void sort (tree <T> & Q, int (*comp) (T,T)) {
  if ( Q.begin() != Q.end())
    sort (Q, Q.begin(), comp);
}

// -----------------------------------------------------------------
// Calcula la altura de la parte del arbol que satisface pred.
// 
//   h = height_if(T,pred);
// Equivale a hacer:
//   copy_if(T,R,pred); h = height(R);
// o tambien:
//   R = T;
//   remove_if(R,not_pred);
//   h = h = height(R);
template<class T>
int height_if (tree<T> & Q,typename tree<T>::iterator n,
	   bool (* pred_fun) (T) ) {
  if ( !pred_fun (*n)) return -1;
  typename tree<T>::iterator c ;
  c = n.lchild();
  int hcmax = -1;
  while (c != Q.end()) {
    int hc = height_if (Q, c++, pred_fun);
    if (hc > hcmax) hcmax = hc;
  }
  return hcmax + 1;
}
template<class T>
int height_if (tree <T> & Q, bool (*pred_fun) (T) ) {
  if (Q.begin() == Q.end()) return 0;
  else 
   return height_if (Q, Q.begin(), pred_fun);
}

// -----------------------------------------------------------------
// Encuentra el camino mas largo que satisface la relacion de orden
// `comp(x,y)'.
template<class T>
void max_path_if (tree<T> & Q, typename tree<T>::iterator n,
		int (*comp) (T,T), list<T> & L) {
  list<T> L2;
  typename tree<T>::iterator cmax, c ;
  int lmax = 0;
  c = n.lchild();
  while (c != Q.end()) {
    L2.clear();
    if ( comp (*n,*c)>0) {
      max_path_if (Q, c, comp, L2);
      if (L2.size() > lmax) {
	cmax = c; 
	lmax = L2.size();
      }
    }
    c++;
  }
  L.clear ();
  L.insert (L.begin(),*n);
  if (cmax != Q.end()) {
    max_path_if (Q,cmax,comp,L2);
    L.splice (L.end(), L2);
  }
}
template<class T>
void max_path_if (tree<T> &Q,int (*comp)(T,T),list<T> &L) {
  L.clear ();
  if (Q.begin() != Q.end()) max_path_if (Q, Q.begin(), comp,L);
}

// -----------------------------------------------------------------
// Varios predicados:
bool oddp      (int j) { return (j % 2 != 0); }
bool evenp     (int j) { return !oddp (j); }
bool non_neg_p (int j) { return j >= 0; }
bool neg_p     (int j) { return !non_neg_p (j); }

// -----------------------------------------------------------------
// Varias funciones asociativas:
int suma   (int  j, int  k) { return j + k; }
int  max   (int  j, int  k) { return (j > k ? j : k); }
int  min   (int  j, int  k) { return (j > k ? k : j); }
bool and_f (bool x, bool y) { return x && y; }
bool or_f  (bool x, bool y) { return x || y; }

// -----------------------------------------------------------------
// Funciones de comparacion:
int menor     (int j, int k) { 
  return (j < k ? 1 : j > k ? -1 : 0); 
}
int mayor     (int j,int k) { 
  return (j > k ? 1 : j < k ? -1 : 0); 
}
int menor_abs (int j, int k) { 
  menor ( abs (j), abs (k) );
}
int mayor_abs (int j, int k) { 
  mayor ( abs (j), abs (k) );
}

// -----------------------------------------------------------------
// Funcion de mapeo
const int M = 10;
int fun (int j) { return j-M; }

// -----------------------------------------------------------------
int main() {
  tree<int> T,Q,S;
  list<int> L;
  for (int j=0; j<20; j++) {
    T.clear();
    make_random_tree(T,2*M,2);
    cout << "arbol random: " << endl;
    print_tree(T);
    
    cout << "\n--- APPLY\n";
    apply(T,fun);
    cout << "T-" << M << ": " << endl;
    print_tree(T);

    cout << "\n--- ALL\n";
    cout << "Todos pares? : " << (all(T,evenp)? "si" : "no") << endl;
    cout << "Todos impares? : " << (all(T,oddp)? "si" : "no") << endl;
    cout << "Alguno par? : " << (any(T,evenp)? "si" : "no") << endl;
    cout << "Alguno impar? : " << (any(T,oddp)? "si" : "no") << endl;

    cout << "Usando reduce: \n";
    cout << "Todos pares? : " 
	 << (reduce(T,and_f,true,evenp)? "si" : "no") << endl;
    cout << "Todos impares? : " 
	 << (reduce(T,and_f,true,oddp)? "si" : "no") << endl;
    cout << "Alguno par? : " 
	 << (reduce(T,or_f,false,evenp)? "si" : "no") << endl;
    cout << "Alguno impar? : " 
	 << (reduce(T,or_f,false,oddp)? "si" : "no") << endl;

    cout << "\n--- REMOVE_IF\n";

    Q = T;
    remove_if(Q,&oddp);
    cout << "saca impares: " << endl;
    print_tree(Q);

    S.clear();
    copy_if(S,T,&evenp);
    cout << "copia pares: " << endl;
    print_tree(S);

    Q = T;
    remove_if(Q,&evenp);
    cout << "saca pares: " << endl;
    print_tree(Q);

    Q = T;
    remove_if(Q,&non_neg_p);
    cout << "saca non neg. " << endl;
    print_tree(Q);

    Q = T;
    remove_if(Q,&neg_p);
    cout << "saca neg.: " << endl;
    print_tree(Q);

    cout << "\n--- REDUCE_UP\n";

    Q = T;
    reduce_up(Q,suma,0);
    cout << "reduce-up(suma): "  << endl;
    print_tree(Q);

    Q = T;
    reduce_up(Q,max,-INT_MAX);
    cout << "reduce-up(max): "  << endl;
    print_tree(Q);

    Q = T;
    reduce_up(Q,min,+INT_MAX);
    cout << "reduce-up(min): "  << endl;
    print_tree(Q);

    cout << "\n--- SORT\n";

    Q = T;
    sort(Q,menor);
    cout << "sort(Q,menor): "  << endl;
    print_tree(Q);

    sort(Q,mayor);
    cout << "sort(Q,mayor): "  << endl;
    print_tree(Q);

    sort(Q,menor_abs);
    cout << "sort(Q,menor): "  << endl;
    print_tree(Q);

    sort(Q,mayor_abs);
    cout << "sort(Q,mayor): "  << endl;
    print_tree(Q);

    cout << "\n--- REDUCE\n";

    cout << "suma: " << reduce(T,suma,0) << endl;
    cout << "max: " << reduce(T,max,-INT_MAX) << endl;
    cout << "min: " << reduce(T,min,+INT_MAX) << endl;

    cout << "\n--- ANY\n";

    cout << "contiene un impar?: " << (any(T,oddp)? "si" : "no") << endl;
    cout << "contiene un par?: " << (any(T,evenp)? "si" : "no") << endl;

    cout << "contiene un elemento no neg.? : " 
	 << (any(T,non_neg_p)? "si" : "no") << endl;
    cout << "contiene un elemento neg.? : " 
	 << (any(T,neg_p)? "si" : "no") << endl;

    cout << "\n---HEIGHT_IF\n";

    cout << "altura par?: " << height_if(T,evenp) << endl;
    cout << "altura impar?: " << height_if(T,oddp) << endl;
    cout << "altura negativos?: " << height_if(T,neg_p) << endl;
    cout << "altura no negativos?: " << height_if(T,non_neg_p) << endl;

    cout << "\n---MAX_PATH_IF\n";

    max_path_if(Q,menor,L);
    cout << "max. camino creciente: "; printl(L);

    max_path_if(Q,mayor,L);
    cout << "max. camino decreciente: "; printl(L);

    max_path_if(Q,menor_abs,L);
    cout << "max. camino creciente (abs): "; printl(L);

    max_path_if(Q,mayor_abs,L);
    cout << "max. camino decreciente (abs): "; printl(L);
    cout << "----------------------------------\n";
  }

  cout << endl ;
  return 0 ;
}
// -----------------------------------------------------------------
