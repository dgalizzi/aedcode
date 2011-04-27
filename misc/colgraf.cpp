//$Id: colgraf.cpp,v 1.19 2005/03/12 16:26:43 mstorti Exp $ 
//
// Implements a basic graph class and two coloring algorithms.
// Coloring by exhaustive search and a greedy one. 
//
// -----------------------------------------------------------------
// INTEL: icc -w -c colgraf.cpp
//        icc -w -o colgraf.exe colgraf.o
// GNU:   g++ -w -c colgraf.cpp
//        g++ -w -o colgraf.exe colgraf.o
// -----------------------------------------------------------------
#include <vector>
#include <cmath>    // This is needed for the "rand" functions
#include <iostream> // input-output
using namespace std;

// -----------------------------------------------------------------
// These are used for generating a random graph

// generates a double random between 0. and 1.
double drand () {return double(rand())/double(RAND_MAX);}
// generates an int random between 0 and "m-1"
int irand (int m) {return int(floor(drand()*double (m)));}

// -----------------------------------------------------------------
// Basic graph class. Vertices are integers from 0
// to (nv-1). and edges are acccessed via a reference
// to an integer. 
class graph{
private:
  // The graph is internally represented as an
  // integer matrix (lower triangular). 
  const int nv;
  vector<int> g;
  // Evaluates a particular coloring
  int evaluate (vector<int> color);
public:
  // Constructor from the number of vertices, where the vector member
  // void resize (size_type num, T val = T) changes to "num" the 
  // vector size. If the vector is lengthened, then, elements with 
  // "val" value are added to the end 
  graph(int nv_a):nv(nv_a) {g.resize (nv * nv, 0);}
  // Access to an edge. Can be used for setting an edge or accessing
  int & edge (int i, int j) { 
    if (j <= i)  // zona triangular inferior incluida diag. ppal
          return g [nv * i + j]; 
    else  return g [nv * j + i]; 
  } 
  // These algorithms return the coloring as an int vector
  // and the number of colors as return value. 
  // Coloring based on exhaustive search. 
  int color_e (vector<int> &color);
  // Coloring based on heuristic algorithm.
  int color_h (vector<int> &color);
  // Print the graph. 
  void print ();
};

// Does a loop over all edges and if it finds
// an edge which connects vertices of the same color
// then returns false (i.e. the coloring is not admisible). 
int graph::evaluate (vector<int> color) {
  for   (int j = 0   ; j < nv-1 ; j++) 
    for (int k = j+1 ; k < nv   ; k++) 
      if (edge (j,k) && color [j] == color [k]) return 0;
  return 1;
}

// -----------------------------------------------------------------
// Exhaustive search algorithm. 
// The algorithm for generating the colorings is as follows.
// an int vector color2[nv+1] of size holds all the colors. 
// color2[j] is the color of vertex "j". Initially it is
// set to all 0. For generating the next coloring. We
// increase the color of the first vertex by 1. If color2[0]>=nc
// then we set his color to 0 and carry one to the next vertex.
// It is like counting in base "nc". We add a dummy vertex with
// "nv" so as to easily detect when we finished with all
// colorings. Also "colors[0..nc-1]" contains the number of
// vertices for each color. So, when evaluating colorings for
// a given "nc" we can skip colorings with less than "nc" colors. 
// -----------------------------------------------------------------
int graph::color_e (vector<int> &color) {
  color.resize (nv, 0);  
  vector <int> color2 (nv+1), colors (nv+1);
  int nc;
  int admisible = 0;
  int evaluated = 0;
  for (nc = 1 ; nc <= nv ; nc++) {
    // Initialize dummy coloring and nbr of colors
    for (int j = 0; j <= nv; j++) color2 [j]=0;
    for (int j = 1; j <= nc; j++) colors [j]=0;
    colors [0] = nv;      
    while (1) {
      if ( color2 [nv] ) break;
      // Check if the coloring has exactly "nc" colors. Otherwise skip
      int eval = 1;
      for (int j = 0 ; j < nc ; j++) 
	if ( !colors [j]) { eval = 0 ; break; }      
      // If number of colors is lower than current value
      // then coloring has been already evaluated
      if (eval) {
	admisible = evaluate(color2);
	evaluated++;
	// If the coloring is admisible, then the algorithm ends. 
	if (admisible) break;
      }
      // Advance to next coloring
      // Update vector colors[] with the number of vertices
      // with a particular color. 
      int c = color2 [0]++;
      colors [c]--;
      colors [c+1]++;
      for (int k = 0 ; k < nv ; k++) 
	if (color2 [k] == nc) {
	  c = color2 [k];
	  color2 [k] = 0;
	  colors [0]++;
	  colors [c]--;
	  c = color2 [k+1];
	  color2 [k+1]++;
	  colors [c]--;
	  colors [c+1]++;
	} else break;
    }
    if (admisible) break;
  }
  // Copy coloring to argument. 
  for (int j = 0 ; j < nv ; j++) color [j] = color2[j];
  // print
  cout << endl ;
  cout << evaluated << " colorings evaluated" << endl;
  print ();
  return nc;
} // end color_e

// -----------------------------------------------------------------
// Heuristic search algorithm
int graph::color_h (vector<int> &coloring) {
  // Initialize set all colors to -1 (not colored)
  coloring.resize (nv);
  for (int k = 0 ; k < nv ; k++) coloring [k] = -1;
  int c = 0 ;                   // index of current color
  int colored = 0;              // number of colored vertices
  //			       
  while (1) { // (stop when nv is reached)
    // Color with "c" color
    for (int j = 0 ; j < nv ; j++) {
      // Try to color all uncolored vertices
      if (coloring [j] != -1) continue;
      int assign_color_c = 1;
      for (int k = 0 ; k < nv ; k++) {
	// Check a vertex if it is connected to another
	// "c" colored vertex. 
	if (edge (j,k) && coloring[k]==c) {
	  // Can not assign color
	  assign_color_c = 0;
	  break;
	}
      } // end k
      if (assign_color_c) { 
	// Assign color, update counter
	coloring [j] = c;
	colored++;
      } // end if
    } // end j
    // Terminate algorithm if all vertices are colored. 
    if (colored == nv) break;
    else c++;			// Pass to next color
  } // end while
  print ();
  return c+1;			// Return nbr of colors
} // end color_h

// -----------------------------------------------------------------
// Basic printing routine.
void graph::print () {
  cout << endl;
  cout << "graph print: " << endl;
  for   (int j = 0    ; j < nv - 1 ; j++) 
    for (int k = j + 1; k < nv     ; k++) 
      if ( edge (j,k) ) cout << j << " " << k << endl ;
} // end print

// -----------------------------------------------------------------
int main (int argc, char **argv) {
  // Generate different cases
#if 0
  // Simple graph in book: Fig. 1.10
  //           c                 a b c d e	 
  //          / \           a  [ 0 0 0 0 1 ]
  //         /   \          b  [ 0 0 1 1 0 ]
  //  a --  e     b  ;  A = c  [ 0 1 0 0 1 ]  (matriz de incidencia)
  //         \   /          d  [ 0 1 0 0 1 ]
  //          \ /           e  [ 1 0 1 1 0 ]        
  //           d     
  //
  //     sol. avida:           sol. opt.:
  //     a, b: red             a, c, d : red
  //     c, d: green           b, e    : green
  //     e   : blue     
  //     total = 3 colores     total = 2 colores   
  //
  int nv = 5;
  graph g (nv);     // define un objeto "g" de la clase "graph" 
  g.edge (0,4) = 1;
  g.edge (4,2) = 1;
  g.edge (4,3) = 1;
  g.edge (2,1) = 1;
  g.edge (3,1) = 1;
#elif 0
  // Another simple graph in book.
  int nv = 6;
  graph g (nv);     // define un objeto "g" de la clase "graph" 
  g.edge (0,1) = 1; 
  g.edge (0,2) = 1;
  g.edge (0,3) = 1;
  g.edge (0,4) = 1;
  g.edge (1,3) = 1;
  g.edge (2,3) = 1;
  g.edge (2,4) = 1;
  g.edge (2,5) = 1;
  g.edge (3,4) = 1;
  g.edge (3,5) = 1;
#elif 1
  // Another simple graph in book.
  int nv=12;
  graph g (nv);     // define un objeto "g" de la clase "graph" 
  g.edge ( 0, 4) = 1;
  g.edge ( 0, 7) = 1;
  g.edge ( 0, 6) = 1;
  g.edge ( 0, 9) = 1;
  g.edge ( 1, 2) = 1;
  g.edge ( 1, 5) = 1;
  g.edge ( 1, 4) = 1;
  g.edge ( 1, 8) = 1;
  g.edge ( 2, 4) = 1;
  g.edge ( 2, 5) = 1;
  g.edge ( 3, 6) = 1;
  g.edge ( 3,10) = 1;
  g.edge ( 4, 5) = 1;
  g.edge ( 4, 7) = 1;
  g.edge ( 5, 7) = 1;
  g.edge ( 5, 8) = 1;
  g.edge ( 6, 9) = 1;
  g.edge ( 6,10) = 1;
  g.edge ( 7, 8) = 1;
  g.edge ( 7,10) = 1;
  g.edge ( 8,10) = 1;
  g.edge ( 8,11) = 1;
  g.edge (10,11) = 1;
#else
  cout << endl ;
  cout << "Random graph with nv vertices and a sparsity sp " << endl ; 
  cout << "where sp = (nbr of edges) / (max nbr of edges)  " << endl ;
  cout << "and max nbr of edges = nv (nv - 1) / 2          " << endl ;
  cout << endl ;
  int nv = 10 ;
  if (argc >= 2) {
    int nread = sscanf (argv [1],"%d", & nv);
  } // end if
  cout << "nv = ", nv << endl ;
  // Generates a graph of nv vertices with sparse ratio "sp"
  double sp = 0.95;
  graph g (nv);
  int loaded = 0;
  int total = nv * (nv - 1)/2;
  while (1) {
    // Insert edges until the nbr of edges = sp * nv(nv-1)/2
    int j = irand (nv);
    int k = irand (nv);
    // Check is edge was already loaded
    if (j == k || g.edge(j,k) ) 
      continue;
    else {
      // Load edge
      g.edge(j,k) = 1;
      loaded++;
      if ( double (loaded) / double (total) >= sp) break;
    } // end if
  } //end while

#endif

  vector<int> coloring (nv);
  int nc ;

  // Do coloring 
  nc = g.color_e (coloring); // Exhaustive algorithm 
  // Print coloring
  cout << endl;
  cout << "Found coloring with " << nc << " colours" << endl ;
  for (int k = 0 ; k < nv ; k++) 
    cout << "colores " << coloring [k] << endl ;

  // Do coloring 
  nc = g.color_h (coloring); // Heuristic algorithm
  // Print coloring
  cout << endl;
  cout << "Found coloring with " << nc << " colours" << endl ;
  for (int k = 0 ; k < nv ; k++) 
    cout << "vertex " << k << ", colour " << coloring [k] << endl ;

  cout << endl;
  return 0 ;
}
// -----------------------------------------------------------------
