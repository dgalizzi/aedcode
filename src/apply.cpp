  template<class T>
  void apply(btree<T> &Q,
	     typename btree<T>::iterator n,
	     T(*f)(T)) {
    if (n==Q.end()) return;
    *n = f(*n);
    apply(Q,n.left(),f);
    apply(Q,n.right(),f);
  }
  template<class T>
  void apply(btree<T> &Q,T(*f)(T)) {
    apply(Q,Q.begin(),f); 
