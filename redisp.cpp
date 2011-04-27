  int B=8, k=3, d=5;
  for (int j=2; j<B; j++) {
    int v = 2*d;
    d = (v<B ? v : (v-B)^k);
  }
