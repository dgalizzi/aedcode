  template<class T> void
  merge_sort(typename std::vector<T>::iterator first,
             typename std::vector<T>::iterator last,
             typename std::vector<T> &tmp,
             bool (*comp)(T&,T&)) {
    int 
      n = last-first;
    if (n==1) return;
    int n1 = n/2, n2 = n-n1;
    typename std::vector<T>::iterator 
      middle = first+n1,
      q = tmp.begin(),
      q1 = first,
      q2 = first+n1;

    merge_sort(first,middle,tmp,comp);
    merge_sort(first+n1,last,tmp,comp);
    
    while (q1!=middle && q2!=last) {
      if (comp(*q2,*q1)) *q++ = *q2++;
      else *q++ = *q1++;
    }
    while (q1!=middle) *q++ = *q1++;
    while (q2!=last) *q++ = *q2++;
    
    q1=first;
    q = tmp.begin();
    for (int j=0; j<n; j++) *q1++ = *q++;
  }

  template<class T> void
  merge_sort(typename std::vector<T>::iterator first,
             typename std::vector<T>::iterator last,
                 bool (*comp)(T&,T&)) {
    std::vector<T> tmp(last-first);
    merge_sort(first,last,tmp,comp);
  }

  template<class T> void 
  merge_sort(typename std::vector<T>::iterator first,
                 typename std::vector<T>::iterator last) {
    merge_sort(first,last,less<T>);
  }
