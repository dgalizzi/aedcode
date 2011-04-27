//__INSERT_LICENSE__
// $Id: trymap2.cpp,v 1.1 2004/03/14 16:13:44 mstorti Exp $

#include <cassert>
//#include <aedsrc/mapv.h>
#include <aedsrc/maplid.h>

using namespace aed;

int main() {
  map M;
  int N=20;
  for (int j=N; j>=0; j--) M.retrieve(j) = 3*j;
  for (int j=0; j<=N; j++) 
    if (!(j%3)) M.erase(M.find(j));
  for (int j=0; j<=N; j++) {
    iterator_t q = M.find(j);
    if (!(j%3)) assert(q==M.end());
    else cout << j << ": " << M.retrieve(j) << endl;
  }
}
