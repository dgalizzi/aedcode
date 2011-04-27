//PP>if 0
// $Id: treebas.cpp,v 1.5 2004/04/18 19:41:16 mstorti Exp $
//PP>endif

#include "./treebas.h"

using namespace std;

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  iterator_t list2tree(tree &T, iterator_t n, const list<elem_t> &L,
		       list<elem_t>::const_iterator &p,
		       elem_t BP,elem_t EP) {
    if (*p != BP) n = T.insert(n,*p);
    else {
      list<elem_t>::const_iterator q = p; q++; 
      assert(*q != BP && *q != EP);
      n = T.insert(n,*q++);
      iterator_t r = n.lchild();
      while (*q != EP) {
	r = list2tree(T,r,L,q,BP,EP);
	r = r.right();
      }
      p = q;
    }
    p++;
    return n;
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  iterator_t list2tree(tree &A,const list<elem_t> &L,elem_t BP,elem_t EP) {
    list<elem_t>::const_iterator p = L.begin();
    return list2tree(A,A.begin(),L,p,BP,EP);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void tree2list(tree &A,iterator_t n,
		 list<elem_t> &L,elem_t BP,elem_t EP) {
    if (n == A.end()) return;
    iterator_t c = n.lchild();
    if (c == A.end()) {
      L.insert(L.end(),A.retrieve(n)); 
    } else {
      L.insert(L.end(),BP); 
      L.insert(L.end(),A.retrieve(n)); 
      while (c != A.end()) {
	tree2list(A,c,L,BP,EP);
	c = c.right();
      }
      L.insert(L.end(),EP);
    }
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void tree2list(tree &A,list<elem_t> &L,elem_t BP,elem_t EP) {
    tree2list(A,A.begin(),L,BP,EP);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void make_random_tree(tree &T,iterator_t n,
			int M,int level,int siblings) {
    double lambda = 1.0/(double(siblings)/double(level)+1.0);
    n = T.insert(n,irand(M));
    iterator_t c = n.lchild();
    while (true) {
      if (drand()<lambda) break;
      make_random_tree(T,c,M,level+1,siblings);
      c = n.lchild();
    }
  }
  
}

//PP>if 0
// Local Variables: *
// mode: c++ *
// End: *
//PP>endif
