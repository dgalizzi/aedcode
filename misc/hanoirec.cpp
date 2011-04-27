// $Id: hanoirec.cpp,v 1.5 2005/06/14 02:02:19 mstorti Exp $
#include <cstdio>
#include <vector>

using namespace std;

void hprint(vector< vector<int> > &vv) {
  for (int j=0; j<3; j++) {
    printf("%s:",(j==0? "A" : j==1? "B" : "C"));
    vector<int> &L = vv[j];
    vector<int>::iterator q = L.begin();
    while (q!=L.end()) printf("%d ");
    printf("\n");
  }
  printf("-------------\n");
}

int moves=0;
vector< vector<int> > vv;

void move1(vector<int> &to,vector<int> &from) { //L-mov1
  int x = from.back();
  from.pop_back();
  to.push_back(x);
  hprint(vv);
  moves++;
}

void move(int n,vector<int> &to,    //L-move
	  vector<int> &from, vector<int> &aux) {
  if (n==1) move1(to,from);
  else {
    move(n-1,aux,from,to);
    move1(to,from);
    move(n-1,to,aux,from);
  }
}

int main() {                        //L-main
  int n = 10;
  vv.resize(3);
  for (int j=0; j<n; j++) 
    vv[0].push_front(j);
  hprint(vv);

  move(n,vv[1],vv[0],vv[2]);
  printf("Solved Hanoi puzzle in %d moves\n",moves);
}
                                     //L-main-e
#if 0
#endif
