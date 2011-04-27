//__INSERT_LICENSE__
// $Id: tryme4.cpp,v 1.2 2005/04/24 05:59:42 mstorti Exp $

#include <aedsrc/list3.h>
#include <iostream>

using namespace aed;
using namespace std;

int main() {
  list<int> l,l2;
  cout << "Antes de llenar\n"; l.print();
  for (int j=0; j<5; j++) l.insert(l.begin(),j);
  cout << "Despue de llenar\n"; l.print();
  l2=l;
  l.printd();
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  l.printd();
  l.print();
  printf("l.size %d\n",l.size());

  l2.print();
  printf("l2.size() %d\n",l2.size());

  list<int> l3(l2);
  l3.print();
  printf("l3.size %d\n",l3.size());

  l2.erase(l2.begin());
  l2.print();
  printf("l2.size() %d\n",l2.size());

}
