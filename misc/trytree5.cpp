//__INSERT_LICENSE__
// $Id: trytree5.cpp,v 1.11 2004/05/21 16:03:26 mstorti Exp $

#include <aedsrc/treebas.h>
#include <list>
#include <cstdio>
#include <cassert>
#include <vector>

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int count_nodes(tree &T,iterator_t n) {
  if (n==T.end()) return 0;
  int m=1;
  iterator_t c = n.lchild();
  while(c!=T.end()) {
    m += count_nodes(T,c);
    c = c.right();
  }
  return m;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int count_nodes(tree &T) { return count_nodes(T,T.begin()); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int height(tree &T,iterator_t n) {
  if (n==T.end()) return -1;
  iterator_t c = n.lchild();
  if (c==T.end()) return 0;
  int son_max_height = -1;
  while (c!=T.end()) {
    int h = height(T,c);
    if (h>son_max_height) son_max_height = h;
    c = c.right();
  }
  return 1+son_max_height;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int height(tree &T) { return height(T,T.begin()); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void 
node_level_stat(tree &T,iterator_t n,
		int level,vector<int> &nod_lev) {
  if (n==T.end()) return;
  assert(nod_lev.size()>=level);
  if (nod_lev.size()==level) nod_lev.push_back(0);
  nod_lev[level]++;
  iterator_t c = n.lchild();
  while (c!=T.end()) {
    node_level_stat(T,c,level+1,nod_lev);
    c = c.right();
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void node_level_stat(tree &T,vector<int> &nod_lev) {
  nod_lev.clear();
  node_level_stat(T,T.begin(),0,nod_lev);
  cout << "level/#nodes: ";
  for (int j=0;j<nod_lev.size();j++) 
    cout << j << "/" << nod_lev[j] << ", ";
  cout << endl;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int max_node(tree &T,iterator_t n) {
  if (n==T.end()) return -1;
  int w = T.retrieve(n);
  iterator_t c = n.lchild();
  while (c!=T.end()) {
    int ww = max_node(T,c);
    c = c.right();
    if (ww > w) w = ww;
  }
  return w;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int max_node(tree &T) { return max_node(T,T.begin()); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int max_leaf(tree &T,iterator_t n) {
  if (n==T.end()) return -1;
  int w = T.retrieve(n);
  iterator_t c = n.lchild();
  if (c==T.end()) return w;
  w = 0;
  while (c!=T.end()) {
    int ww = max_leaf(T,c);
    c = c.right();
    if (ww > w) w = ww;
  }
  return w;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int max_leaf(tree &T) { return max_leaf(T,T.begin()); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int leaf_count(tree &T,iterator_t n) {
  if (n==T.end()) return 0;
  iterator_t c = n.lchild();
  if (c==T.end()) return 1;
  int w = 0;
  while (c!=T.end()) {
    w += leaf_count(T,c);
    c = c.right();
  }
  return w;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int leaf_count(tree &T) { return leaf_count(T,T.begin()); }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void mirror(tree &R);

void mirror(tree &R,iterator_t n) {

  list<tree *> L;
  iterator_t c = n.lchild();
  if (c==R.end()) return;
  while (c != R.end()) {
    tree *T = new tree;
    L.insert(L.begin(),T);
    tree *Q = *L.begin();
    R.splice(Q->begin(),c);
    mirror(*Q);
    c = n.lchild();
  }

  c = n.lchild();
  while (!L.empty()) {
    tree *Q = *L.begin();
    // printf("passing to tree subtree rooted at %d\n",*Q.begin());
    c = R.splice(c,Q->begin());
    c = c.right();
    delete Q;
    L.erase(L.begin());
  }
}

void mirror(tree &R) { mirror(R,R.begin()); }

//---:---<*>---:---<*>---:---<*>---:---<*>
void preorder(tree &T,iterator_t n,list<int> &L) { //L-algo-tree-b
  L.insert(L.end(),T.retrieve(n));                 //L-deref-n

  iterator_t c = n.lchild();
  while (c!=T.end()) {                  //L-test
    preorder(T,c,L);
    c = c.right();                     //L-upd
  }
}
void preorder(tree &T,list<int> &L) {
  if (T.begin()==T.end()) return;
  preorder(T,T.begin(),L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>
void postorder(tree &T,iterator_t n,list<int> &L) {  //L-postorder
  iterator_t c = n.lchild();
  while (c!=T.end()) {
    postorder(T,c,L);
    c = c.right();
  }
  L.insert(L.end(),T.retrieve(n));
}
void postorder(tree &T,list<int> &L) {
  if (T.begin()==T.end()) return;
  postorder(T,T.begin(),L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>
void lisp_print(tree &T,iterator_t n) {             //L-lisp-print
  iterator_t c = n.lchild();
  if (c==T.end()) cout << T.retrieve(n);
  else {
    cout << "(" << T.retrieve(n);
    while (c!=T.end()) {
      cout << " ";
      lisp_print(T,c);
      c = c.right();
    }
    cout << ")";
  }
}
void lisp_print(tree &T) { 
  if (T.begin()!=T.end()) lisp_print(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>
iterator_t tree_copy(tree &T,iterator_t nt,         //L-treecpy
		     tree &Q,iterator_t nq) { 
  nq = Q.insert(nq,T.retrieve(nt)); //L-insert
  iterator_t 
    ct = nt.lchild(),               //L-c-b
    cq = nq.lchild();               //L-c-e
  while (ct!=T.end()) {
    cq = tree_copy(T,ct,Q,cq);
    ct = ct.right();                //L-upd-b
    cq = cq.right();                //L-upd-e
  }
  return nq;
}

void tree_copy(tree &T,tree &Q) {
  if (T.begin() != T.end()) 
    tree_copy(T,T.begin(),Q,Q.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>
iterator_t mirror_copy(tree &T,iterator_t nt,      //L-mirror-copy
		       tree &Q,iterator_t nq) { 
  nq = Q.insert(nq,T.retrieve(nt));
  iterator_t 
    ct = nt.lchild(), 
    cq = nq.lchild();
  while (ct != T.end()) {
    cq = mirror_copy(T,ct,Q,cq);
    ct = ct.right();
  }
  return nq;
}

void mirror_copy(tree &T,tree &Q) {
  if (T.begin() != T.end()) 
    mirror_copy(T,T.begin(),Q,Q.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>
iterator_t prune_odd(tree &T,iterator_t n) {       //L-prune-odd
  if (T.retrieve(n) % 2) n = T.erase(n); //L-erase
  else {
    iterator_t c = n.lchild();
    while (c != T.end()) c = prune_odd(T,c);
    n = n.right();                       //L-walk
  } 
  return n;
}

void prune_odd(tree &T) { 
  if (T.begin() != T.end()) prune_odd(T,T.begin()); 
}
                                                    //L-algo-tree-e
//---:---<*>---:---<*>---:---<*>---:---<*>
void stat(tree &T) {
  vector<int> nod_lev;
  list<int> L;
  tree Q,MT, Tpo;
  cout << "T: "; T.lisp_print(); cout << endl;
  tree_copy(T,Q);
  cout << "T copy: "; T.lisp_print(); cout << endl;
  mirror(Q);
  cout << endl << "T mirror in place: "; Q.lisp_print(); cout << endl;
  mirror_copy(T,MT);
  cout << "T mirror copy: "; MT.lisp_print(); cout << endl << endl;

  tree_copy(T,Tpo);
  prune_odd(Tpo);
  cout << "T pruned odd nodes: "; Tpo.lisp_print(); cout << endl << endl;

  preorder(T,L);
  cout << "preorder(T): "; printl(L);
  L.clear();
  postorder(T,L);
  cout << "postorder(T): "; printl(L); 
  cout << "lisp_print(T): "; lisp_print(T); cout << "\n\n";

  cout << "Number of nodes: " << count_nodes(T) << endl;
  cout << "Max height: " << height(T) << endl;
  cout << "Max node val: " << max_node(T) << endl;
  cout << "Max leaf val: " << max_leaf(T) << endl;
  cout << "Nbr of leaves: " << leaf_count(T) << endl;
  node_level_stat(T,nod_lev);
}

//---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  tree T;
  list<int> L;
  const int BP=-2,EP=-1,EL=-3;
  
  make_random_tree(T,T.begin(),10,1,2);
  T.lisp_print();
  tree2list(T,L,BP,EP);
  
  list<int>::iterator q, p = L.begin();
  q = p;

#if 1
  cout << "List: \n";
  while (p!=L.end()) {
    cout << " ";
    if (*p == BP) cout << "(";
    else if (*p == EP) cout << ")";
    else cout << *p;
    q = p; p++;
  }
  cout << endl;

#if 0
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
    make_random_tree(T,T.begin(),10,1,2);
    stat(T);
    cout << "==============================================================\n" ;
  }

  int v[] = {BP,1,BP,5,0,2,EP,BP,7,3,1,EP,EP,EL};
  L.clear();
  insertl(L,v,EL);
  T.clear();
  list2tree(T,L,BP,EP);
  stat(T);
#endif
}
