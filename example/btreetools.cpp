// -*- mode: c++ -*-
//__INSERT_LICENSE__
// $Id$
/* 
   COMIENZO DE DESCRIPCION 
   Utilitarios varios. 
   keywords: arbol binario
   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
#include <vector>
#include "./util.h"
#include "./btreetools.h"

namespace aed {

// -----------------------------------------------------------------
void make_random_btree (btree <int>           & t, 
                        btree <int> :: iterator n,
                        int                     m,
                        int                     level,
                        double                  siblings) {
  btree <int> :: iterator c ;
  double lambda, nivel ;
  n     = t.insert (n, irand (m) );
  nivel = double (level);
  lambda = 1.0 / ( siblings / nivel + 1.0 );
  for (int j = 0 ; j < 2 ; j++) {
    if  ( j == 0 ) {
      c = n.left () ; }
    else {
      c = n.right () ;
    } // end if
    if ( drand () > lambda) {
      make_random_btree (t, c, m, level+1, siblings);
    } // end if
  } // end for
} // end void

// -----------------------------------------------------------------
void make_random_btree ( btree <int> & t,
                         int           m,
                         double        siblings) {
  t.clear ();
  make_random_btree (t, t.begin (), m, 0, siblings);
} // end void

// -----------------------------------------------------------------
void node_level_stat ( btree <int>           & t,
                       btree <int> :: iterator n,
                       int                     level,
                       vector <int>          & nod_lev) {
  if ( n == t.end () ) return ;
  assert (nod_lev.size () >= level );
  if (nod_lev.size () == level) nod_lev.push_back (0) ;
  nod_lev [level]++ ;
  node_level_stat (t, n.left  (), level+1, nod_lev);
  node_level_stat (t, n.right (), level+1, nod_lev);
} // end void

// -----------------------------------------------------------------
void node_level_stat ( btree  <int> & t,
                       vector <int> & nod_lev) {
  nod_lev.clear ();
  node_level_stat (t, t.begin (), 0, nod_lev);
  cout << "level/#nodes: ";
  for (int j = 0 ; j < nod_lev.size () ; j++) {
     cout << j << "/" << nod_lev [j] << ", " ;
  } // end for
  cout << endl;
} // end void

// -----------------------------------------------------------------
} // end namespace

// -----------------------------------------------------------------
