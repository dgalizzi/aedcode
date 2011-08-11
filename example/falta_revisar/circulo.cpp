// $Id$

/* COMIENZO DE DESCRIPCION 

  __USE_WIKI__
  Coloquemos #n# n\'umeros enteros positivos alrededor de una 
  circunferencia inicial. Construyamos ahora sucesivas 
  circunferencias conc\'entricas {\it hacia el exterior}, de igual 
  cantidad de elementos, los cuales son obtenidos restando (en valor 
  absoluto) pares consecutivos de la \'ultima circunferencia 
  exterior. 
  Entonces, dada una lista #L = [ x_0, x_1, ..., x_{n-1} ]# de #n#
  n\'umeros enteros que representan los valores iniciales alrededor de
  la circunferencia inicial, escribir una funci\'on 
  #int circulo(list<int> &L);# 
  que ejecuta esta tarea y devuelva adem\'as
  el n\'umero de circunferencias iteradas #p#
  [Tomado en el 1er parcial del 21/4/2005].
  keywords: lista

   FIN DE DESCRIPCION */

/* 
  Coloquemos $ n $ n\'umeros enteros positivos alrededor de una 
  circunferencia inicial. Construyamos ahora sucesivas 
  circunferencias conc\'entricas {\it hacia el exterior}, de igual 
  cantidad de elementos, los cuales son obtenidos restando (en valor 
  absoluto) pares consecutivos de la \'ultima circunferencia 
  exterior. Entonces, puede verificarse que si $n=2^k$ en alguna 
  iteraci\'on $p$ aparecer\'an $ n $ n\'umeros iguales. En ese 
  momento se detiene la iteraci\'on. Por ejemplo, supongamos 
  $ k = 2 $, ($n=4$) y que la circunferencia inicial sea
  $ C_0 = (8,2,5,7) $, entonces iteramos y obtendremos sucesivamente,
  $ C_1 = (6,3,2,1) $,
  $ C_2 = (3,1,1,5) $,
  $ C_3 = (2,0,4,2) $,
  $ C_4 = (2,4,2,0) $ y
  $ C_5 = (2,2,2,2) $, por lo que el n\'umero de circunferencias
  iteradas es $ p = 5 $.  
  Entonces, dada una lista $ L = [ x_0, x_1, ..., x_{n-1} ] $ de $ n $
  n\'umeros enteros que representan los valores iniciales alrededor de
  la circunferencia inicial, escribir una funci\'on {\tt int
  circulo(list<int> \& L);} que ejecuta esta tarea y devuelva adem\'as
  el n\'umero de circunferencias iteradas $ p $. 
  \emph{Restricci\'on:} el algoritmo debe ser {\it in place}. 
  \emph{Ayuda:} Pensar a la lista en un \emph{``sentido circular''}. 
  Tener cuidado al generar la diferencia correspondiente al extremo.
  [Tomado en el 1er parcial del 21/4/2005].

   FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c circulo.cpp
//        g++ -w -o circulo.exe util.o circulo.o
// INTEL: icc -w -c util.cpp
//        icc -w -c circulo.cpp      
//        icc -w -o circulo.exe util.o circulo.o
// -----------------------------------------------------------------
#include <iostream>
#include <list>
#include <map>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
// imprime lista y el contador del circulo
void imprime (list <int> & L, int k) {
  list <int> :: iterator p, z;
  cout << endl ;
  cout << "nro de circulo ; k = " << k << endl ;
  cout << "lista L : " ; 
  p = L.begin ();
  z = L.end ();
  while (p != z) cout << *p++ << " " ;
  cout << endl ;
}

//--------------------------------------------------------------------
// imprime lista
void imprime (list <int> & L) {
  list <int> :: iterator p, z;
  cout << "lista L: " ; 
  p = L.begin ();
  z = L.end ();
  while (p != z) cout << *p++ << " " ;
  cout << endl ;
}

//--------------------------------------------------------------------
// imprime mapeo
void imprime (map <int,int> & M) {
  map <int,int> :: iterator p;
  int x_dominio ;
  int y_rango;
  cout << endl ;
  cout << "mapeo actual (x_dominio, y_rango):" << endl ;
  p = M.begin ();
  while (p != M.end () ) {
    x_dominio = p->first;
    y_rango   = p->second;
    cout << "x_dominio = "     <<    x_dominio  << "  " ;
    cout << "M [x_dominio] = " << M [x_dominio] << endl ;
    p++;
  } // end while
}

//--------------------------------------------------------------------
// "utilitario" (o sea NO hace falta verla): 
// genera  en forma aleatoria una lista de permutacion de "n" enteros 
// en el intervalo [0,n)

// -----------------------------------------------------------------
void  random_shuffle (list<int> &L) {
  list<int>::iterator p,z; 
  list<int> q;
  int k,n;
  // Cuenta el numero de elementos en la lista L
  n=0;
  p=L.begin();
  while (p++!=L.end()) n++;
  // En cada iteracion del lazo se saca un elemento
  // al azar de la lista L y se lo inserta en la cola Q
  for (int h=n;h>0;h--) {
    // A esta altura la lista L tiene "h" elementos
    // asi que generamos un entero "k" entre 0 y h-1
    k = irand (h);
    // nos posicionamos en el elemento "k" en la lista L
    p=L.begin();
    for (int j=0;j<h-1;j++) p++;
    // inserta el elemento "k" de la lista L al final de la cola Q
    // y lo elimina de la lista L
    q.insert(q.end(),*p);
    L.erase(p);
  } // end h
  // Vuelve a copiar todos los elementos de la cola a la lista
  z=q.begin();
  while (z!=q.end()) {
    L.insert(L.end(),*z);
    z=q.erase(z);
  } // end while
} 


//--------------------------------------------------------------------
// "auxiliar" (conveniente para la consigna del ejercicio):
// funcion booleana que devuelve True si la lista "L" es constante.
// version 1: con iteradores sobre lista
bool es_constante1 (list <int> & L) {
  list <int> :: iterator p, q;
  p = L.begin ();
  q = p;
  while (q != L.end () && *p == *q) q++; 
  if (q == L.end ()) return true ; 
  else               return false ;
}

//--------------------------------------------------------------------
// "auxiliar" (conveniente para la consigna del ejercicio):
// funcion booleana que devuelve True si la lista "L" es constante.
// version 2: con un mapeo y notacion mas detallada
bool es_constante2 (list <int> & L) {
  map <int,int> M ;
  map <int,int> :: iterator q;
  list <int> :: iterator p;
  int x, y = 1 ;
  p = L.begin ();
  while ( p != L.end () ) {
    x = *p;
    q = M.find (x);               // busca el item "x"
    if (q == M.end ()) M [x] = y; // entonces NO esta en el mapeo "M"
    p++;                          // avanzamos en "M"
  } // end while
  return M.size() == 1 ;          // si es True entonces "L" es cte
}

//--------------------------------------------------------------------
// "auxiliar" (conveniente para la consigna del ejercicio):
// funcion booleana que devuelve True si la lista "L" es constante.
// version 3: con un mapeo pero menos eficiente y notacion "criptica"
bool es_constante3 (list <int> & L) {
  map <int,int> M ;
  list <int> :: iterator p = L.begin ();
  while ( p != L.end () ) M [*p++] = 1 ;
  return M.size() == 1 ;
}

//--------------------------------------------------------------------
// aunque "irrelevante" para este parcial, verlo para "practicar": 
// funcion que devuelve el maximo de una lista de enteros
int maximo (list <int> & L) {
  list <int> :: iterator p;
  int kmax = 0 ;
  p = L.begin (); 
  while (p != L.end ()) {
    if (*p >= kmax) kmax = *p; 
    p++ ;
  } // end while
  return kmax ;
}

//--------------------------------------------------------------------
int circulo (list <int> & L) {
  list <int> :: iterator p, r, q ;
  int k, n;
  int x, y;
  //
  // iteracion 0: circulo inicial
  k = 0 ;
  imprime (L,k) ; // circulo dato : es el circulo numero "0"
  //
  // mientras queden elementos diferentes
  while ( !es_constante1 (L) ) {
    k++;
    cout << "nro de circulo ; k = " << k << endl ;
    p = L.begin ();        // re-empezamos de nuevo a revisar "L"
    while ( p != L.end () ) {
      // "q" es el siguiente de "p" (para restar "hacia adelante")
      q = p ; q++;
      // como es "in place" hay que recordar el original en L.begin
      if (p == L.begin ()) y = *p;
      // si "q" NO es fin de lista entonces
      if (q != L.end ())   // puede restar "hacia adelante"  
        x = abs (*p - *q); //
      else {               // sino hay que restar con el "recordado"
        x = abs (*p - y);  // que estaba en L.begin (lista circular)
      } // end if
      p = L.erase (p);     // suprime en la posicion "p" y la refresca
      L.insert (p,x);      // inserta diferencia "x" en posicion "p"
    } // end while
    // imprime (L,k) ;     // imprime circulo iterado
  } // end while
  // imprime (L,k) ;       // imprime circulo final
  return k ;
}

//--------------------------------------------------------------------
int circula (list <int> & L) {
  int k, n;
  // controla que n sea una potencia de 2
  n = L.size ();
  k = n & (n - 1);
  if (k != 0) { 
     cout << endl ;
     cout << "n = " << n << endl << endl ;
     cout << "ERROR: n debe ser una potencia de 2 !! " << endl ; 
     return 0 ; }
  else {
     return circulo (L);
  }
}

//--------------------------------------------------------------------
int main() {
  list <int> L ;
  int  v [] = {8,2,5,7,-1};
  int  e ;
  bool z ;
  char *c ;
  int kaso = 2;

  if      (kaso == 1) {
    // construye una lista prefijada
    cout << endl;
    cout << "Lista prefijada (su longitud es 1 potencia de 2):" << endl;
    L.clear ();
    insertl (L,v,-1); 
    cout << "lista L: "; printl (L);
    e = circula (L);
    cout << "nro de circulas crecientes (L) = " << e << endl; 
    z = es_constante3 (L);
    cout << endl;
    cout << "es_constante (L) = " << z << endl;
  } // end elseif
  else if (kaso == 2) {
    // construye una lista aleatoria en [0,n), 
    int m = 33 ; 
    int n =  8 ; // cantidad de elementos (UNA POTENCIA DE 2 !!)
    L.clear ();
    for  (int k=0;k<n;k++) L.insert(L.end(),irand(m)); 
    cout << endl;
    cout << "nro de elementos ; n = " << n << endl; 
    cout << "Antes de random_shuffle  : ";
    printl (L);
    random_shuffle (L);
    cout << endl;
    cout << "Despues de random_shuffle: ";
    printl (L);
    // cout << endl << "pausa ... " ; cin.getline (c,1);
    // cout << "pausa .. " ; cin >> e ; cout << endl ;
    e = circula (L);
    // cout << "nro de circulos crecientes (L) = " << e << endl; 
    z = es_constante3 (L);
    cout << endl;
    cout << "es_constante (L) = " << z << endl;
  } // end elseif
  else {
    cout << endl;
    cout << "nothing to do " << endl;
  } // end else
  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
// 
