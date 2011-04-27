class iterator_t {/* ... */};

class map {
 private:
  // ...
 public:
  iterator_t find(domain_t key);
  iterator_t insert(domain_t key,range_t val);
  range_t& retrieve(domain_t key);
  void erase(iterator_t p);
  domain_t key(iterator_t p);
  range_t& value(iterator_t p);
  iterator_t begin();
  iterator_t next(iterator_t p);
  iterator_t end();
  void clear();
  void print();
};

