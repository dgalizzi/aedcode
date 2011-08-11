// $Id$

/* COMIENZO DE DESCRIPCION 

   Escribir una funci\'on #void lexico_stack(int n);#
   que genera todas las subsecuencias ordenadas de 
   la secuencia (1..n). Por ejemplo, si #n=4# debe 
   generar (1), (12), (123), (124), (13), 
   (134), (14) (2), (23), (234) (24), (3), (34) y (4). 
   [Tomado en el 1er parcial del 21/4/2005].
   keywords: pila
   FIN DE DESCRIPCION */

/* Considere el problema de generar todas las subsecuencias
   ordenadas de la secuencia $ X = (1, 2, ..., n) $. 
   %
   Por ejemplo, si $n=4$ las subsecuencias ordenadas de
   $ X = (1,2,3,4) $ son: (1), (12), (123), (124), (13), 
   (134), (14) (2), (23), (234) (24), (3), (34) y (4).
   %
   Esta construcci\'on se puede implementar mediante el uso de 
   una pila $ S $ bajo las siguientes reglas: 
   %
   \begin{itemize}
     \compactlist 
    \item Inicializar la pila con el elemento 1.
    \item Si el tope $ t $ de la pila verifica $ t < n $ 
          entonces apilamos $ t + 1 $.
    \item Si $ t = n $, entonces lo desapilamos 
          y, a continuaci\'on, si la pila no quedara 
          vac\'\i{}a incrementamos el nuevo tope de la misma. 
    \item El algoritmo termina cuando la pila queda vac\'{\i}a. 
   \end{itemize}
   %
   Ejemplo:
   S = (1) ;
   S = (2,1) ;
   S = (3,2,1) ;
   S = (4,3,2,1) ;
   S = (4,2,1) ;
   S = (3,1) ;
   S = (4,3,1) ;
   S = (4,1) ;
   S = (2) ;
   S = (3,2) ;
   S = (4,3,2) ;
   S = (4,2) ;
   S = (3) ;
   S = (4,3) ;
   S = (4) ;
   S = ( ) ;
   %
   % \begin{Verbatim}
   %       4
   %     3 3 4   4       4
   %   2 2 2 2 3 3 4   3 3 4   4
   % 1 1 1 1 1 1 1 1 2 2 2 2 3 3 4 --
   % \end{Verbatim}
   %
   \emph{Consigna:} Escriba un procedimiento 
     {\tt void lexico\_stack(int \&n);}
   en el cual, ingresado el n\'umero natural $ n $ 
   imprime todos los conjuntos ordenados de 
   $(1,2,...,n)$. 
   \emph{Sugerencia:} Implementar el algoritmo descripto llamando 
   a una funci\'on auxiliar {\tt void imprime\_pila(stack<int> \&S)} 
   (implementarla !!) que imprime la pila {\tt S} en forma 
   no-destructiva. 
   \textbf{Restricciones:}
   \begin{itemize} \compactlist 
   \item Usar la interfase STL para pilas.
   \item En {\tt lexico_stack} usar una sola estructura auxiliar. 
   \item En {\tt imprime\_pila()} usar una sola estructura auxiliar. 
   \item No usar otros algoritmos de STL.
   \end{itemize}
   [Tomado en el 1er parcial del 21/4/2005].
   keywords: pila. */

// -----------------------------------------------------------------
// INTEL: icc -v -w -c lexico_stack.cpp
//        icc -v -w -o lexico_stack.exe lexico_stack.o
//
// GNU:   g++ -w -c lexico_stack.cpp
//        g++ -w -o lexico_stack.exe lexico_stack.o
//
// -----------------------------------------------------------------
#include <iostream>
#include <stack>
#include <list>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
void imprime_alreves (stack<int> & S) {
  stack<int> C ;
  int i ; 
  while ( !S.empty() ) {
    i = S.top (); 
    C.push (i) ;
    S.pop (); // la unica forma de avanzar en la pila S
  } //
  cout << "pila S : " ;
  while ( !C.empty() ) {
    i = C.top (); 
    cout << i << " " ;
    S.push (i) ;
    C.pop (); // la unica forma de avanzar en la pila auxiliar C
  } //
  cout << endl ;
}

//--------------------------------------------------------------------
void lexico_stack (int & n) {
  stack<int> S ;
  int i; 
  S.push (1);
  while ( !S.empty() ) {
    imprime_alreves (S);
    i = S.top (); 
    if (i < n) 
      S.push (i+1);
    else {
      S.pop () ;
      if ( !S.empty() ) {
        i = S.top (); S.pop () ;
        S.push (i+1);
      } // end if
    } // end if
  } // end while
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// Version recursiva
void lexico_stack2(list<int> &L,int j,int n,int &count) {
  if (j==n) {
    printl(L);
    count++;
  } else {
    lexico_stack2(L,j+1,n,count);
    L.push_back(j);
    lexico_stack2(L,j+1,n,count);
    L.pop_back();
  }
}

// wrapper..
void lexico_stack2(int n) {
  list<int> L;
  int count=0;
  lexico_stack2(L,0,n,count);
  // printf("n %d, total lexico_stack2s %d\n",n,count);
}

//--------------------------------------------------------------------
int main() {
  int n = 5 ; 
  lexico_stack(n);
  cout << endl;
  lexico_stack2(n);
  return 0;
}
// -----------------------------------------------------------------

