//__INSERT_LICENSE__
// $Id: mirror.h,v 1.5 2004/04/17 04:21:34 mstorti Exp $

#include <aedsrc/tree.h>
#include <aedsrc/treetools.h>
#include <aedsrc/util.h>
#include <list>
#include <cstdio>

using namespace std;

namespace aed {

  template<typename T>
  void mirror(tree<T> &T);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<typename T>
  void mirror(tree<T> &R,
	      typename tree<T>::iterator n) {
    typedef tree<T> tree_t;
    typedef typename tree_t::iterator node_t;

    list<tree_t> L;
    node_t c = n.lchild();
    if (c==R.end()) return;
    while (c!=R.end()) {
      // printf("passing to list subtree rooted at %d\n",*c);
      L.insert(L.begin(),tree_t());
      tree_t &Q = *L.begin();
      R.splice(Q.begin(),c);
#if 0
      cout << "T: \n";
      R.lisp_print();
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
      // printf("passing to tree subtree rooted at %d\n",*Q.begin());
      c = R.splice(c,Q.begin());
      c++;
      L.erase(L.begin());
    }
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<typename T>
  void mirror(tree<T> &R) { mirror(R,R.begin()); }

}
