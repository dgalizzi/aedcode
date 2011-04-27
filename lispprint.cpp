void lisp_print(tree &T,iterator n) {
  iterator c = /* hijo mas izquierdo de n ... */;
  if (/* `c' es `Lambda'... */) {
    cout << /* valor en el nodo `n'... */;
  } else {
    cout << "(" << /* valor de `n' ... */;
    while (/* `c' no es `Lambda'... */) {
      cout << " ";
      lisp_print(T,c);
      c = /* hermano derecho de c ... */;
    }
    cout << ")";
  }
}
