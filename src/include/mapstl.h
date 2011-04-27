template<typename first_t,typename second_t>
class pair {
public:
  first_t first;
  second_t second;
};

template<typename domain_t,typename range_t>
class map  {
private:
  typedef pair<domain_t,range_t> pair_t;
  typedef list<pair_t> list_t;
  list_t l;

public:
  typedef typename list_t::iterator iterator;
  map();
  iterator find(domain_t key);
  range_t & operator[](domain_t key);
  bool empty();
  void erase(iterator p);
  iterator begin();
  iterator end();
  void clear();
};
