cell::cell() : next(list::NULL_CELL) {}

cell *list::cell_space  = NULL;
int list::CELL_SPACE_SIZE = 100;
iterator_t list::NULL_CELL = -1;
iterator_t list::top_free_cell = list::NULL_CELL;

list::list() {
  if (!cell_space) cell_space_init();
  first = last = new_cell();
  cell_space[first].next = NULL_CELL;
}

void list::cell_space_init() {   
  cell_space = new cell[CELL_SPACE_SIZE];
  for (int j=0; j<CELL_SPACE_SIZE-1; j++)
    cell_space[j].next = j+1;
  cell_space[CELL_SPACE_SIZE-1].next = NULL_CELL;
  top_free_cell = 0;
}

iterator_t list::new_cell() {
  iterator_t top = top_free_cell;
  if (top==NULL_CELL) {
    cout << "No hay mas celdas \n";
    abort();
  }
  top_free_cell = cell_space[top_free_cell].next;
  return top;
}

void list::delete_cell(iterator_t c) {
  cell_space[c].next = top_free_cell;
  top_free_cell = c;
}

list::~list() { clear(); }

elem_t &list::retrieve(iterator_t p) { 
  iterator_t q= cell_space[p].next;
  return cell_space[q].elem; 
}

iterator_t list::next(iterator_t p) { 
  return cell_space[p].next; 
}

iterator_t list::prev(iterator_t p) { 
  iterator_t q = first;
  while (cell_space[q].next != p)
    q = cell_space[q].next;
  return q; 
}

iterator_t list::insert(iterator_t p,elem_t k) {
  iterator_t q = cell_space[p].next;
  iterator_t c = new_cell();
  cell_space[p].next = c;
  cell_space[c].next = q;
  cell_space[c].elem = k;
  if (q==NULL_CELL) last = c;
  return p;
}

iterator_t list::begin() { return first; }

iterator_t list::end() { return last; }

iterator_t list::erase(iterator_t p) {
  if (cell_space[p].next == last) last = p;
  iterator_t q = cell_space[p].next;
  cell_space[p].next = cell_space[q].next;
  delete_cell(q);
  return p;
}

iterator_t list::erase(iterator_t p,iterator_t q) {
  if (p==q) return p;
  iterator_t s, r = cell_space[p].next;
  cell_space[p].next = cell_space[q].next;
  if (cell_space[p].next == NULL_CELL) last = p;
  while (r!=cell_space[q].next) {
    s = cell_space[r].next;
    delete_cell(r);
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
  iterator_t c = cell_space[first].next;
  int j=0;
  while (c!=NULL_CELL) { 
    cout << j++ << "(" << c << ") :" << cell_space[c].elem << endl; 
    c = next(c);
  }
}
