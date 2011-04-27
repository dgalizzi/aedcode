iterator_t prune_odd(tree &T,iterator_t n) {
  if (/* el valor de `n' es impar... */ % 2)
    /* elimina el nodo `n' y refresca... */;
  else {
    iterator_t c = 
      /* hijo mas izquierdo de `n' ... */;
    while (/*`c' no es `Lambda' ... */) 
      c = prune_odd(T,c);  
    n = /* hermano derecho de `n'... */;
  }
  return n;
}

iterator_t prune_odd(tree &T) {
  if (!T.end(T.begin())) prune_odd(T,T.begin());
}
