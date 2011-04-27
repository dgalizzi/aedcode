//PP>if 0
// -*- mode: c++ -*-
// $Id: list3.h,v 1.3 2005/04/24 13:56:54 mstorti Exp $
//PP>endif
#ifndef AED_LIST_H 
#define AED_LIST_H

#include <cstddef>  

namespace aed {   //L-p1

  template<class T>
  class list {
  public:
    class iterator;
  private:
    int size_m;
    class cell {
      friend class list;
      friend class iterator;
      T t;
      cell *next;
      cell() : next(NULL) {}
    };
    cell *first, *last;
    void copy(list<T> &L) {
      clear();
      iterator q = L.begin();
      while (q!=L.end())
	insert(end(),*q++);
    }
  public:     //L-p2
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

    list() { //L-p3
      size_m = 0;
      first = new cell;
      last = first;
    }
    list(list<T>&L) {       
      size_m = 0;
      first = new cell;
      last = first;
      copy(L); 
    }
    list<T> &operator=(list<T>&L) { 
      copy(L); 
      return *this; 
    }
    int size() { return size_m; }
    iterator insert(iterator p,T t) {
      cell *q = p.ptr->next;
      cell *c = new cell;
      p.ptr->next = c;
      c->next = q;
      c->t = t;
      if (q==NULL) last = c;
      size_m++;
      return p;
    }
    iterator erase(iterator p) {   //L-p4
      cell *q = p.ptr->next;
      if (q==last) last = p.ptr;
      p.ptr->next = q->next;
      delete q;
      size_m--;
      return p;
    }
    iterator erase(iterator p,iterator q) {
      cell *s, *r = p.ptr->next;
      p.ptr->next = q.ptr->next;
      if (!p.ptr->next) last = p.ptr;
      while (r!=q.ptr->next) {
	s = r->next;
	delete r;
	size_m--;
	r = s;
      }
      return p;
    }
    void clear() { erase(begin(),end()); }  //L-p5
    iterator begin() { return iterator(first); }
    iterator end() { return iterator(last); }
    void print() {   
      iterator p = begin();
      while (p!=end()) cout << *p++ << " ";
      cout << endl;
    }
    void printd() {                         //L-p6
      cout << "h(" << first << ")" << endl;
      cell *c = first->next;
      int j=0;
      while (c!=NULL) { 
	cout << j++ << "(" << c << ") :" << c->t << endl; 
	c = c->next;
      }
    }
  };
 
}
#endif
