// $Id$
/* COMIENZO DE DESCRIPCION

Diversas operaciones sobre un Arbol Ordenado Orientado (AOO). 
{\tt todos\_pares(tree<int> \&A)}: verifica si todas las 
etiquetas son pares. 
{\tt bool algun\_par(tree<int> \&A);}:
verifica si alguna de las etiquetas es par. 
{\tt int nodos\_n(tree<int> \&A,int n);} cuenta los nodos 
cuya etiqueta es igual a {\tt n}. 
{\tt int nodos\_mayores\_que(tree<int> \&A, int m);}
cuenta el n\'umero de nodos cuya etiqueta es mayor 
o igual que {\tt m}. [Tomado en el 2do parcial del 27/5/2004].
keywords: arbol orientado

  FIN DE DESCRIPCION */
// -------------------------------------------------------------------
#include <cstdarg>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include "./util.h"
#include "./tree.h"
#include "./util_tree.h"

using namespace aed;
using namespace std;

// -------------------------------------------------------------------
bool todos_pares(tree<int> &A,tree<int>::iterator n) {
  if (*n % 2) return false;
  tree<int>::iterator c = n.lchild();
  while (c!=A.end()) 
    if (!todos_pares(A,c++)) return false;
  return true;
}
bool todos_pares(tree<int> &A) {
  if (A.begin()==A.end()) return true;
  else return todos_pares(A,A.begin());
}

// -------------------------------------------------------------------
bool algun_par(tree<int> &A,tree<int>::iterator n) {
  if (*n % 2==0) return true;
  tree<int>::iterator c = n.lchild();
  while (c!=A.end()) 
    if (algun_par(A,c++)) return true;
  return false;
}
bool algun_par(tree<int> &A) {
  if (A.begin()==A.end()) return false;
  else return algun_par(A,A.begin());
}

// -------------------------------------------------------------------
int nodos_n(tree<int> &A,
	    tree<int>::iterator m,int n) {
  int count=0;
  if (*m==n) count=1;
  tree<int>::iterator c = m.lchild();
  while (c!=A.end()) count += nodos_n(A,c++,n);
  return count;
}
int nodos_n(tree<int> &A,int n) {
  if (A.begin()==A.end()) return 0;
  else return nodos_n(A,A.begin(),n);
}

// -------------------------------------------------------------------
int nodos_mayores_que(tree<int> &A,
		      tree<int>::iterator n,int m) {
  int count=0;
  if (*n>=m) count=1;
  tree<int>::iterator c = n.lchild();
  while (c!=A.end()) 
    count += nodos_mayores_que(A,c++,m);
  return count;
}
int nodos_mayores_que(tree<int> &A,int m) {
  if (A.begin()==A.end()) return 0;
  else return nodos_mayores_que(A,A.begin(),m);
}

// -------------------------------------------------------------------
void longest_path(tree<int> &A,
		  tree<int>::iterator m,list<int> &L) {
  list<int> Laux;
  L.clear();
  tree<int>::iterator c = m.lchild();
  while (c!=A.end()) {
    longest_path(A,c++,Laux);
    if (Laux.size()>L.size()) L = Laux;
  }
  L.insert(L.begin(),*m);
}

void longest_path(tree<int> &A,list<int> &L) {
  L.clear();
  if (A.begin()!=A.end()) longest_path(A,A.begin(),L);
}

// -------------------------------------------------------------------
void all_paths(tree<int> &A,
	       tree<int>::iterator m,list<int> &path,
	       list<list<int> > &path_list) {
  list<int>::iterator q = path.insert(path.end(),*m);
  path_list.insert(path_list.begin(),path);
  tree<int>::iterator c = m.lchild();
  while(c!=A.end()) 
    all_paths(A,c++,path,path_list);
  path.erase(q);
}

void all_paths(tree<int> &A, list<list<int> > &path_list) {
  list<int> path;
  path_list.clear();
  if (A.begin()!=A.end())
    all_paths(A,A.begin(),path,path_list);
}

void longest_path2(tree<int> &A,list<int> &L) {

  list<list<int> > path_list;
  all_paths(A,path_list);

  L.clear();
  if (path_list.size()>0) {
    list<list<int> >::iterator 
      q = path_list.begin(),
      max_length_list_it = q;
    q++;
    while (q!=path_list.end()) {
      if (q->size() > max_length_list_it->size())
	max_length_list_it = q;
      q++;
    }
    L = *max_length_list_it;
  }
}

// -------------------------------------------------------------------
void path_of_largest(tree<int> &A,
		     tree<int>::iterator m,list<int> &L) {
  L.insert(L.end(),*m);
  tree<int>::iterator c = m.lchild(), cmax;
  if (c==A.end()) return;
  cmax = c++;
  while (c!=A.end()) {
    if (*c>*cmax) cmax=c;
    c++;
  }
  path_of_largest(A,cmax,L);
}

void path_of_largest(tree<int> &A,list<int> &L) {
  L.clear();
  if (A.begin()!=A.end()) path_of_largest(A,A.begin(),L);
}

// -------------------------------------------------------------------
bool check_ordprev(tree<int> &T,
                   tree<int>::iterator m,
                   list<int> &L) {
  list<int>::iterator p = L.begin();
  if ((m==T.end()) != (p==L.end())) return false;
  if (m==T.end()) return true;
  if (*m != *p) return false;
  p = L.erase(p);

  tree<int>::iterator c = m.lchild();
  while (c!=T.end() && p!=L.end()) 
    if (!check_ordprev(T,c++,L)) return false;
  
  if (c!=T.end()) return false;
  return true;
}

bool check_ordprev(tree<int> &T, list<int> &L) {
  if (!check_ordprev(T,T.begin(),L)) return false;
  return L.begin()==L.end();
}

// -------------------------------------------------------------------
bool check_ord(tree<int> &T,
               tree<int>::iterator m,
               list<int> &Lprev,list<int>::iterator &pprev,
               list<int> &Lpost,list<int>::iterator &ppost) {
  if ((m==T.end()) != (pprev==Lprev.end())) return false;
  if ((m==T.end()) != (ppost==Lpost.end())) return false;

  if (m==T.end()) return true;
  printf("*m %d, *pprev %d\n",*m,*pprev);
  if (*m != *pprev) return false;

  tree<int>::iterator c = m.lchild(); 
  pprev++;
  while (c!=T.end() && pprev!=Lprev.end() && ppost!=Lpost.end()) {
    if (!check_ord(T,c++,Lprev,pprev,Lpost,ppost)) return false;
  }
  
  printf("*m %d, *ppost %d\n",*m,*ppost);

  if (c!=T.end()) return false;
  if (*m != *ppost) return false;
  ppost++;

  return true;
}

bool check_ord(tree<int> &T, list<int> &Lprev,
               list<int> &Lpost) {
  list<int>::iterator 
    pprev=Lprev.begin(),
    ppost=Lpost.begin();
  if (!check_ord(T,T.begin(),Lprev,pprev,Lpost,ppost)) return false;
  return (pprev==Lprev.end()) && (ppost==Lpost.end());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
tree<int>::iterator max_son_list(tree<int> &T,tree<int>::iterator n,
                                 int &nsons) {
  nsons=0;
  if (n==T.end()) return T.end();
  tree<int>::iterator c = n.lchild();
  if (c==T.end()) return n;
  tree<int>::iterator q;
  int nsonsn = 0;
  while (c!=T.end()) {
    int nsonsc;
    tree<int>::iterator qc
      = max_son_list(T,c,nsonsc);
    if (nsonsc>nsons) {
      nsons = nsonsc;
      q = qc;
    }
    nsonsn++;
    c++;
  }
  if (nsonsn>nsons) {
    nsons = nsonsn;
    q = n;
  } 
  return q;
}

tree<int>::iterator max_son_list(tree<int> &T,int &nsons) {
  return max_son_list(T,T.begin(),nsons);
}

// -------------------------------------------------------------------
int main2() {
  tree<int> A;
  list<int> L;
  int N=6;
  for (int j=0; j<30; j++) {
    A.clear();
    make_random_tree(A,N,2);
    
    cout << "-----------\nA: " << endl;
    print_tree(A);
    cout << "todos pares? > " 
	 << (todos_pares(A) ? "si" : "no") << endl;
    cout << "algun par? > " 
	 << (algun_par(A) ? "si" : "no") << endl;
    for (int j=0; j<=N; j++)
      cout << "nodos con *n==" << j
	   << ":   " << nodos_n(A,j) << endl;
    for (int j=0; j<=N; j++)
      cout << "nodos con *n>=" << j
	   << ":   " << nodos_mayores_que(A,j) << endl;

    longest_path(A,L);
    cout << "longest path: ";
    printl(L);

    longest_path2(A,L);
    cout << "longest path 2: ";
    printl(L);

    path_of_largest(A,L);
    cout << "path of largest: ";
    printl(L);

  }
  cout << endl ;

  cout << "Construir el arbol (3 (4 5 6) (7 8 9))\n";
  tree<int> T;
  tree<int>::iterator p;
  p = T.insert(T.begin(),3);
  p = T.insert(p.lchild(),4);
  p = T.insert(p.lchild(),5);
  p = T.insert(p.right(),6);

  p = T.begin().lchild().right();
  p = T.insert(p,7);
  p = T.insert(p.lchild(),8);
  p = T.insert(p.right(),9);
  print_tree(T);

  cout << "Inserta en nivel 2, 10 antes del 9:  (3 (4 5 6) (7 8 10 9))\n";
  p = T.begin().lchild().right().lchild().right();
  p = T.insert(p,10);
  print_tree(T);

  T.lisp_print();
  list<int> Lprev,Lpost;
  int vlprev[] = {3,4,5,6,7,8,10,9,-1};
  int vlpost[] = {5,6,4,8,10,9,7,3,-1};
  insertl(Lprev,vlprev,-1);
  insertl(Lpost,vlpost,-1);

  cout << "L == ordprev(A) ? " << check_ordprev(T,Lprev) << endl;
  
  Lprev.clear();
  insertl(Lprev,vlprev,-1);
  cout << "Lprev == ordprev(A) && Lpost == ordpost(A) &&  " 
       << check_ord(T,Lprev,Lpost) << endl;

  return 0 ;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main3() {
  tree<int> A;
  make_random_tree(A,100,3);
  // A.lisp_print();
  print_tree(A);
  int maxsons;
  tree<int>::iterator n = max_son_list(A,maxsons);
  printf("\nmaxsons %d, node %d\n",maxsons,*n);
  return 0;
}
