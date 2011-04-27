  template<class T>
  class set {
  private:
    /* ... */
  public:
    class iterator {
      friend class set;
      T & operator*();
      T *operator->();
      bool operator!=(iterator q);
      bool operator==(iterator q);
    }
    set() {}
    set(const set &A) : L(A.L) {}
    ~set() {}
    set &operator=(set<T> &);
    iterator lower_bound(T t);
    pair<iterator,bool> insert(T x);
    void erase(iterator p);
    int erase(T x);
    void clear();
    iterator find(T x);
    iterator begin();
    iterator end();
    int size();
  };

  template<class T>
  void set_union(set<T> &A,set<T> &B,set<T> &C);

  template<class T>
  void set_intersection(set<T> &A,set<T> &B,set<T> &C);

  template<class T>
  void set_difference(set<T> &A,set<T> &B,set<T> &C);
