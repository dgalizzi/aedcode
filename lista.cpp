#include <iostream>
#include <aedsrc/lista.h>
#include <cstdlib>

using namespace std;
using namespace aed;

int list::MAX_SIZE=100;

list::list() : elems(new elem_t[MAX_SIZE]),
	       size(0) { }

list::~list() { delete[] elems; }

elem_t &list::retrieve(iterator_t p) {
  if (p<0 || p>=size) {
    cout << "p: mala posicion.\n";
    abort();
  }
  return elems[p]; 
}


iterator_t list::begin() { return 0; }

iterator_t list::end() { return size; }

iterator_t list::next(iterator_t p) { 
  if (p<0 || p>=size) {
    cout << "p: mala posicion.\n";
    abort();
  }
  return p+1; 
}

iterator_t list::prev(iterator_t p) { 
  if (p<=0 || p>size) {
    cout << "p: mala posicion.\n";
    abort();
  }
  return p-1; 
}

iterator_t list::insert(iterator_t p,elem_t k) {
  if (size>=MAX_SIZE) {
    cout << "La lista esta llena.\n";
    abort();
  }
  if (p<0 || p>size) {
    cout << "Insertando en posicion invalida.\n";
    abort();
  }
  for (int j=size; j>p; j--) elems[j] = elems[j-1];
  elems[p] = k;
  size++;
  return p;
}

iterator_t list::erase(iterator_t p) {
  if (p<0 || p>=size) {
    cout << "p: posicion invalida.\n";
    abort();
  }
  for (int j=p; j<size-1; j++) elems[j] = elems[j+1];
  size--;
  return p;
}

iterator_t list::erase(iterator_t p,iterator_t q) {
  if (p<0 || p>=size) {
    cout << "p: posicion invalida.\n";
    abort();
  }
  if (q<0 || q>=size) {
    cout << "q: posicion invalida.\n";
    abort();
  }
  if (p>q) {
    cout << "p debe estar antes de q\n";
    abort();
  }
  if (p==q) return p;
  int shift = q-p;
  for (int j=p; j<size-shift; j++) 
    elems[j] = elems[j+shift];
  size -= shift;
  return p;
}

void list::clear() { erase(begin(),end()); }

void list::print() {
  iterator_t p = begin();
  while (p!=end()) {
    cout << retrieve(p) << " ";
    p = next(p);
  }
  cout << endl;
}
