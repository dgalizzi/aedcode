// -*- mode: c++ -*-
// $Id: ktree.h,v 1.7 2005/05/01 15:19:47 mstorti Exp $
#ifndef AED_KTREE_H
#define AED_KTREE_H

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <list>

using namespace std;

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  // `ktree' is an n-ary tree where each node can have
  // at most `k' sons. In addition each son may exist or not.
  // For `k=2' it is equivalent to the binary tree.
  // The `j' son of node `n' is accessed as `n[j]'. 
  template<class T>
  class ktree {
  public:
    class iterator;
  private:
    int k;
    // These are the cells that store the referenciable nodes.
    // The pointers to the son's cells are stored in a C vector
    // `cell **sons' that is allocated in the constructor `cell(k)'. 
    class cell {
      friend class ktree;
      friend class iterator;
      T t;
      cell **sons;
      cell(int k) : sons(NULL) {
	assert(k>0);
	sons = new (cell *)[k];
	for (int j=0; j<k; j++) sons[j]=NULL; 
      }
      ~cell() { if (sons) delete sons; }
    };
    cell *header;
  public:
    static int cell_count_m;
    static int cell_count() { return cell_count_m; }
    class iterator {
    private:
      friend class ktree;
      cell *ptr,*father;
      int son;
      iterator(cell *p,int son_a,cell *f_a)
	: ptr(p), son(son_a), father(f_a) { }
    public:
      iterator(const iterator &q) {
	ptr = q.ptr;
	son = q.son;
	father = q.father;
      }
      T &operator*() { return ptr->t; }
      T *operator->() { return &ptr->t; }
      bool operator!=(iterator q) { return ptr!=q.ptr; }
      bool operator==(iterator q) { return ptr==q.ptr; }
      iterator() : ptr(NULL), son(-1), father(NULL) { }

      iterator operator[](int j) { 
	// assert(j>=0 && j<k);
	return iterator(ptr->sons[j],j,ptr); 
      }

    };

    // By default construct a binary tree. 
    ktree(int k_a=2) {
      k = k_a;
      header = new cell(k);
      cell_count_m++;
    }
    // Copy ctor. (used in ktree<int> T(Q);
    ktree<T>(const ktree<T> &TT) { 
      if (&TT != this) {
	k = TT.order();
	header = new cell;
	cell_count_m++;
	ktree<T> &TTT = (ktree<T> &) TT;
	if (TTT.begin()!=TTT.end()) 
	  copy(begin(),TTT,TTT.begin()); 
      }
    }
    // Used in T = Q;
    ktree &operator=(ktree<T> &TT) { 
      if (this != &TT) {
	clear();
	change_order(TT.order());
	if (TT.begin()!=TT.end()) 
	  copy(begin(),TT,TT.begin()); 
      }
      return *this;
    }
    // Dtor.
    ~ktree() { 
      clear(); 
      delete header; 
      cell_count_m--; 
    }
    // Allows the user to get the arity
    // of the tree
    int order() const { return k; }
    // Allows the user to change the arity
    // of the tree. Clears the tree. 
    void change_order(int k_a) {
      clear();
      if (header) delete header;
      k = k_a;
      header = new cell(k);
    }
    // Inserts an element `t' in the
    // non-dereferentiable position `p'
    iterator insert(iterator p,T t) {
      assert(p==end());
      cell *c = new cell(k);
      cell_count_m++;
      c->t = t;
      p.father->sons[p.son] = c;
      p.ptr = c;
      return p;
    }
    // Eliminates the subtree for dereferentiable
    // position `p'
    iterator erase(iterator p) {
      if(p==end()) return p;
      for (int j=0; j<k; j++) erase(p[j]);
      p.father->sons[p.son] = NULL;
      delete p.ptr;
      cell_count_m--;
      p.ptr = NULL;
      return p;
    }
    // Moves subtree from dereferentiable position
    // `from' to non-dereferentiable position `to'. 
    iterator splice(iterator to,iterator from) {
      if (from==end()) return to;
      cell *c = from.ptr;
      from.ptr = NULL;
      from.father->sons[from.son] = NULL;

      assert(!to.father->sons[to.son]);
      to.father->sons[to.son] = c;
      return to;
    }
    // Copies subtree fron node `nt' of tree TT in
    // node `nq' of `*this'. 
    iterator copy(iterator nq,ktree<T> &TT,iterator nt) {
      assert(TT.k == k);
      nq = insert(nq,*nt);
      for (int j=0; j<k; j++) {
	iterator m = nt[j];
	if (m != TT.end()) copy(nq[j],TT,m);
      }
      return nq;
    }
    // Finds a node by its value.
    iterator find(T t,iterator p) {
      if(p==end() || *p == t) return p;
      for (int j=0; j<k; j++) {
	iterator l = find(t,p[j]);
	if (l!=end()) return l;
      }
      return end();
    }
    iterator find(T t) { return find(t,begin()); }
    // Leaves the tree empty. 
    void clear() { erase(begin()); }
    // Returns the first position in the tree (i.e. the root). 
    iterator begin() { return iterator(header->sons[0],0,header); }
    // Returns a non-dereferentiable position
    // in the tree. 
    iterator end() { return iterator(); }
    // Prints the tree in Lisp notation (sexp's). 
    void lisp_print(iterator n,const char *s=NULL) {
      if (s) cout << s;
      if (n==end()) cout << "."; 
      else {
	bool is_leaf = true;
	for (int j=0; j<k; j++) {
	  if (n[j] != end()) {
	    is_leaf = false;
	    break;
	  }
	}
	if (is_leaf) cout << *n;
	else {
	  cout << "(" << *n << " ";
	  lisp_print(n[0]);
	  for (int j=1; j<k; j++) {
	    cout << " ";
	    lisp_print(n[j]);
	  }
	  cout << ")";
	}
      }
      if (s) cout << endl;
    }
    // Wrapper
    void lisp_print(const char *s=NULL) { 
      lisp_print(begin(),s); 
    }
  };

  template<class T>
  int ktree<T>::cell_count_m = 0;

}
#endif
