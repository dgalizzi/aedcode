void dataflow(vector<set> &gen,
	      vector<set> &kill,
	      vector<set> &defin,
	      vector<set> &defout,
	      vector<set> &ent) {
  int nblock = gen.size();
  bool cambio=true;
  while (cambio) {
    cambio=false;
    for (int j=0; j<nblock; j++) {
      // Calcular la entrada al bloque `defin[j]'
      //    sumando sobre los `defout[m]' que
      //    confluyen al bloque j ...
    }
    int out_prev = defout[j].size();

    cambio=false;
    for (int j=0; j<nblock; j++) {
      // Calcular el nuevo valor de `defout[j]'
      //    usando la ec. de balance de asignaciones... 
      if (defout[j].size() != out_prev) cambio=true;
    }
  }
}
