struct huf_exh_data {
  btree_t best;
  double best_code_len;
  const vector<double> *prob;
};

void min_code_len(btree_t &T,void *data) { 
  huf_exh_data *hp = (huf_exh_data *)data;
  double l = codelen(T,*(hp->prob));
  if (l < hp->best_code_len) {
    hp->best_code_len = l;
    hp->best = T;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void 
huffman_exh(const vector<double> &prob,btree_t &T) {
  int nchar = prob.size();
  list_t L;
  pos_t p;
  huf_exh_data h;
  h.prob = &prob;
  h.best_code_len = DBL_MAX;
  for (int j=0; j<nchar; j++) {
    p = L.insert(L.end(),btree_t());
    p->insert(p->begin(),j);
  }
  comb(L,&min_code_len,&h);
  T.clear();
  T.splice(T.begin(),h.best.begin());
}
