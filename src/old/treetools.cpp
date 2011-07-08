void preorder(tree &T,iterator_t n,list<int> &L) {
  L.insert(L.end(),T.retrieve(n));

  iterator_t c = n.lchild();
  while (c!=T.end()) {
    preorder(T,c,L);
    c = c.right();
  }
}
void preorder(tree &T,list<int> &L) {
  if (T.begin()==T.end()) return;
  preorder(T,T.begin(),L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>
void postorder(tree &T,iterator_t n,list<int> &L) {
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
void lisp_print(tree &T,iterator_t n) {
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
iterator_t tree_copy(tree &T,iterator_t nt,
		     tree &Q,iterator_t nq) { 
  nq = Q.insert(nq,T.retrieve(nt));
  iterator_t 
    ct = nt.lchild(),
    cq = nq.lchild();
  while (ct!=T.end()) {
    cq = tree_copy(T,ct,Q,cq);
    ct = ct.right();
    cq = cq.right();
  }
  return nq;
}

void tree_copy(tree &T,tree &Q) {
  if (T.begin() != T.end()) 
    tree_copy(T,T.begin(),Q,Q.begin());
}

//---:---<*>---:---<*>---:---<*>---:---<*>
iterator_t mirror_copy(tree &T,iterator_t nt,
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
iterator_t prune_odd(tree &T,iterator_t n) {
  if (T.retrieve(n) % 2) n = T.erase(n);
  else {
    iterator_t c = n.lchild();
    while (c != T.end()) c = prune_odd(T,c);
    n = n.right();
  } 
  return n;
}

void prune_odd(tree &T) { 
  if (T.begin() != T.end()) prune_odd(T,T.begin()); 
}
