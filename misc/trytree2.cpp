//__INSERT_LICENSE__
// $Id: trytree2.cpp,v 1.2 2004/03/21 21:39:02 mstorti Exp $

#include <aedsrc/tree.h>
#include <list>
#include <cstdio>

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int main() {
  tree<int> T;
  list<int> L;
  const int BP=-2,EP=-1;
#if 1
  int N = 13;
  int l[]={BP,5,BP,6,8,9,EP,BP,7,10,11,EP,EP};
#else
  int N = 6;
  int l[]={BP,5,6,7,8,EP};
#endif
  L.insert(L.begin(),l,l+N);
  list2tree(T,L,BP,EP);
  T.print_prev();
  T.print_post();

  cout << "After splicing...\n";
  T.splice(T.find(6),T.find(7));
  T.print_prev();
  T.print_post();

}
