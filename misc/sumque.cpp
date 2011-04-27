//PP>if 0
//__INSERT_LICENSE__
// $Id: sumque.cpp,v 1.1 2004/03/29 00:25:46 mstorti Exp $
//PP>endif
#include <queue>
#include <iostream>
#include "./util.h"

using namespace std;

int sumqueue(queue<int> &Q) {  //L-p1
  int sum=0;
  queue<int> Q2;
  while (!Q.empty()) {
    int w = Q.front();
    Q.pop();
    sum += w;
    Q2.push(w);
  }

  while (!Q2.empty()) {
    Q.push(Q2.front());
    Q2.pop();
  }
  return sum;
}
                               //L-p2
int main() {
  queue<int> Q;
  int N=20;
  for (int j=0; j<N; j++) {
    int w = irand(N);
    cout << w << endl;
    Q.push(w);
  }
  cout << "Suma de la cola: " << sumqueue(Q) << endl;
  cout << "Suma de la cola: " << sumqueue(Q) << endl;
}
