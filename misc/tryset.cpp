//__INSERT_LICENSE__
// $Id: tryset.cpp,v 1.2 2004/05/16 15:51:48 mstorti Exp $

#include <iostream>
#include <aedsrc/util.h>
#include <aedsrc/setbas.h>

using namespace aed;
using namespace std;

void set_print(set &A) {
  iterator_t p = A.begin();
  while (p!=A.end()) {
    cout << *p++ << " ";
  }
  cout << endl;
}

int main() {
  set A,B,C;
  int N=10;
  for (int j=0; j<N; j++) {
    A.insert(irand(5*N));
    B.insert(irand(5*N));
  }
  cout << "A: ";  set_print(A);
  cout << "B: ";  set_print(B);

  set_union(A,B,C);
  cout << "A union B: ";  set_print(C);
  
  set_intersection(A,B,C);
  cout << "A intersection B: ";  set_print(C);

  set_difference(A,B,C);
  cout << "A set_difference B: ";  set_print(C);

  set_difference(B,A,C);
  cout << "B set_difference A: ";  set_print(C);
}
