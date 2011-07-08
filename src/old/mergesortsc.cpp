void merge_sort(list<T> &L,bool (comp*)(T&,T&)) {
  if (L.size()==1) return;
  list<T> L1,L2;
  // Separacion: separar L en dos sublistas de
  // tamano similar `L1' y `L2' ...
  merge_sort(L1,comp);
  merge_sort(L2,comp);
  // Fusion: concatenar las listas `L1' y `L2' en `L'
