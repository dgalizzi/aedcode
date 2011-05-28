#ifndef AED_FORWARD_LIST_H 
#define AED_FORWARD_LIST_H

#include <cstddef>
#include <assert.h>
#include <iostream>

namespace aed {

template<class T>
class forward_list {
public:
	class iterator;
private:
	class cell {
		friend class forward_list;
		friend class iterator;
		T t;
		cell *next;
		cell() : next(NULL) {}
	};
	cell *first;
public:
	class iterator {
	private:
		friend class forward_list;
		cell* ptr;
	public:
		T & operator*() { return ptr->t; }
		T *operator->() { return &ptr->t; }
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
			assert(ptr != NULL);
			iterator q = *this;
			ptr = ptr->next;
			return q;
		}
	}; // End class iterator

	forward_list() {
		first = new cell();
	}
	iterator insert_after(iterator p,T t) {
		cell *q = p.ptr->next;
		cell *c = new cell;
		p.ptr->next = c;
		c->next = q;
		c->t = t;
		return iterator(c);
	}
	iterator erase_after(iterator p) {
		assert(p.ptr->next != NULL);
		cell *q = p.ptr->next;
		p.ptr->next = q->next;
		delete q;
		return p;
	}
	iterator erase_after(iterator p,iterator q) {
		assert(p.ptr->next != NULL);
		cell *s, *r = p.ptr->next;
		p.ptr->next = q.ptr;
		while (r!=q.ptr) {
			s = r->next;
			delete r;
			r = s;
		}
		return q;
	}
	void clear() { erase_after(before_begin(),end()); }
	iterator begin() { return iterator(first->next) ; }
	iterator before_begin() { return iterator(first); }
	iterator end() { return iterator(); }
	bool empty() { return begin() == end(); }

	// Métodos no estándar
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

	// Obtener la longitud de la lista. O(n).
	int size() {
		int sz = 0;
		iterator p = begin();
		while (p != end())
		{
			sz ++;
			++p;
		}
		return sz;
	}
};

}
#endif
