//__INSERT_LICENSE__
// $Id: tryhset3.cpp,v 1.2 2004/05/31 21:41:18 mstorti Exp $

#include <mpi.h>
#include <iostream>
#include <aedsrc/util.h>
#include <aedsrc/hashsetbas.h>
//#include <aedsrc/hashsetcbas.h>
//#include <aedsrc/hashsetbaso.h>

using namespace aed;
using namespace std;

int hf(int j) {
  return j;
}

int main(int argc,char **argv) {
  MPI_Init(&argc,&argv);
  int N=1000, M=3*N, NA=20;
  float alpha0=0.05, alpha1=0.95;
  hash_set A(N,hf,-1,-2);
  int j;
  pair<iterator_t,bool> q;
  for (int ja=1; ja<=NA; ja++) {
    for (int pd=0; pd<2; pd++) {
      A.purge_deleted = pd;
      double xi = double(ja)/double(NA);
      double alpha=alpha0+xi*(alpha1-alpha0);
      A.clear();
      int n = 0;
      while (n<int(alpha*N)) {
	int x = irand(M);
	q = A.insert(x);
	if (q.second) n++;
      }
    
      double start = MPI_Wtime();
      A.op_count = 0;
      for (int j=0; j<10000; j++) {
	int w;
	// Inserta un elemento al azar
	while (true) {
	  w = irand(M);
	  q = A.insert(w);
	  if (q.second) break;
	}
	// Elimina un elemento al azar
	while (true) {
	  w = irand(M);
	  if (A.erase(w)==1) break;
	}
	// if (!((j+1) % 10000)) cout << j << endl;
      }
      cout << "alpha: " << alpha << " , purge_deleted: " << pd << endl;
      cout << "rate: " << (MPI_Wtime()-start)/double(N)*1.0e6 << " secs/Mops" <<endl;
      cout << "      " << A.op_count/double(N) << " body-loops/cycle" <<endl;
    }
  }
  MPI_Finalize();
}
