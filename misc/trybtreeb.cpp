//__INSERT_LICENSE__
// $Id: trybtreeb.cpp,v 1.9 2004/04/25 14:04:05 mstorti Exp $

#include <list>
#include <cstdio>
#include <aedsrc/btreebas.h>
#include <aedsrc/btreebtools.h>
#include <aedsrc/util.h>
#include <algorithm>

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void mirror(btree &T,iterator_t n) {              //L-mirror-b
  if (n==T.end()) return;
  else {
    btree tmp;
    tmp.splice(tmp.begin(),n.left());             //L-mirr1
    T.splice(n.left(),n.right());                 //L-mirr2
    T.splice(n.right(),tmp.begin());              //L-mirr3
    mirror(T,n.right());                          //L-mirr-rec-b
    mirror(T,n.left());                           //L-mirr-rec-e
  }
}
void mirror(btree &T) { mirror(T,T.begin()); }   
                                                  //L-mirror-e
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
bool equal_p (btree &T,iterator_t nt,             //L-equal-b
	      btree &Q,iterator_t nq) { 
  if (nt==T.end() xor nq==Q.end()) return false;  //L-l1
  if (nt==T.end()) return true;                   //L-l2
  if (T.retrieve(nt) != Q.retrieve(nq)) return false; //L-l3
  return equal_p(T,nt.right(),Q,nq.right()) &&    //L-l4
    equal_p(T,nt.left(),Q,nq.left());
}
bool equal_p(btree &T,btree &Q) { 
  return equal_p(T,T.begin(),Q,Q.begin()); 
}
                                                 //L-equal-e
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
bool semejante_p (btree &T,iterator_t nt,        //L-semejantep-b
	      btree &Q,iterator_t nq) { 
  if (nt==T.end() xor nq==Q.end()) return false;
  if (nt==T.end()) return true;
  return semejante_p(T,nt.right(),Q,nq.right()) &&
    semejante_p(T,nt.left(),Q,nq.left());
}
bool semejante_p(btree &T,btree &Q) { 
  return semejante_p(T,T.begin(),Q,Q.begin()); 
}
                                                 //L-semejantep-e
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
bool mirror_p (btree &T,iterator_t nt,btree &Q,iterator_t nq) {
  if (nt==T.end() xor nq==Q.end()) return false;
  if (nt==T.end()) return true;
  if (T.retrieve(nt) != Q.retrieve(nq)) return false;
  return mirror_p(T,nt.right(),Q,nq.left()) && 
    mirror_p(T,nt.right(),Q,nq.left());
}
bool mirror_p(btree &T,btree &Q) { return mirror_p(T,T.begin(),Q,Q.begin()); }

int sum1(int j) { return j+1; }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
#define L(n,m) T.insert(T.find(n).left(),m)
#define R(n,m) T.insert(T.find(n).right(),m)
int main() {
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  btree T,Q;
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
  btree R;
  make_random_btree(R,20,8.0);
  R.lisp_print();
  cout << endl;
  node_level_stat(R,nod_lev);

  R.clear();
  make_random_btree(R,10,2.0);
  R.lisp_print();
  cout << endl;
  print_tree(R);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  btree S = R;
  mirror(S);
  cout << "S = mirror of R: \n";
  S.lisp_print();
  cout << endl;
  print_tree(S);

  btree W = R;
  apply(W,sum1);
  cout << "W = R+1: \n";
  W.lisp_print();
  cout << endl;
  print_tree(W);

  cout << "S = S ? " << (equal_p(S,S) ? "yes" : "no") << endl;
  cout << "S = R ? " << (equal_p(S,R) ? "yes" : "no") << endl;
  cout << "S = mirror(S) ? " << (mirror_p(S,S) ? "yes" : "no") << endl;
  cout << "S = mirror(R) ? " << (mirror_p(S,R) ? "yes" : "no") << endl;

  cout << "R \\sim R ? " << (semejante_p(R,R) ? "yes" : "no") << endl;
  cout << "W \\sim R ? " << (semejante_p(W,R) ? "yes" : "no") << endl;
  cout << "S \\sim R ? " << (semejante_p(S,R) ? "yes" : "no") << endl;

}
