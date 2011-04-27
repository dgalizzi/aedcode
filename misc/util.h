// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: util.h,v 1.7 2004/06/15 00:25:39 mstorti Exp $
#ifndef AED_UTIL_H
#define AED_UTIL_H

#include <list>
#include <vector>

double drand();
int irand(int M);

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
template<class T>
void insertl(std::list<T> &L,typename std::list<T>::iterator p,
	     T *v, T term) {
  while (*v!=term) { p = L.insert(p,*v++); p++; }
}

// Inserta elementos del vector `v' en la lista `L'
// en la posicion `p'. Se detiene cuando encuentra
// el elemento `term' en `v'.
// Util para generar listas de la siguiente forma.
// int v[]={1,2,3,4,3,2,1,2,3,4,-1};
// list<int> L; insertl(L,v,-1);
template<class T>
void insertl(std::list<T> &L, T *v, T term) {
  insertl(L,L.begin(),v,term);
}

template<class T>
void printl(std::list<T> &L) {
  typename std::list<T>::iterator p = L.begin();
  while (p!=L.end()) std::cout << *p++ << " ";
  std::cout << std::endl;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
template<class T>
void insertv(std::vector<T> &V,typename std::vector<T>::iterator p,
	     T *v, T term) {
  while (*v!=term) { p = V.insert(p,*v++); p++; }
}

template<class T>
void insertv(std::vector<T> &V, T *v, T term) {
  insertv(V,V.begin(),v,term);
}

template<class T>
void print(std::vector<T> &v) {
  for (int j=0; j<v.size(); j++) {
    std::cout << v[j] << " ";
  }
  std::cout << std::endl;
}

#endif
