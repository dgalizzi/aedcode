void postorder(tree &T,iterator n,list &L) {
  iterator c = /* hijo mas izquierdo de n ... */;
  while (c != T.end()) {
    postorder(T,c,L);
    c = /* hermano a la derecha de c ... */;
  }
  L.insert(L.end(),/* valor en el nodo `n'... */);
}
