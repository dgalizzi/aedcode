// $Id: hanoi.cpp,v 1.6 2005/06/14 01:27:52 mstorti Exp $
#include <cstdio>    //L-hanoi-b
#include <vector>

using namespace std;

void hprint(int n,vector< vector<int> > &vv) {
  for (int j=0; j<3; j++) {
    printf("%s:",(j==0? "A" : j==1? "B" : "C"));
    vector<int> &v = vv[j];
    vector<int>::iterator q = v.begin();
    while (q!=v.end()) printf("%d ",*q++);
    for (int j=v.size(); j<n; j++) printf("  ");
    printf("   ");
  }
  printf("\n");
}

int main() {
  int n = 4;     //L-start
  vector< vector<int> > vv(3);
  for (int j=n-1; j>=0; j--) 
    vv[0].push_back(j);
  hprint(n,vv);
                 
  int minor = 0;   //L-loop
  int moves = 0;
  while (1) {
    // Avanza menor    //L-minor
    int next = (minor+1) % 3;
    vv[minor].pop_back();
    vv[next].push_back(0);
    minor = next;
    hprint(n,vv); moves ++;
    if(vv[minor].size()==n) break;

    // Unica operacion que no cambia al menor   //L-nominor-b
    int lower = (minor+1)%3;
    int higher = (minor+2)%3;
    if (vv[higher].empty()) { }
    else if (vv[lower].empty() || 
	     vv[lower].back() > vv[higher].back()) {
      int tmp = lower;
      lower = higher;
      higher = tmp;
    }
    // Pasar el tope de `lower' a `higher'
    int x = vv[lower].back();
    vv[lower].pop_back();
    vv[higher].push_back(x);
    hprint(n,vv); moves ++;                   //L-nominor-e

  }
  printf("solved puzzle in %d moves\n",moves);
}
                           //L-hanoi-e
#if 0
int moves=0;
while (1) { //L-pseudo-code-b
  // Avanza menor ciclicamente ...
  if(vv[minor].size()==n) break;
  hprint(n,vv); moves++;

  // Realiza unica operacion que no
  // cambia al menor ...
  hprint(n,vv); moves++;
}             
             //L-pseudo-code-e
#endif
