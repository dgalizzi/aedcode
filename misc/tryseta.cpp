//__INSERT_LICENSE__
// $Id: tryseta.cpp,v 1.3 2004/05/16 23:35:41 mstorti Exp $

#include <iostream>
#include <aedsrc/util.h>
#include <aedsrc/setbasa.h>

using namespace aed;
using namespace std;

void set_print(set &A) {
  iterator_t p = A.begin();
  while (p!=A.end()) {
    cout << A.retrieve(p) << " ";
    p = A.next(p);
  }
  cout << endl;
}

void make_random_set(set &A,int M) {
  for (int j=0; j<M; j++) {
    char c = (irand(2)? 'a' : 'A')+irand(26);
    A.insert(c);
  }
}

int main() {
  set A,B,C;
  for (int j=0; j<5; j++) {
    A.clear();
    make_random_set(A,10);
    cout << "A: "; set_print(A);

    B.clear();
    make_random_set(B,10);
    cout << "B: "; set_print(B);
    
    set_union(A,B,C);
    cout << "A union B: ";  set_print(C);
    
    set_intersection(A,B,C);
    cout << "A intersection B: ";  set_print(C);
    
    set_difference(A,B,C);
    cout << "A set_difference B: ";  set_print(C);
    
    set_difference(B,A,C);
    cout << "B set_difference A: ";  set_print(C);
    cout << "-----------------------------------\n";
  }
}
