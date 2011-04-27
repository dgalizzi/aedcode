  typedef int elem_t;      

  typedef list<elem_t>::iterator iterator_t;

  class set {
  private:
    list<elem_t> L;
  public:
    set() {}
    set(const set &A) : L(A.L) {}
    ~set() {}
    elem_t retrieve(iterator_t p) { return *p; }
    iterator_t lower_bound(elem_t t) { 
      list<elem_t>::iterator p = L.begin();
      while (p!=L.end() && t>*p) p++;
      return p;
    }
    iterator_t next(iterator_t p) { return ++p; }
    pair<iterator_t,bool> insert(elem_t x) { 
      pair<iterator_t,bool> q;
      iterator_t p;
      p = lower_bound(x);
      q.second = p==end() || *p!=x;
      if(q.second) p = L.insert(p,x);
      q.first = p;
      return q;
    }
    void erase(iterator_t p) { L.erase(p); }
    void erase(elem_t x) {
      list<elem_t>::iterator 
	p = lower_bound(x);
      if (p!=end() && *p==x) L.erase(p);
    }
    void clear() { L.clear(); }
    iterator_t find(elem_t x) {
      list<elem_t>::iterator 
	p = lower_bound(x);
      if (p!=end() && *p==x) return p;
      else return L.end();
    }
    iterator_t begin() { return L.begin(); }
    iterator_t end() { return L.end(); }
    int size() { return L.size(); }
    friend void set_union(set &A,set &B,set &C);
    friend void set_intersection(set &A,set &B,set &C);
    friend void set_difference(set &A,set &B,set &C);
  };

  void set_union(set &A,set &B,set &C) {
    C.clear();
    list<elem_t>::iterator pa = A.L.begin(),
      pb = B.L.begin(), pc = C.L.begin();
    while (pa!=A.L.end() && pb!=B.L.end()) {
      if (*pa<*pb) { pc = C.L.insert(pc,*pa); pa++; }
      else if (*pa>*pb) {pc = C.L.insert(pc,*pb); pb++; }
      else {pc = C.L.insert(pc,*pa); pa++; pb++; }
      pc++;
    }
    while (pa!=A.L.end()) { 
      pc = C.L.insert(pc,*pa); 
      pa++; pc++; 
    }
    while (pb!=B.L.end()) { 
      pc = C.L.insert(pc,*pb); 
      pb++; pc++; 
    }
  }
  void set_intersection(set &A,set &B,set &C) {
    C.clear();
    list<elem_t>::iterator pa = A.L.begin(),
      pb = B.L.begin(), pc = C.L.begin();
    while (pa!=A.L.end() && pb!=B.L.end()) {
      if (*pa<*pb) pa++;
      else if (*pa>*pb) pb++;
      else { pc=C.L.insert(pc,*pa); pa++; pb++; pc++; }
    }
  }
  // C = A - B
  void set_difference(set &A,set &B,set &C) {
    C.clear();
    list<elem_t>::iterator pa = A.L.begin(),
      pb = B.L.begin(), pc = C.L.begin();
    while (pa!=A.L.end() && pb!=B.L.end()) {
      if (*pa<*pb) { pc=C.L.insert(pc,*pa); pa++; pc++; }
      else if (*pa>*pb) pb++;
      else { pa++; pb++; }
    }
    while (pa!=A.L.end()) { 
      pc = C.L.insert(pc,*pa); 
      pa++; pc++; 
    }
  }
