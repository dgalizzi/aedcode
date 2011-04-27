struct huffman_tree {
  double p;
  btree<int> T;
};

void 
huffman(const vector<double> &prob,btree<int> &T) {
  typedef list<huffman_tree> bosque_t;

  // Contiene todos los arboles
  bosque_t bosque;
  // Numero de caracteres del codigo
  int N = prob.size();
  // Crear los arboles iniciales poniendolos en
  // una lista Los elementos de la lista contienen
  // la probabilidad de cada caracter y un arbol
  // con un solo nodo. Los nodos interiores del
  // arbol tienen un -1 (es solo para
  // consistencia) y las hojas tienen el indice
  // del caracter. (entre 0 y N-1)
  for (int j=0; j<N; j++) {
    // Agrega un nuevo elemento a la lista
    bosque_t::iterator htree = 
      bosque.insert(bosque.begin(),huffman_tree());
    htree->p = prob[j];
    htree->T.insert(htree->T.begin(),j);
  }

  // Aqui empieza el algoritmo de Huffman.
  // Tmp va a contener el arbol combinado
  btree<int> Tmp;
  for (int j=0; j<N-1; j++) {
    // En la raiz de Tmp (que es un nodo interior)
    // ponemos un -1 (esto es solo para chequear).
    Tmp.insert(Tmp.begin(),-1);
    // Tmp_p es la probabilidad del arbol combinado
    // (la suma de las probabilidades de los dos subarboles)
    double Tmp_p = 0.0;
    // Para `k=0' toma el menor y lo pone en el
    // hijo izquierdo de la raiz de Tmp. Para `k=1' en el
    // hijo derecho. 
    for (int k=0; k<2; k++) {
      // recorre el `bosque' (la lista de arboles)
      //  busca el menor. `qmin' es un iterator al menor
      bosque_t::iterator q = bosque.begin(), qmin=q;
      while (q != bosque.end()) {
	if (q->p < qmin->p) qmin = q;
	q++;
      }
      // Asigna a `node' el hijo derecho o izquierdo
      // de la raiz de `Tmp' dependiendo de `k'
      btree<int>::iterator node = Tmp.begin();
      node = (k==0 ? node.left() : node.right());
      // Mueve todo el nodo que esta en `qmin'
      // al nodo correspondiente de `Tmp'
      Tmp.splice(node,qmin->T.begin());
      // Acumula las probabilidades
      Tmp_p += qmin->p;
      // Elimina el arbol correspondiente del bosque. 
      bosque.erase(qmin);
    }
    // Inserta el arbol combinado en el bosque
    bosque_t::iterator r = 
      bosque.insert(bosque.begin(),huffman_tree());
    // Mueve todo el arbol de `Tmp' al nodo
    // recien insertado
    r->T.splice(r->T.begin(),Tmp.begin());
    // Pone la probabilidad en el elemento de la
    // lista
    r->p = Tmp_p;
  }
  // Debe haber quedado 1 solo elemento en la lista
  assert(bosque.size()==1);
  // Mueve todo el arbol que quedo a `T'
  T.clear();
  T.splice(T.begin(),bosque.begin()->T.begin());
}
