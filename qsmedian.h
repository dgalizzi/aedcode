  template<class T>
  int median(typename std::vector<T>::iterator first,
           typename std::vector<T>::iterator last,
           std::vector<T> &dif, int k,
           bool (*comp)(T&,T&)) {
    typename std::vector<T>::iterator 
      q = first;
    int ndif=1; 
    dif[0] = *q++;
    while (q<last) {
      T val = *q++;
      int j;
      for (j=0; j<ndif; j++) 
        // Aca debe compararse por `equivalente'
        // es decir usando comp
        if (!comp(dif[j],val) 
	    && !comp(val,dif[j])) break;
      if (j==ndif) {
        dif[j] = val;
        ndif++;
        if (ndif==k) break;
      }
    }
    typename std::vector<T>::iterator 
      s = dif.begin();
    bubble_sort(s,s+ndif,comp);
    return ndif;
  }
