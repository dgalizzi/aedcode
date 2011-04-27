void quicksort(w,j1,j2) {
  // Ordena el rango [j1,j2) de `w' 
  if (n==1) return;
  // elegir pivote v ...
  l = partition(w,j1,j2,v);
  quicksort(w,j1,l);
  quicksort(w,l,j2);
}

