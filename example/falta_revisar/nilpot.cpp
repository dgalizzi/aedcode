// $Id$

/* COMIENZO DE DESCRIPCION 

   __USE_WIKI__
   Dada una correspondencia #M# tal que el 
   conjunto de sus valores es igual al conjunto 
   de sus claves, encontrar el \'i{}ndice 
   nilpotente, de la misma, es decir el n\'umero de 
   veces #n# que hay que componerla consigo misma 
   hasta llegar a la identidad, es decir #M^n = I#. 
   _Consigna:_  Escribir una funci\'on
   #int nilpot(map<int,int> &M);# que dada una correspondencia
   #M# retorna el m\'\i{}nimo entero \verb+n+ tal que #M^n=I#.
   [Tomado en el 1er parcial 21/4/2005]. 
   keywords: correspondencia

   FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// INTEL: icc -w -c util.cpp
//        icc -w -c nilpot_bo.cpp
//        icc -w -o nilpot_bo.exe nilpot_bo.o util.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c nilpot.cpp
//        g++ -w -o nilpot.exe nilpot.o util.o
// -----------------------------------------------------------------
/* Dadas dos correspondencias #M_1# y #M_2# la _composici\'on_ 
  de ambas es la correspondencia
  #M = M_2 . M_1# tal que si #M_1[a]=b# y #M_2[b]=c#, entonces
  #M[a]=c#. Por ejemplo, si 
  #M1={(0,1),(1,2),(2,0),(3,4),(4,3)}#, y 
  #M2={(0,1),(1,0),(2,3),(3,4),(4,2)}#, entonces
  #M = M_1 . M_2 ={(0,0),(1,3),(2,1),(3,2),(4,4)}#.
  Notemos que para que sea posible componer las dos correspondencias
  es necesario que los valores del contradominio de #M_1# est\'en
  incluidos en las claves de #M_2#. Si el conjunto de valores del
  contradominio de una correspondencia #M# est\'a incluido en el 
  conjunto de sus claves, entonces podemos componer a #M# consigo 
  misma, es decir, #M^2 = M . M#. Por ejemplo, 
  #M_1^2 = M_1 . M_1 = {(0,2),(1,0),(2,1),(3,3),(4,4)}#. 
  De la misma manera puede definirse, #M^3,...,M^n#, componiendo 
  sucesivamente. Puede demostrarse que, para alg\'un #n#, debe ser 
  #M^n=I#, donde #I# es la correspondencia identidad_ , es decir 
  aquella tal que #I[x]=x#. Por ejemplo, si 
  #M = {(0,1),(1,2),(2,0)}#, entonces para #n=3#, #M^n=M^3=I#.
  _Consigna:_  Escribir una funci\'on
  #int nilpot(map<int,int> &M);# que dada una correspondencia
  #M# retorna el m\'\i{}nimo entero \verb+n+ tal que #M^n=I#.
  _Sugerencia:_ Escribir dos funciones auxiliares:
  #void compose(map<int,int> &M1,map<int,int> &M2,map<int,int> &M);# 
  que dadas dos correspondencias #M1, M2#, calcula la composici\'on
  #M = M_2 . M_1#, devolvi\'endola en el argumento #M#,
  #bool is_identity(map<int,int> &M);#
  que dada una correspondencia #M#, retorna #true# si
  #M# es la identidad, y #false# en caso contrario.  */
// -----------------------------------------------------------------
#include <time.h>
#include <sys/time.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std ;

// -------------------------------------------------------------------
typedef map<int,int> map_t;
typedef pair<int,int> pair_t;

// -----------------------------------------------------------------
// Obtiene el tiempo en segundos. 
// warning: `gettimeofday' is a GNU extension. 
double gettod() {
 struct timeval tv;
 gettimeofday (&tv,0);
 return tv.tv_sec + 1e-6 * tv.tv_usec;
}

// -----------------------------------------------------------------
// Imprime la correspondencia
void print_map(map_t &M) {
  map_t::iterator q = M.begin();
  while (q!=M.end()) {
    cout << q->first << " -> " << q->second << endl;
    q++;
  }
}
// -----------------------------------------------------------------
// Compone dos correspondencias 
void compose_map(map_t &M1,
		 map_t &M2,
		 map_t &M) {
  map_t::iterator q = M1.begin();
  while (q!=M1.end()) {
    M[q->first] = M2[q->second];
    q++;
  }
}

// -----------------------------------------------------------------
// Predicado que verifica si una correspondencia es la identidad. 
bool is_identity(map_t &M) {
  map_t::iterator q = M.begin();
  while (q!=M.end()) {
    if (q->first!=q->second) return false;
    q++;
  }
  return true;
}

// -----------------------------------------------------------------
// Verifica cual potencia de M es la identidad (indice nilpotente). 
int nilpot(map<int,int> &M) {
  map_t Mj=M, Maux;
  int n=1;
  while (!is_identity(Mj)) {
    compose_map(M,Mj,Maux);
    Mj = Maux;
    n++;
  }
  return n;
}

// -----------------------------------------------------------------
// Calcula el maximo comum divisor de x e y.
int gcd(int x, int y) {
  int a = x, b = y;
  if (b>a) {
    a = y; b = x;
  }
  while (true) {
    int c = a % b;
    if (!c) return b;
    a = b; b = c;
  }
}

// -----------------------------------------------------------------
// Calcula el minimo comun multiplo de x e y. 
int mcm(int x, int y) {
  return x*y/gcd(x,y);
}

// -------------------------------------------------------------------
// Construye una correspondencia aleatoria como una permutacion. 
void rand_map(map_t &M,int n) {
  // Genera un vector con los elementos 0 a n-1. 
  vector<int> v(n);
  for (int j=0; j<n; j++) v[j] = j;
  // Reordena aleatoriamente usando el
  // algoritmo #random_shuffle# de STL. 
  random_shuffle(v.begin(),v.end());
  // Asigna en la correspondencia el valor
  // #v[j]# a la clave #j#. 
  M.clear();
  for (int j=0; j<n; j++) 
    M[j] = v[j];
}

// -------------------------------------------------------------------
// Esta implementacion es mucho mas eficiente. Para cada una de las 
// claves `k' se calcula su propio indice nilpotente `n(k)' que es 
// el numero de veces que hay que aplicarle `M' para volver a `k'. 
// 
// Por ejemplo, si #M={(0,1),(1,2),(2,0),(3,4),(4,3)}#, entonces
// el indice `n(0)=3' ya que aplicandole la correspondencia a 0 
// obtenemos sucesivamente `0->1->2->0', es decir que debemos 
// aplicarla 3 veces para llegar de nuevo a 0. De la misma forma 
// tenemos `n(1)=3, n(2)=3, n(3)=2, n(4)=2'. El indice nilpotente 
// de `M' es el minimo comun multiplo del indice nilpotente de todas 
// sus claves. Por ejemplo en el caso anterior tenemos 
// #nilpot(M) = mcm(3,3,3,2,2) = 6#.
// 
// Esta implementacion es mucho mas eficiente que la anterior. Si el 
// numero de elementos es #n# entonces el indice nilpotente de #M# 
// puede crecer tanto como el numero de permutaciones de #n#
// elementos, que es #n!#. Como el algoritmo anterior revisa todas 
// las potencias de #M#, puede llegar a ser #O(n.n!)#.  El factor 
// #n# viene del hecho de que para cada potencia #M^j# hacer la
// composicion y chequear para ver si es la identidad es #O(n)#. Por 
// el contrario, el indice nilpotente de cada clave puede ser a lo 
// sumo #n#, de manera que calcular el indice nilpotente de todas las 
// claves puede ser a lo sumo #O(n^2)#. Luego calcular el MCM de todos 
// los indices (usando el algoritmo de Euclides, es a lo sumo 
// #O(n log(n))#. De manera que para el algoritmo rapido tenemos a 
// lo sumo #O(n^2)#.
// -------------------------------------------------------------------
template<class T>
int nilpot2(map<T,T> &M) {
  map_t::iterator q = M.begin();
  int n=1;
  while (q!=M.end()) {
    int c = 1;
    T x = q->first, y=q->second;
    while (y!=x) {
      y = M[y]; c++;
    }
    n = mcm(n,c);
    q++;
  }
  return n;
}

// -------------------------------------------------------------------
int main() {
  map_t M;
  int kaso = 1 ;
  int n ;
  if       (kaso == 1) {
    M.insert(pair_t(0,1));
    M.insert(pair_t(1,2));
    M.insert(pair_t(2,3));
    M.insert(pair_t(3,4));
    M.insert(pair_t(4,0));
    M.insert(pair_t(5,6));
    M.insert(pair_t(6,5));
    print_map (M);
    n = nilpot (M);
    cout << "indice nilpotente ; n = " << n << endl ; 
  } else if (kaso == 2) {
    double t=0.0, t2=0.0;
    int count=0;
    while (true) {
      count++;
      // Genera correspondencias (que son
      // permutaciones) aleatoriamente.
      rand_map(M,20);
      print_map(M);
  
      // Obtiene el indice nilpotente "n" con los dos metodos. 
      // Reporta los tiempos para los dos metodos. 
      double s,elap,elap2; 
      int n2;
      s = gettod();
      // n = nilpot(M);
      elap = gettod()-s;
      t += elap;
  
      s = gettod();
      n2 = nilpot2(M);
      elap2 = gettod()-s;
      t2 += elap2;
      // assert(n==n2);
      printf("nilpot(M): %d, elaps %f,%f, averg: %f,%f\n",
  	   n2,elap,elap2,t/count,t2/count);
    }
  } // end if

  double t=0., t2=0.;
  int count=0;
  while (true) {
    count++;
    // Genera correspondencias (que son
    // permutaciones) aleatoriamente.
    rand_map(M,20);
    // print_map(M);

    // Obtiene el indice nilpotente
    // con los dos metodos. Reporta
    // los tiempos para los dos metodos. 
    double s,elap,elap2; int n,n2;
    s = gettod();
    // n = nilpot(M);
    elap = gettod()-s;
    t += elap;

    s = gettod();
    n2 = nilpot2(M);
    elap2 = gettod()-s;
    t2 += elap2;
    // assert(n==n2);

    printf("nilpot(M): %d, elaps %f,%f, averg: %f,%f\n",
	   n2,elap,elap2,t/count,t2/count);
  }

  cout << endl ;
  return 0 ;
}
// -----------------------------------------------------------------
