//__INSERT_LICENSE__
// $Id: extsort.cpp,v 1.18 2005/06/07 02:09:22 mstorti Exp $

#include <cassert>
#include <iostream>
#include <vector>
#include <aedsrc/util.h>
#include <cstdio>
#include <unistd.h>
#include <algorithm>
#include <mpi.h>

using namespace std;

#define M INT_MAX			// Max element
#define MAX 50000000	  // Max number of elements per file
#define N (MAX*10)		  // number of elements to be sorted

void flush(vector<int> &v,int file_indx) {  //L-flush-b
  char tmp_file[100];
  sort(v.begin(),v.end());
  sprintf(tmp_file,"tmp-file-%d.dat",file_indx);
  FILE *tmp = fopen(tmp_file,"w");
  for (int j=0; j<v.size(); j++) 
    fprintf(tmp,"%d\n",v[j]);
  fclose(tmp);
  v.clear();
}
                                            //L-flush-e
int external_sort(const char *file_in, //L-extsort1
		  const char *file_out) {
  FILE *fid = fopen(file_in,"r");
  int file_indx = 0;
  vector<int> v;
  while (true) {
    int w;
    int nread = fscanf(fid,"%d",&w);
    if (nread==EOF) break;
    v.push_back(w);
    if (v.size()>=MAX) 
      flush(v,file_indx++);
  }
  if (v.size()) flush(v,file_indx++);

  int nfiles = file_indx;             //L-extsort2
  vector<FILE *> files(nfiles,(FILE*)(NULL));
  vector<int> front(nfiles);
  int w;
  char tmp_file[100];

  for (int j=0; j<nfiles; j++) {      //L-extsort2a
    sprintf(tmp_file,"tmp-file-%d.dat",j);
    files[j] = fopen(tmp_file,"r");
    int nread = fscanf(files[j],"%d",&w);
    assert(nread==1);
    front[j] = w;
  }                                   

  // K-way merge                     //L-extsort3
  FILE *out = fopen(file_out,"w");
  while (1) {
    int jmin=-1;
    for (int j=0; j<nfiles; j++) {
      if (!files[j]) continue;
      if (jmin<0 || front[j]<front[jmin])
	jmin = j;
    }
    if (jmin<0) break;
    fprintf(out,"%d\n",front[jmin]);
    int nread = fscanf(files[jmin],
		       "%d",&front[jmin]);
    if (nread!=1) {
      fclose(files[jmin]);
      files[jmin]=NULL;
    }
    
  }
  fclose(out);                      //L-extsort4
  for (int j=0; j<nfiles; j++) {
    sprintf(tmp_file,"tmp-file-%d.dat",j);
    unlink(tmp_file);
  }
}                                   //L-extsort5

int main(int argc,char **argv) {
  MPI_Init(&argc,&argv);
  char *file_in = "input.dat";
  char *file_out = "output.dat";
  FILE *fid = fopen(file_in,"w");
  for (int j=0; j<N; j++) 
    fprintf(fid,"%d\n",rand()%M);
  fclose(fid);
  double start = MPI_Wtime();
  external_sort(file_in,file_out);
  double elapsed = MPI_Wtime()-start;
  printf("elapsed %f, rate %g\n",
	 elapsed,elapsed/N);
  // Check
  fid = fopen(file_out,"r");
  int w1 = -INT_MAX,w2;
  while (true) {
    int nread = fscanf(fid,"%d",&w2);
    if (nread==EOF) break;
    assert(nread==1);
    assert(w2>=w1);
    w1=w2;
  }
  fclose(fid);
  MPI_Finalize();
}
