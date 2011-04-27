  template<class T> void
  quick_sort(typename std::vector<T>::iterator first,
	     typename std::vector<T>::iterator last,
	     bool (*comp)(T&,T&)) {
    int size = last-first;
    int max_bub_size = 9;
    if (size<max_bub_size) {
      bubble_sort(first,last,comp);
      return;
    }
    if (size<=1) return;
    int k=3;
    std::vector<T> dif(k);
    int ndif = median(first, last, dif, k, comp);
    if (ndif==1) return;
    T pivot = dif[ndif/2];
    typename std::vector<T>::iterator l;
    l = partition(first,last,comp,pivot);
    quick_sort(first,l,comp);
    quick_sort(l,last,comp);
  }

  template<class T> void 
  quick_sort(typename std::vector<T>::iterator first,
	     typename std::vector<T>::iterator last) {
    quick_sort(first,last,less<T>);
  }
