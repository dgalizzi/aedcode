//__INSERT_LICENSE__
// $Id$

/* 
   COMIENZO DE DESCRIPCION

   Multiplicar cuatro matrices de n\'umeros reales 
   {\tt M1 M2 M3 M4}, donde {\tt M1} tiene 
   10 filas y 20 columnas, {\tt M2} es de 20 por 50, {\tt M3} 
   es de 50 por 1 y {\tt M4} es de 1 por 100. Asuma que la 
   multiplicaci\'on de una matriz {\tt A (p,q)} por otra 
   {\tt B (q,r)} requiere {\tt z = p q r} operaciones 
   escalares (que es el n\'umero de operaciones requerido por el
   algoritmo de multiplicaci\'on de matrices). Encuentre
   un orden \'optimo en que se deben multiplicar las 
   matrices para minimizar el n\'umero total de operaciones 
   escalares. Como podria encontrarlo si hay una
   cantidad arbitraria de matrices de dimension arbitraria ?
   keywords: algoritmos

   FIN DE DESCRIPCION 
*/
// -----------------------------------------------------------------
// Ejemplo: al correr ingresar los siguientes datos correspondientes
//          al ejercicio de la Guia 
//           5
//          10 20 50 1 100
// -----------------------------------------------------------------
// GNU:   g++ -v -c matrices.cpp
//        g++ -v -o matrices.exe matrices.o
// INTEL: icc -v -w -c matrices.cpp
//        icc -v -w -o matrices.exe matrices.o
// -----------------------------------------------------------------
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <list>
#include <queue>
using namespace std;

// -----------------------------------------------------------------
typedef list<int> list_e;
typedef queue<int> cola_e;

// -----------------------------------------------------------------
int orden_mul_mat(list_e &indices,cola_e &orden) { 
  list_e::iterator p1,p2,p3;  // indices de los tripletes
  list_e::iterator q,z;        // indice central
  int  costo_min,costo_pan,costo_acu;
  // inicializa iteradores
  p1=indices.begin();
  p2=p1; p2++;
  p3=p2; p3++;

  // inicializa costo total acumulado
  costo_acu=0;

  // recorre la lista de indices remanente
  z=indices.end();
  while (p3!=z) {
    costo_min=LONG_MAX;  // maximo entero representable
    // busca menor producto de tripletes
    cout << " " << endl; 
    cout << "revisa lista remanente" << endl;
    while (p3!=z) {
      costo_pan=(*p1)*(*p2)*(*p3);
      cout << "costo del producto analizado = " << costo_pan << endl;
      if (costo_pan<costo_min) { 
	costo_min=costo_pan;      // recuerda minimo producto
	q=p2;                    // recuerda posicion central
      }
      p1++; p2++; p3++;             // avanza al siguiente triplete
    }
    // acumula al total de operaciones
    costo_acu += costo_min;
    cout << "costo minimo    = " << costo_min << endl;
    cout << "costo acumulado = " << costo_acu << endl;

    orden.push(*q);          // poner indice contraido en la cola
    indices.erase(q);         // saca  indice contraido de la lista
    // reinicializa los iteradores de los tripletes al
    // primer, segundo y tercer elemento de la 
    // lista de indices remanentes
    z=indices.end();
    p1=indices.begin();
    p2=p1; p2++;
    p3=p2; p3++;

  }
  indices.clear();
  return costo_acu;
}

// -----------------------------------------------------------------
int main() {

  list_e indices;
  cola_e orden;
  int n,i,costo_min;
  // lectura datos
  cout << endl; 
  cout << "numero de indices: ? "; cin >> n;
  cout << "lista de indices (no repetidos) : ? ";
  for (int j=0;j<n;j++) {
    cin >> i; 
    indices.push_back(i); 
  }
  // calcula
  cout << endl; 
  cout << "computando ... " << endl;
  costo_min=orden_mul_mat(indices,orden);

  // impresion resultados
  cout << endl;   
  cout << "orden en la multiplicacion: ";
  while (!orden.empty()) { 
    cout << orden.front() << " "; 
    orden.pop( ); 
  }
  cout << endl;
  cout << "costo minimo = " << costo_min << endl;
  cout << " " << endl; 
  return 0;
}
// -----------------------------------------------------------------
