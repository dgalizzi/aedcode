#ifndef AED_MAPV_H
#define AED_MAPV_H

#include <iostream>
#include <vector>

using namespace std;

namespace aed {

  template<typename first_t,typename second_t>
  class pair {
  public:
    first_t first;
    second_t second;
    pair() : first(first_t()), second(second_t()) {}
  };

  // iterator para map va a ser el mismo que para listas.
  template<typename domain_t,typename range_t>
  class map  {

  public:
    typedef int iterator;

  private:
    typedef pair<domain_t,range_t> pair_t;
    typedef vector<pair_t> vector_t;
    vector_t v;

    iterator lower_bound(domain_t key) {
      int p=0, q=v.size(), r;
      if (!q || v[p].first >key) return 0;
      while (q-p > 1) {
	r = (p+q)/2;
	range_t kr = v[r].first;
	if (key > kr) p=r;
	else if (key < kr) q=r;
	else if (kr==key) return r;
      }
      if (v[p].first == key) return p;
      else return q;
    }

  public:
    map()  { }

    iterator find(domain_t key) {
      int p = lower_bound(key);
      if (p == v.size() || v[p].first == key) return p;
      else return v.size();
    }
    range_t & operator[](domain_t key) {
      iterator p = lower_bound(key);
      if (p == v.size() || v[p].first != key) {
	v.push_back(pair_t());
	iterator q = v.size(); 
	while (--q > p) v[q] = v[q-1];
	v[p].first = key;
      }
      return v[p].second;
    }
    int erase(domain_t key) { 
      iterator p = find(key); int r = 0;
      if (p!=end()) { erase(p); r = 1; }
      return r;
    }
    bool empty() { return v.size()==0; }
    void erase(iterator p) { 
      iterator q = p;
      while (q != v.size()) {
	v[q] = v[q+1];
	q++;
      }
      v.pop_back();
    }
    iterator begin() { return 0; }
    iterator end() { return v.size(); }
    void clear() { v.clear(); }
    int size() { return v.size(); }
  };
}
#endif

