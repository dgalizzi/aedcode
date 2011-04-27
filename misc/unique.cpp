//__INSERT_LICENSE__
// $Id: unique.cpp,v 1.1 2004/05/31 19:01:15 mstorti Exp $

#include <iostream>
#include <list>
#include <set>
#include "./util.h"

using namespace std;

template<class T>
void unique(list<T> &L) {
  set<T> S;
  typename list<T>::iterator p = L.begin();
  while (p!=L.end()) {
    T v = *p;
    if (S.find(v)!=S.end()) p=L.erase(p);
    else {
      S.insert(v);
      p++;
    }
  }
}

template<class T>
void set_intersection(set<T> &A,set<T> &B,set<T> &C) {
  C.clear();
  typename set<T>::iterator p = A.begin();
  while (p!=A.end()) {
    T v = *p++;
    if (B.find(v)!=B.end()) C.insert(v);
  }
}

template<class T>
void prints(set<T> &S) {
  typename set<int>::iterator p = S.begin();
  while (p!=S.end()) cout << *p++ << " ";
  cout << endl;
}

int main() {
  list<int> L;
  for (int j=0; j<100; j++) L.insert(L.end(),irand(20));
  cout << "Antes de unique\n";
  printl(L);
  unique(L);
  cout << "Despues de unique\n";
  printl(L);

  set<int> A,B,C;
  for (int j=0; j<20; j++) {
    A.insert(irand(40));
    B.insert(irand(40));
  }
  set_intersection(A,B,C);
  cout << "A: ";
  prints(A);
  cout << "B: ";
  prints(B);
  cout << "C: ";
  prints(C);
}
