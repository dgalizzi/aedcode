#ifndef AED_LIST2P_H
#define AED_LIST2P_H

#include <iostream>
#include <aedsrc/list.h>

using namespace std;
using namespace aed;

template<class T>
list<T>::list() {
}

// Prefix
template<typename T>
typename list<T>::iterator
list<T>::iterator::operator++() { 
}

// Postfix
template<typename T>
typename list<T>::iterator
list<T>::iterator::operator++(int x) { 
}

template<typename T>
T & list<T>::iterator::operator*() {
}

template<typename T>
bool list<T>::iterator::operator!=(iterator q) { 
}

template<typename T>
bool list<T>::iterator::operator==(iterator q) { 
}

template<typename T>
typename list<T>::iterator
list<T>::insert(iterator p,T t) {
}

template<typename T>
typename list<T>::iterator
list<T>::begin() { }

template<typename T>
typename list<T>::iterator
list<T>::end() { 

template<typename T>
void list<T>::print() {
  list<T>::iterator p = begin();
  while (p!=end()) cout << *p++ << " ";
  cout << endl;
}

template<typename T>
void list<T>::printd() {
  cout << "h(" << first << ")" << endl;
  cell *c = first->next;
  int j=0;
  while (c!=NULL) { 
    cout << j++ << "(" << c << ") :" << c->t << endl; 
    c = c->next;
  }
}

template<typename T>
typename list<T>::iterator
list<T>::erase(iterator p) {
  cell *q = p.ptr->next;
  if (q==last) last = p.ptr;
  p.ptr->next = q->next;
  delete q;
  return p;
}

template<typename T>
typename list<T>::iterator
list<T>::erase(iterator p,iterator q) {
  iterator r = p;
  while (r!=q) r = erase(r);
  return p;
}

template<typename T>
void list<T>::clear() {
  erase(begin(),end());
}
#endif
