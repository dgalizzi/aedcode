#include "../src/include/list.h"

TEST_CASE("aed::list", "Probar la lista doblemente enlazada")
{
	using aed::list;
	list<int> L;

	// Inserts
	REQUIRE(L.empty());
	L.insert(L.begin(), 1);
	REQUIRE(*L.begin() == 1);
	list<int>::iterator it1 = L.begin();
	it1 = L.insert(it1, 2);
	REQUIRE(L.begin() == it1);
	REQUIRE(*it1++ == 2);
	REQUIRE(*it1++ == 1);
	REQUIRE(it1 == L.end());
	list<int>::iterator it2 = L.insert(it1, 3);
	REQUIRE(it1 == L.end());
	REQUIRE(*it2++ == 3);
	REQUIRE(it2 == it1);
	REQUIRE(it2 == L.end());
	REQUIRE(it1 == L.end());
	it1 = L.begin();
	REQUIRE(*L.begin() == 2);
	REQUIRE(*it1++ == 2);
	REQUIRE(*it1++ == 1);
	REQUIRE(*it1++ == 3);
	REQUIRE(it1 == L.end());
}
