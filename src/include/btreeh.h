template<class T>
class btree {
  /* ... */
 public:
  class iterator {
  /* ... */
  public:
    T &operator*();
    T *operator->();
    bool operator!=(iterator q);
    bool operator==(iterator q);
    iterator left();
    iterator right();
  };
  iterator begin();
  iterator end();
  iterator insert(iterator p,T t);
  iterator erase(iterator p);
  iterator splice(iterator to,iterator from);
  void clear();
};
