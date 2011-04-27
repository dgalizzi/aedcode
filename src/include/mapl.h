  class map;

  class elem_t {
  private:
    friend class map;
    domain_t first;
    range_t second;
  };
  // iterator para map va a ser el mismo que para listas.
  class map  {
  private:
    list l;

    iterator_t lower_bound(domain_t key) {
      iterator_t p = l.begin();
      while (p!=l.end()) {
	domain_t dom = l.retrieve(p).first;
	if (dom >= key) return p;
	p = l.next(p);
      }
      return l.end();
    }

  public:
    map()  { }
    iterator_t find(domain_t key) {
      iterator_t p = lower_bound(key);
      if (p!=l.end() && l.retrieve(p).first == key)
	return p;
      else return l.end();
    }
    iterator_t insert(domain_t key,range_t val) {
      iterator_t p = lower_bound(key);
      if (p==l.end() || l.retrieve(p).first != key) {
	elem_t elem;
	elem.first = key;
	p = l.insert(p,elem);
      }
      l.retrieve(p).second = val;
      return p;
    }
    range_t &retrieve(domain_t key) {
      iterator_t q = find(key);
      if (q==end()) q=insert(key,range_t());
      return l.retrieve(q).second;
    }
    bool empty() { return l.begin()==l.end(); }
    void erase(iterator_t p) { l.erase(p); }
    int erase(domain_t key) { 
      iterator_t p = find(key); int r = 0;
      if (p!=end()) { l.erase(p); r = 1; }
      return r;
    }
    iterator_t begin() { return l.begin(); }
    iterator_t end() { return l.end(); }
    void clear() { l.erase(l.begin(),l.end()); }
    int size() { return l.size(); }
    domain_t key(iterator_t p) { 
      return l.retrieve(p).first; 
    }
    range_t &value(iterator_t p) { 
      return l.retrieve(p).second; 
    }
  };
