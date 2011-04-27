// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: treap.h,v 1.9 2004/12/19 23:16:55 mstorti Exp $
#ifndef PETSCFEM_TREE_H
#define PETSCFEM_TREE_H

#include <aedsrc/btree.h>
#include <list>
#include <iostream>
#include <cmath>

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
template<class T>
class treap_set {
private:
  static int MAX_PRIORITY;
  static int LEFT; 
  static int RIGHT;
  struct node_data {
    T t;
    int prio;
    friend std::ostream& 
    operator<<(std::ostream &s,node_data &d) {
      s << "[" << d.t << "," << d.prio << "]  " ;
      return s;
    }
  };
  typedef typename aed::btree<node_data> tree_t;
  tree_t tree;
  int size_m;
  typedef typename tree_t::iterator node_t;
  typedef typename std::list<node_t> list_t;
  int max_depth(node_t n) {
    if (n==tree.end()) return -1;
    else {
      int ml = max_depth(n.left());
      int md = max_depth(n.right());
      return (ml>md ? ml: md)+1;
    }
  }
  void aver_depth(node_t n,int &wsum,int &sum) {
    if (n==tree.end()) {
      wsum = 0; sum = 0; 
    } else {
      int sumr,wsumr,suml,wsuml;
      aver_depth(n.left(),wsuml,suml);
      aver_depth(n.right(),wsumr,sumr);
      sum = 1+sumr+suml;
      wsum = wsumr+sumr+wsuml+suml;
    }
  }
  // Rotates right the tree 
  // (D (A B C) E) -> (A B (D C E))
  // D and A are updated to their new
  // positions. 
  void right_rotate(node_t &A,node_t &D) {
    tree_t B,C,E;
    node_data Ad = *A;
    B.splice(B.begin(),A.left());
    C.splice(C.begin(),A.right());
    E.splice(E.begin(),D.right());
    tree.insert(D.right(),*D);
    *D = Ad;
    A = tree.erase(A);
    tree.splice(A,B.begin());
    A = D;
    D = A.right();
    tree.splice(D.left(),C.begin());
    tree.splice(D.right(),E.begin());
  }
  // Rotates left the tree 
  // (A B (D C E)) -> (D (A B C) E)
  // D and A are updated to their new
  // positions. 
  void left_rotate(node_t &D,node_t &A) {
    tree_t B,C,E;
    node_data Dd = *D;
    B.splice(B.begin(),A.left());
    C.splice(C.begin(),D.left());
    E.splice(E.begin(),D.right());
    tree.insert(A.left(),*A);
    *A = Dd;
    D = tree.erase(D);
    tree.splice(D,E.begin());
    D = A;
    A = D.left();
    tree.splice(A.left(),B.begin());
    tree.splice(A.right(),C.begin());
  }
  void find_aux(T x,node_t &node) { 
    if (node == tree.end()) return;
    if (node->t == x) return;
    else if (x < node->t) 
      node = node.left();
    else 
      node = node.right();
    find_aux(x,node);
  }
  bool insert_aux(T x,node_t &node) { 
    if (node == tree.end()) {
      node = tree.insert(node,node_data());
      size_m++;
      node->t = x;
      node->prio = rand() % MAX_PRIORITY;
      // printf("insert new val x %d, prio %d\n",x,node->prio);
      return true;
    }
    int side;
    node_t father = node;
    if (node->t == x) return false;
    else if (x < node->t) {
      node = node.left(); side = LEFT;
    } else {
      node = node.right(); side = RIGHT;
    }
    bool ok = insert_aux(x,node);
    if (!ok) return ok;
    // re-balance in order to restore heap property
    if (node->prio < father->prio) {
      if (side == LEFT) right_rotate(node,father);
      else left_rotate(node,father);
    }
    return ok;
  }
  // Pushes `node' by rotations until it is
  // a leave and then prune. 
  void erase_aux(node_t &node) { 
    if (node == tree.end()) return;
    node_t 
      left = node.left(),
      right = node.right();
    if (left == tree.end() 
	&& right == tree.end()) {
      node = tree.erase(node);
      size_m--;
      return;
    } else if (left == tree.end()) 
      left_rotate(right,node);
    else if (right == tree.end() || left->t < right->t) 
      right_rotate(left,node);
    else right_rotate(left,node);
    erase_aux(node);
  }
  node_t min(node_t m) {
    if (m == tree.end()) return tree.end();
    while (true) {
      node_t n = m.left();
      if (n==tree.end()) return m;
      m = n;
    }
  }
  node_t next(node_t n) {
    node_t m = n.right();
    if (m!=tree.end()) {
      while (true) {
	node_t q = m.left();
	if (q==tree.end()) return m;
	m = q;
      }
    } else {
      // search father
      m = tree.begin();
      if (n==m) return tree.end();
      node_t r = tree.end();
      while (true) {
	node_t q;
	if (n->t < m->t) { q = m.left(); r=m; }
	else q = m.right();
	if (q==n) break;
	m = q;
      }
      return r;
    }
  }
public:
  class iterator {
  private:
    node_t node;
    treap_set *treap;
    iterator(node_t m,treap_set &t) 
	: node(m), treap(&t) {}
  public:
    friend class treap_set;
    iterator() : treap(NULL) { }
    iterator(const iterator &n) 
      : node(n.node), treap(n.treap) {}
    iterator& operator=(const iterator& n) { 
      treap=n.treap;
      node = n.node; 
    }
    T &operator*() { return node->t; }
    T *operator->() { return node->t; }
    bool operator!=(iterator q) {
      return q.node!=node;
    }
    bool operator==(iterator q) {
      return q.node==node;
    }
    // Prefix:
    iterator operator++() {
      node = treap->next(node);
      return *this;
    }
    // Postfix:
    iterator operator++(int) {
      node_t q = node;
      node = treap->next(node);
      return iterator(q,*treap);
    }
  };
private:
  typedef typename std::pair<iterator,bool> pair_t;
public:
  treap_set() : size_m(0) {}
  treap_set(const treap_set &A) : tree(A.tree) {}
  ~treap_set() {}
  treap_set &operator=(treap_set<T> &A ) { 
    tree = A.tree; 
  }
  pair_t insert(T x) { 
    pair_t p;
    p.first.node = tree.begin();
    p.second  = insert_aux(x,p.first.node);
    return p;
  }
  int max_depth() {
    return max_depth(tree.begin());
  }
  double aver_depth() {
    int wsum,sum;
    aver_depth(tree.begin(),wsum,sum);
    double avd = double(wsum)/double(sum);
    double q = avd/log2(sum);
    printf("wsum %d, sum %d, <depth>= %f, "
	   "<depth>/(log2 n)= %f\n",
	   wsum,sum,avd,q);
  }
  iterator find(T x) { 
    iterator q;
    q.node = tree.begin();
    find_aux(x,q.node);
    return q;
  }
  void erase(iterator p) {
    if (p.node!=tree.end()) 
      size_m--;
    tree.erase(p.node);
  }
  int erase(T x) {
    node_t node = tree.begin();
    find_aux(x,node);
    if (node == tree.end()) return 0;
    erase_aux(node);
  }
  void clear() { tree.clear(); }
  iterator begin() { 
    return iterator(min(tree.begin()),*this);
  }
  iterator end() { 
    return iterator(tree.end(),*this); 
  }
  int size() { return size_m; }
#if 1
  void print() { 
    tree.lisp_print(); 
    printf("\n");
  }
#endif
};

template<class T>
int treap_set<T>::MAX_PRIORITY = INT_MAX;
// int treap_set<T>::MAX_PRIORITY = 10;

template<class T>
int treap_set<T>::LEFT = 0;

template<class T>
int treap_set<T>::RIGHT = 1;

#endif
