template<class T>
class set {
public:
  class iterator { /* ... */ };
  void insert(T x);
  void erase(iterator p);
  void erase(T x);
  iterator find(T x);
  iterator begin();
  iterator end();
};

