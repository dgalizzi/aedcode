int h2(string s) {
  int v = 0;
  for (int j=0; j<s.size(); j++) {
    v += s[j];
    v = v % 256;
  }
  return v;
}
