// $Id$
/* 
   COMIENZO DE DESCRIPCION 
   Utilitarios varios. 
   keywords: arbol orientado
   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
#include <cstdarg>
#include "./tree.h"
#include "./util_tree.h"

using namespace std;

namespace aed {

  // -----------------------------------------------------------------
  void make_random_tree(tree<int> &T,tree<int>::iterator n,
			int M,int level,int siblings) {
    double lambda = 1.0/(double(siblings)/double(level)+1.0);
    n=T.insert(n,irand(M));
    tree<int>::iterator c=n.lchild();
    while (true) {
      if (drand()<lambda) break;
      make_random_tree(T,c,M,level+1,siblings);
      c=n.lchild();
    }
  }
  // -----------------------------------------------------------------
  void make_random_tree(tree<int> &T,int M,int siblings) {
    make_random_tree(T,T.begin(),M,1,siblings);
  }
  // -----------------------------------------------------------------
  void  print_tree(tree<int> &t,node_t n,string pre,string c) {
    string pres;
    node_t p;
    int es_hoja;
    p=n.lchild();
    es_hoja=(p==t.end());
    cout << pre << "+--" << "(" << * n << ")" << endl;
    if (!es_hoja) cout << pre << c <<  "  |" << endl;
    while (p!=t.end()) {
      pres=pre+c+ "  ";
      if (p.right()!=t.end()) {
        print_tree(t,p++,pres,"|");}
      else { 
        print_tree(t,p++,pres," ");
      }
    }
    if (!es_hoja) cout << pre <<  c << endl;
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  void  print_tree(tree<int> &t) {
    string pre("");
    if (t.begin()!=t.end()) print_tree(t,t.begin(),pre," ");
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  void list2treev(tree<int> &T,int TERM,int BP,
                  int EP,va_list elems) {
    list<int> L;
    add_to_list(L,TERM,elems);
    list2tree(T,L,BP,EP);
  }

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // Load tree from list of node values
  void list2treev(tree<int> &T,int TERM,int BP,int EP,...) {
    va_list elems;
    va_start(elems,EP);
    list2treev(T,TERM,BP,EP,elems);
    va_end(elems);
  }

}
// -------------------------------------------------------------------
