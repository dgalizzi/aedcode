// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: btreetools.h,v 1.7 2004/05/26 01:17:21 mstorti Exp $
#ifndef AED_BTREETOOLS_H
#define AED_BTREETOOLS_H

#include <aedsrc/btree.h>
#include <aedsrc/util.h>
#include <vector>

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<typename elem_t>
  typename btree<elem_t>::iterator
  list2btree(btree<elem_t> &T,
	    typename btree<elem_t>::iterator n,
	    const list<elem_t> &L,
	    typename list<elem_t>::const_iterator  &p,
	    elem_t BP,elem_t EP,elem_t NE) {
    if (*p == NE) { }
    else if (*p != BP) n = T.insert(n,*p);
    else {
      typename list<elem_t>::const_iterator q = p; q++;
      assert(*q != BP && *q != EP && *q != NE);
      n = T.insert(n,*q++);
      list2btree(T,n.left(),L,q,BP,EP,NE);
      list2btree(T,n.right(),L,q,BP,EP,NE);
      p = q;
    }
    p++;
    return n;
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T>
  typename btree<T>::iterator
  list2btree(btree<T> &A,const list<T> &L,T BP,T EP,T NE) {
    typename list<T>::const_iterator p = L.begin();
    return list2btree(A,A.begin(),L,p,BP,EP,NE);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void make_random_btree(btree<int> &T,btree<int>::iterator n,
			 int M,int level,double siblings);

  void make_random_btree(btree<int> &T,int M,double siblings);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void 
  node_level_stat(btree<int> &T,btree<int>::iterator n,
		  int level,vector<int> &nod_lev);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void node_level_stat(btree<int> &T,vector<int> &nod_lev);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T>                      //L-apply-b
  void apply(btree<T> &Q,
	     typename btree<T>::iterator n,
	     T(*f)(T)) {
    if (n==Q.end()) return;
    *n = f(*n);                          //L-apply2
    apply(Q,n.left(),f);
    apply(Q,n.right(),f);
  }
  template<class T>
  void apply(btree<T> &Q,T(*f)(T)) {     //L-apply1
    apply(Q,Q.begin(),f); 
  }                                      //L-apply-e

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T> 
  void print_tree(btree<T> &Q,
		  typename btree<T>::iterator n,
		  const string &pre,const string &c) {
    if (n==Q.end()) {
      cout << pre << "+--<Lambda>" << endl;
      return;
    }
    cout << pre << "+--[" << *n << "]" << endl;
    string pres;
    typename btree<T>::iterator
      ml = n.left(), 
      mr = n.right();
    if (ml!=Q.end() || mr!=Q.end()) {
      cout << pre << c << "  |" << endl;
      pres = pre + c + "  ";
      print_tree(Q,ml,pres,"|");
      print_tree(Q,mr,pres," ");
      cout << pre << c << endl;
    }
  }
  template<class T> 
  void print_tree(btree<T> &Q) {
    string pre("");
    if (Q.begin()!=Q.end()) print_tree(Q,Q.begin(),pre," ");
  }

  // -----------------------------------------------------------------
  template <class T>
  void random_shuffle(btree <T> &Q,
		      typename btree<T>::iterator n) {
    if (n==Q.end()) return;
    // Tira la moneda para ver si invierte o no
    // invierte los hijos
    if (drand()>0.5) return;
    btree<T> tmp;
    tmp.splice(tmp.begin(),n.left());
    Q.splice(n.left(),n.right());
    Q.splice(n.right(),tmp.begin());
  }
  // -----------------------------------------------------------------
  template <class T>
  void random_shuffle(btree<T> &Q) {
    random_shuffle(Q,Q.begin()); 
  }

  // -----------------------------------------------------------------
  template <class T>
  void combine(btree<T> &A,
	       typename btree<T>::iterator a,
	       btree<T> &B,
	       typename btree<T>::iterator b,
	       btree<T> &C,
	       typename btree<T>::iterator c,
	       T (*bin_fun)(T,T)) {
    btree<T> tmp;
    if (a!=A.end() && b!=B.end()) {
      c = C.insert(c,bin_fun(*a,*b));
      combine(A,a.left(),B,b.left(),C,c.left(),bin_fun);
      combine(A,a.right(),B,b.right(),C,c.right(),bin_fun);
    } else if (a!=A.end()) C.copy(c,A,a);
    else if (b!=B.end()) C.copy(c,B,b);
  }

  // -----------------------------------------------------------------
  template <class T>
  void combine(btree<T> &A,btree<T> &B,btree<T> &C,
	       T (*bin_fun)(T,T)) {
		 typedef typename btree<T>::iterator node_t;
		 C.clear();
    combine(A,A.begin(),B,B.begin(),C,C.begin(),bin_fun);
  }

  // -----------------------------------------------------------------
  template <class T>
  bool less_than(btree<T> &T1,typename btree<T>::iterator n1,
		 btree<T> &T2,typename btree<T>::iterator n2) {
    if (n1==T1.end()) return true;
    if (n2==T2.end()) return false;
    if (*n1 > *n2) return false;
    return less_than(T1,n1.left(),T2,n2.left())
      && less_than(T1,n1.right(),T2,n2.right());
  }

  // -----------------------------------------------------------------
  template <class T>
  bool less_than(btree<T> &T1,btree<T> &T2) {
    return less_than(T1,T1.begin(),T2,T2.begin()); 
  }

}

#endif
