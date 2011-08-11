// $Id$

/* COMIENZO DE DESCRIPCION 

*/
// -----------------------------------------------------------------
#include <iostream>
#include <stack>
#include <cmath>
#include "./util.h"

using namespace std ;

// Reordena los elementos de P de manera que los
// que satisfacen el predicado `pred' quedan arriba
// y los que no abajo. 
template<class T> 
void reordena(stack<T> &P, bool (*pred)(T)) {
  stack<T> P_ok, P_not_ok;
  while (!P.empty()) {
    T t = P.top();
    if (pred(t)) P_ok.push(t);
    else P_not_ok.push(t);
    P.pop();
  }
  while (!P_not_ok.empty()) {
    P.push(P_not_ok.top());
    P_not_ok.pop();
  }
  while (!P_ok.empty()) {
    P.push(P_ok.top());
    P_ok.pop();
  }
}

// Ejemplos de predicados: 

bool par(int x) { return x % 2 == 0; }

bool es_primo(int x) { 
  int max = int(sqrt(double(x)));
  for (int j=2; j<=max; j++) {
    if (x % j == 0) return false;
  }
  return true;
}

bool es_cuadrado_perfecto(int x) { 
  int q = int(sqrt(double(x)));
  return x == q*q;
}

//--------------------------------------------------------------------
int main() {
  list<int> L;
  stack<int> P,Q;
  for (int j=0; j<100; j++) {
    // genera listas aleatorias y las copia en `P'
    L.clear();
    randl(L,10,20.0);
    list<int>::iterator q = L.begin();
    while (!P.empty()) P.pop();
    while (q!=L.end()) {
      P.push(*q);
      q = L.erase(q);
    }
    cout << "=====================\n";
    print(P);

    // va copiando `P' en una pila temporaria `Q'
    // y aplica `reordena' con cada uno de los predicados. 
    Q = P;
    reordena(Q,par);
    cout << "Arriba los pares: \n";
    print(Q);

    Q = P;
    reordena(Q,es_primo);
    cout << "Arriba los primos: \n";
    print(Q);

    Q = P;
    reordena(Q,es_cuadrado_perfecto);
    cout << "Arriba los cuadrados perfectos: \n";
    print(Q);
  }
}
