// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: treetools.h,v 1.6 2004/05/27 17:14:28 mstorti Exp $
#ifndef AED_TREETOOLS_H
#define AED_TREETOOLS_H

#include <aedsrc/util.h>

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<typename elem_t>
  typename tree<elem_t>::iterator
  list2tree(tree<elem_t> &T,
	    typename tree<elem_t>::iterator n,
	    const list<elem_t> &L,
	    typename list<elem_t>::const_iterator  &p,
	    elem_t BP,elem_t EP) {
    if (*p != BP) n=T.insert(n,*p);
    else {
      typename list<elem_t>::const_iterator q=p; q++;
      assert(*q!=BP && *q!=EP);
      n=T.insert(n,*q++);
      typename tree<elem_t>::iterator r=n.lchild();
      while (*q!=EP) {
	r=list2tree(T,r,L,q,BP,EP);
	r++;
      }
      p=q;
    }
    p++;
    return n;
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T>
  typename tree<T>::iterator
  list2tree(tree<T> &A,const list<T> &L,T BP,T EP) {
    typename list<T>::const_iterator p=L.begin();
    return list2tree(A,A.begin(),L,p,BP,EP);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void lisp2tree(tree<int> &A,const string &s);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T>
  void tree2list(tree<T> &A,
		 typename tree<T>::iterator n,
		 list<T> &L,T BP,T EP) {
    typedef typename tree<T>::iterator node_t;
    typedef typename list<T>::iterator it;
    if (n==A.end()) return;
    node_t c=n.lchild();
    if (c==A.end()) {
      L.insert(L.end(),*n); 
    } else {
      L.insert(L.end(),BP); 
      L.insert(L.end(),*n); 
      while (c!=A.end()) {
	tree2list(A,c++,L,BP,EP);
      }
      L.insert(L.end(),EP);
    }
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T>
  void tree2list(tree<T> &A,list<T> &L,T BP,T EP) {
    tree2list(A,A.begin(),L,BP,EP);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void make_random_tree(tree<int> &T,int M,int siblings);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T>
  void random_shuffle(tree<T> &Q,
		      typename tree<T>::iterator n) {
    list< tree<T> > L;
    typename tree<T>::iterator c = n.lchild();
    typename list< tree<T> >::iterator p = L.begin();
    while (c!=Q.end()) {
      p = L.insert(p,tree<T>());
      p->splice(p->begin(),c);
      c = n.lchild();
    }
    c = n.lchild();
    while(true) {
      int n=L.size();
      if (n==0) break;
      int j = irand(n);
      p = L.begin();
      for (int k=0; k<j; k++) p++;
      c = Q.splice(c,p->begin());
      L.erase(p);
      random_shuffle(Q,c);
      c++;
    }
  }

  template<class T>
  void random_shuffle(tree<T> &Q) {
    if (Q.begin()!=Q.end()) 
      random_shuffle(Q,Q.begin());
  }
}

#endif
