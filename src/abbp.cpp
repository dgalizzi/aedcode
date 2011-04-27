bool abb_p(aed::btree<int> &T,
	   aed::btree<int>::iterator n,int &min,int &max) {
  aed::btree<int>::iterator l,r;
  int minr,maxr,minl,maxl;
  min = +INT_MAX;
  max = -INT_MAX;
  if (n==T.end()) return true;

  l = n.left();
  r = n.right();

  if (!abb_p(T,l,minl,maxl) || maxl>*n) return false;
  if (!abb_p(T,r,minr,maxr) || minr<*n) return false;
  
  min = (l==T.end()? *n : minl);
  max = (r==T.end()? *n : maxr);
  return true;
}

bool abb_p(aed::btree<int> &T) {
  if (T.begin()==T.end()) return false;
  int min,max;
  return abb_p(T,T.begin(),min,max);
}
