// $Id: set_vector_bit.h,v 1.1 2004/06/18 21:48:06 mstorti Exp $

/*
  COMIENZO DE DESCRIPCION
 
  Dado el siguiente archivo de cabecera {\tt set.h} escriba
  el correspondiente archivo {\tt set.cpp} con la implementaci\'on
  de las funciones indicadas a continuaci\'on:
  (i) Sencillas:
      {\tt end ()},
      {\tt erase (iterator_t p)},
      {\tt clear ()},
      {\tt retrieve (iterator_t p)};
  (ii) M\'as elaboradas:
      {\tt size ()},
      {\tt insert (const elem_t & x)},
      {\tt find (const elem_t & x)},
      {\tt erase (const elem_t & x)};
  (iii) Binarias:
      {\tt set_union (set &A,set &B, set &C)},
      {\tt set_intersection (set &A,set &B,set &C)},
      {\tt set_difference (set &A,set &B,set &C)}.
   Nota: {\tt N} es la cantidad de elementos del conjunto 
   universal, asuma que es una variable global ya definida.
  Keywords: conjunto

  FIN DE DESCRIPCION */

// -----------------------------------------------------------------
// Inicio del Archivo de Cabecera 'set.h':
const int N = 10;
#ifndef SET_H
#define SET_H

#include <vector>
#include <pair.h>

typedef int elem_t;                            
typedef int    (*index_fun)(const elem_t& e); // index   <-- element
typedef elem_t (*element_fun)(int i);         // element <-- index

typedef int iterator_t;

class set {
private:
  std::vector<bool> v; // vector de bits
  index_fun   index;   // index   <-- element
  element_fun element; // element <-- index
public:
  set(index_fun ifun, element_fun efun) 
    : v(N,false), index(ifun), element(efun) { }
  set(const set& S) 
    : v(S.v), index(S.index), element(S.element) { }
  iterator_t begin();
  iterator_t end();
  iterator_t next(iterator_t p);
  elem_t retrieve(iterator_t p);
  std::pair<iterator_t,bool> insert(const elem_t& x);
  iterator_t find(const elem_t& x);
  int erase(const elem_t& x);
  void erase(iterator_t p);
  void clear();
  int size();

  friend void set_union(const set &A, const set &B, set &C);
  friend void set_intersection(const set &A, const set &B, set &C);
  friend void set_difference(const set &A, const set &B, set &C);
};

void set_union(const set &A,const set &B, set &C);
void set_intersection(const set &A, const set &B, set &C);
void set_difference(const set &A, const set &B, set &C);

#endif /* SET_H */

// Fin del Archivo de Cabecera
// -------------------------------------------------------------------


// -------------------------------------------------------------------
// SOLUCIONES:

// ===================================================================
// a) Funciones "Sencillas":

// -------------------------------------------------------------------
iterator_t set::end ()  { return N ; }

// -------------------------------------------------------------------
void set::erase(iterator_t p) {
  v [p] = false;
} // end void

// -------------------------------------------------------------------
void set::clear () {
  for (int j = 0; j < v.size(); j++)  v [j] = false;
} // end void

// -------------------------------------------------------------------
elem_t set::retrieve (iterator_t p) { 
  return element (p);
} // end elem_t


// ===================================================================
// b) Funciones "Mas Elaboradas":

// -------------------------------------------------------------------
int set::size () { 
  int count = 0;
  for (int j = 0; j < v.size(); j++) 
    if ( v[j] == true ) count++;
  return count; 
} // end int

// -------------------------------------------------------------------
std::pair<iterator_t,bool> set::insert(const elem_t& x) {
  int i = index(x);
  if ( v[i] == true )
    return std::pair<iterator_t,bool>(i,false);
  else {
    v [i] = true;
    return std::pair<iterator_t,bool>(i,true);
  } // end if
} // end std

// -------------------------------------------------------------------
iterator_t set::find (const elem_t& x) {
  int i = index (x);
  if ( v[i] == true )
    return i;
  else 
    return N;
} // end iterator

// -------------------------------------------------------------------
int set::erase (const elem_t& x) {
  int i = index (x);
  if ( v [i] == true ){
    v [i] = false;
    return 1; }
  else
    return 0;
} // end int


// ===================================================================
// c) Binarias:

// -------------------------------------------------------------------
void set_union (const set &A, const set &B, set &C) {
  for (int j = 0; j < N; j++) 
    C.v[j] = A.v [j] || B.v [j];
} // end void

// -------------------------------------------------------------------
void set_intersection (const set &A, const set &B, set &C) {
  for (int j = 0; j < N; j++) 
    C.v[j] = A.v [j] && B.v [j];
} // end void

// -------------------------------------------------------------------
void set_difference(const set &A, const set &B, set &C) {
  for (int j = 0; j < N; j++) 
    C.v[j] = A.v [j] && ! B.v [j];
} // end void

// ===================================================================
