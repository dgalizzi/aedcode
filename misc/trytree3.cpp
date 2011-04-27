//__INSERT_LICENSE__
// $Id: trytree3.cpp,v 1.6 2005/04/26 22:04:36 mstorti Exp $

#include <cstdio>
#include <list>
#include <aedsrc/tree.h>
#include <aedsrc/treetools.h>

using namespace aed;
using namespace std;

typedef tree<int> tree_t;
typedef tree_t::iterator node_t;

void mirror(tree_t &T);

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void mirror(tree_t &T,node_t n) {
  list< tree<int> > L;
  node_t c = n.lchild();
  if (c==T.end()) return;
  while (c!=T.end()) {
    printf("passing to list subtree rooted at %d\n",*c);
    L.insert(L.begin(),tree_t());
    tree_t &Q = *L.begin();
    T.splice(Q.begin(),c);
#if 0
    cout << "T: \n";
    T.lisp_print();
    cout << "\nQ: \n";
    Q.lisp_print();
    cout << endl;
#endif
    mirror(Q);
    c = n.lchild();
  }

  c = n.lchild();
  while (!L.empty()) {
    tree_t &Q = *L.begin();
    printf("passing to tree subtree rooted at %d\n",*Q.begin());
    c = T.splice(c,Q.begin());
    c++;
    L.erase(L.begin());
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void mirror(tree_t &T) { mirror(T,T.begin()); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int main() {
  tree<int> T;
  list<int> L;
  const int BP=-2,EP=-1,EL=-3;
#if 1
  int l[]={BP,5,BP,6,8,9,EP,BP,7,10,11,EP,BP,12,13,14,EP,EP,EL};
#else
  int l[]={BP,5,6,7,8,EP,EL};
#endif
  int N=-1;
  while (l[++N]!=EL) { }
  L.insert(L.begin(),l,l+N);
  list2tree(T,L,BP,EP);
  T.lisp_print();
  cout << endl;

  mirror(T,T.begin());
  T.lisp_print();
  cout << endl;
}
