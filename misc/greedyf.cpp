// $Id: greedyf.cpp,v 1.5 2004/01/24 23:02:57 mstorti Exp $ 

#include <iostream>
#include <vector>
#include <set>
// This is needed for the `rand' functions
#include <cmath>

using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// These are used for generating a random graph

// generates a double random between 0. and 1.
double drand() { return double(rand())/double(RAND_MAX); }
// generates an int random between 0 and `m-1'
int irand(int m) { return int(floor(drand()*double(m))); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// Basic graph class. Vertices are integers from 0
// to nv-1. and edges are acccessed via a reference
// to an integer. 
class graph {
private:
  // The graph is internally represented as an
  // integer matrix. (lower triangular). 
  const int nv;
  vector<int> g;
public:
  // Constructor from the number of vertices
  graph(int nv_a) : nv(nv_a) { g.resize(nv*nv,0); }
  // Access an edge. Can be used for setting an edge or
  // accessing.
  int &edge(int j,int k) { 
    if (k<=j) return g[nv*j+k]; 
    else return g[nv*k+j]; 
  }
  void print();
};

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void greedyc(graph &G, set<int> &no_col, set<int> &nuevo_color,
	    vector<int> &tabla_color,int color) {
  // Asigna a `nuevo_color' un conjunto de vertices
  // de `G' a los cuales puede darse el nuevo color `color'
  // sin entrar en conflicto con los ya coloreados
  nuevo_color.clear();
  set<int>::iterator q,w;
  for (q=no_col.begin(); q!=no_col.end(); q++) {
    int adyacente=0;
    for (w=nuevo_color.begin(); w!=nuevo_color.end(); w++) {
      if (G.edge(*q,*w)) {
	adyacente = 1;
	break;    //L-break
      }
    }
    if (!adyacente) {
      // marcar a `*q' como coloreado
      tabla_color[*q] = color;
      // agregar `*q' a `nuevo_color'
      nuevo_color.insert(*q);
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int greedy(graph &G, int nv, vector<int> &tabla_color) {
  int color=0;
  set<int> nuevo_color, no_col;
  set<int>::iterator q;
  for (int k=0; k<nv; k++) no_col.insert(k);
  while (1) {
    greedyc(G,no_col,nuevo_color,tabla_color,color);
    for (q=nuevo_color.begin(); q!=nuevo_color.end(); q++)
      no_col.erase(*q);
    if (!no_col.size()) return color+1;
    color++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// Basic printing routine.
void graph::print() {
  for (int j=0; j<nv-1; j++) 
    for (int k=j+1; k<nv; k++) 
      if (edge(j,k)) printf("(%d ,%d)\n",j,k);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int main() {
  // Another simple graph in book.
#if 0
  int nv=6;
  graph G(nv);
  G.edge(0,1) = 1;
  G.edge(0,2) = 1;
  G.edge(0,3) = 1;
  G.edge(0,4) = 1;
  G.edge(1,3) = 1;
  G.edge(2,3) = 1;
  G.edge(2,4) = 1;
  G.edge(2,5) = 1;
  G.edge(3,4) = 1;
  G.edge(3,5) = 1;
#elif 0
  // Another simple graph in book.
  int nv=12;
  graph G(nv);
  G.edge(0,4) = 1;
  G.edge(0,7) = 1;
  G.edge(0,6) = 1;
  G.edge(0,9) = 1;
  G.edge(1,2) = 1;
  G.edge(1,5) = 1;
  G.edge(1,4) = 1;
  G.edge(1,8) = 1;
  G.edge(2,4) = 1;
  G.edge(2,5) = 1;
  G.edge(3,6) = 1;
  G.edge(3,10) = 1;
  G.edge(4,5) = 1;
  G.edge(4,7) = 1;
  G.edge(5,7) = 1;
  G.edge(5,8) = 1;
  G.edge(6,9) = 1;
  G.edge(6,10) = 1;
  G.edge(7,8) = 1;
  G.edge(7,10) = 1;
  G.edge(10,11) = 1;
#elif 0
  // Another simple graph in book.
  int nv=12;
  graph G(nv);
  G.edge(0,5) = 1;
  G.edge(0,10) = 1;
  G.edge(0,6) = 1;
  G.edge(0,7) = 1;
  G.edge(1,9) = 1;
  G.edge(1,4) = 1;

  G.edge(2,11) = 1;
  G.edge(2,6) = 1;
  G.edge(2,10) = 1;
  G.edge(2,7) = 1;
  G.edge(2,9) = 1;
  
  G.edge(3,11) = 1;
  G.edge(3,4) = 1;

  G.edge(4,11) = 1;
  G.edge(4,1) = 1;
  G.edge(4,3) = 1;

  G.edge(5,0) = 1;
  G.edge(5,6) = 1;
  G.edge(5,10) = 1;

  G.edge(6,0) = 1;
  G.edge(6,5) = 1;
  G.edge(6,10) = 1;
  G.edge(6,2) = 1;
  G.edge(6,11) = 1;

  G.edge(7,0) = 1;
  G.edge(7,8) = 1;
  G.edge(7,9) = 1;
  G.edge(7,2) = 1;
  G.edge(7,10) = 1;

  G.edge(8,7) = 1;
  G.edge(8,9) = 1;

  G.edge(9,4) = 1;
  G.edge(9,1) = 1;
  G.edge(9,2) = 1;
  G.edge(9,7) = 1;
  G.edge(9,8) = 1;

  G.edge(10,5) = 1;
  G.edge(10,7) = 1;
  G.edge(10,2) = 1;
  G.edge(10,6) = 1;
  G.edge(10,0) = 1;

  G.edge(11,6) = 1;
  G.edge(11,2) = 1;
  G.edge(11,4) = 1;
  G.edge(11,3) = 1;

#else
  // Random graph with `nv' vertices and a `sparsity' sp. 
  // sp=(nbr of edges)/(max nbr of edges)
  // where max nbr of edges = nv(nv-1)/2
  int nv=5000;
  // Generates a graph of nv vertices with sparse ratio `sp'
  double sp = 0.5;
  graph G(nv);
  int loaded = 0;
  int total = nv*(nv-1)/2;
  while (1) {
    // Insert edges until the nbr of edges = sp * nv(nv-1)/2
    int j = irand(nv);
    int k = irand(nv);
    // Check is edge was already loaded
    if (j==k || G.edge(j,k)) continue;
    else {
      // Load edge
      G.edge(j,k) = 1;
      loaded++;
      if (double(loaded)/double(total) >= sp) break;
    }
  }
#endif

  cout << "Grafo a colorear" << endl;
  G.print();
  vector<int> tabla_color(nv);
  int nc = greedy(G, nv, tabla_color);

  // Print coloring
  cout << "Coloracion admisible encontrada con " << nc << " colores: " << endl;
  for (int k=0; k<nv; k++) 
    cout << "vertice: " << k << " color: " << tabla_color[k] <<endl;
}
