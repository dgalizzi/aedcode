void merge_sort(list<block> &L,bool (comp*)(T&,T&)) {
  int n = L.size();
  if (n==1) {
    // ordenar los elementos en el unico bloque de
    // `L' ....
  } else {
    list<T> L1,L2;
    // Separacion: separar L en dos sublistas de
    // tamano similar `L1' y `L2' ...
    int
      n1 = n/2,
      n2 = n-n1;
    list<block>::iterator 
      p = L.begin(),
      q = L1.begin();
    for (int j=0; j<n1; j++) 
      q = L1.insert(q,*p++);

    q = L2.begin();
    for (int j=0; j<n2; j++) 
      q = L2.insert(q,*p++);
    
    // Sort individual: 
    merge_sort(L1,comp);
    merge_sort(L2,comp);

    // Fusion: concatenar las listas
    // `L1' y `L2' en `L' ...
  }
}
