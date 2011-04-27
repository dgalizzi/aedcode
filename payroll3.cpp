  map<int,double> sueldo;
  while(1) {
    cout << "Ingrese nro. documento > ";
    int doc;
    double salario;
    cin >> doc;
    if (!doc) break;
    map<int,double>::iterator q = sueldo.find(doc);
    if (q==sueldo.end()) {
      cout << "Ingrese salario mensual: ";
      cin >> salario;
      sueldo[doc]=salario;
    } else {
      cout << "Doc: " << doc << ", salario: " 
	   << sueldo[doc] << endl;
    }
  }
  cout << "No se ingresan mas sueldos..." << endl;

