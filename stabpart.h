  template<class T>
  typename std::vector<T>::iterator 
  stable_partition(typename std::vector<T>::iterator first,
              typename std::vector<T>::iterator last,
              bool (*comp)(T&,T&),T &pivot) {
    int size = (last-first);
    if (size==1) return (comp(*first,pivot)? last : first);
    typename std::vector<T>::iterator 
      middle = first + size/2,
      l1, l2;
    l1 = stable_partition(first,middle,comp,pivot);
    l2 = stable_partition(middle,last,comp,pivot);
    range_swap<T>(l1,middle,l2);
    return l1+(l2-middle);
  }                     
