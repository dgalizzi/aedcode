//__INSERT_LICENSE__
// $Id: trytreap.cpp,v 1.5 2004/12/18 17:12:03 mstorti Exp $

#include <list>
#include <set>
#include <cstdio>
#include <aedsrc/treap.h>
#include <aedsrc/util.h>
#include <cmath>
#include <ctime>

using namespace aed;
using namespace std;

void test1() {
  treap_set<int> A;
  int N = 1000000;
  for (int j=0; j<N; j++) {
    // A.insert(N-j-1);
    A.insert(j);
  }
#if 0
  A.print();
#endif
  printf("depth %d\n",A.max_depth());
  A.aver_depth();

  for (int j=0; j<N; j++) {
    A.erase(j);
#if 0
    printf("erased %d\n",j);
    A.print();
#endif
  }
  A.print();
}

void test2() {
  set<int> A;
  treap_set<int> AT;
  int 
    N = 1000000,
    M = 1000;
  for (int j=0; j<N; j++) {
    int w = rand() % M;

    bool in_A = (A.find(j)==A.end());
    bool in_AT = (AT.find(j) == AT.end());
    assert(in_A == in_AT);
    assert(A.size() == AT.size());

    bool insert = rand() % 2;
    if (insert) {
      A.insert(j);
      AT.insert(j);
    } else {
      A.erase(j);
      AT.erase(j);
    }
  }
}

void test3() {
  set<int> A;
  treap_set<int> AT;

  int 
    N = 10000000,
    M = 100000;
  time_t start;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
#if 1
  start = time(NULL);
  for (int j=0; j<N; j++) {
    int w = rand() % M;
    bool insert = rand() % 2;
    if (insert) A.insert(w);
    else A.erase(w);
  }
  printf("set<>: elapsed %fsecs, size %d\n",
	 difftime(time(NULL),start),A.size());
  
#endif
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
#if 1
  start = time(NULL);
  for (int j=0; j<N; j++) {
    int w = rand() % M;
    bool insert = rand() % 2;
    if (insert) AT.insert(w);
    else AT.erase(w);
  }
  printf("treap_set<>: elapsed %fsecs\n",
	 difftime(time(NULL),start));
#endif
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
}

void test4() {
  treap_set<int> A;
  int N = 10;
  int M = 100;
  printf("inserting ");
  for (int j=0; j<10; j++) {
    int w = rand() % M;
    printf("%d ",w);
    A.insert(w);
  }
  printf("\n");
  printf("In A: ");
  treap_set<int>::iterator q = A.begin();
  while (q!=A.end()) 
    printf("%d ",*q++);
  printf("\n");
}

int main() {
  test4();
}
