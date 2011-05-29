// Lista doblemente enlazada
namespace aed {

template <class T>
class list {
public:
	class iterator;
private:
	class cell {
		friend class list;
		friend class iterator;
		T t;
		cell *prev, *next;
		cell() : prev(NULL), next(NULL) { }
		cell(cell *_prev, cell *_next, T _t) : prev(_prev), next(_next), t(_t) { }
	};
	cell *head, *tail;

public:
	class iterator {
	private:
		friend class list;
		cell* ptr;
	public:
		T & operator*() { return ptr->t; }
		T *operator->() { return &ptr->t; }
		bool operator!=(iterator q) { return ptr!=q.ptr; }
		bool operator==(iterator q) { return ptr==q.ptr; }
		iterator(cell *p=NULL) : ptr(p) {}

		// Prefix:
		iterator operator++() {
			assert(ptr != NULL);
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

		// Prefix:
		iterator operator--() {
			assert(ptr != NULL);
			ptr = ptr->prev;
			return *this;
		}

		// Postfix:
		iterator operator--(int) {
			assert(ptr != NULL);
			iterator q = *this;
			ptr = ptr->prev;
			return q;
		}
	};

	list() {
		tail = new cell(); // placeholder
		head = tail;
	}
	iterator begin() { return iterator(head); }
	iterator end()   { return iterator(tail); }
	bool empty() { return begin() == end(); }

	iterator insert(iterator p, T data) {
		cell *c;
		if (empty()) {
			c = new cell(NULL, tail, data);
			tail->prev = c;
			head = c;
		} else {
			c = new cell(p.ptr->prev, p.ptr, data);

			if (c->prev == NULL)  head = c;
			else c->prev->next = c;

			c->next->prev = c;
			p.ptr->prev = c;
		}
		return iterator(c);
	}

	// TODO: erase(p), erase(p, q), clear(), destructor
};

}
