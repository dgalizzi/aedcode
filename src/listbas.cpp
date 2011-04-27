class iterator_t { /* ... */ };

class list {
private:
  // ...
public:
  // ...
  iterator_t insert(iterator_t p,elem_t x);
  iterator_t erase(iterator_t p);
  elem_t & retrieve(iterator_t p);
  iterator_t next(iterator_t p);
  iterator_t begin();
  iterator_t end();
}

