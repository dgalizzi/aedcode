// $Id: wseries.cpp,v 1.1 2005/06/14 20:34:31 mstorti Exp $
#include <cstdio>
#include <map>

using namespace std;

int rccount = 0;

double p_A(int p,int q) { //L-pa-b
  if (!p) return 1;
  if (!q) return 0;
  rccount++; //S
  return 0.5*(p_A(p-1,q)+p_A(p,q-1));
}
                          //L-pa-e

double p_A2(int p,int q) { //L-dyna-b
  static map< pair<int,int>,double> table;
  if (!p) return 1;
  if (!q) return 0;
  pair<int,int> Q(p,q);
  map< pair<int,int>,double>::iterator w = 
    table.find(Q);
  if (w!=table.end()) return w->second;
  rccount++; //S
  double prob = 0.5*(p_A2(p-1,q)+p_A2(p,q-1));
  table[Q] = prob;
  return prob;
}
                          //L-dyna-e
int main() {
  int p=8, q=10;
  rccount = 0;
  double P_A = p_A(p,q);
  printf("P_A(p=%d,q%d) = %f, (pure rec) recursive calls %d\n",
	 p,q,P_A,rccount);

  rccount=0;
  P_A = p_A2(p,q);
  printf("P_A(p=%d,q%d) = %f, (dyna prog) recursive calls %d\n",
	 p,q,P_A,rccount);
}
