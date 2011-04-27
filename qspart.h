  template<class T>
  typename std::vector<T>::iterator 
  partition(typename std::vector<T>::iterator first,
             typename std::vector<T>::iterator last,
             bool (*comp)(T&,T&),T &pivot) {
    typename std::vector<T>::iterator
      l = first,
      r = last;
    r--;
    while (true) {
      T tmp = *l;
      *l = *r;
      *r = tmp;
      while (comp(*l,pivot)) l++;
      while (!comp(*r,pivot)) r--;
      if (l>r) break;
    }
    return l;
  }                    
