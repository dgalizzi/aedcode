//__INSERT_LICENSE__
// $Id: trysort4.cpp,v 1.1 2004/07/09 14:26:00 mstorti Exp $

#include <iostream>
#include <vector>
#include <aedsrc/util.h>
#include <aedsrc/sort.h>
#include <mpi.h>
#include <cstdio>

using namespace std;
using namespace aed;

bool
less_than_abs(int &x,int &y) {
  return abs(x)<abs(y);
}

void 
make_random(vector<int> &v,int M1,int M2) {
  int N = v.size();
  assert(M2>M1);
  int s = M2-M1;
  for (int j=0; j<N; j++) 
    v[j] = M1 +irand(s);
}

void 
make_random(vector<int> &v,int M=20) {
  make_random(v,0,M);
}

void 
make_random(list<int> &L,int N,int M1,int M2) {
  assert(M2>M1);
  int s = M2-M1;
  L.clear();
  for (int j=0; j<N; j++) 
    L.insert(L.end(),M1 +irand(s));
}

void 
make_random(list<int> &L,int N,int M=20) {
  make_random(L,N,0,M);
}

bool check_sort(vector<int> &v) {
  int size = v.size();
  for (int j=0; j<size-1; j++)
    if (v[j]>v[j+1]) return false;
  return true;
}

void aed::print2() {
  vector<int> &v = *w;  
  for (int j=0; j<v.size(); j++) 
    printf("%2d ",v[j]);
  printf("\n");
}

int qsort_comp(const void *a,const void *b) {
  int *aa = (int *)a;
  int *bb = (int *)b;
  return (*aa>*bb)-(*aa<*bb);
}

int main(int argc,char **argv) {
  MPI_Init(&argc,&argv);
  assert(argc==3);
  int ntimes;
  int nread = sscanf(argv[1],"%d",&ndifmaxx);
  assert(nread==1);
  nread = sscanf(argv[2],"%d",&ntimes);
  assert(nread==1);
  // printf("ntimes %d, k %d\n",ntimes,ndifmaxx);
  assert(ndifmaxx>=2 && ndifmaxx<20);
  assert(ntimes>=1);

  int N = 300;
  vector<int> v(N);
  for (int j=0; j<ntimes; j++) {
    make_random(v,0,100*N);
    quick_sort<int>(v.begin(),v.end());
    cout << qsops << endl;
  }
  MPI_Finalize();
}
