// $Id: util_btree.h,v 1.9 2005/05/18 13:43:41 jdelia Exp $
/* 
   COMIENZO DE DESCRIPCION 
   Utilitarios varios. 
   keywords: arbol binario
   FIN DE DESCRIPCION 
*/
// -------------------------------------------------------------------
#ifndef AED_BTREETOOLS_H
#define AED_BTREETOOLS_H
#include "./btree.h"
#include "./util.h"
#include <vector>

namespace aed {
  // -----------------------------------------------------------------
  template <typename elem_t>
  typename btree<elem_t>::iterator
  list2btree(btree<elem_t> &T,
	      typename btree<elem_t>::iterator n,
	      const list<elem_t> &L,
	      typename list<elem_t>::const_iterator &p,
	      elem_t BP,elem_t EP,elem_t NE) {
    typename list<elem_t>::const_iterator q;
    if (*p==NE) { }
    else if (*p!=BP) {
      n=T.insert(n,*p);}
    else {
      q=p;q++;
      assert(*q!=BP && *q!=EP && *q!=NE);
      n=T.insert(n,*q++);
      list2btree(T,n.left(),L,q,BP,EP,NE);
      list2btree(T,n.right(),L,q,BP,EP,NE);
      p=q;
    }
    p++;
    return n;
  }
  // -----------------------------------------------------------------
  template <class T>
  typename btree<T>::iterator list2btree(btree<T> &A,const list<T> &L,
              T BP,T EP,T NE) {
    typename list <T>::const_iterator p;
    p=L.begin();
    return (list2btree(A,A.begin(),L,p,BP,EP,NE));
  }
  // -----------------------------------------------------------------
  void make_random_btree(btree<int> &t,btree<int>::iterator n,
			 int m,int level,double siblings);
  // -----------------------------------------------------------------
  void make_random_btree(btree<int> &t,int m,double siblings);
  // -----------------------------------------------------------------
  void node_level_stat(btree<int> &t,btree<int>::iterator n,
		        int level,vector<int> &nod_lev);
  // -----------------------------------------------------------------
  void node_level_stat (btree<int> &t,vector<int> &nod_lev);

  // -----------------------------------------------------------------
  template <class T>
  void apply (btree <T> &Q,typename btree<T>::iterator n,T (*f)(T)) {
    if (n==Q.end()) return;
    *n=f(*n) ;
    apply(Q,n.left(),f);
    apply(Q,n.right(),f);
  }
  // -----------------------------------------------------------------
  template <class T>
  void apply(btree<T> &Q,T (*f)(T)) {
    apply(Q,Q.begin(),f); 
  }

} // namespace
#endif
