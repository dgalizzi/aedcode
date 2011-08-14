// $Id$

/* 
   COMIENZO DE DESCRIPCION 
   
   Escribir las funciones {\tt map2list()}
   y {\tt list2map()} de acuerdo a las siguientes especificaciones. 
   {\tt void map2list(map<int,int> \&M,list<int> \&keys,list<int> \&vals);}
   dado un map {\tt M} retorna las listas de claves y valores. 
   {\tt void list2map(list<int> \&keys,list<int> \&vals,map<int,int> \&M);}
   dadas las listas de claves {\tt (k1,k2,k3...)} y valores {\tt (v1,v2,v3...)}
   retorna el map {\tt M} con las asignaciones correspondientes
   {\tt {(k1,v1),(k2,v2),(k3,v3),...}}.  (Nota: Si hay
   *claves repetidas*, solo debe quedar la asignacion
   correspondiente a la *ultima* clave en la lista. Si hay menos
   valores que claves, utilizar cero como valor. Si hay mas valores
   que claves, ignorarlos).
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

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void map2list(map<int,int> &M,
              list<int> &keys,list<int> &vals) {
  // limpia las listas
  keys.clear();
  vals.clear();
  map<int,int>::iterator q = M.begin();
  while (q!=M.end()) {
    // Para cada asignacion, simplemente carga clave
    // y valor en la lista correspondiente
    keys.push_back(q->first);
    vals.push_back(q->second);
    q++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void list2map(list<int> &keys, list<int> &vals,
              map<int,int> &M) {
  M.clear();
  // `q' y `r' iteran sobre posiciones correspondientes
  // en `keys' y `vals'
  list<int>::iterator q=keys.begin(), r=vals.begin();
  // Carga la asignacion en M. Si hay claves
  // repetidas va a quedar la ultima, que es lo que pide
  // el enunciado. 
  while (q!=keys.end() && r!=vals.end()) M[*q++] = *r++;
  // Si llegamos aca es porque alguna de los dos listas se acabo.
  // Si se acabo `keys' entonces no hay que hacer nada y el
  // lazo siguiente no se ejecuta ninguna vez. Si se acabo `vals'
  // entonces el lazo siguiente asigna a las claves restantes el valor 0
  while (q!=keys.end()) M[*q++] = 0;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Funcion auxiliar que imprime el map
void print_map(map<int,int> &M,const char *s=NULL) {
  if (s) printf("%s: ",s);
#if 0
  map<int,int>::iterator q = M.begin();
  while (q!=M.end()) {
    printf("(%d->%d) ",q->first,q->second);
    q++;
  }
#else
#define iter(cont,q) for(typeof(cont.begin()) q=cont.begin(); q!=cont.end(); q++)
#endif
  iter(M,q) 
    printf("(%d->%d) ",q->first,q->second); 
  printf("\n");
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  list<int> keys,vals,keys2,vals2;
  map<int,int> M,M2;
  // La clave 1 esta repetida y hay un valor de mas.
  // Ademas las claves estan desordenadas. 
  int keysp[] = {4,1,2,1,-1};
  int valsp[] = {2,3,3,5,6,-1};
  insertl(keys,keys.begin(),keysp,-1);
  insertl(vals,vals.begin(),valsp,-1);

  printf("keys: "); printl(keys);
  printf("vals: "); printl(vals);
  list2map(keys,vals,M);
  print_map(M,"M despues de list2map(keys,vals,M)");

  map2list(M,keys2,vals2);
  printf("\nDespues de map2list(M,keys2,vals2)\n");
  printf("keys2: "); printl(keys2);
  printf("vals2: "); printl(vals2);
  printf("keys2==keys? %s\n",(keys2==keys? "si" : "no"));
  printf("vals2==vals? %s\n",(vals2==vals? "si" : "no"));
 
  list2map(keys2,vals2,M2);
  print_map(M2,"\nM2 despues de list2map(keys2,vals2,M2)");
  // Deberia ser M2==M
  printf("M2==M? %s\n",(M2==M? "si" : "no"));

  return 0;
}
