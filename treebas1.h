class iterator_t {
  /* .... */
public:
  iterator_t lchild();
  iterator_t right();
};

class tree {
  /* .... */
public:
  iterator_t begin();
  iterator_t end();
  elem_t &retrieve(iterator_t p);
  iterator_t insert(iterator_t p,elem_t t);
  iterator_t erase(iterator_t p);
  void clear();
  iterator_t splice(iterator_t to,iterator_t from);
};
