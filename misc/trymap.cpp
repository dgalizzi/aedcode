//__INSERT_LICENSE__
// $Id: trymap.cpp,v 1.1 2004/03/13 22:46:34 mstorti Exp $

#include <cassert>
#include <aedsrc/mapv.h>
//#include <aedsrc/map.h>

using namespace aed;

typedef map<double,int> map_t;

int main() {
  map_t M;
  int N=20;
  for (int j=N; j>=0; j--) M[j+0.1]=3*j;
  for (int j=0; j<=N; j++) 
    if (!(j%3)) M.erase(M.find(j+0.1));
  for (int j=0; j<=N; j++) {
    double dj = j+0.1;
    map_t::iterator q = M.find(dj);
    if (!(j%3)) assert(q==M.end());
    else cout << dj << ": " << M[j] << endl;
  }
}
