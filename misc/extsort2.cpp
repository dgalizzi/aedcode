//__INSERT_LICENSE__
// $Id: extsort2.cpp,v 1.6 2005/06/05 20:42:53 mstorti Exp $

#include <cassert>
#include <iostream>
#include <vector>
#include <aedsrc/util.h>
#include <cstdio>
#include <unistd.h>
#include <algorithm>
#include <mpi.h>

using namespace std;

#define M 1000
#define Nb 100
#define ntime 10

int MAX;

class fileq {
private:
  list<string>::iterator q;
  int cline;
  FILE *fid;
  char *line;
  size_t N;
  string prefix;
  int indx;
  int nrec;
  void openwf() {
    char line[100];
    sprintf(line,"%s-%d.dat",prefix.c_str(),indx);
    fid = fopen(line,"w");
    assert(fid);
    files.push_back(string(line));
    cline=0;
    indx++;
  }
  enum Status {closed, openr, openw } status;
public:
  fileq() : fid(NULL), line(NULL), 
	     N(0), status(closed) { }
  list<string> files;

  void import_files(list<string> &f) {
    assert(status==closed);
    assert(files.empty());
    files = f;
    f.clear();
  }
  void export_files(list<string> &f) {
    assert(status==closed);
    f = files;
    files.clear();
  }
  void open() {
    assert(status==closed);
    status = openr;
    assert(!files.empty());
    q = files.begin();
    // printf("open fid %s\n",q->c_str());
    fid = fopen(q->c_str(),"r");
    assert(fid);
  }
  int get(unsigned int &w) {
    assert(status==openr);
    while(true) {
      int nread = getline(&line,&N,fid);
      if (nread==-1) {
	fclose(fid);
	// printf("unlink %s\n",q->c_str());
	unlink(q->c_str());
	q = files.erase(q);
	if (q==files.end()) return 0;
	// printf("open fid %s\n",q->c_str());
	fid = fopen(q->c_str(),"r");
	assert(fid);
      } else {
	nread = sscanf(line,"%u",&w);
	assert(nread==1);
	return 1;
      }
    }
  }
  void open_write(const string &prefix_a,
		  int nrec_a,int start=0) {
    assert(status==closed);
    status = openw;
    indx=start;
    nrec = nrec_a;
    prefix = prefix_a;
    assert(files.empty());
    openwf();
  }
  void put(unsigned int w) {
    assert(status==openw);
    if (cline==nrec) {
      fclose(fid);
      openwf();
    }
    cline++;
    fprintf(fid,"%u\n",w);
  }
  int close_write() {
    assert(status!=closed);
    fclose(fid);
    status = closed;
    return indx;
  }
  void close() {
    assert(status!=closed);
    assert(files.empty());
    status = closed;
  }
  void dump() {
    assert(status==closed);
    list<string>::iterator q = files.begin();
    while (q!=files.end()) {
      printf("%s ",q->c_str());
      q++;
    }
    printf("\n");
  }
};

const char *stime() {
  const int N=100;
  static char s[N];
  time_t t;
  time(&t);
  const char *w = ctime(&t);
  strcpy(s,w);
  char *q = s;
  while (q<s+N) {
    if (*q == '\n') {
      *q = '\0';
      break;
    }
    q++;
  }
  return s;
}

void merge(fileq &Q,int &indx) {
  list<string> f;
  int cookie = rand();
  printf(">>> [%X - %s]: ",cookie,stime());
  Q.dump();

  Q.export_files(f);
  if (f.size()==1) {
    fileq Qtmp;
    Qtmp.import_files(f);
    Qtmp.open();

    vector<unsigned int> v;
    unsigned int w;
    while (Qtmp.get(w)) v.push_back(w);
    Qtmp.close();

    sort(v.begin(),v.end());

    Q.open_write("tmp",M,indx);
    for (int j=0; j<v.size(); j++) 
      Q.put(v[j]);
    indx = Q.close_write();

  } else {
    list<string> f1,f2;
    fileq Q1,Q2;
    int 
      n = f.size(),
      n1 = n/2,
      n2 = n-n1;
    list<string>::iterator q = f.begin();
    for (int j=0; j<n1; j++) {
      f1.push_back(*q);
      q = f.erase(q);
    }
    Q1.import_files(f1);

    for (int j=0; j<n2; j++) {
      f2.push_back(*q);
      q = f.erase(q);
    }
    Q2.import_files(f2);

    merge(Q1,indx);
    merge(Q2,indx);

    Q.open_write("tmp",M,indx++);
    unsigned int w1,w2;
    bool ok1,ok2;
    Q1.open();
    Q2.open();
    ok1 = Q1.get(w1);
    ok2 = Q2.get(w2);
    while (ok1 && ok2) {
      if (w2<w1) { 
	Q.put(w2);
	ok2 = Q2.get(w2);
      } else {
	Q.put(w1);
	ok1 = Q1.get(w1);
      }
    }
    while (ok1) {
      Q.put(w1);
      ok1 = Q1.get(w1);
    }
    while (ok2) {
      Q.put(w2);
      ok2 = Q2.get(w2);
    }

    Q1.close();
    Q2.close();
    indx = Q.close_write();
  }
  printf("<<< [%X - %s]: ",cookie,stime());
  Q.dump();
}

void merge(fileq &Q) {
  int indx=0;
  merge(Q,indx);
}

int main(int argc,char **argv) {
  MPI_Init(&argc,&argv);
  MAX = int(sqrt(double(INT_MAX)));
  double cum=0.,start;
  for (int jt=0; jt<ntime; jt++) {
    fileq Q,Q2;
    Q.open_write("file",M);
    unsigned int w,ow,csum = 0;
    for (int j=0; j<Nb*M; j++) {
      w = rand();
      // printf("pone %d\n",w);
      Q.put(w);
      csum += w % MAX;
      csum = csum % MAX;
    }
    printf("check sum: %d\n",csum);
    Q.close_write();

    start = MPI_Wtime();
    merge(Q);
    cum += MPI_Wtime()-start;
  
    int check = 0;
    if (check) {
      printf("checking...\n");
      Q.open();
      unsigned int csum1 = 0;
      ow = 0;
      while(Q.get(w)) {
	// printf("saca %d\n",w);
	if (w<ow) printf("no sorted: %u not< %u\n",ow,w);
	ow = w;
	csum1 += w % MAX;
	csum1 = csum1 % MAX;
      }
      printf("check sum: %d\n",csum1);
      assert(csum==csum1);
    } else {
      printf("removing files...\n");
      list<string> f;
      Q.export_files(f);
      list<string>::iterator q = f.begin();
      while (q!=f.end()) unlink((q++)->c_str());
    }
    int nt = jt+1;
    printf("extsort stat: M %d, Nb %d, ntime %d,time %f, avrg/elem %g\n",
	   M,Nb,nt,cum,cum/(double(M)*double(Nb)*double(nt)));
  }
  MPI_Finalize();
}
