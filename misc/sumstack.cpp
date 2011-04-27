//PP>if 0
//__INSERT_LICENSE__
// $Id: sumstack.cpp,v 1.1 2004/03/28 03:21:40 mstorti Exp $
//PP>endif
#include <stack>
#include <iostream>
#include "./util.h"

using namespace std;

int sumstack(stack<int> &P) {  //L-p1
  int sum=0;
  while (!P.empty()) {
    sum += P.top();
    P.pop();
  }
  return sum;
}

int sumstack2(stack<int> &P) {  //L-p2
  stack<int> Q;
  int sum=0;
  while (!P.empty()) {
    int w = P.top();
    P.pop();
    sum += w;
    Q.push(w);
  }

  while (!Q.empty()) {
    P.push(Q.top());
    Q.pop();
  }
  return sum;
}
                                //L-p3
int main() {
  stack<int> P;
  int N=20;
  for (int j=0; j<N; j++) {
    int w = irand(N);
    cout << w << endl;
    P.push(w);
  }
  cout << "Suma de la pila: " << sumstack2(P) << endl;
  cout << "Suma de la pila: " << sumstack2(P) << endl;
  cout << "Suma de la pila: " << sumstack(P) << endl;
  cout << "Suma de la pila: " << sumstack(P) << endl;
}
