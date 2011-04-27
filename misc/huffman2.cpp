//__INSERT_LICENSE__
// $Id: huffman2.cpp,v 1.4 2004/05/04 02:40:05 mstorti Exp $

#include <aedsrc/btree.h>
#include <aedsrc/btreetools.h>
#include <aedsrc/util.h>
#include <unistd.h>
#include <list>
#include <queue>
#include <cstdio>
#include <aedsrc/huffman.h>

using namespace std;
using namespace aed;

typedef btree<int> btree_t;
typedef btree_t::iterator node_t;

int main() {
  int k=0;
  while (1) {
    vector<double> prob;
    double sum = 0.0;
    for (int j=0; j<7; j++) {
      double w = pow(drand(),3.0);
      prob.push_back(w);
      sum +=w;
    }
    for (int j=0; j<prob.size(); j++) prob[j] /= sum;
    btree_t T,Texh;
    double cle, clh;
    huffman_exh(prob,Texh);
    cle = codelen(Texh,prob);

    huffman(prob,T);
    clh = codelen(T,prob);

#if 0
    cout << "-------------------\nround: " << k << endl;
    cout << "prob: ";
    for (int l=0; l<prob.size(); l++) cout << prob[l] << " ";
    cout << endl;
    cout << "exhaustive: " << endl;
    print_tree(Texh);
    cout << endl;
    cout << "heuristic: " << endl;
    print_tree(T);
    cout << endl;
    cout << "exh/heu: " << cle << " " << clh << endl;
#else
    cout << "round/exh/heu: " << k << " " << cle << " " << clh << endl;
#endif
    if (fabs(cle-clh)>1e-7) {
      cout << "-------------------\nround: " << k << endl;
      cout << "prob: ";
      for (int l=0; l<prob.size(); l++) cout << prob[l] << " ";
      cout << endl;
      cout << "exhaustive: " << endl;
      print_tree(Texh);
      cout << endl;
      cout << "heuristic: " << endl;
      print_tree(T);
      cout << endl;
      cout << "exh/heu: " << cle << " " << clh << endl;
      break;
    }
    k++;
  }
}
