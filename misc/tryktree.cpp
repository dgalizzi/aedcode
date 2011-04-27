//__INSERT_LICENSE__
// $Id: tryktree.cpp,v 1.12 2005/05/01 15:25:02 mstorti Exp $

#include <list>
#include <cstdio>
#include <aedsrc/ktree.h>
//#include <aedsrc/btreetools.h>
#include <aedsrc/util.h>
#include <algorithm>

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Makes `T' a random k-tree preserving arity.
// `lambda' is the probability of a node to be
// dereferentiable (i.e. not to be end()).
// Increasing `lambda' increases the depth of the
// tree. `max' is the maximum number of the values
// stored in the nodes of the tree. The values are in
// the range `[0,max)'.  `max_depth' is the maximum
// depth allowed for the tree.  `gen' is a generator
// function provided by the user that returns the
// sequences of numbers to be inserted in the tree.
// The sequence of numbers are generated by calls
// `x = gen(data)'. 
void
make_ktree(ktree<int> &T,
	   ktree<int>::iterator n,
	   double lambda,
	   int max,
	   int max_depth,
	   int (*gen)(void *data)=NULL,
	   void *data=NULL) {
  // Insert a node here wit probability `lambda'.
  // If depth is grater than mac depth do
  // not insert. 
  if (max_depth<0 || drand()>lambda) return;
  int x;
  // Generate next element to be inserted.
  // By default use the random generator
  // modulo `max'. 
  if (gen) x = gen(data);
  else x = rand() % max;
  n = T.insert(n,x);
  // Apply recursively to the sons of this
  // newly inserted node. 
  int k = T.order();
  for (int j=0; j<k; j++)
    make_ktree(T,n[j],lambda,
	       max,max_depth-1,
	       gen,data);
}

// Wrapper function. May be used with
// default values (NULL) for `gen'
// and `data'. 
void
make_ktree(ktree<int> &T,
	   double lambda,
	   int max,
	   int max_depth,	
	   int (*gen)(void *data)=NULL,
	   void *data=NULL) {
  // First clear the tree. 
  T.clear();
  make_ktree(T,T.begin(),
	     lambda,max,max_depth,
	     gen,data);
}

// Generates a linear sequence 0,1,2,3...
int linear_gen(void *data) {
  int &x = *(int *)data;
  x++;
  return x;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// Copies the tree `mirrored'.
// The copy is `O(n)' (n is the number
// of nodes in the tree. 
ktree<int>::iterator 
mirror_copy(ktree<int> &T1,
	    ktree<int>::iterator n1,
	    ktree<int> &T2,
	    ktree<int>::iterator n2) {
  // Copy only if n1 is dereferenciable
  if (n1==T1.end()) return n2;
  // Insert `n1' val in `n2'
  int k = T1.order();
  n2 = T2.insert(n2,*n1);
  // Copy recursively each son `j' onto the
  // mirror son `k-j-1'
  for (int j=0; j<k; j++) 
    mirror_copy(T1,n1[j],T2,n2[k-j-1]);
}

// Wrapper
void 
mirror_copy(ktree<int> &T1,ktree<int> &T2) {
  // Clear `T2' and make its order
  // equal to that one of `T1'
  T2.clear();
  T2.change_order(T1.order());
  mirror_copy(T1,T1.begin(),T2,T2.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// Makes a tree `T' to be mirror `in-place'.
// This is $O(n)$
void 
make_mirror(ktree<int> &T,
	    ktree<int>::iterator n) {
  // Copy onli dereferenciable nodes
  if (n==T.end()) return;
  // Use an auxiliary tree
  int k = T.order();
  ktree<int> Q(k);
  // Exchange mirrored sons (j,k-j-1)
  // Note that the loop is up to `k/2'.
  for (int j=0; j<k/2; j++) {
    int jj = k-j-1;
    // Splice `n[j]' subtree to `Q'
    T.splice(Q.begin(),n[j]);
    // Splice `n[jj]' subtree to `n[j]'
    T.splice(n[j],n[jj]);
    // Splice `Q' to `n[jj]' 
    T.splice(n[jj],Q.begin());
  }
  // Apply `make_mirror' recursively to each son
  for (int j=0; j<k; j++) 
    make_mirror(T,n[j]);
}

// Wrapper
void 
make_mirror(ktree<int> &T) {
  make_mirror(T,T.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// Eliminates all nodes that satisfies `pred'.
// If a nodes satisfies `pred' then is erased
// all the subtree (without regardign what is in). 
template<class T>
void prune_if(ktree<T> &A,
	      typename ktree<T>::iterator n,
	      bool (*pred)(T t,void *data),
	      void *data) {
  // Check only dereferenciable nodes
  if (n==A.end()) return;
  // If nodes satisfies predicate, then
  // erase all the subtree. 
  if (pred(*n,data)) A.erase(n);
  else {
    // Apply recursively yo all the sons. 
    int k = A.order();
    for (int j=0; j<k; j++) 
      prune_if(A,n[j],pred,data);
  }
}

// Wrapper
template<class T>
void prune_if(ktree<T> &A,
	      bool (*pred)(T t,void *data),
	      void *data=NULL) {
  prune_if(A,A.begin(),pred,data);
}

// Predicate for oddity. 
bool odd(int x) { return x % 2; }

// Predicate to eliminate the multiples of `K'.
// `K' is passed by the argument `data'. 
bool my_pred(int x,void *data) { 
  int K = *(int *)data;
  return x % K==0; 
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// Applies a mapping function `f' to each element
// of the tree, i.e. each element of a node `*n'
// is replaced by `f(*n)'. 
template<class T>
void apply(ktree<T> &A,
	   typename ktree<T>::iterator n,
	   T (*f)(T t,void *data),
	   void *data) {
  // Apply only to dereferenciable nodes
  if (n==A.end()) return;
  // Map this nodes
  *n = f(*n,data);
  // Apply recursively to all the sons
  int k = A.order();
  for (int j=0; j<k; j++) apply(A,n[j],f,data);
}

// Wrapper
template<class T>
void apply(ktree<T> &A, 
	   T (*f)(T t,void *data),
	   void *data=NULL) {
  apply(A,A.begin(),f,data);
}

// This is the data needed for a
// linear mapping `x <- a * x + b'
struct linear_map_coefs_t { int a, b; };

// This is the linear mapping funtion.
// Extracts its data from `data'. 
int linear_map(int x,void *data) { 
  linear_map_coefs_t &coefs 
    = *(linear_map_coefs_t *)data;
  int w = coefs.a*x + coefs.b;
  return w;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Folds a tree from the leaves to the root, i.e.
// after application the value at each node is
// the reduction of the sons values with the
// associative function `assocf'. For instance,
// if `assocf' is the sum function, then each non-leaf
// node gets the sum of the values of the sons.
// `knil' is the neutral (or starting) value for the
// associative function. 
template<class T>
void fold(ktree<T> &A,
	  typename ktree<T>::iterator n,
	  T (*assocf)(T t1,T t2,void *data),
	  T knil,void *data) {
  // Apply only to dereferenciable nodes
  if (n==A.end()) return;

  // Detect first if the node is leaf or not.
  // If it is a leaf, leave. 
  int j, k = A.order();
  for (j=0; j<k; j++) 
    if (n[j] != A.end()) break;
  if (j>=k) return;

  // Computes reduced value of sons by making
  // t = knil
  // t = assocf(t,s0)
  // t = assocf(t,s1)
  // ...
  T t = knil;
  for (j=0; j<k; j++) {
    fold(A,n[j],assocf,knil,data);
    if (n[j] != A.end()) 
      t = assocf(t,*n[j],data);
  }
  // Store reduced value in the node
  *n = t;
}

// Wrapper
template<class T>
void fold(ktree<T> &A, 
	  T (*assocf)(T t1,T t2,void *data),
	  T knil, void *data=NULL) {
  fold(A,A.begin(),assocf,knil,data);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
// Computes a reduced value for all the nodes of the
// tree using associative function `assocf'. 
template<class T>
T reduce(ktree<T> &A,
	    typename ktree<T>::iterator n,
	    T (*assocf)(T t1,T t2,void *data),
	    T knil,void *data) {
  // Apply only to dereferenciable nodes
  if (n==A.end()) return knil;
  
  // Computes reduced value of subtree by making
  // t = knil
  // t = assocf(t,n)
  // t = assocf(t,s0)
  // t = assocf(t,s1)
  // ...
  // where `sj' is the reduced value for subtree
  // of node `j'
  T t = assocf(knil,*n,data);
  int k = A.order();
  for (int j=0; j<k; j++) {
    T u = reduce(A,n[j],assocf,knil,data);
    t = assocf(t,u,data);
  }
  return t;
}

// Wrapper
template<class T>
T reduce(ktree<T> &A,
	 T (*assocf)(T t1,T t2,void *data),
	 T knil,void *data=NULL) {
  return reduce(A,A.begin(),assocf,knil,data);
}

// Associative function for sum
int sum(int x,int y,void *data) {
  return x+y;
}

// Associative function for sum of
// absolute values
int sum_abs(int x,int y,void *data) {
  return abs(x)+abs(y);
}

// Associative function for maximum
int max(int x,int y,void *data) {
  return (x>y ? x : y);
}

// Associative function for maximum
// of absolute values
int max_abs(int x,int y,void *data) {
  int xx = abs(x);
  int yy = abs(y);
  return (xx>yy ? xx : yy);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:
int main() {
  { // Creates dummy scope for checking total
    // destruction of cells.
#if 0
    // Build a simple tree and
    // use operator=. 
    // Tests: insert, p[j], lisp_print(), operator=
    ktree<int> T1(3),T2;
    ktree<int>::iterator p;
    p = T1.insert(T1.begin(),0);
    T1.insert(p[0],1);
    T1.insert(p[1],2);
    T1.insert(p[2],3);
    p = p[0];
    T1.insert(p[0],4);
    T1.insert(p[1],5);
    T1.insert(p[2],6);
    T1.lisp_print();
    printf("\n");

    T2 = T1;
    T2.lisp_print();
    printf("\n");
#endif

#if 1
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
    // Generates N random trees and
    // apply several transformations
    int k=3;
    ktree<int> T(k),R,S,U(k),V,W,W2,
      W3,W4,W5,W6;

    int MAX = 10, N=20;
    printf("max val %d\n",MAX);
    for (int j=0; j<N; j++) {
      make_ktree(T,0.8,MAX,2);
      T.lisp_print("random tree T = ");

      // Tests `find()'
      printf("T has 5: %d\n",(T.find(5)==T.end()));

      // Tests mirror_copy
      mirror_copy(T,R);
      R.lisp_print("R = mirror(T): ");

      // Tests `make_mirror'
      S = T;
      make_mirror(S);
      S.lisp_print("S = mirror(T) in place:");

      // Tests `prune_if'
      V = T;
      int K = 5;
      prune_if(V,my_pred,&K);
      printf("K %d, ",K);
      V.lisp_print("V = T (pruned multiples of K): ");

      // Tests `apply'
      W = T;
      linear_map_coefs_t coefs;
      coefs.b = 0;
      coefs.a = 2;
      apply(W,linear_map,&coefs);
      W.lisp_print("W = 2*T: ");

      W = T;
      coefs.a = 5;
      apply(W,linear_map,&coefs);
      W.lisp_print("W = 5*T: ");

      W2 = T;
      coefs.a = 2;
      coefs.b = -MAX;
      apply(W2,linear_map,&coefs);
      W2.lisp_print("W2 = 2*T - MAX: ");

      // Tests `fold'
      W3 = W2;
      fold(W3,max_abs,0);
      W3.lisp_print("W3 = fold(W2,max_abs): ");

      W4 = W2;
      fold(W4,max,-INT_MAX);
      W4.lisp_print("W4 = fold(W2,max): ");

      W5 = W2;
      fold(W5,sum_abs,0);
      W5.lisp_print("W5 = fold(W2,sum_abs): ");

      W6 = W2;
      fold(W6,sum,0);
      W6.lisp_print("W6 = fold(W2,sum): ");

      // Tests `reduce'
      printf("sum(W2): %d\n",reduce(W2,sum,0));
      printf("sum(|W2|): %d\n",reduce(W2,sum_abs,0));
      printf("max(W2): %d\n",reduce(W2,max,-INT_MAX));
      printf("max(|W2|): %d\n",reduce(W2,max_abs,0));

      printf("================================\n\n\n");
    }
#endif

#if 0
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    // Tests `make_ktree' with a specific generator. 
    ktree<int> X(2);
    int gen=0;
    for (int j=0; j<10; j++) {
      make_ktree(X,0.8,10,2,linear_gen,&gen);
      X.lisp_print("X = generated from linear: ");
    }
#endif
  }
  // Check all cells are destructed
  printf("cells: %d\n",ktree<int>::cell_count());
}
