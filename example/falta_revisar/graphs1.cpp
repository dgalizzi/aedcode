// $Id$

/* 
   COMIENZO DE DESCRIPCION

   Ejercicios usando conjuntos en grafos.
   keywords: conjunto, correspondencia

   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// El grafo G (V,E) del 2do ejemplo (nvtx = 12) es:
//
//     0---1---2          9
//     |  /|  /|         / \
//     | / | / |        /   \
//     |/  |/  |       /     \
//     3---4---5     10------11        grafo G
//     |  /|  /|            
//     | / | / |             
//     |/  |/  |              
//     6---7---8                
//                                              1ra capa de vecinos
//  i  xi=xadj[i]  xj=xadj[i+1]   intervalo     adjncy[xi]:adjncy[xj]
//  0   0           2             [ 0,  2)      1,  3
//  1   2           6             [ 2,  3)      0,  2, 3, 4
//  2   6           9             [ 6,  9)      1,  4, 5
//  3   9          13             [ 9, 13)      0,  1, 4, 6
//  4  13          19             [13, 19)      1,  2, 3, 5, 6, 7
//  5  19          23             [19, 23)      8,  2, 4, 7
//  6  23          26             [23, 26)      3,  4, 7
//  7  26          30             [26, 30)      8,  4, 5, 6
//  8  30          32             [30, 32)      5,  7
//  9  32          34             [32, 34)     10, 11
// 10  34          36             [34, 36)      9, 11
// 11  36          38             [35, 38)      9, 10
//
// Sea el conjunto de vertices Y1 = (0,1,3,4). Entonces, 
//
// 1) el subgrafo G1 = section_graph (G,Y1,S1) esta definido por 
//    todos los vertices de G que estan en Y y las aristas asociadas
//
//     0---1    
//     |  /|    
//     | / |    subgrafo G1
//     |/  |    
//     3---4     
//
// 2) el conjunto de vertices adyacentes A1 = adjacent_set (G,Y1) = 
//    (2,5,6,7) esta definido por aquellos de G que son adjacentes
//    (o primeros vecinos) del subgrafo G1, el cual a su vez esta 
//    definido por los vertices de G que estan en el conjunto de 
//    vertices Y1
//
//          ---2
//            /|
//      G1   / |
//          /  |
//          ---5
//     |  /|  /             
//     | / | /               
//     |/  |/                 
//     6---7                    
//
// -----------------------------------------------------------------
// GNU:   g++ -w -c graphs1.cpp
//        g++ -w -o graphs1.exe graphs1.o
// INTEL: icc -w -c graphs1.cpp
//        icc -w -o graphs1.exe graphs1.o
// -----------------------------------------------------------------
#include <map>
#include <set>
#include <queue>
#include <iostream>

using namespace std;

void vwset (set<int> &S, const char* name=NULL) {
  set<int>::iterator s ;
  if (name) cout << name << " = ";
  s = S.begin();
  while (s != S.end()) cout << *s++ << ", "; 
  cout << endl;
}

void vwgraph (map <int,set<int> > &G, const char* name=NULL) {
  map <int,set<int> >:: iterator g ; 
  if (name) cout << name << " = " << endl;
  g = G.begin ();
  while (g != G.end()) {
    cout << g->first << " : ";
    vwset (g->second);
    g++;
  } // end while
}

bool has_edge (map <int,set<int> > &G, pair<int,int> &edge){
  map <int,set<int> >:: iterator g ;
  int x = edge.first;
  int y = edge.second;
  set <int> adj ; 
  g = G.find (x);
  if (g == G.end()) return false;
  adj = g->second;
  if (adj.find (y) == adj.end()) return false;
  return true;
}

bool add_edge (map <int,set<int> > &G, pair<int,int> &edge){
  int x = edge.first;
  int y = edge.second;
  G [x].insert (y);
  G [y].insert (x);
}

void adjacent_set (map<int,set<int> > &G, set<int> &Y, set<int> &S) {
  map <int,set<int> >:: iterator g ;
  set <int>::iterator x, y ;
  set <int> adj ;
  x = Y.begin();
  while (x != Y.end()) {
    g = G.find (*x);
    if (g != G.end()) {
      adj = g->second;
      y = adj.begin();
      while (y != adj.end()) {
	if (Y.find (*y) == Y.end()) S.insert (*y);
	y++;
      } // end while
    } // end if
    x++;
  } // end while
}

void section_graph (map<int,set<int> > &G, set<int> &Y, map<int,set<int> > &S){
  map <int,set<int> >:: iterator g;
  set <int>:: iterator x, y ;
  set <int> gadj ;

  x = Y.begin();
  while (x != Y.end()) {
    g = G.find (*x);
    if (g != G.end()) {
      gadj = g->second;
      set<int> & sadj = S [*x]; 
      y = gadj.begin ();
      while (y != gadj.end()) {
	if (Y.find (*y) != Y.end()) sadj.insert (*y);
	y++;
      } // end while
    } // end if
    x++;
  } // end while
}

void connected_component (map<int,set<int> > &G, int x, set<int> &C) {
  map <int,set<int> >:: iterator g;
  set <int> adj ;
  set <int>:: iterator y ;
  queue <int> Q;
  g = G.find(x);
  if (g != G.end()) Q.push(x);
  while (!Q.empty()) {
    x = Q.front(); Q.pop();
    C.insert (x);
    //
    adj = G [x];
    y = adj.begin();
    while (y != adj.end()) {
      if (C.find (*y) == C.end()) Q.push (*y);
      y++;
    } // end while
  } // end while
}

void mkgraph (int nvtx, int xadj[], int adjncy[], map<int,set<int> > &G) {
  int xi, xj;
  cout << endl ;
  cout << "mkmesh  ... " << endl;
  G.clear();
  for (int i=0; i < nvtx; i++) {
    xi = xadj [i] ;    // extremo izq cerrado en la posicion de "adjncy"
    xj = xadj [i+1] ;  // extremo der abierto en la posicion de "adjncy"
    G [i].insert (& adjncy [xi], & adjncy [xj]);
    cout << endl ;
    cout << "i  = " << i  << endl;
    cout << "xi = " << xi << endl;
    cout << "xj = " << xj << endl;
    vwgraph (G, "G");
  } // end 
  cout << endl << "pausa ... " ; cin.get ();
}

int main() {
#if 0
  int nvtx     = 9;
  int xadj[]   = {0,2,6,9,13,19,23,26,30,32};
  int adjncy[] = {1,3,0,2,3,4,1,4,5,0,1,4,6,1,2,3,
		  5,6,7,8,2,4,7,3,4,7,8,4,5,6,5,7};
#else
  int nvtx     = 12;
  int xadj[]   = {0,2,6,9,13,19,23,26,30,32,34,36,38};
  int adjncy[] = {1,3,0,2,3,4,1,4,5,0,1,4,6,1,2,3,5,6,7,8,
		  2,4,7,3,4,7,8,4,5,6,5,7,10,11,9,11,9,10};
#endif

  map <int,set<int> > G; 
  mkgraph (nvtx, xadj, adjncy,G); vwgraph (G, "G");
  cout << endl;

  int y1[] = {0,1,3,4};
  set<int> Y1 (y1, y1+4);
  vwset (Y1,"Y1");
  cout << endl;

  int y2[] = {nvtx-3,nvtx-2,nvtx-1,nvtx};
  set<int> Y2 (y2,y2+4);
  vwset (Y2,"Y2");
  cout << endl;

  map <int,set<int> > G1, G2; 
  section_graph (G, Y1, G1); vwgraph (G1, "G1");
  cout << endl;

  section_graph (G, Y2, G2); vwgraph (G2, "G2");
  cout << endl;

  set <int> A1, A2;
  adjacent_set (G, Y1, A1); vwset (A1, "A1");
  adjacent_set (G, Y2, A2); vwset (A2, "A2");
  cout << endl;

  set <int> C1, C2, C3;
  connected_component (G, y1 [0], C1); vwset (C1, "C1");
  connected_component (G, y2 [0], C2); vwset (C2, "C2");
  connected_component (G,  nvtx,  C3); vwset (C3, "C3");

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
