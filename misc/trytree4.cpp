//__INSERT_LICENSE__
// $Id: trytree4.cpp,v 1.19 2005/04/26 22:04:36 mstorti Exp $

#include <list>
#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdio>
#include <aedsrc/tree.h>
#include <aedsrc/treetools.h>
#include <aedsrc/mirror.h>

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
typedef tree<int> tree_t;      //L-utils-b
typedef tree_t::iterator node_t;  //L-typedef

int count_nodes(tree_t &T,node_t n) {
  if (n==T.end()) return 0;
  int m=1;
  node_t c = n.lchild();
  while(c!=T.end()) m += count_nodes(T,c++);
  return m;
}

int count_nodes(tree_t &T) { 
  return count_nodes(T,T.begin()); 
}
                                              
int height(tree_t &T,node_t n) {           //L-height
  if (n==T.end()) return -1;
  node_t c = n.lchild();
  if (c==T.end()) return 0;
  int son_max_height = -1;
  while (c!=T.end()) {
    int h = height(T,c);
    if (h>son_max_height) son_max_height = h;
    c++;
  }
  return 1+son_max_height;
}

int height(tree_t &T) { 
  return height(T,T.begin()); 
}

void 
node_level_stat(tree_t &T,node_t n,
		int level,vector<int> &nod_lev) {
  if (n==T.end()) return;
  assert(nod_lev.size()>=level);
  if (nod_lev.size()==level) nod_lev.push_back(0);
  nod_lev[level]++;
  node_t c = n.lchild();
  while (c!=T.end()) {
    node_level_stat(T,c++,level+1,nod_lev);
  }
}

void node_level_stat(tree_t &T,
		     vector<int> &nod_lev) {
  nod_lev.clear();
  node_level_stat(T,T.begin(),0,nod_lev);
  for (int j=0;j<nod_lev.size();j++) {
    cout << "[level: " << j 
	 << ", nodes: " << nod_lev[j] << "]";
  }
  cout << endl;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int max_node(tree_t &T,node_t n) {
  if (n==T.end()) return -1;
  int w = *n;
  node_t c = n.lchild();
  while (c!=T.end()) {
    int ww = max_node(T,c++);
    if (ww > w) w = ww;
  }
  return w;
}

int max_node(tree_t &T) { 
  return max_node(T,T.begin()); 
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int max_leaf(tree_t &T,node_t n) {
  if (n==T.end()) return -1;
  int w = *n;
  node_t c = n.lchild();
  if (c==T.end()) return w;
  w = 0;
  while (c!=T.end()) {
    int ww = max_leaf(T,c++);
    if (ww > w) w = ww;
  }
  return w;
}

int max_leaf(tree_t &T) { 
  return max_leaf(T,T.begin()); 
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int leaf_count(tree_t &T,node_t n) {         //L-leaf-count
  if (n==T.end()) return 0;
  node_t c = n.lchild();
  if (c==T.end()) return 1;
  int w = 0;
  while (c!=T.end()) w += leaf_count(T,c++);
  return w;
}

int leaf_count(tree_t &T) { 
  return leaf_count(T,T.begin()); 
}
                                             //L-utils-e

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void print_tree(tree_t &T,node_t n,
		string pre,string c) {
  cout << pre << "+--{" << *n << "}" << endl;
  string pres;
  node_t m = n.lchild();
  int is_leaf = m==T.end();
  if (!is_leaf) cout << pre << c << "  |" << endl;
  while (m!=T.end()) {
    pres = pre + c + "  ";
    if (m.right()!=T.end()) print_tree(T,m++,pres,"|");
    else print_tree(T,m++,pres," ");
  }
  if (!is_leaf) cout << pre << c << endl;
}
void print_tree(tree_t &T) {
  string pre("");
  if (T.begin()!=T.end()) 
    print_tree(T,T.begin(),pre," ");
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void stat(tree_t &T) {
  vector<int> nod_lev;
  T.lisp_print(); cout << endl;
  cout << "--------------\n";
  print_tree(T);
  cout << "--------------\n";
  cout << "Number of nodes: " << count_nodes(T) << endl;
  cout << "Max height: " << height(T) << endl;
  cout << "Max node val: " << max_node(T) << endl;
  cout << "Max leaf val: " << max_leaf(T) << endl;
  cout << "Nbr of leaves: " << leaf_count(T) << endl;
  node_level_stat(T,nod_lev);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int main() {
#if 0
  {
  tree_t T;
    list<int> L;
    const int BP=-2,EP=-1,EL=-3;
  
    make_random_tree(T,10,2);

    cout << "cell_count: " << T.cell_count() << endl;
    T.lisp_print(); cout << endl;
    tree2list(T,L,BP,EP);
  
    list<int>::iterator q, p = L.begin();
    q = p;
 
    cout << "List: \n";
    while (p!=L.end()) {
      cout << " ";
      if (*p == BP) cout << "(";
      else if (*p == EP) cout << ")";
      else cout << *p;
      q = p; p++;
    }
    cout << endl;

#if 1
    cout << "Original tree: \n";
    stat(T);

    mirror(T);
    cout << "Mirrored tree: \n";
    stat(T);

    mirror(T);
    cout << "Back to original tree: \n";
    stat(T);
#endif

    for (int j=0; j<5; j++) {
      T.clear();
      make_random_tree(T,10,2);
      stat(T);
    }

    int v[] = {BP,1,BP,5,0,2,EP,BP,7,3,1,EP,EP,EL};
    L.clear();
    insertl(L,v,EL);
    T.clear();
    list2tree(T,L,BP,EP);
    stat(T);

    T.clear();
    make_random_tree(T,10,2);
    T.clear();
    make_random_tree(T,10,3);
    print_tree(T);
    for (int j=0; j<6; j++) {
      random_shuffle(T);
      print_tree(T);
    }

  }
  cout << "cell_count: " << tree_t::cell_count() << endl;
#endif

#if 0
  tree<int> A;
  string s;
  char *line = NULL;
  size_t N;
  while (true) {
    cout << "entre arbol: > ";
    // cin >> s;
    getline(&line,&N,stdin);
    s = string(line);
    lisp2tree(A,s);
    print_tree(A);
  }
#endif

  tree_t T1,T2,X;
  T1.clear();
  make_random_tree(T1,10,2);
  T2.clear();
  make_random_tree(T2,10,2);

#define printtree(T) 				\
  cout << #T;					\
  T.lisp_print(); cout << endl;

  printtree(T1);
  printtree(T2);
  X=T1;
  T1=T2;
  T2=X;
  printtree(T1);
  printtree(T2);
  X=T1;
  T1=T2;
  T2=X;
  printtree(T1);
  printtree(T2);
}
