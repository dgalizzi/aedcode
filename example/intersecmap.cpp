// $Id$

/* 
   COMIENZO DE DESCRIPCION 
   
   Implemente una funci\'on
   {\tt void intersect_map(map< string,list<int> > \&A,}
   {\tt map< string, list<int> > \&B,map< string, list<int> > \&C)}
   que a partir de los diccionarios {\tt A} y {\tt B} construye un 
   diccionario {\tt C} de manera que las claves de {\tt C} son la
   interseccion de las claves de {\tt A} y {\tt B} y para cada clave {\tt k} en
   {\tt C} la imagen {\tt C[k]} es la interseccion de los valores en 
   {\tt A[k]} y {\tt B[k]}. 
   [Tomado en Primer Parcial 17-SET-2009].
   keywords: correspondencia, lista
   
   FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <string>
#include <list>
#include <map>
#include "./util.h"

using namespace std ;
typedef map< string,list<int> > map_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Funcion auxiliar, determina si el elemento `x' esta
// contenido en la lista `L'
bool contains(list<int>&L, int x) {
  list<int>::iterator q = L.begin();
  while (q!=L.end()) {
    if (x==*q) return true;
    q++;
  }
  return false;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void intersect_map(map_t &A, map_t &B, map_t &C) {
  map_t::iterator qa = A.begin(), qb;
  // Busca claves que esten en ambos maps
  while (qa!=A.end()) {
    qb = B.find(qa->first);
    if (qb!=B.end()) {
      // Las claves qa->first y qb->first son las mismas. 
      // la, lb son las listas correspondientes.
      // lc es la lista que deberia ser la interseccion
      // en el sentido de conjuntos de la y lc.
      // Notar que la linea abajo inserta la asignaciona
      // para qa->first en C y al mismo tiemo obtiene una referencia
      // al valor (lc)
      list<int> 
        &la = qa->second,
        &lb = qb->second,
        &lc = C[qa->first];
      // Carga la interseccion de `la' y `lb' en `lc'
      list<int>::iterator qla = la.begin();
      while (qla!=la.end()) {
        // Debe chequear que el elemento de `la' este en
        // `lb', pero que no este ya en `lc' ya que `lc'
        // es un conjunto. Es decir no debe tener elementos
        // repetidos. 
        if (!contains(lc,*qla) && contains(lb,*qla))
          lc.insert(lc.end(),*qla);
        qla++;
      }
    }
    qa++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void print_map(map_t &M,const char *s=NULL) {
  // Funcion auxiliar que imprime el map
  map_t::iterator q = M.begin();
  if (s) printf("%s:\n",s);
  while (q!=M.end()) {
    printf("'%s' -> [",q->first.c_str());
    list<int> &L = q->second;
    list<int>::iterator p = L.begin();
    while (p!=L.end()) printf("%d,",*p++);
    printf("]\n");
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  map_t A,B,C;

  // Carga el ejemplo en el texto del parcial
  // YY es la unica clave repetida y que por lo tanto
  // debe quedar. 
  add_to_list(A["XX"],-1,3,3,1,2,2,7,-1);
  add_to_list(A["YY"],-1,7,1,5,5,4,1,-1);
  print_map(A,"A");

  add_to_list(B["YY"],-1,3,3,4,5,8,1,-1);
  add_to_list(B["ZZ"],-1,1,1,9,-1);
  print_map(B,"B");

  intersect_map(A,B,C);
  print_map(C,"C = A \\cup B");
  return 0;
}
