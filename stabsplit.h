    int size = L.size();
    if (size==1) return;
    std::list<T> L1,L2;
    int n1 = size/2;
    int n2 = size-n1;
    for (int j=0; j<n1; j++) {
      L1.insert(L1.end(),*L.begin());
      L.erase(L.begin());
    }
    for (int j=0; j<n2; j++) {
      L2.insert(L2.end(),*L.begin());
      L.erase(L.begin());
    }
