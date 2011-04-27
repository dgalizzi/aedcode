// $Id$

/*
  COMIENZO DE DESCRIPCION

Diversas operaciones con conjuntos:
flat: Escribir una funcion predicado 
   {\tt bool flat(vector< set<int> > \&sw, int n);}
   que retorna verdadero si cada par de enteros (j,k) con 0<=j,k<n 
   esta contenido en al menos uno de los conjunto en sw. 
es-neg: Escribir una funcion predicado
  {\tt bool es_neg(set<int> \&A,set<int> \&B);} que retorna verdadero
  si el conjunto B contiene exactamente los mismos elementos 
  que A, pero cambiados de signo. 
en-todos: Escribir una funcion
  predicado {\tt bool en\_todos(vector< set<int> > \&v)} que retorna
  verdadero si existe al menos un elemento que pertenece a todos los
  conjuntos v[j].
mediana: Escribir una funcion
  {\tt int mediana(list<int> \&L)} que retorna la mediana de los
  valores contenidos en la lista {\tt L}. 
[Tomados en el 3er parcial del 24-jun-2004]
Keywords: conjunto

  FIN DE DESCRIPCION */

#include <iostream>
#include <list>
#include <algorithm>
#include "../aedsrc/setl.h"
#include "./util.h"

using namespace std;
using namespace aed;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
//
//     AUXILIARES
//
// Hace un vector random insertando N elementos al azar en [M1,M2)
// Guarda que el conjunto final puede tener menos de N elementos
// ya que varios de los elementos insertados pueden coincidir entre si. 
void make_random_set(set<int> &s,int N,int M1, int M2) {
  s.clear();
  for (int j=0; j<N; j++) s.insert(M1+irand(M2-M1));
}

void make_random_set(set<int> &s,int N,int M) {
  make_random_set(s,N,0,M);
}

// Imprime el conjunto
template <class T>
void prints (set <T> & S) {
  typename set <T> :: iterator p ;
  p = S.begin ();
  while (p != S.end ()) cout << *p++ << " ";
  cout << endl;
}

//---:---<*>---:---<*>---:-  FLAT  :---<*>---:---<*>---:---<*>---: 
/* Escribir una funcion predicado bool disjuntos(v)
   que verifica si todos los conjuntos dentro del vector
   de conjuntos v[] son disjuntos 
   Se est\'a dise\~nando una red inerconectada por switches y se desea,
   para reducir lo m\'as posible la \emph{latencia} entre nodos, que cada par
   de nodos est\'e conectado en forma directa por al menos un switch. 
   Sabemos que el n\'umero de nodos es \verb+n+  y tenemos un 
   \verb+vector< set<int> > sw+ que contiene para cada switch el
   conjunto de los nodos conectados por ese switch, es decir
   \verb+sw[j]+ es un conjunto de enteros que representa el conjunto de
   nodos inteconectados por el switch $j$. \\
   \emph{ Consigna: }Escribir una funci\'on predicado 
   \verb+bool flat(vector< set<int> > &sw, int n);+
   que retorna verdadero si cada par de enteros $(j,k)$ con $0\le j,k<
   n$ est\'a contenido en al menos uno de los conjunto en \verb+sw[]+.

   Por ejemplo, para
   vector \verb+sw+ ser\'\i{}a
   \begin{equation} 
   \text{\tt sw[0]} = \{0,1,2,3,4\},\ \ 
   \text{\tt sw[1]} = \{0,1,5,6,7\},\ \ 
   \text{\tt sw[2]} = \{2,3,4,5,6,7\}
   \end{equation}
   %
   Por lo tanto \verb+flat(sw,8)+ debe retornar \verb+true+. 
   Por otra parte si tenemos
   %
   \begin{equation} 
   \text{\tt sw[0]} = \{0,2,3,4\},\ \ 
   \text{\tt sw[1]} = \{0,1,5,7\},\ \ 
   \text{\tt sw[2]} = \{2,3,5,6,7\}
   \end{equation}
   %
   entonces los pares $(0,6)$, $(1,2)$, $(1,3)$, $(1,4)$, $(1,6)$, 
   $(4,5)$, $(4,6)$ y $(4,7)$ no est\'an conectados en forma
   directa y \verb+flat(sw,8)+ debe retornar \verb+false+. \\
   \emph{Sugerencia 1: } Recorrer todos los pares de valores $(j,k)$ y
   para cada par recorrer todos los conjuntos en \verb+sw[]+ hasta
   encontrar uno que contenga al par. \\
   \emph{Sugerencia 2: } Puede ser de ayuda el escribir una funci\'on 
   auxiliar \verb+bool estan_conectados(sw,j,k)+. 
*/
bool flat(vector< set<int> > &sw, int n) {
  for (int j=0; j<n-1; j++) {
    for (int k=j+1; k<n; k++) {
      int l;
      for (l=0; l<sw.size(); l++) {
	if (sw[l].find(j)!=sw[l].end() 
	    && sw[l].find(k)!=sw[l].end()) break;
      }
      if (l==sw.size()) {
	cout << "par (" << j << "," << k << ") no esta!!\n";
	return false;
      }
    }
  }
  return true;
}

//---:---<*>---:---<*>---:- ES-NEG >---:---<*>---:---<*>---:---<*>---: 
/*
  Escribir una funci\'on predicado
  \verb+bool es_neg(set<int> &A,set<int> &B);+ que retorna verdadero
  si el conjunto \verb+B+ contiene exactamente los mismos elementos 
  que \verb+A+, pero cambiados de signo. Por ejemplo, si
  $A=\{-5,-3,5,10\}$ y $B=\{-10,-5,3,5\}$ entonces \verb+es_neg(A,B)+
  debe retornar \verb+true+. Mientras que si $A=\{-5,-3,2,10\}$ y
  $B=\{-10,-5,4,5\}$, entonces debe retornar \verb+false+ ya que el
  elemento 2 de $A$ y el 4 de $B$ no tienen su negativo en el otro
  conjunto. \\
  \emph{Estrategia 1: } Crear un conjunto temporario con los
  negativos de $A$ y compararlo con $B$. \\
  \emph{Estrategia 2: } Recorrer los elementos de $A$ y verificar que
  su negativo est\'e en $B$ y viceversa. 
*/ 
bool es_neg(set<int> &A,set<int> &B) {
  set<int>::iterator p = A.begin();
  if (A.size()!=B.size()) return false;
  while (p!=A.end()) if (B.find(-*p++)==B.end()) return false;
  return true;
}
   

//---:---<*>---:---<*>-   EN-TODOS ----<*>---:---<*>---:---<*>---: 
/*
  Escribir una funci\'on
  predicado \verb+bool en_todos(vector< set<int> > &v);+ que retorna
  verdadero si existe al menos un elemento que pertenece a todos los
  conjuntos \verb+v[j]+. Por ejemplo, si
  %
  \begin{equation} 
  \text{\tt v[0]} = \{0,2,3,4,5\},\ \ 
  \text{\tt v[1]} = \{0,1,5,7\},\ \ 
  \text{\tt v[2]} = \{2,3,5,6,7\}
  \end{equation}
  %
  entonces \verb+en_todos(v)+ debe retornar \verb+true+ ya que 5 est\'a en los
  tres conjuntos. Por el contrario, si 
  %
  \begin{equation} 
  \text{\tt v[0]} = \{0,2,3,4,5\},\ \ 
  \text{\tt v[1]} = \{0,1,7\},\ \ 
  \text{\tt v[2]} = \{2,3,5,6,7\}
  \end{equation}
  %
  entonces \verb+en_todos(v)+ debe retornar \verb+false+. \\
  \emph{Sugerencia: } generar
  el conjunto que es la intersecci\'on de todos los \verb+v[j]+ y
  finalmente verificar si es vac\'\i{}o o no. 
*/
bool en_todos(vector< set<int> > &v) {
  int n = v.size();
  if (!n) return false;
  set<int> w = v[0]; // La interseccion de todos los conjuntos
  set<int> tmp;
  for (int j=1; j<n; j++) {
    set_intersection(w,v[j],tmp);
    if (tmp.empty()) return false;
    w = tmp;
  }
  cout << "interseccion de todos: ";
  prints(w);
  return true;
}

// Igual que el anterior pero un poco mas eficiente.  Usa punteros a
// conjuntos para w y tmp de manera que se ahorra una copia por
// iteracion.
bool en_todos2(vector< set<int> > &v) {
  int n = v.size();
  if (!n) return false;
  set<int> w1 = v[0], w2; // La interseccion de todos los conjuntos
  set<int> *w=&w1, *tmp=&w2, *aux;
  for (int j=1; j<n; j++) {
    set_intersection(*w,v[j],*tmp);
    if (tmp->empty()) return false;
    // Aca en vez de copiar los conjuntos
    // hace un swap de los punteros
    aux = w; w=tmp; tmp=aux;
  }
  cout << "interseccion de todos: ";
  prints(*w);
  return true;
}


//---:---<*>---:---<*>--  MEDIANA  :---<*>---:---<*>---:---<*>---: 
/*
  Escribir una funci\'on
  \verb+int mediana(list<int> &L);+ que retorna la mediana de los
  valores contenidos en la lista \verb+L+. Recordemos que la mediana
  de una serie de $n$ valores consiste en el valor que queda en la
  posicion $n/2$ despu\'es de ordenarlos. Por ejemplo, si
  $L=(3,2,4,-1,0)$ la mediana es 2. Asumir que todos los elementos en
  $L$ son distintos. \\
  \emph{Sugerencia: } Insertar los elementos en un conjunto temporario
  $A$ y despu\'es buscar la posici\'on apropiada, recorri\'endolo con
  un iterator. Recordemos que al iterar sobre un conjunto los
  elementos aparecen en forma ordenada de menor a mayor. 
*/
int mediana(list<int> &L) {
  if (!L.size()) {
    cout << "No se puede tomar la mediana de un conjunto vacio!!\n";
    return -INT_MAX; // Como si fuera "- infinito" 
  }
  set<int> A;
  list<int>::iterator p = L.begin();
  while (p!=L.end()) A.insert(*p++);
  if (L.size()!=A.size()) {
    cout << "Atencion: elementos repetidos en la lista!!\n";
  }
  int n = A.size();
  set<int>::iterator q = A.begin();
  for (int j=0; j<n/2; j++) q++;
  return *q;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int main () {
  // verifica `flat'. Crea un vector de conjuntos aleatorio.  los
  // imprime y verifica si son disjuntos o no. Lo repite varias veces.
  int N = 5;
  vector< set<int> > v(N);
  for (int k=0; k<10; k++) { // repite el experimento 10 veces
    cout << "-----------\n";
    for (int j=0; j<N; j++) {
      make_random_set(v[j],12,10);
      cout << "S_" << j << ": ";
      prints(v[j]);
    }
    cout << "es flat ? " << (flat(v,10) ? "si" : "no") << endl;
  }
  cout << "-----------\n\n\n";

  // verifica `es-neg'. Crea un vector con N conjuntos
  // aleatorios e inserta los negativos de esos conjuntos.
  // Despues hace un random_shuffle() del vector para
  // desordenarlo y le va aplicando el es_neg() a cada par
  // de sets en el vector.
  N = 3;
  v.clear();
  v.resize(2*N);
  for (int j=0; j<N; j++) {
    make_random_set(v[j],10,-10,11);
    set<int>::iterator p = v[j].begin();
    while (p!=v[j].end()) v[j+1].insert(-*p++);
  }
  random_shuffle(v.begin(),v.end());
  for (int j=0; j<2*N-1; j++) {
    for (int k=j+1; k<2*N; k++) {
      cout << "-----------\n";
      cout << "set " << j << ": "; prints(v[j]);
      cout << "set " << k << ": "; prints(v[k]);
      cout << "es_neg(v[" << j << "],v[" << k << "]): " 
	   << (es_neg(v[j],v[k]) ? "si" : "no") << endl;
    }
  }
  cout << "-----------\n\n\n";
  
  // verifica `en-todos'. Crea un vector de conjuntos aleatorio
  // y le aplica el en_todos(). Imprime la interseccion de
  // todos los conjuntos. Prueba las dos
  // versiones (en_todos() y en_todos2())
  N = 6;
  v.clear();
  v.resize(N);
  for (int k=0; k<20; k++) { // repite el experimento 20 veces
    cout << "-----------\n";
    for (int j=0; j<N; j++) {
      make_random_set(v[j],10,10);
      cout << "v[" << j << "]: ";
      prints(v[j]);
    }
    cout << "en-todos(v)? " << (en_todos(v) ? "si" : "no") << endl;
    cout << "en-todos2(v)? " << (en_todos2(v) ? "si" : "no") << endl;
  }

  // verifica `mediana'. Crea una lista aleatoria. Le aplica 
  // `mediana' y cuenta cuantos elementos menores que la mediana
  // hay (deberian ser n/2-1).
  list<int> L;
  for (int k=0; k<20; k++) { // repite el experimento 20 veces
    L.clear();
    cout << "-----------\n";
    randl(L,1000,11);
    cout << "lista: "; printl(L);
    int menores=0;
    list<int>::iterator p = L.begin();
    int med = mediana(L);
    while (p!=L.end()) if(*p++ < med) menores++;
    cout << "mediana: " << med << ", menores: " << menores << endl;
  }
} 
