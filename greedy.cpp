void greedy(graph &G, set<int> &no_col,
	    set<int> &nuevo_color,
	    vector<int> &tabla_color,int color) {
  // Asigna a `nuevo_color' un conjunto de vertices
  // de `G' a los cuales puede darse el mismo nuevo color
  // sin entrar en conflicto con los ya coloreados
  nuevo_color.clear();
  set<int>::iterator q;
  for (q=no_col.begin(); q!=no_col.end(); q++) {
    if (/* `*q' no es adyacente a
	   ningun vertice en `nuevo_color' ...  */) {
      // marcar a `*q' como coloreado
      // ...
      // agregar `*q' a `nuevo_color'
      // ...
    }
  }
}

