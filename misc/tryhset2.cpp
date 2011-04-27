//__INSERT_LICENSE__
// $Id: tryhset2.cpp,v 1.2 2004/05/31 19:01:15 mstorti Exp $

#include <iostream>
#include <set>
#include <aedsrc/util.h>
#include <aedsrc/hashsetbas.h>
//#include <aedsrc/hashsetcbas.h>
//#include <aedsrc/hashsetbaso.h>

using namespace aed;
using namespace std;

int hf(int j) {
  return j;
}

void print(hash_set &S) {
  iterator_t p = S.begin();
  while(p!=S.end()) {
    cout << S.retrieve(p) << " ";
    p = S.next(p);
  }
  cout << endl;
}

int rpop(set<int> &S) {
  int n = S.size();
  int j = irand(n);
  set<int>::iterator p = S.begin();
  for (int k=0; k<j; k++) p++;
  int v = *p;
  S.erase(p);
  return v;
}

int main() {
  int N=1000, M=100000;
  float alpha=0.7;
  hash_set A(N,hf,-1,-2);
  // hash_set A(100,hf);
  // hash_set A(100,hf);
  set<int> S;
  int sum=0;
  int j;
  for (j=0; j<int(alpha*N); j++) {
    int x = irand(M);
    S.insert(x);
    A.insert(x);
  }
  
  for (int j=0; j<200000; j++) {
    int w;
    pair<iterator_t,bool> q;
    pair<set<int>::iterator,bool> qs;
    // Inserta un elemento al azar
    while (true) {
      w = irand(M);
      q = A.insert(w);
      if (q.second) break;
    }
    qs = S.insert(w);
    assert(qs.second);
    // Elimina un elemento al azar
    w = rpop(S);
    assert(A.erase(w)==1); 
    if (!((j+1) % 10000)) cout << j << endl;
  }
}
