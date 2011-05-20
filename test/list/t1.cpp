#include "../../src/include/list.h"
#include <cassert>
#include <iostream>
//using aed::list;
#include <list>
using std::list;
using std::cout;
using std::endl;


int main()
{
	list<int> l;
	l.insert(l.end(), 1);
	l.insert(l.end(), 0);
	l.insert(l.end(), 5);
	l.insert(l.begin(), 6);

	list<int>::iterator it = l.begin();
	assert(*it++ == 6);
	assert(*it++ == 1);
	assert(*it++ == 0);
	list<int>::iterator it2 = l.insert(it, 2);
	//l.printd();
	cout << *it << " :: " << *it2 << endl;
	assert(*it2++ == 2);
	cout << *it << " :: " << *it2 << endl;
	assert(it2 == it);
	assert(*it++ == 5);
	assert(it == l.end());

	assert(l.size() ==  5);
	l.clear();
	assert(l.size() == 0);

	cout << "list pasó la prueba\n";

	return 0;
}
