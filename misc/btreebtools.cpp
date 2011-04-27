// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: btreebtools.cpp,v 1.5 2004/04/25 04:30:13 mstorti Exp $

#include <vector>
#include <string>
#include <aedsrc/util.h>
#include <aedsrc/btreebtools.h>

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  iterator_t
  list2btree(btree &T, iterator_t n,
	     const list<elem_t> &L, 
	     list<elem_t>::const_iterator  &p,
	    elem_t BP,elem_t EP,elem_t NE) {
    elem_t tp = *p;
    if (tp == NE) { }
    else if (tp != BP) n = T.insert(n,tp);
    else {
      list<elem_t>::const_iterator q = p; q++;
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
  iterator_t
  list2btree(btree &A,const list<elem_t> &L,elem_t BP,elem_t EP,elem_t NE) {
    list<elem_t>::const_iterator p = L.begin();
    return list2btree(A,A.begin(),L,p,BP,EP,NE);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void make_random_btree(btree &T,iterator_t n,
			int M,int level,double siblings) {
    n = T.insert(n,irand(M));
    double lambda = 1.0/(siblings/double(level)+1.0);
    for (int j=0; j<2; j++) {
      iterator_t c = (j==0 ? n.left() : n.right());
      if (drand()>lambda) make_random_btree(T,c,M,level+1,siblings);
    }
  }
  void make_random_btree(btree &T,int M,double siblings) {
    T.clear();
    make_random_btree(T,T.begin(),M,0,siblings);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void 
  node_level_stat(btree &T,iterator_t n,
		  int level,vector<int> &nod_lev) {
    if (n==T.end()) return;
    assert(nod_lev.size()>=level);
    if (nod_lev.size()==level) nod_lev.push_back(0);
    nod_lev[level]++;
    node_level_stat(T,n.left(),level+1,nod_lev);
    node_level_stat(T,n.right(),level+1,nod_lev);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void node_level_stat(btree &T,vector<int> &nod_lev) {
    nod_lev.clear();
    node_level_stat(T,T.begin(),0,nod_lev);
    cout << "level/#nodes: ";
    for (int j=0;j<nod_lev.size();j++) 
      cout << j << "/" << nod_lev[j] << ", ";
    cout << endl;
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  static void 
  print_tree(btree &T,iterator_t n,string pre,string c) {
    if (n==T.end()) {
      cout << pre << "+--<Lambda>" << endl;
      return;
    }
    cout << pre << "+--" << T.retrieve(n) << endl;
    string pres;
    iterator_t ml = n.left(), mr = n.right();
    if (ml!=T.end() || mr!=T.end()) {
      cout << pre << c << "  |" << endl;
      pres = pre + c + "  ";
      print_tree(T,ml,pres,"|");
      print_tree(T,mr,pres," ");
      cout << pre << c << endl;
    }
  }
  void print_tree(btree &T) {
    string pre("");
    if (T.begin()!=T.end()) print_tree(T,T.begin(),pre," ");
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  static void 
  apply(btree &T,iterator_t n,int_scalar_fun f) {
    if (n==T.end()) return;
    T.retrieve(n) = f(T.retrieve(n));
    apply(T,n.left(),f);
    apply(T,n.right(),f);
  }
  void apply(btree &T,int_scalar_fun f) { 
    apply(T,T.begin(),f); 
  }
}

