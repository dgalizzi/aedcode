  class tree;
  class iterator_t;

  //---:---<*>---:---<*>---:---<*>---:---<*>
  class cell {
    friend class tree;
    friend class iterator_t;
    elem_t elem;
    cell *right, *left_child;
    cell() : right(NULL), left_child(NULL) {}
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>
  class iterator_t {
  private:
    friend class tree;
    cell *ptr,*prev,*father;
    iterator_t(cell *p,cell *prev_a, cell *f_a) 
      : ptr(p), prev(prev_a), father(f_a) { }
  public:
    iterator_t(const iterator_t &q) {
      ptr = q.ptr;
      prev = q.prev; 
      father = q.father;
    }
    bool operator!=(iterator_t q) { return ptr!=q.ptr; }
    bool operator==(iterator_t q) { return ptr==q.ptr; }
    iterator_t() 
      : ptr(NULL), prev(NULL), father(NULL) { }

    iterator_t lchild() {
      return iterator_t(ptr->left_child,NULL,ptr); 
    }
    iterator_t right() { 
      return iterator_t(ptr->right,ptr,father); 
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>
  class tree {
  private:
    cell *header;
    tree(const tree &T) {}
  public:

    tree() {
      header = new cell;
      header->right = NULL;
      header->left_child = NULL;
    }
    ~tree() { clear(); delete header; }

    elem_t &retrieve(iterator_t p) {
      return p.ptr->elem; 
    }  

    iterator_t insert(iterator_t p,elem_t elem) {
      assert(!(p.father==header && p.ptr));
      cell *c = new cell;
      c->right = p.ptr;
      c->elem = elem;
      p.ptr = c;
      if (p.prev) p.prev->right = c;
      else p.father->left_child = c;	
      return p;
    }
    iterator_t erase(iterator_t p) {
      if(p==end()) return p;
      iterator_t c = p.lchild();
      while (c!=end()) c = erase(c);
      cell *q = p.ptr;
      p.ptr = p.ptr->right;
      if (p.prev) p.prev->right = p.ptr;
      else p.father->left_child = p.ptr;
      delete q;
      return p;
    }

    iterator_t splice(iterator_t to,iterator_t from) {
      assert(!(to.father==header && to.ptr));
      cell *c = from.ptr;

      if (from.prev) from.prev->right = c->right;
      else from.father->left_child = c->right;

      c->right = to.ptr;
      to.ptr = c;
      if (to.prev) to.prev->right = c;
      else to.father->left_child = c;

      return to;
    }

    iterator_t find(elem_t elem) {
      return find(elem,begin()); 
    }
    iterator_t find(elem_t elem,iterator_t p) {
      if(p==end() || retrieve(p) == elem) return p;
      iterator_t q,c = p.lchild();
      while (c!=end()) {
	q = find(elem,c);
	if (q!=end()) return q;
	else c = c.right();
      }
      return iterator_t();
    }
    void clear() { erase(begin()); }
    iterator_t begin() { 
      return iterator_t(header->left_child,NULL,header); 
    }
    iterator_t end() { return iterator_t(); }    

