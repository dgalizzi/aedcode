// $Id$
/* COMIENZO DE DESCRIPCION

Diversas operaciones con \'arboles binarios:
semejante: determina si dos \'arboles tienen la misma estructura;
espejo   : determina si la estructura de un \'arbol es la espejada 
           de otro;
iguales  : determina si dos \'arboles son iguales,
           en estructura y contenido;
copiaespejo: copia un \'arbol en otro en forma espejada.
keywords: arbol binario

  FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include "./btree.h"
#include "./util.h"
#include "./util_btree.h"

using namespace aed;
using namespace std;

// -----------------------------------------------------------------
bool semejante (btree<int> & A, btree<int>:: iterator p,
                btree<int> & B, btree<int>:: iterator q) { 
  bool b1, b2 ;
  if      ( p == A.end () xor q == B.end () ) {
    return (false) ; }
  else if ( p == A.end () ) {
    return (true)  ; }
  else {
    b1 = semejante (A, p.left  (), B, q.left  ()) ;
    b2 = semejante (A, p.right (), B, q.right ()) ;
    return (b1 && b2) ;
  } // end if
}
bool semejante (btree<int> & A, btree<int> & B){
 return semejante (A, A.begin(), B, B.begin());
}

// -----------------------------------------------------------------
bool espejo (btree<int> & A, btree<int>:: iterator p,
             btree<int> & B, btree<int>:: iterator q) { 
  bool b1, b2 ;
  if      ( p == A.end () xor q == B.end () ) {
    return (false) ; }
  else if ( p == A.end () ) {
    return (true)  ; }
  else {
    b1 = espejo (A, p.left  (), B, q.right ()) ;
    b2 = espejo (A, p.right (), B, q.left  ()) ;
    return (b1 && b2) ;
  } // end if
}
bool espejo (btree<int> & A, btree<int> & B){
  return espejo (A, A.begin(), B, B.begin());
}

// -----------------------------------------------------------------
bool iguales (btree<int> & A, btree<int>:: iterator p,
              btree<int> & B, btree<int>:: iterator q) { 
  bool b1, b2 ;
  if      ( p == A.end () xor q == B.end () ) { 
    return (false) ; }
  else if ( p == A.end () ) { 
    return (true)  ; }
  else if ( *p != *q ) { 
    return (false) ; }
  else {
    b1 = iguales (A, p.right (), B, q.right ()); 
    b2 = iguales (A, p.left  (), B, q.left  ());
    return (b1 && b2) ;
  } // end if
}
bool iguales (btree<int> & A, btree<int> & B){
  return iguales (A, A.begin(), B, B.begin());
}

// -----------------------------------------------------------------
void copia_espejo (btree<int> & A, btree<int>:: iterator p) {
  btree <int> T ;
  if ( p == A.end () ) { 
    return ; }
  else {
    T.splice ( T.begin (), p.left  () );
    A.splice ( p.left  (), p.right () );
    A.splice ( p.right (), T.begin () );
    copia_espejo ( A, p.right () );
    copia_espejo ( A, p.left  () );
  } // end if
}
void copia_espejo (btree<int> & A){
  copia_espejo (A, A.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// El tipo de funciones de comparaci\'on
typedef bool (*comp_fun)(int,int);

// `n' debe ser dereferenciable.
// Si el sub\'arbol de `n' es ABB, entonces
// retorna `true' if min, max son los valores
// m\'inimos y m\'aximos del \'arbol.
// Si no es ABB entonces retorna `false' (los
// valores de min y max est\'an indefinidos).
bool abb_p(aed::btree<int> &T,
	   aed::btree<int>::iterator n,
	   int &min,int &max,comp_fun lessf) {
  aed::btree<int>::iterator l,r;
  int minr,maxr,minl,maxl;
  min = *n;
  max = *n;

  l = n.left();
  if (l!=T.end()) {
    if (!abb_p(T,l,minl,maxl,lessf) 
	|| lessf(*n,maxl)) return false;
    min = minl;
  } else min = *n;

  r = n.right();
  if (r!=T.end()) {
    if (!abb_p(T,r,minr,maxr,lessf) 
	|| lessf(minr,*n)) return false;
    max = maxr;
  } else max = *n;

  return true;
}

bool abb_p(aed::btree<int> &T,comp_fun lessf) {
  if (T.begin()==T.end()) return true;
  int min,max;
  return abb_p(T,T.begin(),min,max,lessf);
}

bool lessf(int x,int y) { return x<y; }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int is_full(aed::btree<int> &T,
            aed::btree<int>::iterator n,
            int &height, int &nnodes) {
  if (n==T.end()) {
    height = -1;
    nnodes = 0;
    return 1;
  }

  aed::btree<int>::iterator 
    l = n.left(), r = n.right();
  int hl,nnodesl,hr,nnodesr;
  if (!is_full(T,l,hl,nnodesl)) return 0;
  if (!is_full(T,r,hr,nnodesr)) return 0;
  if (hr!=hl) return 0;
  height = hr+1;
  nnodes = nnodesl+nnodesr+1;
  return 1;
}

int is_full(aed::btree<int> &T) {
  int height, nnodes;
  int r = is_full(T,T.begin(),height,nnodes);
  printf("is_full %d, height %d, nnodes %d\n",r,height,nnodes);
  return r;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void build_full_tree(aed::btree<int> &T,
                     int depth,int M) {
  if (depth==0) return;
  aed::btree<int> T1;

  aed::btree<int>::iterator n =
    T.insert(T.begin(),rand()%M);

  build_full_tree(T1,depth-1,M);
  T.splice(n.left(),T1.begin());

  build_full_tree(T1,depth-1,M);
  T.splice(n.right(),T1.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int remove_leafs(aed::btree<int> &T,
                 aed::btree<int>::iterator n,
                 int min_leaf_val) {
  if (n==T.end()) return 0;

  aed::btree<int>::iterator 
    l = n.left(), r = n.right();
  *n += remove_leafs(T,l,min_leaf_val) 
    + remove_leafs(T,r,min_leaf_val);

  l = n.left();
  r = n.right();
  if (l==T.end() && r==T.end() && *n<min_leaf_val) {
    int retval = *n;
    n = T.erase(n);
    return retval;
  } else return 0;
}

// -----------------------------------------------------------------
void  tareas (btree <int> & A, 
              btree <int> & B,
              btree <int> & C) {
  bool b1, b2, b3, b4, b5, b6 ;

  cout << endl ; cout << "A = " ; A.lisp_print () ; cout << endl ;
  cout << endl ; cout << "B = " ; B.lisp_print () ; cout << endl ;
  cout << endl ; cout << "C = " ; C.lisp_print () ; cout << endl ;

  b1 = semejante (A, B);
  b2 = semejante (A, C);
  cout << endl ; cout << "semejante (A,B) = " << b1 << endl ;
  cout << endl ; cout << "semejante (A,C) = " << b2 << endl ;

  b3 = iguales (A, A);
  b4 = iguales (A, B);
  cout << endl ; cout << "iguales (A,A)   = " << b3 << endl ;
  cout << endl ; cout << "iguales (A,B)   = " << b4 << endl ;

  b5 = espejo (A, B);
  b6 = espejo (A, C);
  cout << endl ; cout << "espejo (A,B)    = " << b5 << endl ;
  cout << endl ; cout << "espejo (A,C)    = " << b6 << endl ;

  copia_espejo (A) ;
  cout << endl ; cout << "copia_espejo (A) = " ; 
  A.lisp_print () ; cout << endl ;

}

typedef int dato;
const dato BP=-1, EP=-2, NE=-3, EL=-4;
void checkabb(int *l) {
  btree <dato> A;
  list <dato> L;
  L.clear();
  insertl (L, l, EL);
  A.clear();
  list2btree (A, L, BP, EP, NE);
  printf("tree: "); A.lisp_print();
  printf("\nA es ABB? %s\n---------\n",
  (abb_p(A,lessf)? "SI" : "NO"));
}

// -----------------------------------------------------------------
int main2 () {
  btree <int> A, B, C;
  int kaso = 5;
  cout << endl; 
  cout << "operaciones con Arboles Binarios " << endl ;

  if (kaso == 1) {
    typedef int dato;
    const dato BP=-1, EP=-2, NE=-3, EL=-4;
    btree <dato> A, B, C;
    list <dato> L1, L2;
    dato l1[]={BP,1,2,BP,8,BP,4,NE,5,EP,9,EP,EP,EL};
    dato l2[]={BP,1,BP,8,9,BP,4,5,NE,EP,EP,2,EP,EL};
    L1.clear();
    L2.clear();
    insertl (L1, l1, EL);
    insertl (L2, l2, EL);
    list2btree (A, L1, BP, EP, NE);
    list2btree (B, L2, BP, EP, NE);
    C = A ;
    tareas (A,B,C);
  } else if (kaso == 2) {
    make_random_btree (A, 10, 1.4);
    B = A ;
    make_random_btree (C,  8, 0.6);
    tareas (A,B,C);
  } else if (kaso == 3) {
    dato l1[]={BP,5,1,BP,7,6,BP,8,NE,9,EP,EP,EP,EL};
    checkabb(l1);

    dato l2[]={BP,5,1,BP,7,6,BP,8,9,NE,EP,EP,EP,EL};
    checkabb(l2);

    dato l3[]={BP,5,1,BP,7,4,BP,8,NE,9,EP,EP,EP,EL};
    checkabb(l3);

    dato l4[]={BP,5,1,BP,7,6,BP,8,2,NE,EP,EP,EP,EL};
    checkabb(l4);

    dato l5[]={BP,5,1,BP,7,6,BP,10,9,NE,EP,EP,EP,EL};
    checkabb(l5);
  } else if (kaso == 5) {
    make_random_btree (A, 10, 1.4);
    A.lisp_print();
    cout << endl;
    remove_leafs(A,A.begin(),10);
    A.lisp_print();
    cout << endl;
  }

  cout << endl;
  return 0 ;
} // end main

int main() {
  btree<int> T;
  build_full_tree(T,5,15);
  cout << endl ; cout << "T = " ; T.lisp_print() ; cout << endl ;
  int v = is_full(T);
}

