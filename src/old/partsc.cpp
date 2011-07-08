int partition(w,first,last,v) {
  // Particiona el rango [j1,j2) de `w'
  // con respecto al pivote `v'
  if (n==1) return (w[first]<v ? first : last);
  int middle = (first+last)/2;
  l1 = partition(w,first,middle,v);
  l2 = partition(w,middle,last,v);
  // Intercambia [l1,middle) con [middle,l2)
  swap(l1,middle,l2);
}
