  const int N=52;
  typedef char elem_t;
  int indx(elem_t c) { 
    if (c>='a' && c<='z') return c-'a'; 
    else if (c>='A' && c<='Z') return 26+c-'A'; 
    else cout << "Elemento fuera de rango!!\n"; abort(); 
  }
  elem_t element(int j) { 
    assert(j<N);
    return (j<26 ? 'a'+j : 'A'+j-26); 
  }
