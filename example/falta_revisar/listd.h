// -*- c++ -*-

#ifndef AED_LIST_H
#define AED_LIST_H

/* COMIENZO DE DESCRIPCION
   
   Clase de listas doblemente enlazadas con punteros. 
   keywords: lista

   FIN DE DESCRIPCION */

namespace aed {

  template<typename T>
  class list {

  private:

    struct cell {
      T     data;
      cell* prev;
      cell* next;
      cell() 
	: data(), prev(0), next(0) { }
      cell(const cell& c) 
	: data(c.data), prev(c.prev), next(c.next) { }
      cell(const T& t, cell* p=0, cell* n=0)
	: data(t), prev(p), next(n) { }
    }; // !struct cell
  
  public:

    class iterator {
      friend class list;
    private:
      cell* ptr;
      iterator(cell* c) : ptr(c) { }
    public:
      iterator() : ptr(0) { }
      iterator(const iterator& p) : ptr(p.ptr)  { }
      bool operator==(const iterator& p) { return ptr == p.ptr; }
      bool operator!=(const iterator& p) { return ptr != p.ptr; }
      T& operator*()  { return  ptr->data; }
      T* operator->() { return &ptr->data; }
      iterator& operator++() { // prefix
	ptr = ptr->next; 
	return *this;
      }
      iterator operator++(int) { // postfix
	iterator tmp(ptr);
	ptr = ptr->next; 
	return tmp;
      }
    }; // !class iterator

  private:

    cell header;

  public:

    list()  { header.prev = header.next = &header; }
    ~list() { clear(); }

    iterator begin() { return iterator(header.next); }
    iterator end()   { return iterator(&header); }
    bool     empty() { return begin() == end(); }
    void     clear() { erase(begin(), end()); }

    iterator insert(iterator q, const T& t) {
      cell* p = q.ptr->prev; // prev cell
      cell* n = q.ptr;       // next cell
      // allocate new cell
      cell* c = new cell(t,p,n);
      // update prev and next cell
      p->next = n->prev = c;
      // return iterator
      return iterator(c);
    }

    iterator erase(iterator q) {
      cell* p = q.ptr->prev; // prev cell
      cell* n = q.ptr->next; // next cell
      // deallocate old cell
      delete q.ptr;
      // update prev and next cell
      p->next = n; n->prev = p;
      // return iterator
      return iterator(n);
    }

    iterator erase(iterator q, iterator r) {
      cell* p = q.ptr->prev; // prev cell
      cell* n = r.ptr;	     // next cell
      // deallocate old cells in range
      cell* s = q.ptr;
      cell* e = r.ptr;
      while (s != e) { 
	cell* c = s->next; 
	delete s;
	s = c; 
      }
      // update prev and next cell
      p->next = n; n->prev = p;
      // return iterator
      return r;
    }

  }; // !class list
 
} // !namespace aed

#endif // !AED_LIST_H
