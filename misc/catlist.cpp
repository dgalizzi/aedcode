//__INSERT_LICENSE__
// $Id: catlist.cpp,v 1.1 2004/03/11 11:31:13 mstorti Exp $

#include <iostream>
#include <ext/slist>

using namespace std;
using namespace __gnu_cxx;

int main() {
  slist<int> l1,l2,l;
  int N=10000,M=100;
  for (int j=0; j<N; j++) l1.insert(l1.end(),j);
  l2=l1;
  for (int k=0; k<M; k++) {
    l.clear();
    l.insert(l.end(),l1.begin(),l1.end());
    l.insert(l.end(),l2.begin(),l2.end());
  }
#if 0
  slist<int>::iterator q;
  for (q=l1.begin(); q!=l1.end(); q++) cout << *q << " ";
  cout << endl;
#endif
}
