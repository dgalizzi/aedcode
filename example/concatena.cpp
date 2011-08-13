// $Id$

/* 
   COMIENZO DE DESCRIPCION 

   Escriba procedimientos para concatenanar:
   a) dos listas {\tt L1} y {\tt L2} usando {\tt insert};
   b) un vector {\tt VL} de {\tt n} listas usando {\tt insert};
   c) una lista {\tt LL} de {\tt n} sublistas usando {\tt insert} 
      ``b\'asico'';
   d) una lista {\tt LL} de {\tt n} sublistas usando una opci\'on 
      de {\tt insert};
   e) una lista {\tt LL} de {\tt n} sublistas usando {\tt splice}.
   keywords: lista

   FIN DE DESCRIPCION */
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c concatena.cpp
//        g++ -w -o concatena.exe util.o concatena.o
// INTEL: icc -w -c util.cpp
//        icc -w -c concatena.cpp
//        icc -w -o concatena.exe util.o concatena.o
// -----------------------------------------------------------------
#include <iostream>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
// concatenana dos listas "L1" y "L2" usando "insert"
template <typename t>
void concat_insert_2l (list<t> &L1,list<t> &L2,list<t> &L){
  L.clear();
  L.insert(L.end(),L1.begin(),L1.end());
  L.insert(L.end(),L2.begin(),L2.end());
}

//--------------------------------------------------------------------
// concatenana el vector"VL" de "n" listas usando "insert"
template <typename t>
void concat_insert_vl (vector< list<t> > &VL,list<t> &L) {
  typename list<t>::iterator q,z;
  int n;
  L.clear();
  n=VL.size();
  for (int i=0;i<n;i++) {
    q=VL[i].begin();
    z=VL[i].end();
    while (q!= z) L.insert(L.end(),*q++);
  } // end while
}

//--------------------------------------------------------------------
// concatenana una lista LL de "n" sublistas usando insert "basico"
template <typename t>
void concat_inserb_ll(list< list<t> > &LL,list<t> &L) {
  typename list< list<t> >::iterator p,y;
  typename list<t>::iterator q,z;
  L.clear();                            // re-inicializa nueva lista
  p=LL.begin();                         // iterador de la lista
  y=LL.end();                           // fin de la lista
  while (p!=y) {                        // recorre lista
    q=(*p).begin();                     // *p recorre sublista
    z=(*p).end();                       // *z es fin de sublista
    while (q!=z) L.insert(L.end(),*q++);// inserta la sublista actual
    p++;                                // avanza a la sgte sublista
  } // end while
}

//--------------------------------------------------------------------
// concatenana lista LL de "n" sublistas usando una opcion de insert
template <typename t>
void concat_interv_ll(list< list<t> > &LL,list<t> &L) {
  typename list< list<t> >::iterator p;
  L.clear();
  for (p=LL.begin();p!=LL.end();p++) {
    L.insert(L.end(),(*p).begin(),(*p).end());
  } // end i
}

//--------------------------------------------------------------------
// concatenana la lista "LL" de "n" sublistas usando "splice"
template <typename t>
void concat_splice_ll(list< list<t> > &LL,list<t> &L) { 
  typename list< list<t> >::iterator p;
  L.clear();
  for (p=LL.begin();p!=LL.end();p++) L.splice(L.end(),*p);
}

//--------------------------------------------------------------------
// llena un vector "vl" de "n" listas con listas "l_i" de longitudes 
// aleatorias "n_i" y contenidos tambien aleatorios (numeros enteros)
template <typename t>
void generar_vl(vector< list <t> > &vl) {
  typename  list< list<t> >::iterator p;
  int  k,z,n;
  n=vl.size();
  for (int i=0;i<n;i++) {
    z=irand(10);
    for (int j=0;j<z;j++) {
      k=irand(100);
      vl[i].insert(vl[i].end(),k);      
    }
  }
}

//--------------------------------------------------------------------
// imprime vector de listas
template <typename t>
void imprime_vl(vector< list <t> > &vl) {
  typename list<t>::iterator q,z;
  int n;
  n=vl.size();
  // imprime cada lista
  for (int i=0;i<n;i++) {
    cout << "lista l [" << i << "]: "; printl(vl[i]);
  }
}

//--------------------------------------------------------------------
int main() {
  typedef int dato;
  typedef list<dato> lista;
  typedef vector<lista> vecto_l;
  typedef list<lista>  lista_l;
  int v0[]={2,4,6,8,11,13,14,-1};
  int v1[]={1,3,5,7,9,27,-1};
  int v2[]={2,4,6,8,42,50,-1};
  int n=4;        // numero de listas
  vecto_l VL(n);  // constructor del vector de "n" listas
  lista_l LL(n);  // constructor de  lista  de "n" sublistas
  lista L1,L2,L;

  cout << endl;
  cout << "procedimientos para concatenanar: " << endl << endl;

  cout << "dos listas L1 y L2 usando insert" << endl;
  // arma lista L1
  insertl(L1,v1,-1); cout << "lista L1: "; printl(L1);
  // arma lista L2
  insertl(L2,v2,-1); cout << "lista L2: "; printl(L2);
  // tarea
  concat_insert_2l(L1,L2,L); 
  cout << "lista concatenada L: "; printl(L);
  cout << endl;

  cout << "un vector de n sublistas usando insert" << endl;
  generar_vl(VL);   // genera random  
  imprime_vl(VL);
  concat_insert_vl(VL,L); 
  cout << "lista concatenada L: ";  
  printl(L);
  cout << endl;

  cout << "una lista de n sublistas con insert basico" << endl;
  generar_vl(VL);   // genera random  
  imprime_vl(VL);
  copy(VL.begin(),VL.end(),LL.begin());
  concat_inserb_ll(LL,L); 
  cout << "lista concatenada L: ";
  printl(L);
  cout << endl;

  cout << "una lista de n sublistas con intervalo en insert" << endl;
  generar_vl(VL);   // genera random  
  imprime_vl(VL);
  copy(VL.begin(),VL.end(),LL.begin());
  concat_interv_ll(LL,L); 
  cout << "lista concatenada L: ";
  printl(L);
  cout << endl;

  cout << "una lista de n listas usando splice" << endl;
  generar_vl(VL);   // genera random  
  imprime_vl(VL);
  copy(VL.begin(),VL.end(),LL.begin());
  concat_splice_ll(LL,L); 
  cout << "lista concatenada L: ";
  printl(L);

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
