T tmp = w[0];
int k2 = 0;
while (true) {
  int k1 = (k2<n2 ? k2+n1 : k2-n2);
  if (k1==0) break;
  w[k2] = w[k1];
  k2 = k1;
}
w[k2] = tmp;
