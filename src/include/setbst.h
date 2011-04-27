  template<class T>
  class set {
  private:
    typedef btree<T> tree_t;
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

    void set_union_aux(tree_t &t,node_t n) {
      if (n==t.end()) return;
      else {
	insert(*n);
	set_union_aux(t,n.left());
	set_union_aux(t,n.right());
      }
    }
    void set_intersection_aux(tree_t &t,
			      node_t n, set &B) {
      if (n==t.end()) return;
      else {
	if (B.find(*n)!=B.end()) insert(*n);
	set_intersection_aux(t,n.left(),B);
	set_intersection_aux(t,n.right(),B);
      }
    }
    void set_difference_aux(tree_t &t,
			    node_t n, set &B) {
      if (n==t.end()) return;
      else {
	if (B.find(*n)==B.end()) insert(*n);
	set_difference_aux(t,n.left(),B);
	set_difference_aux(t,n.right(),B);
      }
    }
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
	    if (*n<*m) { q = m.left(); r=m; }
	    else q = m.right();
	    if (q==n) break;
	    m = q;
	  }
	  return r;
	}
      }
    public:
      iterator() : bstree(NULL) { }
      iterator(const iterator &n) 
	: node(n.node), bstree(n.bstree) {}
      iterator& operator=(const iterator& n) { 
	bstree=n.bstree;
	node = n.node; 
      }
      T &operator*() { return *node; }
      T *operator->() { return &*node; }
      bool operator!=(iterator q) { 
	return node!=q.node; }
      bool operator==(iterator q) { 
	return node==q.node; }

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
    pair_t insert(T x) { 
      node_t q = find(x).node;
      if (q == bstree.end()) {
	q = bstree.insert(q,x);
	return pair_t(iterator(q,bstree),true);
      } else return pair_t(iterator(q,bstree),false);
    }
    void erase(iterator m) { 
      node_t p = m.node;
      node_t qr = p.right(),
	ql = p.left();
      if (qr==bstree.end() && ql==bstree.end())
	bstree.erase(p);
      else if (qr == bstree.end()) {
	btree<T> tmp;
	tmp.splice(tmp.begin(),ql);
	bstree.erase(p);
	bstree.splice(p,tmp.begin());
      } else if (ql == bstree.end()) {
	btree<T> tmp;
	tmp.splice(tmp.begin(),p.right());
	bstree.erase(p);
	bstree.splice(p,tmp.begin());
      } else { 
	node_t r = min(qr);
	T minr = *r;
	erase(iterator(r,bstree));
	*p = minr;
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
	if (x<*m) m = m.left();
	else if (x>*m) m = m.right();
	else return iterator(m,bstree);
      }
    }
    iterator begin() { 
      return iterator(min(bstree.begin()),bstree);
    }
    iterator end() { 
      return iterator(bstree.end(),bstree); 
    }
    int size() { 
      return size_aux(bstree,bstree.begin()); }
    friend void 
    set_union<>(set<T> &A,set<T> &B,set<T> &C);
    friend void 
    set_intersection<>(set<T> &A,set<T> &B,set<T> &C);
    friend void 
    set_difference<>(set<T> &A,set<T> &B,set<T> &C);
  };

  template<class T> void 
  set_union(set<T> &A,set<T> &B,set<T> &C) {
    C.clear();
    C.set_union_aux(A.bstree,A.bstree.begin());
    C.set_union_aux(B.bstree,B.bstree.begin());
  }

  template<class T> void 
  set_intersection(set<T> &A,set<T> &B,set<T> &C) {
    C.clear();
    C.set_intersection_aux(A.bstree,
			   A.bstree.begin(),B);
  }

  // C = A - B
  template<class T> void 
  set_difference(set<T> &A,set<T> &B,set<T> &C) {
    C.clear();
    C.set_difference_aux(A.bstree,
			 A.bstree.begin(),B);
  }
