// $Id$

/*
  COMIENZO DE DESCRIPCION

Diversas operaciones con conjuntos:
disjuntos: verifica si una serie de conjuntos son disjuntos entre si. 
cubre_todo: verifica si un dado conjunto W cubre incluye a toda una
     serie de conjuntos Si.
todos_pares: verifica si todos los elementos de un conjunto son pares. 
Keywords: conjunto, lista

  FIN DE DESCRIPCION */

#include <iostream>
#include <list>
#include "../aedsrc/setl.h"
#include "./util.h"

using namespace std;
using namespace aed;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
//
//     AUXILIARES
//
// Hace un vector random insertando N elementos al azar entre 0 y M-1
// Guarda que el conjunto final puede tener menos de N elementos
// ya que varios de los elementos insertados pueden coincidir entre si. 
void make_random_set(set<int> &s,int N,int M) {
  s.clear();
  for (int j=0; j<N; j++) 
    s.insert(irand(M));
}

// Imprime el conjunto
template <class T>
void prints (set <T> & S) {
  typename set <T> :: iterator p ;
  p = S.begin ();
  while (p != S.end ()) cout << *p++ << " ";
  cout << endl;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// Escribir una funcion predicado bool disjuntos(v)
// que verifica si todos los conjuntos dentro del vector
// de conjuntos v[] son disjuntos 
bool disjuntos(vector< set<int> > &v) {
  int n = v.size();
  // Dos lazos anidados que recorren los pares de conjuntos.  para
  // cada par debemos verificar que la interseccion de los dos
  // conjuntos sea vacia.  Por supuesto si no hace falta verificar j,k
  // y k,j ya que el resultado de la interseccion es independiente del
  // orden.  Sobre todo debe evitarse que verifique al conjunto
  // consigo mismo (es decir el caso j=k) ya que en ese caso la
  // interseccion daria no vacia, (a menos que el conjuntos sea nulo).
  for (int j=0; j<n-1; j++) {
    for (int k=j+1; k<n; k++) {
      set<int> tmp;
      set_intersection(v[j],v[k],tmp);
      if (!tmp.empty()) { 
	cout << j << " y " << k << " no son disjuntos!!\n";
	return false;
      }
    }
  }
  return true;
}

// Escribir una funcion predicado cubre_todo(v,W) que verifica
// si todos los conjuntos en el vector de conjuntos v estan
// incluidos en W. 
bool cubre_todo(vector< set<int> > &v,set<int> W) {
  // Primero hacemos la union de todos los conjuntos en
  // v `todo_v' y despues hacemos la diferencia dif = todo_v - W
  // Si esta diferencia es no vacia entonces quiere decir que
  // hay al menos un elemento en los v[j] que no esta en W. 
  int n = v.size();
  set<int> todo_v,tmp,dif;
  for (int j=0; j<n; j++) {
    set_union(v[j],todo_v,tmp);
    todo_v = tmp;
  }
  set_difference(todo_v,W,dif);
  if (!dif.empty()) {
    cout << "elementos no contenidos en W: ";
    prints(dif);
  }
  return dif.empty();
}

int main () {
  // verifica `disjuntos'. Crea un vector de conjuntos aleatorio.  los
  // imprime y verifica si son disjuntos o no. Lo repite varias veces.
  int N = 10;
  vector< set<int> > v(N);
  for (int k=0; k<10; k++) {
    for (int j=0; j<N; j++) {
      make_random_set(v[j],3,1000);
      cout << "S_" << j << ": ";
      prints(v[j]);
    }
    cout << "disjuntos? " << (disjuntos(v) ? "si" : "no") << endl;
  }

  // verifica `cubre_todo'. Crea un vector W insertando 200 enteros
  // entre 0 y 100. (Notar que no necesariamente W contendra a todos
  // los enteros del 0 al 100). Despues genera un vector con 3
  // conjuntos de 3 elementos (o menos) y verifica. Lo repite varias
  // veces.
  set<int> W;
  make_random_set(W,250,100);
  N=3; 
  v.resize(N);
  for (int k=0; k<30; k++) {
    cout << "\n\n\n------------------\n";
    cout << "W: ";
    prints(W);
    for (int j=0; j<N; j++) {
      make_random_set(v[j],3,100);
      cout << "S_" << j << ": ";
      prints(v[j]);
    }
    cout << "W contiene a todos los v[j] ? " << (cubre_todo(v,W) ? "si" : "no") << endl;
  }

} 
