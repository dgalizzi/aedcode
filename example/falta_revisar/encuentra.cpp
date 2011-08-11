// $Id$
/*
  COMIENZO DE DESCRIPCION

  Verifica si los elementos de `L2' estan en `L1' (en el mismo orden,
  pero no necesariamente en forma consecutiva). Si es asi, retorna
  true y en `indx' retorna los indices de los elementos de `L1' que
  corresponden a los elementos de `L2'. 
  keywords: lista

  FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// GNU:   g++ -w -c encuentra.cpp
//        g++ -w -o encuentra.exe encuentra.o
// INTEL: icc -v -w -c encuentra.cpp
//        icc -v -w -o encuentra.exe encuentra.o
// -----------------------------------------------------------------
#include <iostream>
#include <list>
#include "./util.h"
using namespace std ;

// -----------------------------------------------------------------
bool encuentra(list<int> &L1, list<int> &L2, list<int> &indx) {
  indx.clear();
  list<int>::iterator 
  p1=L1.begin(),
  p2=L2.begin();
  int j=0;
  while (p1!=L1.end() && p2!=L2.end()) {
    if (*p2 == *p1) { p2++; indx.push_back(j); }
    p1++; j++;
  } // end while
  if (p2==L2.end()) return true;
  else {indx.clear(); return false;}
}

//--------------------------------------------------------------------
int main() {
  // Este es el ejemplo del final
  list <int> L1,L2,indx;
  int v [] = {13,9,8,12,9,6,12,2,9,14,18,10,-1};
  insertl (L1,v,-1);
  int v2 [] = {13,9,9,6,2,14,-1};
  insertl (L2,v2,-1);

  bool f = encuentra(L1,L2,indx);
  if (f) printl(indx);
  else cout << "L1 no contiene a L2!!!!\n";

  // Aplica a listas aleatorias
  for (int j=0; j<100; j++) {
    // genera listas aleatorias de longitud media 20 (L1)
    // y 3 (L2)
    L1.clear();
    randl(L1,10,20.0);
    L2.clear();
    randl(L2,10,3.0);
    // verifica si `L2' esta contenido en `L1'. 
    cout << "------------------" << endl;
    cout << "L1: " << endl;
    printl(L1);
    cout << "L2: " << endl;
    printl(L2);
    bool f = encuentra(L1,L2,indx);
    if (f) printl(indx);
    else cout << "L1 no contiene a L2!!!!\n";
  }
  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
