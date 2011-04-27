bool equal_p (btree &T,iterator_t nt,
	      btree &Q,iterator_t nq) { 
  if (nt==T.end() xor nq==Q.end()) return false;
  if (nt==T.end()) return true;
  if (T.retrieve(nt) != Q.retrieve(nq)) return false;
  return equal_p(T,nt.right(),Q,nq.right()) &&
    equal_p(T,nt.left(),Q,nq.left());
}
bool equal_p(btree &T,btree &Q) { 
  return equal_p(T,T.begin(),Q,Q.begin()); 
}
