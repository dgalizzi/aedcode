  class cell;
  typedef cell *iterator_t;

  class list {
  private:
    cell *first, *last;
  public:
    list();
    ~list();
    iterator_t insert(iterator_t p,elem_t j);
    iterator_t erase(iterator_t p);
    iterator_t erase(iterator_t p,iterator_t q);
    void clear();
    iterator_t begin();
    iterator_t end();
    void print();
    void printd();
    iterator_t next(iterator_t p);
    iterator_t prev(iterator_t p);
    elem_t & retrieve(iterator_t p);
    int size();
  };           

  class cell {
    friend class list;
    elem_t elem;
    cell *next;
    cell() : next(NULL) {}
  }; 
