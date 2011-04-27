//PP>if 0
// $Id: sort.h,v 1.51 2005/06/05 00:00:37 mstorti Exp $
#ifndef AED_SORT_H
#define AED_SORT_H

#include <cstdio>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <aedsrc/util.h>

using namespace std;

namespace aed {
  //PP>endif

  std::vector<int> *w = NULL;
  void print2();

  template<class T>   //L-lesst-b
  bool less(T &x,T &y) {
    return x<y;
  }                   
                      //L-lesst-e
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  bool equivalent(std::vector<int> &v1, std::vector<int> &v2, 
                  bool (*comp)(int&,int&)) {
    bool eq = true;
    for (int j=0; j<v1.size(); j++) {
      // if (v1[j]!=v2[j]) {
      if (comp(v1[j],v2[j]) || comp(v2[j],v1[j])) {
        printf("j %d, v1[j] %d, v2[j] %d\n",j,v1[j],v2[j]);
        eq = false;
      }
    }
    return eq;
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  bool equivalent(std::vector<int> &v1, 
		  std::vector<int> &v2) {
    return equivalent(v1,v2,less<int>);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T> void //L-bubble-sort-b
  bubble_sort(typename std::vector<T>::iterator first,
              typename std::vector<T>::iterator last,
                   bool (*comp)(T&,T&)) {
    // print2(); //S
    int size = last-first;
    for (int j=0; j<size-1; j++) {
      for (int k=size-1; k>j; k--) {         //L-bubsort-bub-b
        if (comp(*(first+k),*(first+k-1))) { //L-bubble-comp
          T tmp = *(first+k-1);             //L-bubble-swap-b
          *(first+k-1) = *(first+k);
          *(first+k) = tmp;                 //L-bubble-swap-e
        }
      }                                     
      // print2(); //L-bubsort-bub-e //S
    }
  }                

  template<class T> void 
  bubble_sort(typename std::vector<T>::iterator first,
              typename std::vector<T>::iterator last) {
    bubble_sort(first,last,less<T>);
  }                  
                        //L-bubble-sort-e

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T> void  //L-insertion-sort-b
  insertion_sort(typename 
                 std::vector<T>::iterator first,
                 typename 
                 std::vector<T>::iterator last,
                 bool (*comp)(T&,T&)) {
    int size = last-first;
    // print2(); //S
    for (int j=1; j<size; j++) {    //L-inssort-ker-b
      T tmp = *(first+j);
      int k=j-1;
      while (true) {                  //L-insertion-swap-b
        if (!comp(tmp,*(first+k))) break;
        // if (comp(*(first+k),tmp)) break;
        *(first+k+1) = *(first+k);
        if (--k < 0) break;
      }                               //L-insertion-swap-e
      *(first+k+1) = tmp;
      // print2(); //S
    }
  }                                 //L-inssort-ker-e
                      //L-insertion-sort-e

  template<class T> void  //L-insertion-sort-w-b
  insertion_sort(typename 
                 std::vector<T>::iterator first,
                 typename 
                 std::vector<T>::iterator last) {
    insertion_sort(first,last,less<T>);
  }
                      //L-insertion-sort-w-e

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T> void //L-selection-sort-b
  selection_sort(typename 
		 std::vector<T>::iterator first,
                 typename 
		 std::vector<T>::iterator last,
                 bool (*comp)(T&,T&)) {
    int size = last-first;
    // print2(); //S
    for (int j=0; j<size-1; j++) { //L-selsort-ker-b
      typename std::vector<T>::iterator 
        min = first+j,
        q = min+1;
      while (q<last) {               //L-ssort-min-b
        if (comp(*q,*min)) min = q;
        q++;
      }                              //L-ssort-min-e
      T tmp = *(first+j);            //L-selsort-swap-b
      *(first+j) = *min;
      *min = tmp;                    //L-selsort-swap-e
      // print2(); //S
    }
  }                                //L-selsort-ker-e
                                   //L-selection-sort-e

  template<class T> void //L-selection-sort-w-b
  selection_sort(typename 
		 std::vector<T>::iterator first,
                 typename 
		 std::vector<T>::iterator last) {
    selection_sort(first,last,less<T>);
  }
                      //L-selection-sort-w-e
  // This is because make_heap is confused with the STL one
  // #define make_heap make_heap_aed
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T> void //L-heap-sort-b
  re_heap(typename std::vector<T>::iterator first,
	  typename std::vector<T>::iterator last,
	  bool (*comp)(T&,T&),int j=0) {
    int size = (last-first);
    T tmp;
    while (true) {
      typename std::vector<T>::iterator
        higher,
        father = first + j,
        l = first + 2*j+1,
        r = l + 1;
      if (l>=last) break; //L-is-leave
      if (r<last) 
        higher = (comp(*l,*r) ? r : l);
      else higher = l;    //L-1son
      if (comp(*father,*higher)) {
        tmp = *higher;
        *higher = *father;
        *father = tmp;
      }
      j = higher - first;
    }
  }

  template<class T> void 
  make_heap(typename std::vector<T>::iterator first,
	    typename std::vector<T>::iterator last,
                 bool (*comp)(T&,T&)) {
    int size = (last-first);
    for (int j=size/2-1; j>=0; j--) 
      re_heap(first,last,comp,j);
  }

  template<class T> void 
  heap_sort(typename std::vector<T>::iterator first,
	    typename std::vector<T>::iterator last,
	    bool (*comp)(T&,T&)) {
    make_heap(first,last,comp);
    typename std::vector<T>::iterator
      heap_last = last;
    T tmp;
    while (heap_last>first) {
      heap_last--;
      tmp = *first;            //L-heap-xc-b
      *first = *heap_last;
      *heap_last = tmp;        //L-heap-xc-e
      re_heap(first,heap_last,comp); //L-heap-rh
    }
  }

  template<class T> void 
  heap_sort(typename std::vector<T>::iterator first,
	    typename std::vector<T>::iterator last) {
    heap_sort(first,last,less<T>);
  }                            //L-heap-sort-e

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 

  template<class T>   //L-ibub-b
  void apply_perm(typename std::vector<T>::iterator first,
                  typename std::vector<T>::iterator last,
                  std::vector<int> &indx) {
    int size = last-first;
    assert(indx.size()==size);
    int sorted = 0;
    T tmp;
    while (sorted<size) {
      if(indx[sorted]!=sorted) {
        int k = sorted;
        tmp = *(first+k);
        while (indx[k]!=sorted) {
          int kk = indx[k];
          *(first+k)=*(first+kk);
          indx[k] = k;
          k = kk;
        }
        *(first+k) = tmp;
        indx[k] = k;
      }
      sorted++;
    }
  }

  template<class T>
  void ibubble_sort(typename std::vector<T>::iterator first,
                   typename std::vector<T>::iterator last,
                   bool (*comp)(T&,T&)) {
    int size = last-first;
    std::vector<int> indx(size);
    for (int j=0; j<size; j++) indx[j] = j;

    for (int j=0; j<size-1; j++) {   //L-ibub-int-b
      for (int k=size-1; k>j; k--) {
        if (comp(*(first+indx[k]),*(first+indx[k-1]))) {
          int tmp = indx[k-1];
          indx[k-1] = indx[k];
          indx[k] = tmp;
        }
      }
    }                               //L-ibub-int-e
    apply_perm<T>(first,last,indx);  //L-perm
  }                

  template<class T>
  void ibubble_sort(typename std::vector<T>::iterator first,
                   typename std::vector<T>::iterator last) {
   ibubble_sort(first,last,less<T>);
  }                  
                           //L-ibub-e
#if 0
  std::vector<int> indx;
  
  template<class T>
  void apply_perm(typename std::vector<T>::iterator first,
                  typename std::vector<T>::iterator last,
                  vector<int> &indx) {
    int size = last-first;
    assert(indx.size()==size);
    int sorted = 0;
    T tmp;
    while (sorted<size) {
      if(indx[sorted]!=sorted) {
        int k = sorted;
        tmp = *(first+k);
        while (indx[k]!=sorted) {
          int kk = indx[k];
          *(first+k)=*(first+kk);
          indx[k] = k;
          k = kk;
        }
        *(first+k) = tmp;
        indx[k] = k;
      }
      sorted++;
    }
  }

  bool (*indirect_comp)(int j,int k) {
    return comp_fun(v[j],v[k]);
  }

  template<class T>
  void ibubble_sort(typename std::vector<T>::iterator first,
                    typename std::vector<T>::iterator last) {
    int size = last-first;
    indx.resize(size);
    for (int j=0; j<size; j++) indx[j]=j;
    bubble_sort(indx.begin(),indx.end(),
                indirect_comp);
    apply_perm(first,last,indx);
    indx.clear();
  }

  template<class T>
  void ibubble_sort(typename std::vector<T>::iterator first,
                   typename std::vector<T>::iterator last) {
    ibubble_sort(first,last,less<T>);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  bool (*iheap_sort_comp)(int &i,int &j);

  template<class T>
  void iheap_sort(typename std::vector<T>::iterator first,
                  typename std::vector<T>::iterator last) {
    int size = last-first;
    std::vector<int> indx(size);
    for (int j=0; j<size; j++) indx[j]=j;
    heap_sort(indx.begin(),indx.end(),iheap_sort_comp);
    int sorted = 0;
    T tmp;
    while (sorted<size) {
      if(indx[sorted]!=sorted) {
        int k = sorted;
        tmp = *(first+k);
        while (indx[k]!=sorted) {
          int kk = indx[k];
          *(first+k)=*(first+kk);
          indx[k] = k;
          k = kk;
        }
        *(first+k) = tmp;
        indx[k] = k;
      }
      sorted++;
    }
  }

  template<class T>
  void iheap_sort(typename std::vector<T>::iterator first,
                   typename std::vector<T>::iterator last) {
    iheap_sort(first,last,less<T>);
  }
#endif

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  int gcd(int m,int n) {   //L-swap-b
    int M,N;
    if (m>n) {
      M=m; N=n;
    } else {
      N=m; M=n;
    }
    while (true) {
      int rest = M % N;
      if (!rest) return N;
      M = N; N= rest;
    }
  }

  template<class T>
  void range_swap(typename std::vector<T>::iterator first,
                  typename std::vector<T>::iterator middle,
                  typename std::vector<T>::iterator last) {
    int 
      n1 = middle-first,
      n2 = last-middle;
    if (!n1 || !n2) return;
    int m = gcd(n1,n2);
    for (int j=0; j<m; j++) {
      T tmp = *(first+j);
      int k2 = j;
      while (true) {
        int k1 = (k2<n2 ? k2+n1 : k2-n2);
        if (k1==j) break;
        *(first+k2) = *(first+k1);
        k2 = k1;
      }
      *(first+k2) = tmp;
    }
  }

  template<class T>     //L-stab-part-b
  typename std::vector<T>::iterator 
  stable_partition(typename std::vector<T>::iterator first,
              typename std::vector<T>::iterator last,
              bool (*comp)(T&,T&),T &pivot) {
    int size = (last-first);
    if (size==1) return (comp(*first,pivot)? last : first);
    typename std::vector<T>::iterator 
      middle = first + size/2,
      l1, l2;
    l1 = stable_partition(first,middle,comp,pivot);
    l2 = stable_partition(middle,last,comp,pivot);
    range_swap<T>(l1,middle,l2);
    return l1+(l2-middle);
  }                     
                             //L-stab-part-e

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void print(std::vector<int>::iterator first,
             std::vector<int>::iterator last) {
    std::vector<int>::iterator q = first;
    while (q<last) std::cout << *q++ << " ";
    std::cout << std::endl;
  }

  void print(std::vector<int> &v) {
    print(v.begin(),v.end());
  }

  void print(const char *s,
             std::vector<int>::iterator first,
             std::vector<int>::iterator last) {
    std::cout << s; print(first,last);
  }

  template<class T>    //L-qs-median
  int median(typename std::vector<T>::iterator first,
           typename std::vector<T>::iterator last,
           std::vector<T> &dif, int k,
           bool (*comp)(T&,T&)) {
    typename std::vector<T>::iterator 
      q = first;
    int ndif=1; 
    dif[0] = *q++;
    while (q<last) {
      T val = *q++;
      int j;
      for (j=0; j<ndif; j++) 
        // Aca debe compararse por `equivalente'
        // es decir usando comp
        if (!comp(dif[j],val) 
	    && !comp(val,dif[j])) break; //L-qs-neq
      if (j==ndif) {
        dif[j] = val;
        ndif++;
        if (ndif==k) break;
      }
    }
    typename std::vector<T>::iterator 
      s = dif.begin();
    bubble_sort(s,s+ndif,comp);
    return ndif;
  }
                       //L-qs-median-e
  template<class T>    //L-partition
  typename std::vector<T>::iterator 
  partition(typename std::vector<T>::iterator first,
             typename std::vector<T>::iterator last,
             bool (*comp)(T&,T&),T &pivot) {
    typename std::vector<T>::iterator
      l = first,
      r = last;
    r--;
    while (true) {   //L-part-loop-b
      T tmp = *l;
      *l = *r;
      *r = tmp;
      while (comp(*l,pivot)) l++;
      while (!comp(*r,pivot)) r--;
      if (l>r) break;
    }                //L-part-loop-e
    return l;
  }                    
                     //L-partition-e
#define partition stable_partition
  template<class T> void //L-qsort
  quick_sort(typename std::vector<T>::iterator first,
	     typename std::vector<T>::iterator last,
	     bool (*comp)(T&,T&)) {
    int size = last-first;
    int max_bub_size = 9;
    if (size<max_bub_size) {
      bubble_sort(first,last,comp);
      return;
    }
    if (size<=1) return;
    int k=3;
    std::vector<T> dif(k);
    int ndif = median(first, last, dif, k, comp);
    if (ndif==1) return;
    T pivot = dif[ndif/2];
    typename std::vector<T>::iterator l;
    l = partition(first,last,comp,pivot);
    quick_sort(first,l,comp);
    quick_sort(l,last,comp);
  }

  template<class T> void 
  quick_sort(typename std::vector<T>::iterator first,
	     typename std::vector<T>::iterator last) {
    quick_sort(first,last,less<T>);
  }
                  //L-qsort-e

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T>
  void print(typename std::vector<T>::iterator first,
             typename std::vector<T>::iterator last,
             int inc) {
    while (first<last) {
      cout << *first << " ";
      first += inc;
    }
    cout << endl;
  }

#define SHELLQ std::queue<T, std::list<T> >
#define dbg
#ifdef dbg
  std::string s;
#endif

  template<class T>
  void shell_flush(typename SHELLQ &Q,
                   typename std::vector<T>::iterator &p,
                   T &w,int inc) {
    while (!Q.empty() && Q.front()<=w) {
      *p = Q.front();
      p += inc;
      Q.pop();
    }
  }

  template<class T>
  void shell_sort(typename std::vector<T>::iterator first,
                  typename std::vector<T>::iterator last,
                  int inc, bool (*comp)(T&,T&),
                  typename SHELLQ &Q) {
    int n = 1+(last-first-1)/inc;
    if (n==1) return;
    typename std::vector<T>::iterator 
      p = first,
      q1 = p,
      q2 = p+inc,
      tmp;
    
#ifdef dbg          //S-b
    cout << s << "vector: ";
    print<T>(first,last,inc);
    cout << s << "stride 1: ";
    print<T>(first,last,2*inc);
    cout << s << "stride 2: ";
    print<T>(first+inc,last,2*inc);
    std::string sc = s;
    s += "   ";
#endif             //S-e
    shell_sort(q1,last,2*inc,comp,Q);
    shell_sort(q2,last,2*inc,comp,Q);

    while (true) {
      if (q1>q2) {
        tmp = q1;
        q1 = q2;
        q2 = tmp;
      }
      if (q2>=last) break;
      if (comp(*q2,*q1)) {
        Q.push(*q2);
        q2 += 2*inc;
      } else {
        Q.push(*q1);
        q1 += 2*inc;
      }
      while(p<q1) {
        *p = Q.front();
        p += inc;
        Q.pop();
      }
    }
    while(q1<last) {
      Q.push(*q1);
      q1 += 2*inc;
    }
    while (!Q.empty()) {
      *p = Q.front();
      p += inc;
      Q.pop();
    }
#ifdef dbg   //S-b
    s = sc;
    cout << s << "vector ordenado: ";
    print<T>(first,last,inc);
#endif       //S-e
  } 

  template<class T>
  void shell_sort(typename std::vector<T>::iterator first,
                  typename std::vector<T>::iterator last,
                  bool (*comp)(T&,T&)) {
    typename SHELLQ Q;
#ifdef dbg    //S-b
    s = "";
#endif        //S-e
    shell_sort(first,last,1,comp,Q);
  }

  template<class T>
  void shell_sort(typename std::vector<T>::iterator first,
                  typename std::vector<T>::iterator last) {
    shell_sort(first,last,less<T>);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T> void //L-merge-sort-b 
  merge_sort(std::list<T> &L,bool (*comp)(T&,T&)) {
    std::list<T> L1,L2;
    if (L.size()==1) return;
    bool flag = true;
    while (!L.empty()) {           //L-ms-split-b
      std::list<T> &LL = (flag ? L1 : L2);
      LL.insert(LL.end(),*L.begin());
      L.erase(L.begin());
      flag = !flag;
    }                              //L-ms-split-e

    merge_sort(L1,comp);
    merge_sort(L2,comp);

    typename std::list<T>::iterator  //L-ms-merge-b
      p1 = L1.begin(),
      p2 = L2.begin();
    while (!L1.empty() && !L2.empty()) {
      std::list<T> &LL = 
        (comp(*L2.begin(),*L1.begin()) ? L2 : L1);  //L-ms-push
      L.insert(L.end(),*LL.begin());
      LL.erase(LL.begin());
    }
    while (!L1.empty()) {
      L.insert(L.end(),*L1.begin());
      L1.erase(L1.begin());
    }
    while (!L2.empty()) {
      L.insert(L.end(),*L2.begin());
      L2.erase(L2.begin());
    }                                //L-ms-merge-e
  }

  template<class T>
  void merge_sort(std::list<T> &L) {
    merge_sort(L,less<T>);
  }     //L-merge-sort-e

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  template<class T>
  void merge2_sort(std::list<T> &L,bool (*comp)(T&,T&)) {
    int size = L.size();   //L-stab-split-b
    if (size==1) return;
    std::list<T> L1,L2;
    int n1 = size/2;
    int n2 = size-n1;
    for (int j=0; j<n1; j++) {
      L1.insert(L1.end(),*L.begin());
      L.erase(L.begin());
    }
    for (int j=0; j<n2; j++) {
      L2.insert(L2.end(),*L.begin());
      L.erase(L.begin());
    }
                           //L-stab-split-e
    merge2_sort(L1,comp);
    merge2_sort(L2,comp);

    typename std::list<T>::iterator
      p1 = L1.begin(),
      p2 = L2.begin();
    while (!L1.empty() && !L2.empty()) {
      std::list<T> &LL = 
        (comp(*L2.begin(),*L1.begin()) ? L2 : L1);
      L.insert(L.end(),*LL.begin());
      LL.erase(LL.begin());
    }
    while (!L1.empty()) {
      L.insert(L.end(),*L1.begin());
      L1.erase(L1.begin());
    }
    while (!L2.empty()) {
      L.insert(L.end(),*L2.begin());
      L2.erase(L2.begin());
    }
  }

  template<class T>
  void merge2_sort(std::list<T> &L) {
    merge2_sort(L,less<T>);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
#define merge_sort merge3_sort
  template<class T> void   //L-merge-sort-vec-b
  merge_sort(typename std::vector<T>::iterator first,
             typename std::vector<T>::iterator last,
             typename std::vector<T> &tmp,
             bool (*comp)(T&,T&)) {
    // print("enter merge3: ",first,last); //S
    int 
      n = last-first;
    if (n==1) return;
    int n1 = n/2, n2 = n-n1;
    typename std::vector<T>::iterator 
      middle = first+n1,
      q = tmp.begin(),
      q1 = first,
      q2 = first+n1;

    merge_sort(first,middle,tmp,comp);
    merge_sort(first+n1,last,tmp,comp);
    
    // print("sorted subsec: ",first,last); //S
    while (q1!=middle && q2!=last) {    //L-merge3-m-b
      if (comp(*q2,*q1)) *q++ = *q2++;
      else *q++ = *q1++;
    }
    while (q1!=middle) *q++ = *q1++;
    while (q2!=last) *q++ = *q2++;      //L-merge3-m-e
    
    q1=first;                           //L-merge3-cpy-b
    q = tmp.begin();
    for (int j=0; j<n; j++) *q1++ = *q++; //L-merge3-cpy-e
    // print("merged and copied: ",first,last); //S
  }

  template<class T> void
  merge_sort(typename std::vector<T>::iterator first,
             typename std::vector<T>::iterator last,
                 bool (*comp)(T&,T&)) {
    std::vector<T> tmp(last-first);   //L-merge3-tmp
    merge_sort(first,last,tmp,comp);
  }

  template<class T> void 
  merge_sort(typename std::vector<T>::iterator first,
                 typename std::vector<T>::iterator last) {
    merge_sort(first,last,less<T>);
  }
                     //L-merge-sort-vec-e
#undef merge_sort
  //PP>if 0
}
// Local Variables: *
// mode: c++ *
// End: *
//PP>endif
#endif
