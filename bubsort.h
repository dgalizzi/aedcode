  template<class T> void
  bubble_sort(typename std::vector<T>::iterator first,
              typename std::vector<T>::iterator last,
                   bool (*comp)(T&,T&)) {
    int size = last-first;
    for (int j=0; j<size-1; j++) {
      for (int k=size-1; k>j; k--) {
        if (comp(*(first+k),*(first+k-1))) {
          T tmp = *(first+k-1);
          *(first+k-1) = *(first+k);
          *(first+k) = tmp;
        }
      }                                     
    }
  }                

  template<class T> void 
  bubble_sort(typename std::vector<T>::iterator first,
              typename std::vector<T>::iterator last) {
    bubble_sort(first,last,less<T>);
  }                  
