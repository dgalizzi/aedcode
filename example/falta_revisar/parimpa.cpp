// $Id$

/* 
   COMIENZO DE DESCRIPCION

   Escribir una funci\'on {\tt 
   void encolar\_trabajo (queue <int> &par, queue <int> &impar, int job)} 
   que, dado un c\'odigo de trabajo n lo pone o bien en la cola 
   {\tt par}, o bien en la cola {\tt impar}, dependiendo del n\'umero 
   {\tt job}. Escribir una funci\'on {\tt 
   int siguiente_trabajo (queue <int> &par, queue <int> &impar)} 
   que obtiene el siguiente trabajo a procesar, dando mayor prioridad 
   a la cola {\tt par}.
   keywords: cola 

   FIN DE DESCRIPCION
*/
// -----------------------------------------------------------------
// GNU:   g++ -c parimpa.cpp
//        g++ -o parimpa.exe parimpa.o
// INTEL: icc -v -c parimpa.cpp
//        icc -v -o parimpa.exe parimpa.o
// -----------------------------------------------------------------
#include <queue>
#include <iostream>
#include "./util.h"
using namespace std;

// -----------------------------------------------------------------
void encolar_trabajo (queue<int> &par,queue<int> &impar,int job) {
  if (job % 2) 
    impar.push(job);
  else 
    par.push(job);
}

// -----------------------------------------------------------------
int siguiente_trabajo (queue<int> &par,queue<int> &impar) {
  queue <int> *Q=NULL;
  int job;
  if      (  !par.empty())  Q = &par;
  else if (!impar.empty())  Q = &impar;
  if (Q) {
    job = Q->front();
    Q -> pop();
    return job;
  } // end if
  else return -1;
}

// -----------------------------------------------------------------
int main () {
  queue <int> par,impar;
  int n=10;
  int job;
  // Simula sistema de colas
  cout << endl;
  for (int j = 0 ; j < n ; j++ ) {
    // Tira la moneda para saber si pone un trabajo o lo saca
    if ( drand () < 0.5) {
      job = irand(n);
      encolar_trabajo (par,impar,job);
      cout << "Pone trabajo " << job << " en cola \n"; } 
    else {
      cout << "Saca trabajo. ";
      job = siguiente_trabajo (par,impar);
      if (job == -1) 
	cout << "no hay mas trabajos en cola \n";
      else 
        cout << "Procesando trabajo " << job << endl;
    } // end if
  } // end j
  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
