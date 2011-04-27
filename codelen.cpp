double codelen(btree_t &T,node_t n,
	       const vector<double> &prob,double &w) {
  if (n.left()==T.end()) {
    w = prob[*n];;
    return 0.;
  } else {
    double wl,wr,lr,ll;
    ll = codelen(T,n.left(),prob,wl);
    lr = codelen(T,n.right(),prob,wr);
    w = wr+wl;
    return wl+wr+ll+lr;
  }
}

double codelen(btree_t &T,
	       const vector<double> &prob) {
  double ww;
  return codelen(T,T.begin(),prob,ww);
}
