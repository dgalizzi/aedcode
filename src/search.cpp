int search(int l,int *a,int n) {
  int j;
  for (j=0; j<n; j++) 
    if (a[j]==l) break;
  return j;
}
