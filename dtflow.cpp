void dataflow(vector<set> &gen,
	      vector<set> &kill,
	      vector<set> &defin,
	      vector<set> &defout,
	      vector<set> &ent) {
  int nblock = gen.size();
  set tmp;
  bool cambio=true;
  while (cambio) {
    for (int j=0; j<nblock; j++) {
      defin[j].clear();
      iterator_t p = ent[j].begin();
      while (p!=ent[j].end()) {
	int k = ent[j].retrieve(p);
	set_union(defin[j],defout[k],tmp);
	defin[j] = tmp;
	p = ent[j].next(p);
      }
    }
    cambio=false;
    for (int j=0; j<nblock; j++) {
      int out_prev = defout[j].size();
      set_union(defin[j],gen[j],tmp);
      set_difference(tmp,kill[j],defout[j]);
      if (defout[j].size()!=out_prev) cambio=true; 
    }
  }
}
