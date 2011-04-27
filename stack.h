#ifndef AED_STACK_H
#define AED_STACK_H

#include <aedsrc/list.h>

namespace aed {

  template<class T>
  class stack : private list<T> {
  private:
    int size_m;
  public:
    stack() : size_m(0) { }
    void clear() { erase(begin(),end()); size_m = 0; }
    T &top() { return *begin(); }
    void pop() { erase(begin()); size_m--; }
    void push(T x) { insert(begin(),x); size_m++; }
    int size() { return size_m; }
    bool empty() { return size_m==0; }
  };
}
#endif
