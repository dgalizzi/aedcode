typedef tree<int> tree_t;
typedef tree_t::iterator node_t;

int count_nodes(tree_t &T,node_t n) {
  if (n==T.end()) return 0;
  int m=1;
  node_t c = n.lchild();
  while(c!=T.end()) m += count_nodes(T,c++);
  return m;
}

int count_nodes(tree_t &T) { 
  return count_nodes(T,T.begin()); 
}
                                              
int height(tree_t &T,node_t n) {
  if (n==T.end()) return -1;
  node_t c = n.lchild();
  if (c==T.end()) return 0;
  int son_max_height = -1;
  while (c!=T.end()) {
    int h = height(T,c);
    if (h>son_max_height) son_max_height = h;
    c++;
  }
  return 1+son_max_height;
}

int height(tree_t &T) { 
  return height(T,T.begin()); 
}

void 
node_level_stat(tree_t &T,node_t n,
		int level,vector<int> &nod_lev) {
  if (n==T.end()) return;
  assert(nod_lev.size()>=level);
  if (nod_lev.size()==level) nod_lev.push_back(0);
  nod_lev[level]++;
  node_t c = n.lchild();
  while (c!=T.end()) {
    node_level_stat(T,c++,level+1,nod_lev);
  }
}

void node_level_stat(tree_t &T,
		     vector<int> &nod_lev) {
  nod_lev.clear();
  node_level_stat(T,T.begin(),0,nod_lev);
  for (int j=0;j<nod_lev.size();j++) {
    cout << "[level: " << j 
	 << ", nodes: " << nod_lev[j] << "]";
  }
  cout << endl;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int max_node(tree_t &T,node_t n) {
  if (n==T.end()) return -1;
  int w = *n;
  node_t c = n.lchild();
  while (c!=T.end()) {
    int ww = max_node(T,c++);
    if (ww > w) w = ww;
  }
  return w;
}

int max_node(tree_t &T) { 
  return max_node(T,T.begin()); 
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int max_leaf(tree_t &T,node_t n) {
  if (n==T.end()) return -1;
  int w = *n;
  node_t c = n.lchild();
  if (c==T.end()) return w;
  w = 0;
  while (c!=T.end()) {
    int ww = max_leaf(T,c++);
    if (ww > w) w = ww;
  }
  return w;
}

int max_leaf(tree_t &T) { 
  return max_leaf(T,T.begin()); 
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int leaf_count(tree_t &T,node_t n) {
  if (n==T.end()) return 0;
  node_t c = n.lchild();
  if (c==T.end()) return 1;
  int w = 0;
  while (c!=T.end()) w += leaf_count(T,c++);
  return w;
}

int leaf_count(tree_t &T) { 
  return leaf_count(T,T.begin()); 
}
