bool semejante_p (btree &T,iterator_t nt,
	      btree &Q,iterator_t nq) { 
  if (nt==T.end() xor nq==Q.end()) return false;
  if (nt==T.end()) return true;
  return semejante_p(T,nt.right(),Q,nq.right()) &&
    semejante_p(T,nt.left(),Q,nq.left());
}
bool semejante_p(btree &T,btree &Q) { 
  return semejante_p(T,T.begin(),Q,Q.begin()); 
}
