bool check_sum(list<int> &L1, list<int> &L2) {
  list<int>::iterator p,q;
  p = L1.begin();
  q = L2.begin();
  int suma = 0;
  while (true) {
    if (q==L2.end()) break;               
    else if (suma==*q) { suma=0; q++; }
    else if (p==L1.end()) break;
    else if (suma<*q) suma += *p++;
    else return false;
  }
  return suma==0 && p==L1.end() && q==L2.end();
}
