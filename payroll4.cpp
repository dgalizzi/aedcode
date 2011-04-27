  // declarar `tabla_sueldos' como `map' ...
  while(1) {
    cout << "Ingrese nro. documento > ";
    int doc;
    double sueldo;
    cin >> doc;
    if (!doc) break;
    if (/* No tiene `doc' sueldo asignado?... */) {
      cout << "Ingrese sueldo mensual: ";
      cin >> sueldo;
      // Asignar `doc -> sueldo'
      // ...
    } else {
      // Reportar el valor almacenado
      // en `tabla_sueldos'
      // ...
      cout << "Doc: " << doc << ", sueldo: " 
	   << sueldo << endl;
    }
  }
  cout << "No se ingresan mas sueldos..." << endl;

