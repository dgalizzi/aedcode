// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: treetools3.cpp,v 1.3 2004/05/27 17:14:28 mstorti Exp $

#include <aedsrc/tree.h>
#include <aedsrc/treetools.h>

using namespace std;

namespace aed {

  void make_random_tree(tree<int> &T,tree<int>::iterator n,
			int M,int level,int siblings) {
    double lambda = 1.0/(double(siblings)/double(level)+1.0);
    n=T.insert(n,irand(M));
    tree<int>::iterator c=n.lchild();
    while (true) {
      if (drand()<lambda) break;
      make_random_tree(T,c,M,level+1,siblings);
      c=n.lchild();
    }
  }

  void make_random_tree(tree<int> &T,int M,int siblings) {
    make_random_tree(T,T.begin(),M,1,siblings);
  }

  void lisp2tree(tree<int> &A,const string &s) {
    list<int> L;
    int EP = INT_MAX, BP=INT_MAX-1;
    const char *p = s.c_str();
    char num[100];
    while (true) {
      if (*p == '\0') break;
      else if (*p == '(') {
	L.push_back(BP);
	p++;
      } else if (*p == ')') {
	L.push_back(EP);
	p++;
      } else if (*p == ' ') p++;
      else if (*p>='0' && *p<='9') {
	char *pn=num;
	*pn=*p;
	while (*p>='0' && *p<='9') {
	  *pn++ = *p++;
	}
	*++pn='\0';
	int n = atoi(num);
	L.push_back(n);
      } else p++;
    } 
    // list<int>::iterator q = L.begin();
    // while (q!=L.end()) cout << *q++ << " ";
    // cout << endl;
    A.clear();
    list2tree(A,L,BP,EP);
  }
}
