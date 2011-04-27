  typedef int elem_t;      

  class iterator_t {
  private:
    /* ... */;
  public:
    bool operator!=(iterator_t q);
    bool operator==(iterator_t q);
  };

  class set {
  private:
    /* ... */;
  public:
    set();
    set(const set &);
    ~set();
    elem_t retrieve(iterator_t p);
    pair<iterator_t,bool> insert(elem_t t);
    void erase(iterator_t p);
    int erase(elem_t x);
    void clear();
    iterator_t next(iterator_t p);
    iterator_t find(elem_t x);
    iterator_t begin();
    iterator_t end();
  };
  void set_union(set &A,set &B,set &C);
  void set_intersection(set &A,set &B,set &C);
  void set_difference(set &A,set &B,set &C); 

