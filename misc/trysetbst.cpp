//__INSERT_LICENSE__
// $Id: trysetbst.cpp,v 1.9 2004/06/13 17:52:19 mstorti Exp $

#include <iostream>
#include <aedsrc/setbst.h>
#include <aedsrc/util.h>
#include <set>
#include <algorithm>

template<class T>
void set_print(set<T> &A) {
  typename set<T>::iterator p = A.begin();
  while (p!=A.end()) {
    cout << *p++ << " ";
  }
  cout << endl;
}

template<class T>
void set_print(aed::set<T> &A) {
  typename aed::set<T>::iterator p = A.begin();
  while (p!=A.end()) {
    cout << *p++ << " ";
  }
  cout << endl;
}

bool are_equal(aed::set<int> &A,set<int> &B) {
  aed::set<int>::iterator a=A.begin();
  set<int>::iterator b=B.begin();
  if (A.size() != B.size()) return false;
  while (a!=A.end() && b!=B.end()) {
    if (*a!=*b) return false;
    a++; b++;
  }
  return a==A.end() && b==B.end();
}

bool abb_p(aed::btree<int> &T,      //L-abb-p-b
	   aed::btree<int>::iterator n,int &min,int &max) {
  aed::btree<int>::iterator l,r;
  int minr,maxr,minl,maxl;
  min = +INT_MAX;
  max = -INT_MAX;
  if (n==T.end()) return true;

  l = n.left();
  r = n.right();

  if (!abb_p(T,l,minl,maxl) || maxl>*n) return false;  //L-cond-abb-1
  if (!abb_p(T,r,minr,maxr) || minr<*n) return false;  //L-cond-abb-2
  
  min = (l==T.end()? *n : minl);
  max = (r==T.end()? *n : maxr);
  return true;
}

bool abb_p(aed::btree<int> &T) {
  if (T.begin()==T.end()) return false;
  int min,max;
  return abb_p(T,T.begin(),min,max);
}
//L-abb-p-e

void avheight(aed::btree<int> &T,
	      aed::btree<int>::iterator m,
	      int &n,int &sum_lev,
	      int &nlvs, int &sum_lev_lv) {
  if (m==T.end()) {
    n = 0;
    sum_lev = 0;
    nlvs = 0;
    sum_lev_lv = 0;
    return;
  } else {
    int ns, sum_levs, nlvss, sum_lev_lvs;
    n = 1;
    sum_lev = 0;
    nlvs = ((m.right()==T.end() && m.left()==T.end()) ? 1 : 0);
    sum_lev_lv = 0;

    avheight(T,m.left(),ns,sum_levs,nlvss,sum_lev_lvs);
    n += ns;
    sum_lev += sum_levs + ns;
    nlvs += nlvss;
    sum_lev_lv += sum_lev_lvs + nlvss;

    avheight(T,m.right(),ns,sum_levs,nlvss,sum_lev_lvs);
    n += ns;
    sum_lev += sum_levs + ns;
    nlvs += nlvss;
    sum_lev_lv += sum_lev_lvs + nlvss;

    return;
  }
}

void avheight(aed::btree<int> &T,double &avdep, double &avdeplv) {
  if (T.begin()!=T.end()) {
    int n, sum_lev,nlvs,sum_lev_lv;
    avheight(T,T.begin(),n,sum_lev,nlvs,sum_lev_lv);
    avdep = double(sum_lev)/double(n);
    // cout << "sum_lev_lv: " << sum_lev_lv << endl;
    // cout << "nlvs: " << nlvs << endl;
    avdeplv = double(sum_lev_lv)/double(nlvs);
    return;
  }
}

int main() {
  set<int> A,B,C,Acpy;
  aed::set<int> AA,BB,CC,AAcpy;
  int N=1024*256, m=3, M=100;
  double avdepth = 0.0, avdepthlv=0.0;
  for (int k=0; k<M; k++) {
    AA.clear();
    for (int j=0; j<N; j++) {
      int x = irand(m*N);
      AA.insert(x);
    }
    double ad,adlv;
    avheight(AA.tree(),ad,adlv);
    cout << "ad: " << ad << " ,adlv: " << adlv << endl;
    avdepth += ad;
    avdepthlv += adlv;
  }
  cout << "avrg depth: " << avdepth/double(M) << endl;
  cout << "min. avrg depth: " << log2(double(N))-1 << endl;

  cout << "avrg depth leaves: " << avdepthlv/double(M) << endl;
  cout << "min. avrg depth leaves: " << log2(double(N)) << endl;

#if 0
  cout << "insertando ";
  for (int j=0; j<N; j++) {
    int x = irand(m*N);
    cout << x << endl;
    A.insert(x);
    AA.insert(x);
    x = irand(m*N);
    B.insert(x);
    BB.insert(x);
  }
  cout << endl;
  print_tree(AA.tree());

  assert(are_equal(AA,A));
  assert(are_equal(BB,B));

  set_print(A);
  set_print(AA);

#define VER_ABB(T)					\
  cout << #T " is abb: " << abb_p(T.tree()) << endl;	\
  assert(abb_p(T.tree()))

  VER_ABB(AA);
  VER_ABB(BB);

  for (int j=0; j<m*N; j++) {
    bool inA = (A.find(j)!=A.end());
    bool inAA = (AA.find(j)!=AA.end());
    if (inA != inAA) 
      cout << "in A: " << inA 
	   << "in AA: " << inAA << endl;
  }

  Acpy = A;
  AAcpy = AA;
  assert(are_equal(AAcpy,Acpy));
  VER_ABB(AAcpy);

  for (int j=0; j<m*N; j++) {
    A.erase(2*j);
    AA.erase(2*j);
  }
  assert(are_equal(AA,A));

  cout << "Eliminados los elementos pares\n";
  set_print(A);
  set_print(AA);
  VER_ABB(AA);

  A = Acpy;
  AA = AAcpy;

  cout << "Recupera elementos\n";
  set_print(A);
  set_print(AA);
  assert(are_equal(AA,A));
  VER_ABB(AA);

  cout << "B\n";
  set_print(B);
  set_print(BB);
  VER_ABB(BB);

  aed::set_union(AA,BB,CC);
  C.clear();
  set_union(A.begin(),A.end(),
	    B.begin(),B.end(),inserter(C,C.begin()));
  assert(are_equal(CC,C));
  VER_ABB(CC);

  cout << "C = A union B\n";
  set_print(C);
  set_print(CC);

  aed::set_intersection(AA,BB,CC);
  C.clear();
  set_intersection(A.begin(),A.end(),
		   B.begin(),B.end(),inserter(C,C.begin()));
  assert(are_equal(CC,C));
  VER_ABB(CC);

  cout << "C = A intersection B\n";
  set_print(C);
  set_print(CC);

  aed::set_difference(AA,BB,CC);
  C.clear();
  set_difference(A.begin(),A.end(),
		 B.begin(),B.end(),inserter(C,C.begin()));
  assert(are_equal(CC,C));
  VER_ABB(CC);

  cout << "C = A - B\n";
  set_print(C);
  set_print(CC);

  aed::set_difference(BB,AA,CC);
  C.clear();
  set_difference(B.begin(),B.end(),
		 A.begin(),A.end(),inserter(C,C.begin()));
  assert(are_equal(CC,C));
  VER_ABB(CC);

  cout << "C = B - A \n";
  set_print(C);
  set_print(CC);
#endif
}
