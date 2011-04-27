list::list() : first(new cell), last(first) {
  first->next = NULL;
}

list::~list() { clear(); delete first; }

elem_t &list::retrieve(iterator_t p) { 
  return p->next->elem; 
}

iterator_t list::next(iterator_t p) { 
  return p->next; 
}

iterator_t list::prev(iterator_t p) {
  iterator_t q = first;
  while (q->next != p) q = q->next;
  return q; 
}

iterator_t
list::insert(iterator_t p,elem_t k) {  
  iterator_t q = p->next;
  iterator_t c = new cell;
  p->next = c;
  c->next = q;
  c->elem = k;
  if (q==NULL) last = c;
  return p;
}

iterator_t list::begin() { return first; }

iterator_t list::end() { return last; }

iterator_t list::erase(iterator_t p) {
  if (p->next==last) last = p;
  iterator_t q = p->next;
  p->next = q->next;
  delete q;
  return p;
}

iterator_t list::erase(iterator_t p,iterator_t q) {
  if (p==q) return p;
  iterator_t s, r = p->next;
  p->next = q->next;
  if (!p->next) last = p;
  while (r!=q->next) {
    s = r->next;
    delete r;
    r = s;
  }
  return p;
}

void list::clear() { erase(begin(),end()); }

void list::print() {
  iterator_t p = begin();
  while (p!=end()) {
    cout << retrieve(p) << " ";
    p = next(p);
  }
  cout << endl;
}

void list::printd() {
  cout << "h(" << first << ")" << endl;
  iterator_t c = first->next;
  int j=0;
  while (c!=NULL) { 
    cout << j++ << "(" << c << ") :" << c->elem << endl; 
    c = c->next;
  }
}
        
int list::size() {
  int sz = 0;
  iterator_t p = begin();
  while (p!=end()) {
    sz++;
    p = next(p);
  }
  return sz;
}
