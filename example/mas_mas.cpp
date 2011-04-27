// -----------------------------------------------------------------
// INTEL: source /opt/intel_cc_80/bin/iccvars.sh
//        alias icc='/opt/intel_cc_80/bin/icc'
//        icc -w -o  mas_mas.exe mas_mas.cpp
//
// -----------------------------------------------------------------
// GNU:   g++ -w -o  mas_mas.exe mas_mas.cpp
//
// -----------------------------------------------------------------
// PGI:   pgCC -V -o mas_mas.exe mas_mas.cpp
//
// -------------------------------------------------------------------
#include <iostream>
using namespace std;

// -------------------------------------------------------------------
// A) Esta funcion "reproduce" los dos efectos del operador
//    pos-incremento "i++":
//    1) devolver (por referencia) la variable antes 
//       del incremento ;
//    2) como efecto colateral tambien devuelve (por referencia)
//       la variable incrementada.
int  inc_pos (int &i) {
  int viejo = i ;
  i = i + 1 ;
  return viejo ;
}

// -------------------------------------------------------------------
// B) Esta funcion "reproduce" los dos efectos del operador
//    pre-incremento "++i":
//    1) devolver (por referencia) la variable despues
//       del incremento ;
//    2) como efecto colateral tambien devuelve (por referencia) 
//       la variable preincrementada.
int  inc_pre (int &i) {
  i = i + 1 ;
  int viejo = i ;
  return viejo ;
}

// -------------------------------------------------------------------
// C) Version pos-incremento usando una clase definida por el usuario
class mi_int  {
public:
  int A ;
  mi_int &operator = (mi_int I) {
    A = I.A ;
    return *this;
  }
  mi_int operator ++ (int) {
    mi_int Q = *this;
    A++ ;
    return Q;
  }
} ;

// -------------------------------------------------------------------
int main () {

  int     i, j, k ;
  mi_int  I, J, K ;

  cout << endl ;
  cout << "pos-incremento: " << endl ;

  j = 5 ;
  i = j ;
  k = j++;
  cout << " i = " << i   << "  k = " << k   << "  j = " << j   << endl ;

  j = 5 ;
  i = j ;
  k = inc_pos (j);
  cout << " i = " << i   << "  k = " << k   << "  j = " << j   << endl ;

  J.A = 5;
  I = J ;
  K = J++;
  cout << " I = " << I.A << "  k = " << K.A << "  j = " << J.A << endl ;

  cout << endl ;
  cout << "pre-incremento: " << endl ;

  j = 5 ; 
  i = j ;
  k = ++j;
  cout << " i = " << i   << "  k = " << k   << "  j = " << j  << endl ;

  j = 5 ;
  i = j ;
  k = inc_pre (j);
  cout << " i = " << i   << "  k = " << k   << "  j = " << j  << endl ;

  cout << endl ;
  return 0 ;
} // end main
// -------------------------------------------------------------------
