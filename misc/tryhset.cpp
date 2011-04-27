//__INSERT_LICENSE__
// $Id: tryhset.cpp,v 1.6 2004/05/31 03:36:41 mstorti Exp $

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

int main() {
  hash_set A(10,hf,-1,-2);
  // hash_set A(100,hf);
  // hash_set A(100,hf);
  set<int> S;
  int sum=0;
  int j;
  for (j=0; j<15; j++) {
    int x = irand(100);
    bool ba,bs;
    bs = (S.find(x)==S.end());
    ba = (A.find(x)==A.end());
    assert(ba==bs);
    // cout << "ba: " << ba << ", bs: " << bs << endl;
    if (irand(2)) {
      // Inserta
      // cout << "Insertando " << x;
      pair<iterator_t,bool> r = A.insert(x);
      // if (!r.second) cout << " Ya estaba...";
      pair<set<int>::iterator,bool> rr = S.insert(x);
      assert(r.second==rr.second);
    } else {
      // Borra
      int c;
      if (drand()>0.5) c = A.erase(x);
      else {
	iterator_t q = A.find(x);
	if (q!=A.end()) { c=1; A.erase(q); }
	else c=0;
      }
      // cout << "Borrando " << x;
      // if (!k) cout << " No estaba...";
      int cc = S.erase(x);
      assert(c==cc);
    }
    // cout << " Total: " << A.size() << endl;
    sum += A.size();
    if (j%1000==0) cout << "average size: " 
			<< double(sum)/double(j) << endl;
  }
  print(A);
  cout << "S: ";
  set<int>::iterator q = S.begin();
  while (q!=S.end()) {
    cout << *q++ << " ";
  }
  cout << endl;
  cout << "average size: " 
       << double(sum)/double(j) << endl;
}
