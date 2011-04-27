void inssort(vector<int> &a) {
  int n=a.size();
  for (int j=1; j<n; j++) {
    int x = a[j];
    int k = j;
    while (--k>=0 && x<a[k]) a[k+1] = a[k];
    a[k+1] = x;
  }
}
