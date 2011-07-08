void greedyc(graph &G, set<int> &no_col,
	     set<int> &nuevo_color,
	     vector<int> &tabla_color,int color) {
  // Asigna a `nuevo_color' un conjunto de vertices
  // de `G' a los cuales puede darse el mismo nuevo color
  // sin entrar en conflicto con los ya coloreados
  nuevo_color.clear();
  set<int>::iterator q,w;
  for (q=no_col.begin(); q!=no_col.end(); q++) {
    int adyacente=0;
    for (w=nuevo_color.begin(); 
	 w!=nuevo_color.end(); w++) {
      if (G.edge(*q,*w)) {
	adyacente = 1;
	break;
      }
    }
    if (!adyacente) {                         
      // marcar a `*q' como coloreado
      tabla_color[*q] = color;
      // agregar `*q' a `nuevo_color'
      nuevo_color.insert(*q);
    }
  }
}

