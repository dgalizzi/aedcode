bool string_less_cs(const string &a,const string &b) {
  int na = a.size();
  int nb = b.size();
  int n = (na>nb ? nb : na);
  for (int j=0; j<n; j++) {
    if (a[j] < b[j]) return true;
    else if (b[j] < a[j]) return false;
  }
  return na<nb;
}
