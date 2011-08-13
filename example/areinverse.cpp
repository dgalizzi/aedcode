// $Id$

/* 
   COMIENZO DE DESCRIPCION 
   
   Dos corresponencias {\tt M1} y {\tt M2} son inversas una 
   de la otra si tienen el mismo numero de asignaciones y 
   para cada par de asignacion {\tt x->y} en {\tt M1} existe 
   el par {\tt y->x} en {\tt M2}. Escribir una funcion predicado
   {\tt bool areinverse(map<int,int> \&M1,map<int,int> \&M2);} que
   determina si las correspondencias {\tt M1}, {\tt M2} son una la 
   inversa de la otra o no. 
   [Tomado en Primer Parcial 17-SET-2009].
   keywords: correspondencia, lista
   
   FIN DE DESCRIPCION */

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std ;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool areinverse(map<int,int> &M1,map<int,int> &M2) {
  // Tienen que tener la misma cantidad de asignaciones
  if (M1.size()!=M2.size()) return false;
  map<int,int>::iterator q1 = M1.begin(),q2;
  while (q1!=M1.end()) {
    int x = q1->first,
      y = q1->second;
    // verificar que `y' tiene un valor asignado
    // y que es `x'
    q2 = M2.find(y);
    if (q2==M2.end() || q2->second!=x) return false;
    q1++;
  }
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void print_map(map<int,int> &M) {
  // Funcion auxiliar que imprime el map
  map<int,int>::iterator q = M.begin();
  while (q!=M.end()) {
    printf("(%d -> %d) ",q->first,q->second);
    q++;
  }
  printf("\n");
}

//--------------------------------------------------------------------
int main() {
  map<int,int> M1,M2;
  int N=10;

  // Deberia retornar `true'
  M1.clear();
  M2.clear();
  for (int j=0; j<N; j++) {
    int x = j, y = (j+3)%N;
    M1[x] = y;
    M2[y] = x;
  }
  printf("M1: \n");
  print_map(M1);
  printf("M2: \n");
  print_map(M2);
  printf("are inverses ? %d\n",areinverse(M1,M2));

  // Deberia retornar `false' porque 
  // elige un k al azar y le cambia la asignacion
  // (le asigna cualquier cosa (-5))
  int k = rand()%N;
  M1[k] = -5;
  printf("M1: \n");
  print_map(M1);
  printf("M2: \n");
  print_map(M2);
  printf("are inverses ? %d\n",areinverse(M1,M2));

  // Deberia retornar `false' porque la imagen
  // no tiene el mismo tamano
  M1.clear();
  M2.clear();
  for (int j=0; j<N; j++) {
    int x = j-N/2, y = x*x;
    M1[x] = y;
    M2[y] = x;
  }
  printf("M1: \n");
  print_map(M1);
  printf("M2: \n");
  print_map(M2);
  printf("are inverses ? %d\n",areinverse(M1,M2));

  return 0;
}
// -----------------------------------------------------------------
