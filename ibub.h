  template<class T>
  void apply_perm(typename std::vector<T>::iterator first,
                  typename std::vector<T>::iterator last,
                  std::vector<int> &indx) {
    int size = last-first;
    assert(indx.size()==size);
    int sorted = 0;
    T tmp;
    while (sorted<size) {
      if(indx[sorted]!=sorted) {
        int k = sorted;
        tmp = *(first+k);
        while (indx[k]!=sorted) {
          int kk = indx[k];
          *(first+k)=*(first+kk);
          indx[k] = k;
          k = kk;
        }
        *(first+k) = tmp;
        indx[k] = k;
      }
      sorted++;
    }
  }

  template<class T>
  void ibubble_sort(typename std::vector<T>::iterator first,
                   typename std::vector<T>::iterator last,
                   bool (*comp)(T&,T&)) {
    int size = last-first;
    std::vector<int> indx(size);
    for (int j=0; j<size; j++) indx[j] = j;

    for (int j=0; j<size-1; j++) {
      for (int k=size-1; k>j; k--) {
        if (comp(*(first+indx[k]),*(first+indx[k-1]))) {
          int tmp = indx[k-1];
          indx[k-1] = indx[k];
          indx[k] = tmp;
        }
      }
    }
    apply_perm<T>(first,last,indx);
  }                

  template<class T>
  void ibubble_sort(typename std::vector<T>::iterator first,
                   typename std::vector<T>::iterator last) {
   ibubble_sort(first,last,less<T>);
  }                  
