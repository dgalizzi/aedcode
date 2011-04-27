  map sueldo;
  while(1) {
    cout << "Ingrese nro. documento > ";
    int doc;
    double salario;
    cin >> doc;
    if(!doc) break;
    iterator_t q = sueldo.find(doc);
    if (q==sueldo.end()) {
      cout << "Ingrese salario mensual: ";
      cin >> salario;
      sueldo.insert(doc,salario);
      cout << sueldo.size() <<  " salarios cargados" << endl;
    } else {
      cout << "Doc: " << doc << ", salario: " 
	   << sueldo.retrieve(doc) << endl;
    }
  }
  cout << "No se ingresan mas sueldos..." << endl;

