// $Id$

/*
  COMIENZO DE DESCRIPCION

  Dada una lista de enteros {\tt L} y dos listas {\tt SEQ} y 
  {\tt REEMP} escribir una funci\'on {\tt 
  void reemplaza (list<int> \&L, list<int> \&SEQ, list<int> \&REEMP)}  
  que busca todas las secuencias de {\tt SEQ} en {\tt L} y las 
  reemplaza por {\tt REEMP}. Por ejemplo, si 
  L=(1 2 3 4 5 1 2 3 4 5 1 2 3 4 5), SEQ=(4 5 1) y REEMP=(9 7 3), 
  entonces despues de llamar a {\tt reemplaza} debe quedar
  L=(1 2 3 9 7 3 2 3 9 7 3 2 3 4 5). Este procedimiento tiene 
  un efecto equivalente a la funci\'on {\tt reemplazar} de los 
  editores de texto.
  [Tomado el 1er parcial, 16 abril 2002]
  keywords: lista

  FIN DE DESCRIPCION
*/
// -----------------------------------------------------------------
/* SOlUCION:

  Se sugiere el siguiente algoritmo. Recorrer la lista L con la
  posicion P y la SEQ con la posicion Q, hasta que P llegue al fin
  de L. En todo momento se mantiene una cola C con los ultimos
  elementos de L que coinciden con los de SEQ.  En el siguiente 
  paso se pueden dar tres posibilidades:

  1) Si llegamos al fin de SEQ, entonces toda la lista SEQ estaba
  en L y, por lo tanto, insertamos la lista REEMP en la posicion 
  P de L. Tambien vaciamos la cola C;

  2) Si el elemento en Q es igual al que esta en P entonces
  suprimimos el elemento de L y lo ponemos en la cola C. 
  Tambien avanzamos la posicion Q en REEMP;

  3) Si el elemento en Q no es igual al que esta en P, entonces
  insertamos toda la cola C en la lista L en la posicion P y 
  reseteamos la posicion Q al principio de SEQ.
 */
// -----------------------------------------------------------------
// GNU:   g++ -w -c util.cpp
//        g++ -w -c reemplaza.cpp
//        g++ -w -o reemplaza.exe util.o reemplaza.o
// INTEL: icc -w -c util.cpp
//        icc -w -c reemplaza.cpp
//        icc -w -o reemplaza.exe util.o reemplaza.o
// -----------------------------------------------------------------
#include <list>
#include <queue>
#include <iostream>
#include "./util.h"
using namespace std;

// -----------------------------------------------------------------
void reemplaza1 (list <int> & L, 
                 list <int> & SEQ, 
                 list <int> & REEMP)  {
  queue<int> C ;
  list<int> :: iterator p, q, r;
  list<int> H ;
  // copia REEMP en la lista auxiliar H
  H.clear ();
  r = REEMP.begin () ;
  while (r != REEMP.end () ) { H.insert (H.begin (),*r) ; r++ ; }
  // Inicializa posiciones
  p =   L.begin ();
  q = SEQ.begin ();
  // recorre lista L
  while ( p != L.end() ) {
    if ( q == SEQ.end () ) {    
      // 1) llegamos al fin de SEQ pues todo SEQ esta en la lista L
      //    vaciamos la cola C
      while ( !C.empty () ) C.pop ();
      //    insertamos REEMP en la lista L
      r = H.begin () ;
      while (r != H.end () ) { p = L.insert (p++,*r); r++ ; }
      // reseteamos la posicion Q en la lista SEQ
      q = SEQ.begin ();    } 
    else if (*p == *q) {
      // 2) Hay otro elemento en la lista L igual al de SEQ
      //    por lo que lo ponemos en la cola C 
      C.push (*p) ;
      //    lo suprimimos en L y avanzamos en SEQ
      p = L.erase (p);      
      q++ ;            } 
    else {
      // 3) los elementos no son iguales 
      while ( !C.empty () ) {
	p = L.insert ( p, C.front () );
	C.pop ();
	p++;
      } // end while
      p++;
    } // end if
  } // while
  while ( !C.empty() ) {
    p = L.insert ( p, C.front () );
    C.pop ();
    p++;
  } // end while
}

// -----------------------------------------------------------------
// Variante sin el uso de una cola
// Pero, como siempre, sin usar el operador "--"
//
// Se recorre mientras no sea fin de la lista L con el iterador P y, 
// cada vez que aparezca el primer elemento de SEQ, se la registra
// con la posicion auxiliar Q. Luego copiamos P en T, y vamos 
// avanzando T y Q simultaneamente mientras, o bien no lleguemos
// al final de L o de SEQ, o bien cuando no esta todo SEQ en el 
// tramo analizado. Si toda la secuencia SEQ se encontro en ese 
// tramo, entonces inicializamos T en Q (en donde empezaba SEQ)
// y R en comienzo de REEMP. Vamos suprimiendo el elemento de L 
// apuntado por T, insertamos el apuntado por R y avanzamos T y R.
// Finalmente actualizamos P (el cual recorre L actual) y seguimos
// explorando.
void reemplaza2 ( list <int> & L, 
                  list <int> & SEQ, 
                  list <int> & REEMP){
  list <int> :: iterator p, q, r, t;
  bool esta ; 
  p = L.begin ();
  while ( p != L.end () ) {
    r = SEQ.begin () ;
    q = p ;       // recordamos donde empezaria (quizas) SEQ en L
    t = p ;       // inicializamos T en P
    esta = true ; // somos optimistas
    while ( r != SEQ.end () && t != L.end () ) {
      if  ( *r == *t ) { // seguimos encontrando SEQ en L
        r++ ;
        t++ ; }
      else {
        esta = false ;   // la secuencia SEQ es incompleta
        break ;
      } // end if
    } // end while
    if (esta == true) {
      r = REEMP.begin (); 
      t = q ;              // inicia en el lugar donde empezo SEQ
      while ( r != REEMP.end () ) { // borra e inserta
        t = L.erase (t) ;  // suprimimos y actualizamos
        L.insert (t, *r) ; // inserta un elemento de SEQ en L
        r++ ;              // avanzo en SEQ
      } // end  while  
      p = t ;              // actualizo iterador del lazo principal
    } // end if
    p++ ;                  // avanzo
  } // end while
} // end void

// -----------------------------------------------------------------
int main () {
  list<int> L, SEQ, REEMP;
  int v [] = {8,4,5,1,2,3,4,5,9,1,-1};
  int s [] = {4,5,1,-1};
  int r [] = {9,7,3,-1};

  // 1ra variante
  cout << endl ; 
  cout << "1ra variante: usando una cola auxiliar" << endl ;

  L.clear(); insertl (L, v, -1); 
  SEQ.clear(); insertl(SEQ, s, -1);
  REEMP.clear(); insertl(REEMP, r ,-1);
  cout << "L    : "; printl (L);
  cout << "SEQ  : "; printl (SEQ);
  cout << "REEMP: "; printl (REEMP);
  reemplaza1 (L, SEQ, REEMP);
  cout << "reemplaza1: "; printl (L);

  // 2da variante
  cout << endl ; 
  cout << "2da variante: recordando donde empieza SEQ " << endl ;
  L.clear(); insertl(L, v, -1); 
  SEQ.clear(); insertl(SEQ, s, -1);
  REEMP.clear (); insertl (REEMP, r ,-1);
  cout << "L    : "; printl (L);
  cout << "SEQ  : "; printl (SEQ);
  cout << "REEMP: "; printl (REEMP);
  reemplaza2 (L, SEQ, REEMP);
  cout << "reemplaza2: "; printl (L);

  cout << endl ;
  return 0 ;
} // end main
// -----------------------------------------------------------------
