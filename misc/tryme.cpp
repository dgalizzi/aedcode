//__INSERT_LICENSE__
// $Id: tryme.cpp,v 1.3 2003/12/24 11:09:48 mstorti Exp $

#include <aedsrc/list.h>
#include <aedsrc/list2.h>
#include <iostream>

using namespace aed;

int main() {
  list<int> l;
  cout << "Antes de llenar\n"; l.print();
  for (int j=0; j<5; j++) l.insert(j,l.begin());
  cout << "Despue de llenar\n"; l.print();
  l.printd();
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  l.printd();
  l.print();
#if 0
  cout << "Borra \n"; l.print();
  l.clear();
  cout << "Despue de vaciar\n"; l.print();
#endif
}
