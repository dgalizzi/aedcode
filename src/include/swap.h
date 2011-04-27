  int gcd(int m,int n) {
    int M,N;
    if (m>n) {
      M=m; N=n;
    } else {
      N=m; M=n;
    }
    while (true) {
      int rest = M % N;
      if (!rest) return N;
      M = N; N= rest;
    }
  }

  template<class T>
  void range_swap(typename std::vector<T>::iterator first,
                  typename std::vector<T>::iterator middle,
                  typename std::vector<T>::iterator last) {
    int 
      n1 = middle-first,
      n2 = last-middle;
    if (!n1 || !n2) return;
    int m = gcd(n1,n2);
    for (int j=0; j<m; j++) {
      T tmp = *(first+j);
      int k2 = j;
      while (true) {
        int k1 = (k2<n2 ? k2+n1 : k2-n2);
        if (k1==j) break;
        *(first+k2) = *(first+k1);
        k2 = k1;
      }
      *(first+k2) = tmp;
    }
  }
