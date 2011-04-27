//__INSERT_LICENSE__
// $Id: tryme2.cpp,v 1.2 2003/12/24 18:39:25 mstorti Exp $

#include <aedsrc/listp.h>
#include <iostream>
#include <cmath>

using namespace std;
using namespace aed;

typedef list_int_iterator list_iterator;
typedef list_int list;

double drand() { return double(rand())/double(RAND_MAX); }

int main() {
  list l;
#if 0
  cout << "Antes de llenar\n"; l.print();
  for (int j=0; j<5; j++) l.insert(j,l.begin());
  cout << "Despues de llenar\n"; l.print();
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  l.print();
  cout << "Borra \n"; l.print();
  l.clear();
  cout << "Despue de vaciar\n"; l.print();
#endif

  // Numero de operaciones extracciones
  int nops = 100;
  // Las fluctuaciones en la posicion estan entre 
  // -DP y DP
  int DP = 10;
  // Los elementos en la lista estan entre 0 y N-1
  int N=100;
  list_iterator p = l.begin();
  for (int j=0; j<nops; j++) {
    int dpos = int(ceil((2*drand()-1)*double(DP)));
    if (dpos>0) {
      for (int k=0; k<dpos; k++) 
	if (p!=l.end()) p = l.next(p);
    } else {
      for (int k=0; k<-dpos; k++) 
	if (p!=l.begin()) p = l.prev(p);
    }
    cout << "avanza " << dpos;
    if (drand()>0.5) {
      int x = int(floor(N*drand()));
      cout << ", inserta " << x << endl;
      l.insert(x,p);
    } else {
      if (p!=l.end()) {
	cout << ", elimina elemento " << l.retrieve(p) <<endl;
	l.erase(p);
      }
    }
    l.print();
  }
}
