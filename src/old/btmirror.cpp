void mirror(btree &T,iterator_t n) {
  if (n==T.end()) return;
  else {
    btree tmp;
    tmp.splice(tmp.begin(),n.left());
    T.splice(n.left(),n.right());
    T.splice(n.right(),tmp.begin());
    mirror(T,n.right());
    mirror(T,n.left());
  }
}
void mirror(btree &T) { mirror(T,T.begin()); }   
