int bsearch2(vector<int> &a,int k,int j1, int j2) {
  if (j1==j2-1) {
    if (a[j1]==k) return j1;
    else return j2;
  } else {
    int p = (j1+j2)/2;
    if (k<a[p]) return bsearch2(a,k,j1,p);
    else return bsearch2(a,k,p,j2);
  }
}

int bsearch(vector<int> &a,int k) {
  int n = a.size();
  if (k<a[0]) return 0;
  else return bsearch2(a,k,0,n);
}
