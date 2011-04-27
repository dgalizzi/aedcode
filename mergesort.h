  template<class T> void
  merge_sort(std::list<T> &L,bool (*comp)(T&,T&)) {
    std::list<T> L1,L2;
    if (L.size()==1) return;
    bool flag = true;
    while (!L.empty()) {
      std::list<T> &LL = (flag ? L1 : L2);
      LL.insert(LL.end(),*L.begin());
      L.erase(L.begin());
      flag = !flag;
    }

    merge_sort(L1,comp);
    merge_sort(L2,comp);

    typename std::list<T>::iterator
      p1 = L1.begin(),
      p2 = L2.begin();
    while (!L1.empty() && !L2.empty()) {
      std::list<T> &LL = 
        (comp(*L2.begin(),*L1.begin()) ? L2 : L1);
      L.insert(L.end(),*LL.begin());
      LL.erase(LL.begin());
    }
    while (!L1.empty()) {
      L.insert(L.end(),*L1.begin());
      L1.erase(L1.begin());
    }
    while (!L2.empty()) {
      L.insert(L.end(),*L2.begin());
      L2.erase(L2.begin());
    }
  }

  template<class T>
  void merge_sort(std::list<T> &L) {
    merge_sort(L,less<T>);
