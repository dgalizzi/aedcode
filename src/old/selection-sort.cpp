  template<class T> void
  selection_sort(typename std::vector<T>::iterator first,
		 typename std::vector<T>::iterator last,
		 bool (*comp)(T&,T&)) {
    int size = last-first;
    for (int j=0; j<size-1; j++) {
      typename std::vector<T>::iterator 
	min = first+j,
	q = min++;
      while (q<last) {
	if (comp(*q,*min)) min = q;
	q++;
      }
      T tmp = *(first+j);
      *(first+j) = *min;
      *min = tmp;
    }
  }

  template<class T> void 
  selection_sort(typename std::vector<T>::iterator first,
		 typename std::vector<T>::iterator last) {
    selection_sort(first,last,less<T>);
  }
