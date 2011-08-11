//$Id$
/*
  COMIENZO DE DESCRIPCION

Keywords: correspondencia

  FIN DE DESCRIPCION */

#include <map>
#include <iostream>
#include <aedsrc/util.h>

using namespace std;

void print (map<int,int> &M) {
  map<int,int>::iterator q = M.begin();
  while (q!=M.end()) {
    cout << q->first << " -> " << q->second << endl;
    q++;
  }
}

int main () {
  map<int,int> M;
  int N = 100;
  int m = 50;
  for (int j=0; j<N; j++) {
    int j = irand(m);
    int k = j+1+irand(5);
    M[j] = k;
  }

  cout << "antes de compactar: ";
  print(M);

  map<int,int>::iterator q = M.begin();
  while (q!=M.end()) {
    int v = q->first;
    int w = q->second;
    while (true) {
      map<int,int>::iterator r = M.find(w);
      if (r==M.end()) break;
      w = r->second;
    }
    M[v] = w;
    q++;
  }

  cout << "despues de compactar: ";
  print(M);
} 
