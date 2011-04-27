class graph {
private:
  const int nv;
  vector<int> g;
public:
  // Constructor a partir del numero de vertices
  graph(int nv_a) : nv(nv_a) { g.resize(nv*nv,0); }
  // Este metodo permite acceder a una arista tanto para 
  // agregar la arista (`g.edge(i,j)=1') como para
  // consultar un valor particular de la
  // arista. (`adyacente = g.edge(i,j)') 
  int &edge(int j,int k) { 
    if (k<=j) return g[nv*j+k]; 
    else return g[nv*k+j]; 
  }
};

