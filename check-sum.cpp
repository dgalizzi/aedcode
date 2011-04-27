bool check_sum(list &L1, list &L2) {
  iterator_t p,q;
  p = L1.begin();
  q = L2.begin();
  int suma = 0;
  while (true) {
    if (q==L2.end()) break;               
    else if (suma==L2.retrieve(q)) {
      suma=0; 
      q = L2.next(q);
    }   
    else if (p==L1.end()) break;
    else if (suma<L2.retrieve(q)) {
      suma += L1.retrieve(p);
      p = L1.next(p);                     
    }
    else return false;
  }
  return suma==0 && p==L1.end() && q==L2.end();
}
