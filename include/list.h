#ifndef AED_LIST_H 
#define AED_LIST_H

#include <cstddef>  
#include <iostream>  

namespace aed {

  template<class T>
  class list {
  public:
    class iterator;
  private:
    class cell {
      friend class list;
      friend class iterator;
      T t;
      cell *next;
      cell() : next(NULL) {}
    };
    cell *first, *last;
  public:
    class iterator {
    private:
      friend class list;
      cell* ptr;
    public:
      T & operator*() { return ptr->next->t; }
      T *operator->() { return &ptr->next->t; }
      bool operator!=(iterator q) { return ptr!=q.ptr; }
      bool operator==(iterator q) { return ptr==q.ptr; }
      iterator(cell *p=NULL) : ptr(p) {}
      // Prefix:
      iterator operator++() {
	ptr = ptr->next;
	return *this;
      }
      // Postfix:
      iterator operator++(int) {
	iterator q = *this;
	ptr = ptr->next;
	return q;
      }
    };  

    list() {
      first = new cell;
      last = first;
    }
    iterator insert(iterator p,T t) {
      cell *q = p.ptr->next;
      cell *c = new cell;
      p.ptr->next = c;
      c->next = q;
      c->t = t;
      if (q==NULL) last = c;
      return p;
    }
    iterator erase(iterator p) {
      cell *q = p.ptr->next;
      if (q==last) last = p.ptr;
      p.ptr->next = q->next;
      delete q;
      return p;
    }
    iterator erase(iterator p,iterator q) {
      cell *s, *r = p.ptr->next;
      p.ptr->next = q.ptr->next;
      if (!p.ptr->next) last = p.ptr;
      while (r!=q.ptr->next) {
	s = r->next;
	delete r;
	r = s;
      }
      return p;
    }
    void clear() { erase(begin(),end()); }
    iterator begin() { return iterator(first); }
    iterator end() { return iterator(last); }
    void print() {   
      iterator p = begin();
      while (p!=end()) std::cout << *p++ << " ";
      std::cout << std::endl;
    }
    void printd() {
      std::cout << "h(" << first << ")" << std::endl;
      cell *c = first->next;
      int j=0;
      while (c!=NULL) { 
	std::cout << j++ << "(" << c << ") :" << c->t << std::endl; 
	c = c->next;
      }
    }
    int size() {
      int sz = 0;
      iterator p = begin();
      while (p++!=end()) sz++;
      return sz;
    }
  };
 
}
#endif
