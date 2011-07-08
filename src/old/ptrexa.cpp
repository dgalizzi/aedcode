int *min(int *v,int n) {
  int x = v[0];
  int jmin = 0;
  for (int k=1; k<n; k++) {
    if (v[k]<x) {
      jmin = k;
      x = v[jmin];
    }
  }
  return &v[jmin];
}

void print(int *v,int n) {
  cout << "Vector: (";
  for (int j=0; j<n; j++) cout << v[j] << " ";
  cout << "), valor minimo: " << *min(v,n) << endl;
}

int main() {
  int v[] = {6,5,1,4,2,3};
  int n = 6;

  print(v,n);
  for (int j=0; j<6; j++) {
    *min(v,n) = 2* (*min(v,n));
    print(v,n);
  }
}

