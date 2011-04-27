// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: hashsetcbas.h,v 1.2 2004/05/24 04:03:24 mstorti Exp $
#ifndef AED_HASHSETCBAS_H
#define AED_HASHSETCBAS_H

#include <list>
#include <vector>
#include <utility>

namespace aed {
  typedef int key_t;
  typedef std::list<key_t> list_t;
  typedef list_t::iterator pos_t;
  typedef int (*hash_fun)(key_t x);
  typedef int (*redisp_fun)(key_t x);

  class iterator_t {
  private:
    friend class hash_set;
    int bucket;
    pos_t p;
    iterator_t(int b,pos_t p_a) 
      : bucket(b), p(p_a) {}
  };

  int linear_redisp_fun(int j) { return j; }

  class hash_set {
  private:
    hash_set(const hash_set&) {}
    hash_set& operator=(const hash_set&) {}
    hash_fun h;
    int n;
    int count;
    std::vector<list_t> v;
    pos_t find(list_t &L,key_t x) {
      pos_t p = L.begin();
      while (p!=L.end()) {
	if (*p==x) break;
	p++;
      }
      return p;
    }
  public:
    hash_set(int n_a,hash_fun h_a) 
      : n(n_a), v(n), h(h_a), count(0) { }
    std::pair<iterator_t, bool> 
      insert(const key_t& x) {
      int bucket = h(x) % n;
      list_t &L = v[bucket];
      pos_t q = find(L,x);
      if (q!=L.end()) {
	iterator_t p(bucket,q);
	return std::pair<iterator_t,bool>(p,false);
      } else {
	count++;
	q = L.insert(L.begin(),x);
	iterator_t p(bucket,q);
	return std::pair<iterator_t,bool>(p,false);
      }
    }
    int erase(const key_t& x) {
      int bucket = h(x) % n;
      list_t &L = v[bucket];
      pos_t q = find(L,x);
      if (q!=L.end()) {
	L.erase(q);
	count--;
	return 1;
      } else return 0;
    }
    void clear() {
      count=0;
      for (int j=0; j<n; j++) v[j].clear();
    }
    int size() { return count; }
    void print() {
      for (int j=0; j<n; j++) {
	list_t &L = v[j];
	pos_t p = L.begin();
	while (p!=L.end()) std::cout << *p++ << " ";
      }
      std::cout << std::endl;
    }
  };

}
#endif
