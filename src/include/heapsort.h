  template<class T> void
  re_heap(typename std::vector<T>::iterator first,
	  typename std::vector<T>::iterator last,
	  bool (*comp)(T&,T&),int j=0) {
    int size = (last-first);
    T tmp;
    while (true) {
      typename std::vector<T>::iterator
        higher,
        father = first + j,
        l = first + 2*j+1,
        r = l + 1;
      if (l>=last) break;
      if (r<last) 
        higher = (comp(*l,*r) ? r : l);
      else higher = l;
      if (comp(*father,*higher)) {
        tmp = *higher;
        *higher = *father;
        *father = tmp;
      }
      j = higher - first;
    }
  }

  template<class T> void 
  make_heap(typename std::vector<T>::iterator first,
	    typename std::vector<T>::iterator last,
                 bool (*comp)(T&,T&)) {
    int size = (last-first);
    for (int j=size/2-1; j>=0; j--) 
      re_heap(first,last,comp,j);
  }

  template<class T> void 
  heap_sort(typename std::vector<T>::iterator first,
	    typename std::vector<T>::iterator last,
	    bool (*comp)(T&,T&)) {
    make_heap(first,last,comp);
    typename std::vector<T>::iterator
      heap_last = last;
    T tmp;
    while (heap_last>first) {
      heap_last--;
      tmp = *first;
      *first = *heap_last;
      *heap_last = tmp;
      re_heap(first,heap_last,comp);
    }
  }

  template<class T> void 
  heap_sort(typename std::vector<T>::iterator first,
	    typename std::vector<T>::iterator last) {
    heap_sort(first,last,less<T>);
