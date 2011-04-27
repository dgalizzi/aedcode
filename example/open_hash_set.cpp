// $Id$

/*
  COMIENZO DE DESCRIPCION

  Diccionarios con tablas de dispersion abierta:
  dado el archivo de cabecera {\tt hash_set.h}, escriba
  el correspondiente archivo {\tt open_hash_set.cpp} con la 
  implementaci\'on de las funciones indicadas a continuaci\'on,
  (i)  Sencillas:
       {\tt erase (iterator_t p)},
       {\tt clear ()},
       {\tt size ()};
  (ii) M\'as elaboradas: 
       {\tt insert (const key_t & x)}; 
       {\tt find (const key_t & x)}; 
       {\tt erase (const key_t & x)}.
  Keywords: conjunto, diccionario

  FIN DE DESCRIPCION */

// -----------------------------------------------------------------
// Inicio del Archivo de Cabecera 'hash_set.h':

#ifndef HASH_SET_H
#define HASH_SET_H

#include <list>
#include <vector>
#include <pair.h>

typedef int key_t;
typedef int (*hash_fun)(key_t x);

class hash_set;

class iterator_t {
  friend class hash_set;
 private:
  int bucket;                   // numero de cubeta
  std::list<key_t>::iterator p; // posicion en la lista
  iterator_t(int bucket_a, std::list<key_t>::iterator p_a) 
    : bucket(bucket_a), p(p_a) { }
 public:
  iterator_t() { };
  bool operator == (iterator_t q);
  bool operator != (iterator_t q);
};

class hash_set {
 private:
  int B;       // cantidad de cubetas
  int count;   // cantidad de elementos en el conjunto
  hash_fun h;  // puntero a la funcion de hash
  std::vector< std::list<key_t> > v; // vector de cubetas
 public:
  hash_set(const hash_set& s);
  hash_set(int B_a,hash_fun h_a) : B(B_a), v(B), h(h_a), count(0) {}
  iterator_t begin();
  iterator_t end();
  iterator_t next(iterator_t p);
  key_t retrieve(iterator_t p);
  std::pair<iterator_t,bool> insert(const key_t& x);
  iterator_t find(const key_t& x);
  int erase(const key_t& x);
  void erase(iterator_t p);
  void clear();
  int size();
};

#endif /* HASH_SET_H */

// Fin del Archivo de Cabecera
// -------------------------------------------------------------------


// -------------------------------------------------------------------
// SOLUCIONES:

// ===================================================================
// a) Funciones "Sencillas":

// -------------------------------------------------------------------
void hash_set::erase(iterator_t p) {
  v [p.bucket].erase(p.p);
} // end void

// -------------------------------------------------------------------
void hash_set::clear() {
  count = 0;
  for (int j=0; j<B; j++) v [j].clear();
} // end void

// -------------------------------------------------------------------
int hash_set::size () { 
  return count; 
} // end int


// ===================================================================
// b) Funciones "Mas Elaboradas":

// -------------------------------------------------------------------
std::pair<iterator_t,bool> hash_set::insert (const key_t& x) 
{
  int b = h (x) % B;
  std::list<key_t> &L = v[b];
  std::list<key_t>::iterator p = L.begin();
  while (p != L.end() && *p != x) p++;
  if (p != L.end() && *p == x)
    return std::pair<iterator_t,bool>(iterator_t(b,p),false);
  else {
    count++;
    p = L.insert (p,x);
    return std::pair<iterator_t,bool>(iterator_t(b,p),true);
  } // end if
} // end std

// -------------------------------------------------------------------
iterator_t hash_set::find (const key_t& x) 
{
  int b = h (x) % B;
  std::list<key_t> &L = v [b];
  std::list<key_t>::iterator p = L.begin();
  while (p != L.end() && *p != x) p++;
  if (p != L.end() && *p == x) 
       return iterator_t(b,p);
  else return end();
} //end iterator_t

// -------------------------------------------------------------------
int hash_set::erase (const key_t& x) {
  int b = h(x) % B;
  std::list<key_t> &L = v[b];
  std::list<key_t>::iterator p = L.begin();
  while (p!=L.end() && *p!=x) p++;
  if (p != L.end() && *p==x) {
    L.erase (p);
    count--;
    return 1; } 
  else 
    return 0;
} // end int

// ===================================================================
