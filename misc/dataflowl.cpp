//__INSERT_LICENSE__
// $Id: dataflowl.cpp,v 1.2 2004/05/23 23:39:27 mstorti Exp $

#include <vector>
#include <iostream>
#include <aedsrc/util.h>
#include <aedsrc/setl.h>

using namespace aed;
using namespace std;

void set_print(set<int> &A) {
  set<int>::iterator p = A.begin();
  while (p!=A.end()) {
    cout << *p++ << " ";
  }
  cout << endl;
}

void set_insert(set<int> &A,int *v,int term) {
  while (*v != term) A.insert(*v++);
}

void dataflow(vector< set<int> > &gen,  //L-dataflow-b
	      vector< set<int> > &kill,
	      vector< set<int> > &defin,
	      vector< set<int> > &defout,
	      vector< set<int> > &ent) {
  int nblock = gen.size();
  set<int> tmp;
  bool cambio=true;
  while (cambio) {
    for (int j=0; j<nblock; j++) {
      defin[j].clear();                //L-defin-b
      set<int>::iterator p = ent[j].begin();
      while (p!=ent[j].end()) {
	int k = *p;
	set_union(defin[j],defout[k],tmp);
	defin[j] = tmp;
	p++;
      }                                //L-defin-e
    }
    cambio=false;
    for (int j=0; j<nblock; j++) {     //L-defout-b
      int out_prev = defout[j].size();
      set_union(defin[j],gen[j],tmp);
      set_difference(tmp,kill[j],defout[j]);
      if (defout[j].size()!=out_prev) cambio=true; 
    }                                  //L-defout-e
#if 0         //S-b
    for (int j=0; j<nblock; j++) {
      cout << "defin[" << j << "]: "; 
      set_print(defin[j]);
      cout << "defout[" << j << "]: "; 
      set_print(defout[j]);
    }
#endif        //S-e
  }
}
                                 //L-dataflow-e
int main() {
  int nblock = 8, term=-1;
  vector< set<int> > 
    gen(nblock),kill(nblock),
    defout(nblock),defin(nblock),
    ent(nblock);
  
  int g0[]={1,2,3,-1};
  set_insert(gen[0],g0,term);
  int g1[]={4,5,-1};
  set_insert(gen[1],g1,term);
  int g3[]={6,-1};
  set_insert(gen[3],g3,term);
  int g4[]={7,8,-1};
  set_insert(gen[4],g4,term);
  int g7[]={9,-1};
  set_insert(gen[7],g7,term);

  int k0[]={4,5,6,7,8,9,-1};
  set_insert(kill[0],k0,term);
  int k1[]={2,3,7,8,-1};
  set_insert(kill[1],k1,term);
  int k3[]={1,9,-1};
  set_insert(kill[3],k3,term);
  int k4[]={2,3,4,5,-1};
  set_insert(kill[4],k4,term);
  int k7[]={1,6,-1};
  set_insert(kill[7],k7,term);

  int b1[]={0,-1};
  set_insert(ent[1],b1,term);
  int b2[]={1,-1};
  set_insert(ent[2],b2,term);
  int b3[]={2,-1};
  set_insert(ent[3],b3,term);
  int b4[]={3,7,-1};
  set_insert(ent[4],b4,term);
  int b5[]={2,4,-1};
  set_insert(ent[5],b5,term);
  int b6[]={5,-1};
  set_insert(ent[6],b6,term);
  int b7[]={5,-1};
  set_insert(ent[7],b7,term);

  dataflow(gen,kill,defin,defout,ent);
  
  for (int j=0; j<nblock; j++) {
    cout << "defin[" << j << "]: "; set_print(defin[j]);
    cout << "defout[" << j << "]: "; set_print(defout[j]);
  }

}
