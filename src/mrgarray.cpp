void merge(vector<int> &a) {
  queue<int> C;
  int n = a.size();
  if (n==0) return;
  if (n % 2) {
    cout << "debe haber un numero par de elementos en el vector\n";
    exit(1);
  }
  int p=0,q=0, minr, maxr;

  print(a,C,p,q);
  while (q<n) {
    if (a[q]<=a[q+1]) {
      minr = a[q];
      maxr = a[q+1];
    } else {
      maxr = a[q];
      minr = a[q+1];
    }
    while (!C.empty() && C.front()<=minr) {
      a[p++] = C.front();
      C.pop();
    }
    a[p++] = minr;
    C.push(maxr);
    q += 2;
    print(a,C,p,q);
  }
  while (!C.empty()) {
    a[p++] = C.front();
    C.pop();
  }
}
