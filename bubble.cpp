void bubble_sort(vector<int> &a) {
  int n = a.size();
  // Lazo externo. En cada ejecucion de este lazo
  // el elemento j-esimo menor elemento llega a la
  // posicion `a[j]'
  for (int j=0; j<n-1; j++) {
    // Lazo interno. Los elementos consecutivos se
    // van comparando y eventualmente son intercambiados. 
    for (int k=n-1; k>j; k--) {
      if (a[k-1] > a[k]) {
	int tmp = a[k-1];
	a[k-1] = a[k];
	a[k]=tmp;
      }
    }
  }
}

