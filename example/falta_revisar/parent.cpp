// $Id$

/*
  COMIENZO DE DESCRIPCION

  Control de par\'entesis en una expresi\'on algebraica usando
  TAD-PILA de caracteres. Por parentizaci\'on en una expresi\'on
  algebraica consideramos \'unicamente los simbolos: par\'entisis, 
  corchetes y llaves.
  keywords: pila

  FIN DE DESCRIPCION
*/

// -----------------------------------------------------------------
//  La cadena leida (caracter a caracter) puede contener otros
//  simbolos. Pero, para el control, prestamos atenci\'on s\'olo 
//  a los caracteres de parentizaci\'on, de los cuales:
// 
//  a) si el simbolo leido es "abierto", entonces se lo almacena a
//     la espera de encontrar un "cerrado";
//
//  b) si el simbolo leido es "cerrado", entonces se determina si el
//     ULTIMO simbolo "abierto" almacenado es del mismo tipo. Si lo
//     son, entonces ambos parentizan correctamente, no hace falta
//     considerarlos ulteriormente, y se prosigue evaluando el resto 
//     de la cadena. Si no lo son, entonces, la cadena estar\'a mal
//     parentizada.
//
//  En consecuencia, el TAD a usar sera tal que "el \'ultimo en 
//  entrar, es el primero en salir", o sea, una PILA.  
// -----------------------------------------------------------------
// GNU:   g++ -c parent.cpp
//        g++ -o parent.exe parent.o
// INTEL: icc -v -c parent.cpp
//        icc -v -o parent.exe parent.o
// -----------------------------------------------------------------
#include <stack>
#include <iostream>
using namespace std;

// -----------------------------------------------------------------
int main() {
  int nax=100;
  char line[nax];
  stack <char> p;
  int n;
  char *t;
  //  while (true) {
    while (!p.empty()) p.pop();
    cout << "Ingrese expresion: > ";
    cin.getline(line,n);
    n=strlen(line);
    t=line;
    while (*t!='\0') {
      if      (*t=='(') p.push( ')');
      else if (*t=='{') p.push('}');
      else if (*t=='[') p.push(']');
      else if (*t==']' || *t=='}' || *t==')') {
	if (!p.empty() && *t==p.top()) p.pop();
	else break;
      } // end if
      t++;
    } // end while
    if (p.empty() && *t=='\0') 
      cout << "Los parentesis matchean bien" << endl;
    else 
      cout << "Los parentesis NO matchean bien" << endl;
    //} // end while 
  cout << endl ;
  return 0 ;
} // end main
// -----------------------------------------------------------------
