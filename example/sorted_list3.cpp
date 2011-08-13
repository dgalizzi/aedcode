// $Id$
/*
  COMIENZO DE DESCRIPCION

   Escriba procedimientos para insertar, suprimir y buscar    
   un elemento en una lista ordenada {\tt L}. 
   Versi\'on mediante una {\tt clase gen\'erica} 
   (comparar con {\tt sorted_list1.cpp} y {\tt sorted_list2.cpp}). 
   keywords: lista

  FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// GNU  : g++ -w -c util.cpp
//        g++ -w -c sorted_list3.cpp
//        g++ -w -o sorted_list3.exe util.o sorted_list3.o
// INTEL: icc -w -c util.cpp
//        icc -w -c sorted_list3.cpp
//        icc -w -o sorted_list3.exe util.o sorted_list3.o
// -------------------------------------------------------------------
#include <list>
using namespace std ;

// -------------------------------------------------------------------
template<typename T>  // sintaxis para una clase generica:
class sorted_list {   // template <class Tipo> class Nombre { }
private:
  list<T> data;
public:
  typedef typename list<T>::iterator posicion;
  sorted_list () {}
  sorted_list (list<T> & L) : data(L) {this->data.sort();}
  ~sorted_list () { }
  void clear() { this->data.clear(); }
  posicion begin () {return this->data.begin();};
  posicion end () {return this->data.end();}  
  posicion insert (const T &); // no hay posicion pues esta ordenada
  posicion erase (const T &);
  posicion find (const T &);
};

// -----------------------------------------------------------------
// inserta un item "x" en la lista ordenada "L"
template<typename T>
typename sorted_list<T>::posicion sorted_list<T>::insert(const T& x){
  posicion p = begin();
  while ( p != end() && *p < x ) p++; // avanzar
  p = this->data.insert (p,x); // inserta item 'x' en 'p'
  return p;
}

// -----------------------------------------------------------------
// suprime un item "x" en la lista ordenada "L"
template<typename T>
typename sorted_list<T>::posicion sorted_list<T>::erase(const T& x) {
  posicion p = begin();
  while ( p != end() && *p < x ) p++; // avanzar mientras pueda
  if ( p != end() ) {           // si "p" no es final de "L"
    if ( *p == x )              // y como "*p" es igual a "x", borrar
      p = this->data.erase (p); // y refrescar posicion
    else                        // como "x" no esta en posicion "p"
      p++;                      // avanza
  }
  return p;
}

// -----------------------------------------------------------------
// busca posicion "p" de un item "x" en la lista ordenada "L"
template<typename T>
typename sorted_list<T>::posicion sorted_list<T>::find(const T& t) {
  posicion p = begin();
  while ( p!= end() && *p < t ) p++; // avanzar
  if( p != end() && *p == t ) // '*p' esta en 'L', retornar 'p'.
    return p;
  else                        // '*p' no esta en 'L', retornar 'end()'.
    return end();
}

// ------------------------------------------------------------------
// auxiliar para impresion
#include <iostream>
#include <iterator>
template<typename T>
ostream& operator<<(ostream& os, sorted_list<T>& L) {
  os << "( ";
  copy(L.begin(), L.end(), ostream_iterator<T>(os," "));
  os << " )";
  return os;
}

// ------------------------------------------------------------------
// Test
using namespace std ;

int main() {

  int v1[] = {4,2,6,3,7,1,-1}  ;  int const n1 = 6 ;
  int v2[] = {9,0,3,2,7,8,4,-1};  int const n2 = 7 ;
  list<int> L;  
  int x ;

  cout << endl;
  cout << "Tareas simples sobre una lista ordenada S " << endl;

  for (int i=0; i<n1; i++) L.insert(L.end(),v1[i]);
  for (int i=0; i<n2; i++) L.insert(L.end(),v2[i]);

  sorted_list <int> S (L);
  sorted_list <int> :: posicion p ;
 
  cout << "Lista ordenada actual S: "; cout << S << endl;

  for (int i=0; i<n1; i++) S.insert (v1[i]);
  cout << "Lista ordenada actual S: "; cout << S << endl;

  for (int i=0; i<n1; i++) S.erase  (v1[i]);
  cout << "Lista ordenada actual S: "; cout << S << endl;


  x = 6 ;
  cout << endl << "Busca elemento x = " << x << endl;
  p = S.find (x);
  if ( p != S.end () )
    cout << "se lo encontro en la lista ordenada S "   << endl;
  else
    cout << "no se lo encontro en la lista ordenada S" << endl;

  x = 5 ; 
  cout << endl << "Busca elemento x = " << x << endl;
  p = S.find (x);
  if ( p != S.end () )
    cout << "se lo encontro en la lista ordenada S"    << endl;
  else
    cout << "no se lo encontro en la lista ordenada S" << endl;

  S.insert (-758);
  S.insert (136);
  S.erase (0);
  S.insert (5);
  S.erase (3);
  cout << endl ;
  cout << "Lista ordenada actual S: "; cout << S << endl;

  S.clear();
  cout << "Lista despues de un clear S: "; cout << S << endl;

  cout << endl ;
  return 0 ;
}
// ------------------------------------------------------------------

