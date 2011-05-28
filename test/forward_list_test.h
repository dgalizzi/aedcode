//#include <forward_list>
//using std::forward_list;

#include "../src/include/forward_list.h"
using aed::forward_list;

#include "list.h"

TEST_CASE("Forward list", "Probar la forward list")
{
	// Llenar la lista y pruebas varias
	// (insert_after, before_begin, begin, end)
	forward_list<int> fl;
	REQUIRE(fl.begin() == fl.end());
	fl.insert_after(fl.before_begin(), 1);
	fl.insert_after(fl.before_begin(), 2);
	REQUIRE(*fl.begin() == 2);

	forward_list<int>::iterator it1 = fl.insert_after(fl.before_begin(), 3);
	fl.insert_after(it1, 4);
	REQUIRE(*it1 == 3);
	it1 ++;
	REQUIRE(*it1 == 4);
	REQUIRE(fl.end() != fl.begin());
	it1 ++;
	REQUIRE(it1 != fl.end());

	// postfix
	it1 = fl.begin();
	REQUIRE(*it1++ == 3)
	REQUIRE(*it1++ == 4)
	REQUIRE(*it1++ == 2)
	REQUIRE(*it1++ == 1)
	REQUIRE(it1 == fl.end())

	// erase_after(iterator, iterator)
	it1 = fl.begin();
	forward_list<int>::iterator it2 = it1;
	++ it2;
	++ it2;
	++ it2;
	REQUIRE(*it1 == 3);
	REQUIRE(*it2 == 1);
	fl.erase_after(it1, it2);
	REQUIRE(*it1++ == 3);
	REQUIRE(*it1++ == 1);
	REQUIRE(it1 == fl.end());

	fl.clear();
	REQUIRE(fl.empty());

	// insert_after y erase_after returns
	it1 = fl.insert_after(fl.before_begin(), 1);
	REQUIRE(*it1 == 1);
	it1 = fl.insert_after(fl.before_begin(), 2);
	REQUIRE(*it1 == 2);
	it2 = fl.insert_after(fl.before_begin(), 3);
	REQUIRE(*it1 == 2);
	REQUIRE(*it2 == 3);
}
