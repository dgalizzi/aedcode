  typedef int key_t;

  class hash_set;
  class iterator_t {
    friend class hash_set;
  private:
    int bucket;
    std::list<key_t>::iterator p;
    iterator_t(int b,std::list<key_t>::iterator q)
      : bucket(b), p(q) { }
  public:
    bool operator==(iterator_t q) {
      return (bucket == q.bucket && p==q.p);
    }
    bool operator!=(iterator_t q) { 
      return !(*this==q); 
    }
    iterator_t() { }
  };
  typedef int (*hash_fun)(key_t x);

  class hash_set {
  private:
    typedef std::list<key_t> list_t;
    typedef list_t::iterator listit_t;
    typedef std::pair<iterator_t,bool> pair_t;
    hash_set(const hash_set&) {}
    hash_set& operator=(const hash_set&) {}
    hash_fun h;
    int B;
    int count;
    std::vector<list_t> v;
    iterator_t next_aux(iterator_t p) {
      while (p.p==v[p.bucket].end() 
	     && p.bucket<B-1) {
	p.bucket++;
	p.p = v[p.bucket].begin();
      }
      return p;
    }
  public:
    hash_set(int B_a,hash_fun h_a) 
      : B(B_a), v(B), h(h_a), count(0) { }
    iterator_t begin() {
      iterator_t p = iterator_t(0,v[0].begin());
      return next_aux(p);
    }
    iterator_t end() {
      return iterator_t(B-1,v[B-1].end());
    }
    iterator_t next(iterator_t p) {
      p.p++; return next_aux(p);
    }
    key_t retrieve(iterator_t p) { return *p.p; }
    pair_t insert(const key_t& x) {
      int b = h(x) % B;
      list_t &L = v[b];
      listit_t p = L.begin();
      while (p!= L.end() && *p!=x) p++;
      if (p!= L.end()) 
	return pair_t(iterator_t(b,p),false);
      else {
	count++;
	p = L.insert(p,x);
	return pair_t(iterator_t(b,p),true);
      }
    }
    iterator_t find(key_t& x) {
      int b = h(x) % B;
      list_t &L = v[b];
      listit_t p = L.begin();
      while (p!= L.end() && *p!=x) p++;
      if (p!= L.end()) 
	return iterator_t(b,p);
      else return end();
    }
    int erase(const key_t& x) {
      list_t &L = v[h(x) % B];
      listit_t p = L.begin();
      while (p!= L.end() && *p!=x) p++;
      if (p!= L.end()) {
	L.erase(p);
	count--;
	return 1;
      } else return 0;
    }
    void erase(iterator_t p) {
      v[p.bucket].erase(p.p);
    }
    void clear() {
      count=0;
      for (int j=0; j<B; j++) v[j].clear();
    }
    int size() { return count; }
  };
