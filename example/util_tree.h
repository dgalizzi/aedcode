// $Id: util_tree.h,v 1.10 2006/04/27 21:01:39 mstorti Exp $
/* 
   COMIENZO DE DESCRIPCION 
   Utilitarios varios. 
   keywords: arbol orientado
   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
#ifndef AED_TREETOOLS_H
#define AED_TREETOOLS_H

#include "./util.h"

namespace aed {

  // -------------------------------------------------------------
  template <typename elem_t>
  typename tree<elem_t>::iterator
  list2tree (tree<elem_t> &T,
	    typename tree<elem_t>::iterator n,
	    const list<elem_t> &L,
	    typename list<elem_t>::const_iterator  &p,
	    elem_t BP,elem_t EP) {
    if (*p != BP) n=T.insert(n,*p);
    else {
      typename list<elem_t>::const_iterator q=p; q++;
      assert(*q != BP && *q != EP);
      n = T.insert(n,*q++);
      typename tree<elem_t>::iterator r = n.lchild();
      while (*q != EP) {
	r = list2tree(T,r,L,q,BP,EP);
	r++;
      }
      p=q;
    }
    p++;
    return n;
  }

  // -------------------------------------------------------------
  template <class T>
  typename tree<T>::iterator
  list2tree(tree<T> &A,const list<T> &L,T BP,T EP) {
    typename list<T>::const_iterator p = L.begin();
    return list2tree(A,A.begin(),L,p,BP,EP);
  }

  // -------------------------------------------------------------
  template <class T>
  void tree2list(tree<T> &A,
		 typename tree<T>::iterator n,
		 list<T> &L,T BP,T EP) {
    typedef typename tree<T>::iterator node_t;
    typedef typename list<T>::iterator it;

    if (n==A.end()) return;
    node_t c = n.lchild();
    if (c==A.end()) {
      L.insert(L.end(),*n); 
    } else {
      L.insert(L.end(),BP); 
      L.insert(L.end(),*n); 
      while (c!=A.end()) {
	tree2list(A,c++,L,BP,EP);
      }
      L.insert(L.end(),EP);
    }
  }

  // -------------------------------------------------------------
  template <class T>
  void tree2list(tree<T> &A,list<T> &L,T BP,T EP) {
    tree2list(A,A.begin(),L,BP,EP);
  }

  // -------------------------------------------------------------
  void make_random_tree(tree<int> &T,int M,int siblings);

  // -------------------------------------------------------------
  typedef tree<int> tree_t;
  typedef tree<int>::iterator node_t;
  void print_tree(tree<int> &T,node_t n,string pre,string c);
  void print_tree(tree<int> &T);
  int readnum(string &s, unsigned int &n);
  /*
     La siguiente función NO es a prueba de errores, y asume cierta sintaxis que
     si no se respeta el resultado es indefinido.
     Se asume que:
     - La notación corresponde a un árbol válido.

     - Siempre después de un '(' hay un número. Es decir, después de abrir
     paréntesis, no se puede cerrar un paréntesis, ni tampoco abrir otro.
     Los siguientes strings son inválidos:
     "(1 2 () 3)"
     "(1 2 ((3) 4) 5)"

     - El string no termina con espacios, es decir, el
     siguiente string es inválido:
     "(1 (2 3) 4) "
     Notar que al final hay un espacio.

     - Los enteros están dentro del rango válido del int,
     no hay verificación contra overflow de enteros.
   */
  void lisp2tree(string s, tree<int> &T, unsigned int &i, tree<int>::iterator it);
  void lisp2tree(string s, tree<int> &T);

  void list2treev(tree<int> &T,int TERM,int BP,
                  int EP,va_list elems);

  void list2treev(tree<int> &T,int TERM,int BP,int EP,...);

}
#endif
// ---------------------------------------------------------------
