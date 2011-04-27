//__INSERT_LICENSE__
// $Id: trystack.cpp,v 1.3 2004/02/28 13:23:46 mstorti Exp $

#ifdef USE_LISTP
#include <aedsrc/stackbasi.h>
#elif defined USE_LISTC
#include <aedsrc/stackbasc.h>
#elif defined USE_LIST
#include <aedsrc/stack.h>
#define stack stack<int>
#else
#warning Not defined list class!!
#endif

#include <iostream>

using namespace aed;
using namespace std;

int main() {
  stack P;
  const int N=10;
  for (int j=0; j<N; j++) P.push(j);
  while (!P.empty()) {
    cout << P.top() << " " << endl;
    P.pop();
  }
  cout << endl;
}
