void preorder(tree &T,iterator n,list &L) {
  L.insert(L.end(),/* valor en el nodo `n'... */);
  iterator c = /* hijo mas izquierdo de n... */;
  while (/* `c' no es `Lambda'... */) {
    preorder(T,c,L);
    c = /* hermano a la derecha de c... */;
  }
}
