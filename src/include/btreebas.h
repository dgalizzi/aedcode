  typedef int elem_t;      
  class cell;
  class iterator_t;

  class cell {
    friend class btree;
    friend class iterator_t;
    elem_t t;
    cell *right,*left;
    cell() : right(NULL), left(NULL)  {}
  };

  class iterator_t {
  private:
    friend class btree;
    cell *ptr,*father;
    enum side_t {NONE,R,L};
    side_t side;
    iterator_t(cell *p,side_t side_a,cell *f_a)
      : ptr(p), side(side_a), father(f_a) { }

  public:
    iterator_t(const iterator_t &q) {
      ptr = q.ptr;
      side = q.side;
      father = q.father;
    }
    bool operator!=(iterator_t q) { return ptr!=q.ptr; }
    bool operator==(iterator_t q) { return ptr==q.ptr; }
    iterator_t() : ptr(NULL), side(NONE),

		   father(NULL) { }

    iterator_t left() { 
      return iterator_t(ptr->left,L,ptr); 
    }
    iterator_t right() { 
      return iterator_t(ptr->right,R,ptr); 
    }
  };

  class btree {
  private:
    cell *header;
    iterator_t tree_copy_aux(iterator_t nq,
			   btree &TT,iterator_t nt) {
      nq = insert(nq,TT.retrieve(nt));
      iterator_t m = nt.left();
      if (m != TT.end()) tree_copy_aux(nq.left(),TT,m);
      m = nt.right();
      if (m != TT.end()) tree_copy_aux(nq.right(),TT,m);
      return nq;
    }
  public:
    static int cell_count_m;
    static int cell_count() { return cell_count_m; }
    btree() {
      header = new cell;
      cell_count_m++;
      header->right = NULL;
      header->left = NULL;
    }
    btree(const btree &TT) {
      if (&TT != this) {
	header = new cell;
	cell_count_m++;
	header->right = NULL;
	header->left = NULL;
	btree &TTT = (btree &) TT;
	if (TTT.begin()!=TTT.end()) 
	  tree_copy_aux(begin(),TTT,TTT.begin()); 
      }
    }
    ~btree() { clear(); delete header; cell_count_m--; } 
    elem_t & retrieve(iterator_t p) { return p.ptr->t; }
    iterator_t insert(iterator_t p,elem_t t) {
      cell *c = new cell;
      cell_count_m++;
      c->t = t;
      if (p.side == iterator_t::R)      
	p.father->right = c;
      else p.father->left = c;
      p.ptr = c;
      return p;
    }
    iterator_t erase(iterator_t p) {
      if(p==end()) return p;
      erase(p.right());
      erase(p.left());
      if (p.side == iterator_t::R) 
	p.father->right = NULL;
      else p.father->left = NULL;
      delete p.ptr;
      cell_count_m--;
      p.ptr = NULL;
      return p;
    }

    iterator_t splice(iterator_t to,iterator_t from) {
      cell *c = from.ptr;
      from.ptr = NULL;
      if (from.side == iterator_t::R) 
	from.father->right = NULL;
      else 
	from.father->left = NULL;
      if (to.side == iterator_t::R) to.father->right = c;
      else to.father->left = c;
      to.ptr = c;
      return to;
    }
    iterator_t find(elem_t t) { return find(t,begin()); }
    iterator_t find(elem_t t,iterator_t p) {
      if(p==end() || p.ptr->t == t) return p;
      iterator_t l = find(t,p.left());
      if (l!=end()) return l;
      iterator_t r = find(t,p.right());
      if (r!=end()) return r;
      return end();
    }
    void clear() { erase(begin()); }
    iterator_t begin() { 
      return iterator_t(header->left,
			iterator_t::L,header); 
    }
    iterator_t end() { return iterator_t(); }

    void lisp_print(iterator_t n) {
      if (n==end()) { cout << "."; return; }
      iterator_t r = n.right(), l = n.left();
      bool is_leaf = r==end() && l==end();
      if (is_leaf) cout << retrieve(n);
      else {
	cout << "(" << retrieve(n) << " ";
	lisp_print(l);
	cout << " ";
	lisp_print(r);
	cout << ")";
      }
    }
    void lisp_print() { lisp_print(begin()); }
  };
