//__INSERT_LICENSE__
// $Id: trybtree.cpp,v 1.7 2005/04/26 16:19:06 mstorti Exp $

#include <list>
#include <cstdio>
#include <aedsrc/btree.h>
#include <aedsrc/btreetools.h>
#include <aedsrc/util.h>
#include <algorithm>

using namespace aed;
using namespace std;

int suma10(int j) { return j+10; }
int sum(int j,int k) { return j+k; }

void rota(btree<int> &A,btree<int> &B,btree<int> &C) {
  btree<int> X;
  X=A;
  A=B;
  B=C;
  C=X;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
#define L(n,m) T.insert(T.find(n).left(),m)
#define R(n,m) T.insert(T.find(n).right(),m)
int main() {
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  btree<int> T,Q;
  vector<int> nod_lev;

  T.insert(T.begin(),1);
  L(1,2);
  R(1,3);
  L(2,4);
  // R(2,5);
  // L(3,6);
  R(3,7);
  T.lisp_print();
  cout << endl;

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  const int BP=-1,EP=-2,EL=-3,NE=-4;
  list<int> L;
  int l[]={BP,1,BP,2,4,NE,EP,BP,3,NE,7,EP,EP,EL};
  insertl(L,L.begin(),l,EL);
  list2btree(Q,L,BP,EP,NE);
  Q.lisp_print();
  cout << endl;
  node_level_stat(Q,nod_lev);
  cout << endl;

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  btree<int> R;
  make_random_btree(R,20,1.0);
  R.lisp_print();
  cout << endl;
  node_level_stat(R,nod_lev);
  
  btree<int> S = R;
  apply(S,suma10);
  S.lisp_print();

  for (int j=0; j<5; j++) {
    random_shuffle(S);
    print_tree(S);
  }

  btree<int> A,B,C;
  for (int j=0; j<5; j++) {
    A.clear();
    double p=0.2;
    make_random_btree(A,20,p);
    cout << "A: \n";
    print_tree(A);
    
    B.clear();
    make_random_btree(B,20,p);
    cout << "B: \n";
    print_tree(B);

    combine(A,B,C,sum);
    cout << "C: \n";
    print_tree(C);

#define MENOR(A,B) cout << #A "<" #B ":   "<< \
(less_than(A,B) ? "si" : "no" ) << endl;

    MENOR(A,B);
    MENOR(B,A);
    MENOR(A,C);
    MENOR(C,A);
    MENOR(B,C);
    MENOR(C,B);
    cout << "----------\n";

    for (int j=0; j<3; j++) {
      rota(A,B,C);
      MENOR(A,B);
      MENOR(B,A);
      MENOR(A,C);
      MENOR(C,A);
      MENOR(B,C);
      MENOR(C,B);
      cout << "----------\n";
    }
  }

}
