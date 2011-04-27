  typedef int iterator_t;

  class list {
  private:
    static int MAX_SIZE;
    elem_t *elems;
    int size;
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
    iterator_t next(iterator_t p);
    iterator_t prev(iterator_t p);
    elem_t & retrieve(iterator_t p);
  };

