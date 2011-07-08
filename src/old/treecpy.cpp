iterator tree_copy(tree &T,iterator nt,
		   tree &Q,iterator nq) {
  nq = /* nodo resultante de insertar el
	  elemento de `nt' en `nq' ... */; 
  iterator 
    ct = /* hijo mas izquierdo de `nt' ...*/, 
    cq = /* hijo mas izquierdo de `nq' ...*/;
  while (/* `ct' no es `Lambda'... */) {
    cq = tree_copy(T,ct,Q,cq);
    ct = /* hermano derecho de `ct'... */;
    cq = /* hermano derecho de `cq'... */;
  }
  return nq;
}
