#ifndef AED_MAP_H
#define AED_MAP_H

#include <aedsrc/list.h>
#include <iostream>

using namespace std;

namespace aed {

  template<typename first_t,typename second_t>
  class pair {
  public:
    first_t first;
    second_t second;
    pair(first_t f=first_t(),second_t s=second_t()) 
      : first(f), second(s) {}
  };

  // iterator para map va a ser el mismo que para listas.
  template<typename domain_t,typename range_t>
  class map  {

  private:
    typedef pair<domain_t,range_t> pair_t;
    typedef list<pair_t> list_t;
    list_t l;

  public:
    typedef typename list_t::iterator iterator;

  private:
    iterator lower_bound(domain_t key) {
      iterator p = l.begin();
      while (p!=l.end()) {
	domain_t dom = p->first;
	if (dom >= key) return p;
	p++;
      }
      return l.end();
    }

  public:
    map()  { }

    iterator find(domain_t key) {
      iterator p = lower_bound(key);
      if (p!=l.end() && p->first == key)
	return p;
      else return l.end();
    }
    range_t & operator[](domain_t key) {
      iterator q = lower_bound(key);
      if (q==end() || q->first!=key) 
        q = l.insert(q,pair_t(key,range_t()));
      return q->second;
    }
    bool empty() { return l.begin()==l.end(); }
    void erase(iterator p) { l.erase(p); }
    iterator begin() { return l.begin(); }
    iterator end() { return l.end(); }
    iterator next(iterator p) { return l.next(p); }
    void clear() { l.erase(l.begin(),l.end()); }
  };
}
#endif

