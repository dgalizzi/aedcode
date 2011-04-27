//__INSERT_LICENSE__
// $Id: trybtree2.cpp,v 1.1 2005/05/25 02:46:53 mstorti Exp $

#include <list>
#include <cstdio>
#include <aedsrc/btree.h>
#include <aedsrc/btreetools.h>
#include <aedsrc/util.h>
#include <algorithm>

using namespace aed;
using namespace std;

// Retorna -1 si T1<T2, 0 si T1==T2, +1 si T1>T2
int comp_btree(btree<int> &T1,btree<int>::iterator n1,
	    btree<int> &T2,btree<int>::iterator n2,
	    int (*comp)(int x,int y)) {
  if (n1==T1.end() && n2==T2.end()) return 0;
  if (n1==T1.end()) return -1;
  if (n2==T2.end()) return +1;
  int v = comp(*n1,*n2);
  if (v) return v;
  v = comp_btree(T1,n1.left(),T2,n2.left(),comp);
  if (v) return v;
  return comp_btree(T1,n1.right(),T2,n2.right(),comp);
}

int comp_btree(btree<int> &T1, btree<int> &T2,
	    int (*comp)(int x,int y)) {
  comp_btree(T1,T1.begin(),T2,T2.begin(),comp);
}

int comp(int x,int y) {
  return (y>x) - (x>y);
}

int compa(int x,int y) {
  int yy = abs(y);
  int xx = abs(x);
  return (yy>xx) - (xx>yy);
}

int M=11;

int f(int x) { return 2*x-M; }

int main() {
  const int N=100;
  btree<int> *A[N];
  for (int j=0; j<N; j++) {
    A[j] = new btree<int>;
    double p=0.2;
    make_random_btree(*A[j],M,p);
    apply(*A[j],f);
    for (int k=0; k<j; k++) {
      if (!comp_btree(*A[j],*A[k],compa)) {
	printf("A[j], A[k]: \n");
	A[j]->lisp_print();
	printf("\n");
	A[k]->lisp_print();
	printf("------\n");
      }
    }
  }
}
