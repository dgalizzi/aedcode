//PP>if 0
// $Id: settreap.h,v 1.1 2004/06/09 00:47:03 mstorti Exp $
#ifndef AED_SETBST_H
#define AED_SETBST_H

#include <aedsrc/btree.h>
#include <aedsrc/btreetools.h>
#include <utility>
// #include <cmath>

using namespace std;

namespace aed {

//PP>endif
  template<class T>
  class set {
  private:
    struct node_data { 
      int prio;
      T val;
      node_data(const T &v,int p) 
 	: prio(p), val(v) { }
      node_data() : prio(0) { }
      //PP>if 0
      void print() {
	cout << "[val:" << val << ", p:" << prio << "]";
      }
      //PP>endif
    };
    typedef btree<node_data> tree_t;
    typedef typename tree_t::iterator node_t;
    tree_t bstree;
    node_t min(node_t m) {
      if (m == bstree.end()) return bstree.end();
      while (true) {
	node_t n = m.left();
	if (n==bstree.end()) return m;
	m = n;
      }
    }
    //PP>if 0
    void print(node_t n) { 
      if (n == bstree.end()) {
	cout << ".";
	return;
      }
      node_t 
	r = n.right(),
	l = n.left(),
	e = bstree.end();
      if (r==e && l==e) {
	n->print();
	return;
      }
      cout << "("; n->print(); 
      cout << " "; print(l);
      cout << " "; print(r);
      cout << ")";
    }
    //PP>endif

    void rebalance(node_t f) {
      
    }

#if 0
    void set_union_aux(tree_t &t,node_t n) {
      if (n==t.end()) return;
      else {
	insert(*n);
	set_union_aux(t,n.left());
	set_union_aux(t,n.right());
      }
    }
    void set_intersection_aux(tree_t &t,node_t n, set &B) {
      if (n==t.end()) return;
      else {
	if (B.find(*n)!=B.end()) insert(*n);
	set_intersection_aux(t,n.left(),B);
	set_intersection_aux(t,n.right(),B);
      }
    }
    void set_difference_aux(tree_t &t,node_t n, set &B) {
      if (n==t.end()) return;
      else {
	if (B.find(*n)==B.end()) insert(*n);
	set_difference_aux(t,n.left(),B);
	set_difference_aux(t,n.right(),B);
      }
    }
#endif
    int size_aux(tree_t t,node_t n) {
      if (n==t.end()) return 0;
      else return 1+size_aux(t,n.left())
	     +size_aux(t,n.right());
    }
  public:
    class iterator {
    private:
      friend class set;
      node_t node;
      tree_t *bstree;
      iterator(node_t m,tree_t &t) 
	: node(m), bstree(&t) {}
      node_t next(node_t n) {
	node_t m = n.right();
	if (m!=bstree->end()) {
	  while (true) {
	    node_t q = m.left();
	    if (q==bstree->end()) return m;
	    m = q;
	  }
	} else {
	  // busca el padre
	  m = bstree->begin();
	  if (n==m) return bstree->end();
	  node_t r = bstree->end();
	  while (true) {
	    node_t q;
	    if (n->val < m->val) { q = m.left(); r=m; }
	    else q = m.right();
	    if (q==n) break;
	    m = q;
	  }
	  return r;
	}
      }
    public:
      iterator() : bstree(NULL) { }
      iterator(const iterator &n) : node(n.node), bstree(n.bstree) {}
      iterator& operator=(const iterator& n) { 
	bstree=n.bstree;
	node = n.node; 
      }
      T &operator*() { return node->val; }
      T *operator->() { return &node->val; }
      bool operator!=(iterator q) { return node!=q.node; }
      bool operator==(iterator q) { return node==q.node; }

      // Prefix:
      iterator operator++() {
	node = next(node);
	return *this;
      }
      // Postfix:
      iterator operator++(int) {
	node_t q = node;
	node = next(node);
	return iterator(q,*bstree);
      }
    };
  private:
    typedef pair<iterator,bool> pair_t;
  public:
    set() {}
    set(const set &A) : bstree(A.bstree) {}
    ~set() {}
    iterator lower_bound(T t) { 
      assert(0);
    }
    pair_t insert(T x) { 
      node_t q, f = bstree.begin();
      if (f==bstree.end()) {
	bstree.insert(f,node_data(x,rand()%100));
	return pair_t(iterator(f,bstree),true);
      }
      while(true) {
	if (x < f->val) q = f.left();
	else if (x > f->val) q = f.right();
	else return pair_t(f,false);
	if (q==bstree.end()) break;
	f = q;
      }
      bstree.insert(q,node_data(x,rand()%100));
      rebalance(f);
    }
    void erase(iterator m) { 
      node_t p = m.node;
      node_t qr = p.right(),
	ql = p.left();
      if (qr==bstree.end() && ql==bstree.end())
	bstree.erase(p);
      else if (qr == bstree.end()) {
	tree_t tmp;
	tmp.splice(tmp.begin(),ql);
	bstree.erase(p);
	bstree.splice(p,tmp.begin());
      } else if (ql == bstree.end()) {
	tree_t tmp;
	tmp.splice(tmp.begin(),p.right());
	bstree.erase(p);
	bstree.splice(p,tmp.begin());
      } else { 
	node_t r = min(qr);
	node_data val = *r;
	erase(iterator(r,bstree));
	*p = val;
      } 
    }
    int erase(T x) {
      iterator q = find(x);
      int ret;
      if (q==end()) ret = 0;
      else {
	erase(q);
	ret = 1; 
      }
      return ret;
    }
    void clear() { bstree.clear(); }
    iterator find(T x) {
      node_t m = bstree.begin();
      while (true) {
	if (m == bstree.end()) 
	  return iterator(m,bstree);
	if (x < m->val) m = m.left();
	else if (x > m->val) m = m.right();
	else return iterator(m,bstree);
      }
    }
    iterator begin() { 
      return iterator(min(bstree.begin()),bstree);
    }
    iterator end() { 
      return iterator(bstree.end(),bstree); 
    }
    int size() { return size_aux(bstree,bstree.begin()); }
    friend void set_union<>(set<T> &A,set<T>  &B,set<T>  &C);
    friend void set_intersection<>(set<T>  &A,set<T>  &B,set<T>  &C);
    friend void set_difference<>(set<T>  &A,set<T>  &B,set<T>  &C);
    //PP>if 0
    void print() { 
      print(bstree.begin()); 
      cout << endl;
    }
    //PP>endif
  };

  template<class T>
  void set_union(set<T> &A,set<T> &B,set<T> &C) {
#if 0
    C.clear();
    C.set_union_aux(A.bstree,A.bstree.begin());
    C.set_union_aux(B.bstree,B.bstree.begin());
#endif
  }

  template<class T>
  void set_intersection(set<T> &A,set<T> &B,set<T> &C) {
#if 0
    C.clear();
    C.set_intersection_aux(A.bstree,A.bstree.begin(),B);
#endif
  }

  // C = A - B
  template<class T>
  void set_difference(set<T> &A,set<T> &B,set<T> &C) {
#if 0
    C.clear();
    C.set_difference_aux(A.bstree,A.bstree.begin(),B);
#endif
  }

//PP>if 0
}
#endif
// Local Variables: *
// mode: c++ *
// End: *
//PP>endif
