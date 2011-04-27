  class list;
  typedef int iterator_t;

  class cell {
    friend class list;
    elem_t elem;
    iterator_t next;
    cell();
  };

  class list {
  private:
    friend class cell;
    static iterator_t NULL_CELL;
    static int CELL_SPACE_SIZE;
    static cell *cell_space;
    static iterator_t top_free_cell;
    iterator_t new_cell();
    void delete_cell(iterator_t c);
    iterator_t first, last;
    void cell_space_init();    
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
  };
