void greedy(graph &G, int nv,
	    vector<int> &tabla_color) {
  int color=0;
  set<int> nuevo_color, no_col;
  set<int>::iterator q;
  // Inicialmente ponemos todos los vertices en
  // `no_col'
  for (int k=0; k<nv; k++) no_col.insert(k);
  while (1) {
    // Determina a cuales vertices podemos asignar el
    // nuevo color
    greedyc(G,no_col,nuevo_color,
	    tabla_color,color);
    // Saca los vertices que se acaban de colorear
    // (`nuevo_color') de `no_col'
    // ...
    // Detecta el fin del algoritmo cuando ya no hay
    // mas vertices para colorear.
    // ...
    color++;
  }
}

