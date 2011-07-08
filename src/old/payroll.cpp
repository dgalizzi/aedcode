//__INSERT_LICENSE__
// $Id: payroll-pp.cpp,v 1.2 2004/07/19 03:01:09 mstorti Exp $

#include <map>
#include <iostream>

using namespace std;

int main() {
  map<int,double> sueldo;
  while(1) {
    cout << "Ingrese nro. documento > ";
    int doc;
    double salario;
    cin >> doc;
    map<int,double>::iterator q = sueldo.find(doc);
    if (q==sueldo.end()) {
      cout << "Ingrese salario mensual: ";
      cin >> salario;
      sueldo[doc] = salario;
    } else {
      cout << "Doc: " << doc << ", salario: " << q->second << endl;
    }
  }
}
