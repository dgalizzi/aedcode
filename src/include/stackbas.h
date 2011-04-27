  class stack : private list {
  private:
    int size_m;
  public:
    stack();
    void clear();
    elem_t& top();
    void pop();
    void push(elem_t x);
    int size();
    bool empty();
  };

