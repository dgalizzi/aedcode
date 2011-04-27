  template<class T>
  class set {
  private:
    list<T> L;
  public:
    typedef typename list<T>::iterator iterator;
    typedef pair<iterator,bool> pair_t;
    set() {}
    set(const set &A) : L(A.L) {}
    ~set() {}
    iterator lower_bound(T t) { 
      iterator p = L.begin();
      while (p!=L.end() && t>*p) p++;
      return p;
    }
    pair_t insert(T x) { 
      iterator p = lower_bound(x);
      if(p==end() || *p!=x) {
	p = L.insert(p,x);
	return pair_t(p,true);
      } else {
	return pair_t(end(),false); 
      }
    }
    void erase(iterator p) { L.erase(p); }
    int erase(T x) {
      iterator p = lower_bound(x);
      if (p!=end() && *p==x) {
	L.erase(p); return 1;
      } else return 0;
    }
    void clear() { L.clear(); }
    iterator find(T x) {
      iterator p = lower_bound(x);
      if (p!=end() && *p==x) return p;
      else return L.end();
    }
    iterator begin() { return L.begin(); }
    iterator end() { return L.end(); }
    int size() { return L.size(); }
    bool empty() { return !L.size(); }
    friend void set_union<>(set<T> &A,set<T>  &B,set<T>  &C);
    friend void set_intersection<>(set<T>  &A,set<T>  &B,set<T>  &C);
    friend void set_difference<>(set<T>  &A,set<T>  &B,set<T>  &C);
  };

  template<class T>
  void set_union(set<T> &A,set<T> &B,set<T> &C) {
    C.clear();
    typename list<T>::iterator pa = A.L.begin(),
      pb = B.L.begin(), pc = C.L.begin();
    while (pa!=A.L.end() && pb!=B.L.end()) {
      if (*pa<*pb) {pc = C.L.insert(pc,*pa); pa++; }
      else if (*pa>*pb) {pc = C.L.insert(pc,*pb); pb++; }
      else {pc = C.L.insert(pc,*pa); pa++; pb++; }
      pc++;
    }
    while (pa!=A.L.end()) { 
      pc = C.L.insert(pc,*pa); pa++; pc++; 
    }
    while (pb!=B.L.end()) { 
      pc = C.L.insert(pc,*pb); pb++; pc++; 
    }
  }

  template<class T>
  void set_intersection(set<T> &A,set<T> &B,set<T> &C) {
    C.clear();
    typename list<T>::iterator pa = A.L.begin(),
      pb = B.L.begin(), pc = C.L.begin();
    while (pa!=A.L.end() && pb!=B.L.end()) {
      if (*pa<*pb) pa++;
      else if (*pa>*pb) pb++;
      else {C.L.insert(pc,*pa); pa++; pb++; }
    }
  }

  // C = A - B
  template<class T>
  void set_difference(set<T> &A,set<T> &B,set<T> &C) {
    C.clear();
    typename list<T>::iterator pa = A.L.begin(),
      pb = B.L.begin(), pc = C.L.begin();
    while (pa!=A.L.end() && pb!=B.L.end()) {
      if (*pa<*pb) {C.L.insert(pc,*pa); pa++; }
      else if (*pa>*pb) pb++;
      else { pa++; pb++; }
    }
    while (pa!=A.L.end()) { 
      pc = C.L.insert(pc,*pa); pa++; pc++; 
    }
  }
