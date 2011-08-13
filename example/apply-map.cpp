// $Id$

/* COMIENZO DE DESCRIPCION 

   Escribir una funci\'on
   {\tt void apply_map(list<int> \&L, map<int,int> \&M, list<int> \&ML)} que,
   dada una lista {\tt L} y una correspondencia {\tt M} retorna por
   {\tt ML} una lista con los resultados de aplicar {\tt M} a los
   elementos de {\tt L}. Si alg\'un elemento de {\tt L} no esta en el dominio
   de {\tt M}, entonces el elemento correspondiente de {\tt ML} no es
   incluido. Por ejemplo, si
   {\tt L = (1,2,3,4,5,6,7,1,2,3)} y
   {\tt M= {(1,2),(2,3),(3,4),(4,5),(7,8)}},
   entonces, despu\'es de hacer {\tt apply_map(L,M,ML)}, debe quedar
   {\tt ML = {(2,3,4,5,8,2,3,4)}}.

   Restricciones: No usar estructuras auxiliares. El tiempo de
   ejecucion del algoritmo debe ser O(n), donde {\tt n} es el numero de
   elementos en la lista, asumiendo que las operaciones usadaas de
   correspondencia son O(1). 

   [Tomado en el 1er parcial del 20/4/2006].
   keywords: lista, correspondencia

   FIN DE DESCRIPCION */
#include <iostream>
#include <map>
#include <list>
#include "./util.h"

using namespace std ;


//--------------------------------------------------------------------
void apply_map(list<int> &L, 
	       map<int,int> &M, 
	       list<int> &ML) {
  ML.clear();
  list<int>::iterator q = L.begin();
  while (q!=L.end()) {
    if (M.find(*q)!=M.end()) {
      ML.insert(ML.end(),M[*q]);
    }
    q++;
  }
}

//--------------------------------------------------------------------
int main() {
  int vl[] = {1,2,3,4,5,6,7,1,2,3,-1};
  list<int> L,ML; 
  insertl(L,vl,-1);
  
  map<int,int> M;
  M[1] = 2;
  M[2] = 3;
  M[3] = 4;
  M[4] = 5;
  M[7] = 8;
  
  apply_map(L,M,ML);
  cout << "ML: ";
  list<int>::iterator q = ML.begin();
  while (q!=ML.end()) cout << " " << *q++;
  cout << endl;
}
// -----------------------------------------------------------------
// 
