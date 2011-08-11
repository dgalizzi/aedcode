// $Id$

#include <cstdio>
#include <vector>
#include <string>
using namespace std;

int main() {
  int N=10;
  vector< vector<string> > Vgen;
  Vgen.resize(N);
  for (int k=0; k<N; k++) Vgen[k].resize(N);
  char *line = new char[N*N];
  for (int j=0; j<N; j++) {
    for (int k=0; k<N; k++) {
      sprintf(line,"line j %d, k%d",j,k);
      Vgen[j][k] = line;
    }
  }

  for (int j=0; j<N; j++) {
    for (int k=0; k<N; k++) {
      printf("linea j %d, k%d, contiene: %s\n",
	     j,k,Vgen[j][k].c_str());
    }
  }
  delete[] line;
}
