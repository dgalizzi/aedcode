void purge(list &L) {                     //L-code-b
  iterator_t p,q;
  p = L.begin();                          //L-assign-p
  while (p!=L.end()) {                    //L-cond-loop-p
    q = L.next(p);                        //L-assign-q
    while (q!=L.end()) {
      if (L.retrieve(p)==L.retrieve(q)) { //L-compare
	q = L.erase(q);                   //L-erase-q
      } else {
	q = L.next(q);
      }
    }
    p = L.next(p);                        //L-next-p
  }
}

void purge(list &L) {
  iterator_t p,q;
  p = L.begin();                          //L-assign-p
  while (p!=L.end()) {                    //L-cond-loop-p
    q = L.next(p);                        //L-assign-q
    while (q!=L.end()) {
      if (L.retrieve(p)==L.retrieve(q)) { //L-compare
	q = L.erase(q);                   //L-erase-q
      } else {
	q = L.next(q);
      }
    }
    p = L.next(p);                        //L-next-p
  }
}
                                          //L-code-e
