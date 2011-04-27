  template<class T> void
  insertion_sort(typename 
                 std::vector<T>::iterator first,
                 typename 
                 std::vector<T>::iterator last,
                 bool (*comp)(T&,T&)) {
    int size = last-first;
    for (int j=1; j<size; j++) {
      T tmp = *(first+j);
      int k=j-1;
      while (true) {
        if (!comp(tmp,*(first+k))) break;
        // if (comp(*(first+k),tmp)) break;
        *(first+k+1) = *(first+k);
        if (--k < 0) break;
      }
      *(first+k+1) = tmp;
    }
  }
