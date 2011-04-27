//PP>if 0
// $Id aed-2.0.1-24-g97d2ae4 Wed Oct 10 22:16:35 2007 -0300$
#ifndef AED_SETBASA_H
#define AED_SETBASA_H

#include <vector>
#include <utility>

using namespace std;

namespace aed {

//PP>endif
  const int N=52;                 //L-defs
  typedef char elem_t;
  int indx(elem_t c) { 
    if (c>='a' && c<='z') return c-'a'; 
    else if (c>='A' && c<='Z') return 26+c-'A'; 
    cout << "Elemento fuera de rango!!\n"; abort(); 
  }
  elem_t element(int j) { 
    assert(j<N);
    return (j<26 ? 'a'+j : 'A'+j-26); 
  }

  typedef int iterator_t;        //L-set-char-b

  class set {
  private:
    vector<bool> v;
    iterator_t next_aux(iterator_t p) {
      while (p<N && !v[p]) p++;
      return p;
    }
    typedef pair<iterator_t,bool> pair_t;
  public:
    set() : v(N,0) { }
    set(const set &A) : v(A.v) {}
    ~set() {}
    iterator_t lower_bound(elem_t x) { 
      return next_aux(indx(x)); 
    }
    pair_t insert(elem_t x) {
      iterator_t k = indx(x);
      bool inserted = !v[k];
      v[k] = true; 
      return pair_t(k,inserted); 
    }
    elem_t retrieve(iterator_t p) { return element(p); }
    void erase(iterator_t p) { v[p]=false; }
    int erase(elem_t x) { 
      iterator_t p = indx(x);
      int r = (v[p] ? 1 : 0);
      v[p] = false; 
      return r;
    }
    void clear() { for(int j=0; j<N; j++) v[j]=false; }
    iterator_t find(elem_t x) { 
      int k = indx(x);
      return (v[k] ? k : N); 
    }
    iterator_t begin() { return next_aux(0); }
    iterator_t end() { return N; }
    iterator_t next(iterator_t p) { 
      return next_aux(++p); 
    }
    int size() { 
      int count=0;
      for (int j=0; j<N; j++) if (v[j]) count++;
      return count; 
    }
    friend void set_union(set &A,set &B,set &C);
    friend void set_intersection(set &A,set &B,set &C);
    friend void set_difference(set &A,set &B,set &C);
  };

  void set_union(set &A,set &B,set &C) {
    for (int j=0; j<N; j++) C.v[j] = A.v[j] || B.v[j];
  }
  void set_intersection(set &A,set &B,set &C) {
    for (int j=0; j<N; j++) C.v[j] = A.v[j] && B.v[j];
  }
  void set_difference(set &A,set &B,set &C) {
    for (int j=0; j<N; j++) C.v[j] = A.v[j] && ! B.v[j];
  }
                             //L-set-char-e
//PP>if 0
}
#endif
// Local Variables: *
// mode: c++ *
// End: *
//PP>endif
