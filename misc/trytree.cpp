//__INSERT_LICENSE__
// $Id: trytree.cpp,v 1.13 2004/04/11 21:11:08 mstorti Exp $

#include <aedsrc/tree.h>
#include <list>
#include <cstdio>

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
typedef list<int>::const_iterator it;
typedef tree<int>::iterator node;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
node make_tree(tree<int> &T,node n,
	       const list<int> &L1,it L1_b,it L1_e,
	       const list<int> &L2,it L2_b,it L2_e) {
  // Range is void
  if (L1_b==L1_e) return node();
  // Insert root of subtree
  n = T.insert(n,*L1_b);
  // Loop over sons of `n' 
  // Get subtree range
  it p1,q1,p2,q2;
  node r = n.lchild();
  // `p1' contains first lchild of `n'
  p1 = L1_b; p1++; q1 = p1;
  p2 = L2_b; q2 = p2;
  while (p1 != L1_e) {
    // [p2,q2) will contain subtree of `q2' in post-order
    // Find lchild `q2'
    // printf("Looking for range of subtree rooted at %d\n",*p1);
    int n = 0;
    // printf("range in L2 is [p2,q2): ");
    while (1) {
      assert(q2!=L2.end());
      assert(q2!=L2_e);
      n++;
      // printf("%d ",*q2);
      if (*q2==*p1) break;
      q2++;
    }
    q2++; 
    // printf("\n");
    // [p2,q2) contains subtree of `q2'
    // Find `q1' by advancing p1 `n' times
    // printf("range in L1 is [p1,q1): ");
    for (int j=0; j<n; j++) {
      //      printf("%d ",*q1);
      q1++;
    }
    // printf("\n");
    r = make_tree(T,r,L1,p1,q1,L1,p2,q2);
    // Update p1,p2
    p1 = q1;
    p2 = q2;
    r++;
  }
  // Last element in range of L1 should be equal to root at `n'
  assert(*q2 == *L1_b);
  return n;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
node make_tree(tree<int> &T,const list<int> &L1,
	       const list<int> &L2) {
  return make_tree(T,T.begin(),
		   L1,L1.begin(),L1.end(),
		   L2,L2.begin(),L2.end());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
node list2tree(tree<int> &T,node n,
	       const list<int> &L,it &p,int BP,int EP) {
  if (*p != BP) n = T.insert(n,*p);
  else {
    it q = p; q++;
    assert(*q != BP && *q != EP);
    n = T.insert(n,*q++);
    node r = n.lchild();
    while (*q != EP) {
      r = list2tree(T,r,L,q,BP,EP);
      r++;
    }
    p = q;
  }
  p++;
  return n;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
node list2tree(tree<int> &T,const list<int> &L,int BP,int EP) {
  it p = L.begin();
  return list2tree(T,T.begin(),L,p,BP,EP);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int main() {
  tree<int> T;
  list<int> L;
  const int BP=-2,EP=-1;
#if 1
  int N = 13;
  int l[]={BP,5,BP,6,8,9,EP,BP,7,10,11,EP,EP};
#else
  int N = 6;
  int l[]={BP,5,6,7,8,EP};
#endif
  L.insert(L.begin(),l,l+N);
  list2tree(T,L,BP,EP);
  T.print_prev();
  T.print_post();

  cout << "After splicing...\n";
  T.splice(T.find(6),T.find(7));
  T.print_prev();
  T.print_post();

#if 0
  tree<int> T;
  list<int> L1,L2;
  int N = 7;
  int l1[]={5,6,8,9,7,10,11};
  int l2[]={8,9,6,10,11,7,5};
  L1.insert(L1.begin(),l1,l1+N);
  L2.insert(L2.begin(),l2,l2+N);
  make_tree(T,L1,L2);
  T.print_prev();
  T.print_post();
#endif
#if 0
  int j=0;
  while (1) {
    j++;
    bool print = !(j % 1000000);
    if (print) cout << "On iter " << j <<endl;
#if 1
    tree<int>::iterator p5,p6,p7,p8,p9,p10,p11;
    p5 = T.insert(T.begin(),5);
    p6 = T.insert(p5.lchild(),6);
    p7 = p6.right();
    p7 = T.insert(p7,7);
    p8 = T.insert(p6.lchild(),8);
    p9 = p8.right();
    p9 = T.insert(p9,9);
    p10 = T.insert(p7.lchild(),10);
    p11 = p10.right();
    p11 = T.insert(p11,11);
#else
    T.insert(T.begin(),5);
    T.insert(T.find(5).lchild(),6);
    T.insert(T.find(6).right(),7);
    T.insert(T.find(6).lchild(),8);
    T.insert(T.find(8).right(),9);
    T.insert(T.find(7).lchild(),10);
    T.insert(T.find(10).right(),11);
#endif

    if (print) {
      cout << "preorder; " << endl;
      T.print_prev();
      cout << "postorder; " << endl;
      T.print_post();
    }

    T.erase(T.find(7));
    if (print) {
      cout << "Borra subarbol de 7\n";
      cout << "preorder; " << endl;
      T.print_prev();
      cout << "postorder; " << endl;
      T.print_post();
    }

    T.erase(T.begin());
    if (print) {
      cout << "Borra todo\n";
      cout << "preorder; " << endl;
      T.print_prev();
      cout << "postorder; " << endl;
      T.print_post();
    }
  }
#endif
}
