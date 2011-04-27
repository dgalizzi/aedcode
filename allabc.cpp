typedef void (*traverse_tree_fun) (btree_t &T, void *data);

typedef list< btree<int> > list_t;
typedef list_t::iterator pos_t;

void comb(list_t &L,traverse_tree_fun f,void *data=NULL) {
  if (L.size()==1) {
    f(*L.begin(),data);
    return;
  } 
  int n=L.size();
  for (int j=0; j<n-1; j++) {
    for (int k=j+1; k<n; k++) {
      btree_t T;
      T.insert(T.begin(),-1);
      node_t m = T.begin();

      pos_t pk=L.begin();
      for (int kk=0; kk<k; kk++) pk++;
      T.splice(m.left(),pk->begin());
      L.erase(pk);

      pos_t pj=L.begin();
      for (int jj=0; jj<j; jj++) pj++;
      T.splice(m.right(),pj->begin());
      L.erase(pj);

      pos_t p = L.insert(L.begin(),btree_t());
      p->splice(p->begin(),T.begin());

      comb(L,f,data);

      p = L.begin();
      m = T.splice(T.begin(),p->begin());
      L.erase(p);

      pj=L.begin();
      for (int jj=0; jj<j; jj++) pj++;
      pj = L.insert(pj,btree_t());
      pj->splice(pj->begin(),m.right());
	
      pk=L.begin();
      for (int kk=0; kk<k; kk++) pk++;
      pk = L.insert(pk,btree_t());
      pk->splice(pk->begin(),m.left());

    }
  }
}
