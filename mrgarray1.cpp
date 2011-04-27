void merge(vector<int> &a) {
  int n = a.size();
  // C = cola vacia ...
  int p=0, q=0, minr, maxr;
  while (q<n) {
    // minr = min(a_q,a_{q+1}, maxr = max(a_q,a_{q+1}
    if (a[q]<=a[q+1]) {
      minr = a[q];
      maxr = a[q+1];
    } else {
      maxr = a[q];
      minr = a[q+1];
    }
    // Apendizar todos los elementos del frente de la cola menores que
    // min(a_q,a_{q+1}) al rango [0,p), actualizando eventualmente
    while ( /* C no esta vacia... */) {
      x = /* primer elemento de C ... */;
      if (x>minr) break;
      a[p++] = x;
      // Saca primer elemento de C ...
    }
    a[p++] = minr;
    a[p++] = minr;
    // Apendizar `maxr' al rango [0,p) ...
    q += 2;
  }
  // Apendizar todos los elementos en C menores que
  // min(a_q,a_{q+1}) al rango [0,p)
  // ...
}
