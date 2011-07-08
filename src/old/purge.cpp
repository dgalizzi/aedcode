void purge(list &L) {
  iterator_t p,q;
  p = L.begin();
  while (p!=L.end()) {
    q = L.next(p);
    while (q!=L.end()) {
      if (L.retrieve(p)==L.retrieve(q)) {
	q = L.erase(q);
      } else {
	q = L.next(q);
      }
    }
    p = L.next(p);
  }
}

int main() {
  list L;
  const int M=10;
  for (int j=0; j<2*M; j++) 
    L.insert(L.end(),irand(M));
  cout << "Lista antes de purgar: " << endl;
  print(L);
  cout << "Purga lista... " << endl;
  purge(L);
  cout << "Lista despues de purgar: " << endl;
  print(L);
}
