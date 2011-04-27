char tolower(char c) {
  if (c>='A' && c<='Z') c += 'a'-'A';
  return c;
}

bool string_less_ci(const string &a,
		    const string &b) { 
  int na = a.size();
  int nb = b.size();
  int n = (na>nb ? nb : na);
  for (int j=0; j<n; j++) {
    char 
      aa = tolower(a[j]),
      bb = tolower(b[j]);
    if (aa < bb) return true; 
    else if (bb < aa) return false; 
  }
  return na<nb;
}
