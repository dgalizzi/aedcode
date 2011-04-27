// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: btreetools.cpp,v 1.3 2004/04/25 21:37:33 mstorti Exp $

#include <vector>
#include <aedsrc/util.h>
#include <aedsrc/btreetools.h>

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void make_random_btree(btree<int> &T,btree<int>::iterator n,
			int M,int level,double siblings) {
    n = T.insert(n,irand(M));
    double lambda = 1.0/(siblings/double(level)+1.0);
    for (int j=0; j<2; j++) {
      btree<int>::iterator c = (j==0 ? n.left() : n.right());
      if (drand()>lambda) make_random_btree(T,c,M,level+1,siblings);
    }
  }
  void make_random_btree(btree<int> &T,int M,double siblings) {
    T.clear();
    make_random_btree(T,T.begin(),M,0,siblings);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void 
  node_level_stat(btree<int> &T,btree<int>::iterator n,
		  int level,vector<int> &nod_lev) {
    if (n==T.end()) return;
    assert(nod_lev.size()>=level);
    if (nod_lev.size()==level) nod_lev.push_back(0);
    nod_lev[level]++;
    node_level_stat(T,n.left(),level+1,nod_lev);
    node_level_stat(T,n.right(),level+1,nod_lev);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void node_level_stat(btree<int> &T,vector<int> &nod_lev) {
    nod_lev.clear();
    node_level_stat(T,T.begin(),0,nod_lev);
    cout << "level/#nodes: ";
    for (int j=0;j<nod_lev.size();j++) 
      cout << j << "/" << nod_lev[j] << ", ";
    cout << endl;
  }

}

