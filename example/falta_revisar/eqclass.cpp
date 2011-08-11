// $Id$

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__

   Dado un conjunto #S# y una relacion de orden 
   #bool comp(int x,int y)# separar #S#, segun 
   sus clases de equivalencia en una lista #list<set<int>> L#. 
   Signatura: 
   #void eqclass(set<int> &S, bool (*)(int x,int y),list<set<int>> &L)#

   [Tomado en el 3er parcial 2008-11-20].  
   keywords: conjunto

   FIN DE DESCRIPCION */

#include <time.h>
#include <sys/time.h>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>
#include "./util.h"

using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Utilidad que imprime el conjunto
void print_set(set<int> &s,const char *lab=NULL) {
  set<int>::iterator q = s.begin();
  if (lab) printf("%s: ",lab);
  while (q != s.end()) 
    printf("%d ",*q++);
  printf("\n");
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Toma un elemento '*q' de S y lo va insertando en la
// clase (o sea el conjunto) correspondiente de
// L. El algoritmo para
void eqclass(set<int> &S, bool (*comp)(int x,int y),
             list<set<int> > &L) {
  L.clear(); 
  set<int>::iterator q = S.begin();
  while (q != S.end()) {
    list<set<int> >::iterator r = L.begin();
    int xr;
    while (r!=L.end()) {
      // `xr' es un elemento cualquiera de el conjunto `*r'
      xr = *(*r).begin();
      // Se detiene cuando *q <= xr
      // (Similar al algoritmo `lower_bound')
      if (!comp(xr,*q)) break;
      r++;
    }
    // En esta posicion esta o deberia estar
    // la clase de equivalencia (o sea el conjunto)
    // correspondiente a `*q'
    if (r==L.end() || comp(*q,xr)) {
      // No esta la clase equivalente a '*q', insertamos
      // un conjunto vacio
      r = L.insert(r,set<int>());
    }
    // Inserta el elemento
    r->insert(*q);
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
typedef bool (*less_fun_t)(int x,int y);
less_fun_t less_fun;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// `Adapta' una funcion de comparacion para enteros
// a una para conjuntos de enteros. Esto es necesario
// para la version `eqclass3()'. 
bool less_for_sets(set<int> x,set<int> y) {
  // Verifica que los conjuntos no deberian estar vacios
  assert(!x.empty());
  assert(!y.empty());
  // Compara cualquiera elemento de `x' con cualquiera de `y'
  // (Total, como son clases de equivalencia deberian ser todos
  // equivalentes entre si). 
  return less_fun(*x.begin(),*y.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Toma un elemento '*q' de S y lo va comparando con las
// clases ya guardadas en `L', si no lo encuentra lo guarda
// al final, en una nueva clase.  Lo bueno de esta version
// es que no hay que andar buscando donde insertar,
// simplemente lo inserta al final. Lo malo es que entonces
// las clases quedan en principio desordenadas pero despues
// se pueden ordenar usando el `sort()', pero OJO es un sort
// de una lista de conjuntos de enteros.
void eqclass2(set<int> &S, bool (*comp)(int x,int y),
              list<set<int> > &L) {
  L.clear(); 
  set<int>::iterator q = S.begin();
  while (q != S.end()) {
    list<set<int> >::iterator r = L.begin();
    int xr;
    while (r!=L.end()) {
      // `xr' es un elemento cualquiera de el conjunto `*r'
      xr = *(*r).begin();
      // Se detiene cuando *q <= xr
      // (Similar al algoritmo `lower_bound')
      if (!comp(xr,*q) && !comp(*q,xr)) break;
      r++;
    }
    // O bien `r' esta apuntando a la clase de equivalencia
    // de `*q' o bien estamos al final de la lista.
    if (r==L.end()) {
      // No esta la clase equivalente a '*q', insertamos
      // un conjunto vacio
      r = L.insert(r,set<int>());
    }
    // Inserta el elemento
    r->insert(*q);
    q++;
  }

  // Bueno, ahora lo unico que falta es ordenar las clases
  // de equivalencia. Para eso podemos usar `sort', pero OJO
  // en este caso cada elemento de la lista es un conjunto de
  // manera que tenemos que construir un predicado ad-hoc.
  // Un punto debil es que tenemos que pasar la funcion
  // a `less_for_sets' por un puntero global. No se como
  // hacerlo de otra forma. 
  less_fun = comp;
  L.sort(less_for_sets);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// En esta version ponemos todos los elementos de
// de `S' en un vector, lo ordenamos y despues
// vamos leyendo las clases de equivalencia del vector
// (deberian quedar ordenadas). 
void eqclass3(set<int> &S, bool (*comp)(int x,int y),
              list<set<int> > &L) {
  L.clear(); 
  vector<int> v;
  set<int>::iterator q = S.begin();
  while (q!=S.end()) v.push_back(*q++);

  sort(v.begin(),v.end(),comp);
  int j=0, k;
  while (j<v.size()) {
    // Busca la clase de equivalencia del siguiente elemento
    // `j'.  Como lo acabamos de ordenar estan todos juntos,
    // en el intervalo [j,k)
    list<set<int> >::iterator q = L.insert(L.end(),set<int>());
    k = j;
    while (!comp(v[j],v[k]) && !comp(v[k],v[j])) {
      q->insert(v[k]);
      k++;
    }
    j = k;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool less_abs(int x,int y) {
  // Menor en valor absoluto
  return abs(x) < abs(y);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int modulo(int n,int m) {
  int k = n % m;
  if (k<0) k += m;
  return k;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool less_mod(int x,int y) {
  // Compara por modulo 10, o sea que las
  // clases de equivalencia son
  // {pares}, {impares}
  return modulo(x,2) < modulo(y,2);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Funcion utilitaria que imprime todos los
// conjuntos de `L' uno por linea
void print_set_list(list< set<int> > &L) {
  list< set<int> >::iterator q = L.begin();
  while(q != L.end()) {
    print_set(*q);
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// El tipo de funciones que separa un conjunto por clases de
// equivalencia. Esto nos permite escribir despues una funcion
// que `prueba' cada uno de los algoritmos. 
typedef void eqclass_fun_t(set<int> &S, bool (*comp)(int x,int y),
                           list<set<int> > &L);

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Prueba uno de los algoritmos
void test_eqclass_fun(eqclass_fun_t eqclass_fun) {
  
  set<int> S;

  // Inserta los enteros en [-4,4]
  for (int j=-4; j<=4; j++)
    S.insert(j);
  list< set<int> > L;

  printf("clases de equivalencia para less_abs()\n");
  // Las clases de equivalencia deberian ser
  // {0} y los pares {-x,x} con x>0. 
  eqclass_fun(S, less_abs, L);
  print_set_list(L);
  
  printf("clases de equivalencia para less_mod()\n");
  // Las clases de equivalencia deberian ser
  // {pares}, {impares}
  eqclass_fun(S, less_mod, L);
  print_set_list(L);
  
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  // Prueba cada uno de los algoritmos 
  printf("------ Con EQCLASS ------\n");
  test_eqclass_fun(eqclass);
  printf("------ Con EQCLASS2 ------\n");
  test_eqclass_fun(eqclass2);
  printf("------ Con EQCLASS3 ------\n");
  test_eqclass_fun(eqclass3);
}
