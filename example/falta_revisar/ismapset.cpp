// $Id$

/* 
   COMIENZO DE DESCRIPCION 

    __USE_WIKI__
    Escribir una funci\'on predicado
    #bool is_mapped_set(set<int> &A,set<int> &B,int (*mapfun)(int));#
    que retorna verdadero si el conjunto #B# contiene los elementos
    de #A#, mapeados via la funcion #mapfun#. 
    [Tomado en recuperatorio 29-NOV-2007].
    keywords: conjunto

    FIN DE DESCRIPCION */

// -----------------------------------------------------------------
#include <iostream>
#include <vector>
#include <set>
using namespace std ;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int is_mapped_set(set<int> &A, set<int> &B, int (*mapfun)(int)) {
  // `fA' contiene la imagen de todos los elementos de `A'
  set<int> fA;
  set<int>::iterator p=A.begin();
  while (p!=A.end()) {
    fA.insert(mapfun(*p));
    p++;
  }
  // Verifica que sea igual a `B' usando
  // la comparacion de conjuntos
  return fA==B;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int is_mapped_set2(set<int> &A, set<int> &B, int (*mapfun)(int)) {
  // Si la funcion es biunivoca, (es decir si x!=y implica
  // f(x)!=f(y)), entonces se puede hacer `in-place' (sin
  // contenedores auxiliares, recorriendo los elementos `x'
  // de `A' y verificando que `f(x)' este en `B'. Ademas
  // hay que verificar que los tamanos sean iguales. 
  if (A.size()!=B.size()) return 0;
  set<int>::iterator p=A.begin();
  while (p!=A.end()) 
    if (B.find(mapfun(*p++))==B.end()) return 0;
  return 1;
}

// La funcion cuadrado (NO es biunivoca)
int square(int x) { return x*x; }

// La funcion x -> -x (SI es biunivoca)
int neg(int x) { return -x; }

//--------------------------------------------------------------------
int main() {
  set<int> A,B,B2;
  A.insert(-5);
  A.insert(-3);
  A.insert(5);
  A.insert(10);

  B.insert(9);
  B.insert(25);
  B.insert(100);

  B2.insert(5);
  B2.insert(3);
  B2.insert(-5);
  B2.insert(-10);

  printf("\n\n----------------\n");
  printf("Usando is-mapped-set()\n");
  printf("B==sq(A)? %d (deberia ser 'true')\n",
         is_mapped_set(A,B,square));
  printf("B2==neg(A)? %d (deberia ser 'true')\n",
         is_mapped_set(A,B2,neg));

  printf("\n\n----------------\n");
  printf("\n\nUsando is-mapped-set2() \n"
         "         (Solo para funciones biunivocas!!)\n");
  printf("B==sq(A)? %d (deberia ser 'true')\n",
         is_mapped_set2(A,B,square));
  printf("B2==neg(A)? %d (deberia ser 'true')\n",
         is_mapped_set2(A,B2,neg));

  printf("\n\n----------------\n");
  B.insert(2);
  printf("B==sq(A)? %d (deberia ser 'false')\n",
         is_mapped_set(A,B,square));

  B.erase(2);
  B.erase(100);
  printf("B==sq(A)? %d (deberia ser 'false')\n",
         is_mapped_set(A,B,square));

  B.insert(100);
  printf("B==sq(A)? %d (deberia ser 'true')\n",
         is_mapped_set(A,B,square));
}
