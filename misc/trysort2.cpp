//__INSERT_LICENSE__
// $Id: trysort2.cpp,v 1.9 2005/06/05 14:59:02 mstorti Exp $

#include <iostream>
#include <vector>
#include <aedsrc/util.h>
#include <aedsrc/sort.h>
#include <mpi.h>
#include <cstdio>

using namespace std;
using namespace aed;

typedef list<int> list_t;

#define LEXICO

bool
less_than_list(list_t &x,list_t &y) {
#ifdef LEXICO
  list_t::iterator 
    xp = x.begin(),
    yp = y.begin();
  while (xp!=x.end() && yp!=y.end()) {
    if (*xp<*yp) return true;
    else if (*xp>*yp) return false;
    xp++;
    yp++;
  }
  return yp!=y.end();
#else
  return x.size() < y.size();
#endif
}

bool
less_than_list2(list_t x,list_t y) {
  list_t xx=x, yy=y;
  return less_than_list(xx,yy);
}

int qsort_comp(const void *a,const void *b) {
  typedef list_t list_t;
  list_t *aa = (list_t *)a;
  list_t *bb = (list_t *)b;
  return less_than_list(*bb,*aa)
    -less_than_list(*aa,*bb);
}

void 
make_random(list_t &L,int N,int M1,int M2) {
  assert(M2>M1);
  int s = M2-M1;
  L.clear();
  for (int j=0; j<N; j++) 
    L.insert(L.end(),M1 +irand(s));
}

void print(vector<list_t> &v) {
  for (int j=0; j<v.size(); j++) printl(v[j]);
}

bool check_sort(vector<list_t> &v) {
  int size = v.size();
  for (int j=0; j<size-1; j++)
    if (less_than_list(v[j+1],v[j])) return false;
  return true;
}

vector<list_t> *ww=NULL;

bool icomp(int &i,int &j) {
  return less_than_list((*ww)[i],(*ww)[j]);
}

int main(int argc,char **argv) {
  MPI_Init(&argc,&argv);

  int NN=100, M=300000, ntimes=3;
  double sumN = 0.0;
  vector<list_t> v,vcpy;
  double tmerge=0.0;
  double 
    tbub=0.0, 
    tibub=0.0, 
    theap=0.0, 
    tiheap=0.0, 
    tquick = 0.0, 
    tshell = 0.0, 
    tstl = 0.0, 
    tcsort = 0.0, 
    tinsert = 0.0, 
    tselec = 0.0, 
    start;

  for (int k=0; k<ntimes; k++) {
    int N = NN+irand(NN);
    // int N = NN;
    sumN += N;
    vcpy.resize(N);
    for (int j=0; j<N; j++) 
      make_random(vcpy[j],irand(M),0,2);

    // #define SLOW
#ifdef SLOW
    v = vcpy;
    start = MPI_Wtime();
    bubble_sort<list_t>(v.begin(),v.end(),less_than_list);
    tbub += MPI_Wtime() - start;
    // print(v);
    assert(check_sort(v));

    v = vcpy;
    start = MPI_Wtime();
    ibubble_sort<list_t>(v.begin(),v.end(),less_than_list);
    tibub += MPI_Wtime() - start;
    // print(v);
    // assert(check_sort(v));

    v = vcpy;
    start = MPI_Wtime();
    insertion_sort<list_t>(v.begin(),v.end(),less_than_list);
    tinsert += MPI_Wtime() - start;
    // print(v);
    assert(check_sort(v));
    
    v = vcpy;
    start = MPI_Wtime();
    selection_sort<list_t>(v.begin(),v.end(),less_than_list);
    // print(v);
    tselec += MPI_Wtime() - start;
    assert(check_sort(v));
#endif

    v = vcpy;
    start = MPI_Wtime();
    heap_sort<list_t>(v.begin(),v.end(),less_than_list);
    theap += MPI_Wtime() - start;
    assert(check_sort(v));
    // print(v);

#if 0    
    v = vcpy;
    start = MPI_Wtime();
    ww = &v;
    iheap_sort_comp = icomp;
    iheap_sort<list_t>(v.begin(),v.end(),less_than_list);
    tiheap += MPI_Wtime() - start;
    // print(v);
    assert(check_sort(v));
#endif

    start = MPI_Wtime();
    quick_sort<list_t>(v.begin(),v.end(),less_than_list);
    tquick += MPI_Wtime() - start;
    // cout << "quick cum: " << tquick << endl;
    // print(v);
    assert(check_sort(v));

    v = vcpy;
    start = MPI_Wtime();
    sort(v.begin(),v.end(),less_than_list2);
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
  cout << "ind bubble: " << tibub/sumN << endl;
  cout << "insert: " << tinsert/sumN << endl;
  cout << "selec: " << tselec/sumN << endl;
#endif
  cout << "heap: " << theap/sumN << endl;
  cout << "iheap: " << tiheap/sumN << endl;
  cout << "quick: " << tquick/sumN << endl;
  cout << "shell: " << tshell/sumN << endl;
  cout << "stl: " << tstl/sumN << endl;
  // cout << "csort: " << tcsort/sumN << endl;

  MPI_Finalize();
}
