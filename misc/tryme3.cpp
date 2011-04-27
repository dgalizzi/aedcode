#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

void set_print(set<int> &c) {
  set<int>::iterator q;
  for (q=c.begin(); q!=c.end(); q++) cout << *q << " ";
  cout <<endl;
}

int main() {
  set<int> a,b,c;
  a.insert(1);
  a.insert(2);
  a.insert(3);

  b.insert(3);
  b.insert(4);
  b.insert(5);

  cout << "a: " << endl;
  set_print(a);

  cout << "b: " << endl;
  set_print(b);

  c.clear();
  set_union(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()));
  cout << "union(a,b)" << endl;
  set_print(c);

  c.clear();
  set_intersection(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()));
  cout << "intersection(a,b): " << endl;
  set_print(c);

  c.clear();
  set_difference(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()));
  cout << "a-b" << endl;
  set_print(c);

  c.clear();
  set_difference(b.begin(),b.end(),a.begin(),a.end(),inserter(c,c.begin()));
  cout << "b-a" << endl;
  set_print(c);

}
