// $Id$
/*
  COMIENZO DE DESCRIPCION

  Escribir una funci\'on {\tt void creciente(queue<int> \&Q)} que elimina
  elementos de {\tt Q} de tal manera de que los elementos que quedan
  est\'en ordenados en forma creciente. 
  [Tomado en el 1er parcial 27-APR-2004]
  keywords: lista

  FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
/*  Por ejemplo, si {\tt P=(5,5,9,13,19,17,16,20,19,21)}, entonces
  despu\'es de hacer !+creciente(Q)+ debe quedar
  !+P+=$(5,5,9,13,19,20,21)$.  Usar una cola auxiliar. Se sugiere
  utilizar el siquiente algoritmo: Ir eliminando los elementos de la
  pila !+Q+ y ponerlos en la cola auxiliar !+Q2+ s\'olo si el elemento
  es mayor o igual que el m\'aximo actual. Finalmente volver a pasar
  todos los elementos de !+Q2+ a !+Q+.  % \textbf{Restricciones:}
  \begin{itemize} \compactlist \item Usar la interfase STL para colas.
  \item No usar m\'as estructuras auxiliares que la indicada ni otros
  algoritmos de STL.  \item El algoritmo debe ser $O(n)$.  
*/
// -----------------------------------------------------------------
// INTEL: source /opt/intel_cc_80/bin/iccvars.sh
//        alias cc='/opt/intel_cc_80/bin/icc'
//        /opt/intel_cc_80/bin/icc -w -c      util.cpp
//        /opt/intel_cc_80/bin/icc -w -c creciente.cpp
//        /opt/intel_cc_80/bin/icc -w -o creciente.exe creciente.o
//
// GNU:   g++ -w -c util.cpp
//        g++ -w -c creciente.cpp
//        g++ -w -o creciente.exe creciente.o util.o
//
// -----------------------------------------------------------------
#include <queue>
#include <iostream>
#include "./util.h"

using namespace std;

// -----------------------------------------------------------------
void creciente (queue <int> & Q) {
  int w, max ;
  // Asegura que al menos haya un elemento
  if (Q.empty()) return;
  // Cola auxiliar
  queue<int> Q2;
  // `max' mantiene el maximo de los elementos
  // hasta ahora visitados
  max = Q.front();
  while (!Q.empty()) {
    // Saca elemento de `Q' y lo mantiene en `w'
    w = Q.front();
    Q.pop();
    if (w >= max) {
      // Si es >= lo pone en `Q2' y
      // actualiza el maximo actual. 
      max = w;
      Q2.push(w);
    } // end if
  } // end while
  // Pasa todo `Q2' de vuelta a `Q'. 
  while (!Q2.empty()) {
    Q.push (Q2.front());
    Q2.pop ();
  }
} // end void

// -----------------------------------------------------------------
int main () {
  queue <int> Q;
  int w = 0;
  for (int j = 0 ; j < 10 ; j++) {
    w = w + irand (11) -4;
    cout << w << " ";
    Q.push (w);
  }
  cout << endl;
  creciente (Q);
  while (!Q.empty ()) {
    cout << Q.front () << " ";
    Q.pop ();
  } // end while
  cout << endl;
  return 0 ;
} // end main 
// -----------------------------------------------------------------
