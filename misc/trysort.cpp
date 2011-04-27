//__INSERT_LICENSE__
// $Id: trysort.cpp,v 1.21 2005/06/05 14:59:02 mstorti Exp $

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
make_random(vector<int> &v,int M1,int M2,double slope) {
  int N = v.size();
  int s = M2-M1;
  for (int j=0; j<N; j++) 
    v[j] = int(M1+j*slope) + irand(s);
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
  double 
    tbub=0.0, 
    theap=0.0, 
    tquick = 0.0, 
    tshell = 0.0, 
    tquick2 = 0.0, 
    tstl = 0.0, 
    tcsort = 0.0, 
    tinsert = 0.0, 
    tselec = 0.0, 
    tmerge3 = 0.0, 
    start;
  // int NN= 262144;
  int NNN=27;
  for (int j=2; j<NNN; j++) {
    int NN = int(pow(2.0,double(j)));
    cout << "NN: " << NN << "---------------------\n";
    int ntimes=10;
    double sumN = 0.;
    vector<int> v,vcpy;
    w = &v;
    list<int> L;
    double tmerge=0.0;
    
#if 1
    for (int k=0; k<ntimes; k++) {
      // int N = NN+irand(NN);
      int N = NN;
      sumN += N;
      vcpy.resize(N);
      // make_random(vcpy,0,0*N,4.0);
      make_random(vcpy,0,4*N,0.0);

      //#define SLOW
#ifdef SLOW
      v = vcpy;
      // print(v);
      start = MPI_Wtime();
      bubble_sort<int>(v.begin(),v.end());
      tbub += MPI_Wtime() - start;
      // cout << "bubble cum: " << tbub << endl;
      // print(v);
      assert(check_sort(v));

      v = vcpy;
      start = MPI_Wtime();
      insertion_sort<int>(v.begin(),v.end());
      tinsert += MPI_Wtime() - start;
      assert(check_sort(v));
      // cout << "insert cum: " << tinsert << endl;
    
      v = vcpy;
      start = MPI_Wtime();
      selection_sort<int>(v.begin(),v.end());
      tselec += MPI_Wtime() - start;
      assert(check_sort(v));
      // cout << "selec cum: " << tselec << endl;
#endif

      v = vcpy;
      start = MPI_Wtime();
      heap_sort<int>(v.begin(),v.end());
      theap += MPI_Wtime() - start;
      assert(check_sort(v));
      // cout << "heap cum: " << theap << endl;
    
      v = vcpy;
      start = MPI_Wtime();
      quick_sort<int>(v.begin(),v.end());
      tquick += MPI_Wtime() - start;
      // cout << "quick cum: " << tquick << endl;
      // print(v);
      assert(check_sort(v));

      v = vcpy;
      start = MPI_Wtime();
      // print(v);
      merge3_sort<int>(v.begin(),v.end());
      tmerge3 += MPI_Wtime() - start;
      // cout << "merge3 cum: " << tmerge3 << endl;
      // print(v);
      assert(check_sort(v));

#if 0
      v = vcpy;
      start = MPI_Wtime();
      quick_sort2<int>(v.begin(),v.end());
      // cout << "qsort2_ops: " <<  qsort2_ops << endl;
      tquick2 += MPI_Wtime() - start;
      // cout << "quick cum: " << tquick2 << endl;
      // print(v);
      assert(check_sort(v));
#endif

#if 0
      start = MPI_Wtime();
      v = vcpy;
      shell_sort<int>(v.begin(),v.end());
      tshell += MPI_Wtime() - start;
      // cout << "shell cum: " << tshell << endl;
      assert(check_sort(v));
#endif

      v = vcpy;
      start = MPI_Wtime();
      sort(v.begin(),v.end());
      tstl += MPI_Wtime() - start;
      // cout << "stl cum: " << tstl << endl;
      // print(v);
      assert(check_sort(v));

      v = vcpy;
      start = MPI_Wtime();
      qsort(&*v.begin(),v.size(),sizeof(int),qsort_comp);
      tcsort += MPI_Wtime() - start;
      // cout << "csort cum: " << tcsort << endl;
      // print(v);
      assert(check_sort(v));
    }
#ifdef SLOW
    cout << "bubble: " << tbub/sumN << endl;
    cout << "insert: " << tinsert/sumN << endl;
    cout << "selec: " << tselec/sumN << endl;
#endif
    cout << "heap: " << theap/sumN << endl;
    cout << "quick: " << tquick/sumN << endl;
    cout << "merge3: " << tmerge3/sumN << endl;
    cout << "quick2: " << tquick2/sumN << endl;
    cout << "stl: " << tstl/sumN << endl;
    cout << "csort: " << tcsort/sumN << endl;
    cout << "shell: " << tshell/sumN << endl;

    sumN = 0.;
    for (int k=0; k<ntimes; k++) {
      int N = NN+irand(NN);
      sumN += N;
      make_random(L,N,10*N);
      start = MPI_Wtime();
      merge_sort(L);
      tmerge += MPI_Wtime() - start;
      // cout << "merge cum: " << tmerge << endl;
      // cout << "sorted list: ";
      // printl(L);
    }
    cout << "merge: " << tmerge/sumN << endl;
  }

  MPI_Finalize();
#endif
}
