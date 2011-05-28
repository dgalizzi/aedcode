#ifndef AED_QUEUE_H
#define AED_QUEUE_H

#include <aedsrc/list.h>

namespace aed {

template<class T>
class queue : private list<T> {

private:
	int size_m;
public:
	queue() : size_m(0) { }
	void clear() { erase(begin(),end()); size_m = 0; }
	T front() { return *begin(); }
	void pop() { erase(begin()); size_m--; }
	void push(T x) { insert(end(),x); size_m++; }
	int size() { return size_m; }
	bool empty() { return size_m==0; }
};

}
#endif
