// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id: btreebtools.h,v 1.4 2004/04/25 04:30:13 mstorti Exp $
#ifndef AED_BTREEBTOOLS_H
#define AED_BTREEBTOOLS_H

#include <aedsrc/btreebas.h>
#include <aedsrc/util.h>
#include <vector>

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  iterator_t
  list2btree(btree &T, iterator_t n,
	     const list<elem_t> &L, 
	     list<elem_t>::const_iterator  &p,
	     elem_t BP,elem_t EP,elem_t NE);

  iterator_t
  list2btree(btree &A,const list<elem_t> &L,elem_t BP,elem_t EP,elem_t NE);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void make_random_btree(btree &T,iterator_t n,
			 int M,int level,double siblings);

  void make_random_btree(btree &T,int M,double siblings);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void 
  node_level_stat(btree &T,iterator_t n,
		  int level,vector<int> &nod_lev);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void node_level_stat(btree &T,vector<int> &nod_lev);

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
  void print_tree(btree &T);

  typedef int (*int_scalar_fun )(int);
  void apply(btree &T,int_scalar_fun f);
}

#endif
