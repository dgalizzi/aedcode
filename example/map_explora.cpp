// $Id$
/* COMIENZO DE DESCRIPCION 

  __USE_WIKI__
  Consigna: usando las operaciones de los TAD lista, mapeo y cola, 
  escribir un procedimiento 
  #void map_explora(vector<list<int> > &V, map<int,int> &M)#, 
  en el cual, dada una red de #n# computadoras representada por un 
  vector de listas de enteros #V#, construya dicho mapeo #M#.
  keywords: lista, cola, correspondencia

  FIN DE DESCRIPCION */

/* 
   Considere una red de $n$ computadoras enumeradas $ i=0,1,...(n-1) $ 
   las cuales pueden estar conectadas entre si de diversas maneras. 
   Dicha informaci\'on de la interconexi\'on se la puede almacenar 
   mediante un vector de $ n $ listas cuyos elementos son los enteros 
   $ [0, n) $ que designan a cada computadora. Cada sublista $ V_i $ 
   enumera las primeras "vecinas" de la computadora $ i $, para 
   $ 0 \le i < n $. Por ejemplo, supongamos que el vector de listas
   $ V = [ v_0, v_1, v_2, v_3, v_4, v_5, v_6, v_7, v_8, v_9 ]$, 
   de las 10 computadoras enumeradas entre 0 y 9 es:
   $ V=[ (6), (8), (7), (6), (8), (7), (0,3), (2,5,9), (1,4,9), (7)] $.
   Por ejemplo, las primeras vecinas de las computadoras 7 y 8 son
   son (2,5,9) y (1,4,9), respectivamente. Si hacemos un dibujo de 
   la red resultante (ver programa demo) observaremos que hay dos
   subredes, a saber, la subred 1 conformada por las computadoras 
   G1 = (0,3,6) y la subred 2 conformada por las computadoras 
   G2 = (1,2,4,5,7,8,9). Ver otro ejemplo en el programa demo.
   Entonces, dado un vector de listas $ V $ que representa una 
   red posiblemente desconexa interesa identificar todas las 
   subredes que pueda contener. Esta tarea se puede resolver 
   construyendo la correspondencia $ M = M (X,Y) $ que mapea del 
   dominio $ X=[0,n) $ de las computadoras presentes en la red, al 
   rango $ Y = [1, g_{max}] $ de las subredes posibles. 
   Un algoritmo que ejecuta esta tarea se resume en el programa demo.
   Consigna: usando las operaciones de los TAD lista, mapeo y cola, 
   escribir un procedimiento {\tt 
   void map\_explora (vector < list <int> > \& V, map <int,int> \& M)
   }
   en el cual, dada una red de $n$ computadoras representada por un 
   vector de listas de enteros {\tt V}, construya dicho mapeo $ M $.
   keywords: lista, cola, correspondencia 
*/

// -----------------------------------------------------------------
// Considere una red de $n$ computadoras (o PC's) 
// numeradas $i=0,1,...(n-1)$ las cuales pueden estar conectadas 
// entre si de diversas maneras.
// 
// Ejemplo 1: supongamos $ n = 10 $ computadoras interconectadas de 
// la siguiente manera
// 
//                       x 4
//                       |
//                       |
//      x 0       1 x----x 8
//       \               |
//        \              |
//         x 6           x 9
//        /              |
//       /               |
//      x 3       2 x----x 7
//                       |
//                       |
//                       x 5
// 
// esta informaci\'on ``topol\'ogica'' se la puede almacenar mediante 
// el vector 
// 
//        v_0  v_1  v_2  v_3  v_4  v_5  v_6  v_7  v_8  v_9  
//   V = ( 6 ,  8 ,  7 ,  6  , 8  , 7  , 0  , 2  , 1  , 7 ) 
//                                       |    |    |    |
//                                       3    5    4    8
//                                            |    |     
//                                            9    9     
// 
// de $ n $ listas cuyos elementos son los enteros $ [0, n) $ que 
// designan a cada computadora. Cada sublista $ V_i $ enumera las 
// primeras "vecinas" de la computadora $ i $, para $ 0 \le i < n $. 
// En este ejemplo, las primeras vecinas de cada una son:
// 
// vecinas (0) = (6);
// vecinas (1) = (8);
// vecinas (2) = (7);
// vecinas (3) = (6);
// vecinas (4) = (8);
// vecinas (5) = (7);
// vecinas (6) = (0,3);
// vecinas (7) = (2,5,9);
// vecinas (8) = (1,4,9);
// vecinas (9) = (7,8);
//   
// en este caso observamos que hay 2 subredes, a saber:
// 
// . subred 1: conformada por computadoras G1 = (0,3,6)
// . subred 2: conformada por computadoras G2 = (1,2,4,5,7,8,9)
// 
// Ejemplo 2: consideremos ahora a las $ n = 10 $ computadoras 
// interconectadas de la siguiente manera:
//                          
//                x--------x--------x
//              2 |\      /| 1        9
//                | \    / |
//                |  \  /  |
//                |   \/   |
//                |   x\ 4 |
//                |     \  |
//                |      \ |
//                |       \|
//     8 x--------x 3      x 6
//               /|       /|
//              / |      / |
//             /  |     /  |
//            /   |    /   |
//           /    |   /    |
//          /     |  /     |
//         /      | /      |
//     0  /     5 |/       | 7
//       x--------x--------x  
// 
// cuya representaci\'on mediante un vector de listas es:
// 
//         v_0 v_1  v_2  v_3  v_4  v_5  v_6  v_7  v_8  v_9) 
//   V = ( 3    2    1    0    1    0    1    5    3    1  )
//         |    |    |    |    |    |    |    |
//         5    4    3    2    2    3    4    6
//              |    |    |    |    |    |
//              6    4    5    6    6    5    
//              |         |         |    |
//              9         8         7    7
// 
// ahora las primeras vecinas de cada computadora son
// 
// vecinas (0) = (3,5);
// vecinas (1) = (2,4,6,8);
// vecinas (2) = (1,3,4);
// vecinas (3) = (0,2,5,8);
// vecinas (4) = (1,2,6);
// vecinas (5) = (0,3,6,7);
// vecinas (6) = (1,4,5,7);
// vecinas (7) = (5,6);
// vecinas (8) = (3);
// vecinas (9) = (1);
// 
// en este  caso hay una unica red definida por 
// G1 = (0,1,2,3,4,5,6,7,8,9).
// 
// 
// 
// Entonces, dado un vector de listas $ V $ que representa una 
// red posiblemente desconexa interesa identificar todas las 
// subredes que pueda contener.
// 
// Esta tarea se puede resolver construyendo la correspondencia
// $ M = M (X,Y) $ que mapea del dominio $ X=[0,n) $ de las 
// computadoras presentes en la red, al rango $ Y = [1, g_{max}] $ 
// de las subredes posibles. 
// 
// Un algoritmo que ejecuta esta tarea puede ser el siguiente:
// 
// comenzar
//   inicializar contador de subred $ g = 1 $
//   para cada computadora $ i=0,1,...,n-1 $ hacer
//     si el tamanio del mapeo $ M (0..n-1,1..g_{max}) $ es $n$ 
//        entonces fin (pues ya estan todos revisadas)
//     averiguar si la computadora $ i $ ya estaba en el mapeo $ M $
//     si no estaba entonces
//       asignarla a la subred $ g $ 
//       encolarla en la cola $ Q $
//     fin si
//     mientras la cola $ Q $ no este vacia iterar
//       descolamos una computadora $ k $
//       para cada posicion valida $ p $ en la sublista $ V_k $ hacer
//         recuperar la computadora $ j $ en la posicion $ p $;
//         averiguar si $ j $ ya estaba en el mapeo $ M $;
//         si no estaba entonces
//            asignarla en el mapeo $ M [j] = g $
//            encolarla para luego revisarla
//         fin si
//       fin para
//     fin mientras
//     incrementar g en 1
//   fin para $i$
// fin
// -----------------------------------------------------------------
// INTEL: icc -w -c map_explora.cpp
//        icc -w -o map_explora.exe map_explora.o
//
// GNU:   g++ -w -c map_explora.cpp
//        g++ -w -o map_explora.exe map_explora.o
//
// -----------------------------------------------------------------
#include <iostream>
#include <list>
#include <map>
#include "./util.h"
using namespace std ;

//--------------------------------------------------------------------
void imprime (list <int> & L) {
  list <int> :: iterator p, z;
  cout << "lista : " ; 
  p = L.begin ();
  z = L.end ();
  while (p != z) cout << *p++ << " " ;
  cout << endl ;
}

//--------------------------------------------------------------------
void imprime (vector < list <int> > & V) {
  list <int> :: iterator p, z;
  int n ;
  n = V.size();
  cout << "nro de listas  ; n = " << n << endl ;
  for (int k = 0 ; k < n ; k++) {
    cout << "sublista " << k << " : " ; 
    p = V [k].begin ();
    z = V [k].end ();
    while (p != z) cout << *p++ << " " ;
    cout << endl ;
  } // end k
} // end void

//--------------------------------------------------------------------
void imprime (map <int,int> & M) {
  map <int,int> :: iterator p;
  int x_dominio ;
  int y_rango;
  cout << endl ;
  cout << "mapeo actual (x_dominio, y_rango):" << endl ;
  p = M.begin ();
  while (p != M.end () ) {
    x_dominio = p->first;
    y_rango   = p->second;
    cout << "x_dominio = "     <<    x_dominio  << "  " ;
    cout << "M [x_dominio] = " << M [x_dominio] << endl ;
    p++;
  } // end while
}

//--------------------------------------------------------------------
void imprime (queue<int> & Q) {
  queue<int> C ;
  int x ; 
  cout << endl ;
  cout << "cola  Q: " ;
  while ( !Q.empty() ) {
    x = Q.front (); 
    C.push (x) ;
    cout << x << " " ;
    Q.pop (); // la unica forma de avanzar en la cola Q
  } //
  cout << endl ;
  while ( !C.empty() ) {
    x = C.front (); 
    Q.push (x) ;
    C.pop (); // la unica forma de avanzar en la cola C
  } //
}

//--------------------------------------------------------------------
void map_explora (vector < list <int> > & V, map <int,int> & M) {
  queue <int> Q ;
  map <int,int> :: iterator q;
  list <int> :: iterator p;
  int h, k, g, n ;
  int x_dominio ;
  int y_rango;
  g = 1;                        // inicializa contadora de subredes
  n = V.size();                 // numero de computadoras
  // revisa cada computadora i=0,1,...,n-1
  for (int i=0 ; i < n-1 ; i++) {
    if (M.size() == n) return ; // ya estan todas vistas
    x_dominio = i ;             // la PC "i" es candidata
    q = M.find (x_dominio);     // averigua si ya estaba
    if ( q == M.end () ) {      // entonces no estaba
      M [x_dominio] = g ;       // y la asigna a la subred "g" 
      Q.push (x_dominio);       // y la encola para luego revisarla
    } // end if
    while ( !Q.empty() ) { 
      k = Q.front ();           // descola la PC numeros "k"
      Q.pop();
      imprime (Q);
      // lazo para revisar las primeras vecinas de la PC numero "k"
      p = V [k].begin ();
      while ( p != V [k].end() ) {
        x_dominio = *p++ ;      // la PC numero "*p" es candidata
        q = M.find (x_dominio); // averigua si ya estaba
        if (q == M.end()) {     // entonces no estaba
           M [x_dominio] = g ;  // y la asigna al subred "g" 
           Q.push (x_dominio);  // y la encola para luego revisarla
        } // end if
      } // end while
      imprime (M);
    } // end while
    // si quedan computadoras no-vistas, seran de la siguiente subred
    g++;
  }
} // end i

//--------------------------------------------------------------------
int main() {
  map <int,int> M;
  int n = 10 ;
  vector < list <int> > V (n);  
  int kaso = 2 ;
  if    (kaso == 1) {
    //
    // red conexa:
    int v0[] = {3,5}     ; int n0 = 2 ;
    int v1[] = {2,4,6,9} ; int n1 = 4 ;
    int v2[] = {1,3,4}   ; int n2 = 3 ;
    int v3[] = {0,2,5,8} ; int n3 = 4 ;
    int v4[] = {1,2,6}   ; int n4 = 3 ;
    int v5[] = {0,3,6,7} ; int n5 = 4 ;
    int v6[] = {1,4,5,7} ; int n6 = 4 ;
    int v7[] = {6,7}     ; int n7 = 2 ;
    int v8[] = {3}       ; int n8 = 1 ;
    int v9[] = {1}       ; int n9 = 1 ;
    for (int i=0; i < n0; i++) V [0].insert (V[0].end(), v0[i]);
    for (int i=0; i < n1; i++) V [1].insert (V[1].end(), v1[i]);
    for (int i=0; i < n2; i++) V [2].insert (V[2].end(), v2[i]);
    for (int i=0; i < n3; i++) V [3].insert (V[3].end(), v3[i]);
    for (int i=0; i < n4; i++) V [4].insert (V[4].end(), v4[i]);
    for (int i=0; i < n5; i++) V [5].insert (V[5].end(), v5[i]);
    for (int i=0; i < n6; i++) V [6].insert (V[6].end(), v6[i]);
    for (int i=0; i < n7; i++) V [7].insert (V[7].end(), v7[i]);
    for (int i=0; i < n8; i++) V [8].insert (V[8].end(), v8[i]);
    for (int i=0; i < n9; i++) V [9].insert (V[9].end(), v9[i]);
    imprime (V);
    map_explora (V,M);
    imprime (M); }
  else if (kaso == 2) {
    //
    // red desconexa: con 2 subredes
    int v0[] = {6}       ; int n0 = 1 ;
    int v1[] = {8}       ; int n1 = 1 ;
    int v2[] = {7}       ; int n2 = 1 ;
    int v3[] = {6}       ; int n3 = 1 ;
    int v4[] = {8}       ; int n4 = 1 ;
    int v5[] = {7}       ; int n5 = 1 ;
    int v6[] = {0, 3}    ; int n6 = 2 ;
    int v7[] = {2, 5, 9} ; int n7 = 3 ;
    int v8[] = {1, 4, 9} ; int n8 = 3 ;
    int v9[] = {7, 8}    ; int n9 = 2 ;
    for (int i=0; i < n0; i++) V [0].insert (V[0].end(), v0[i]);
    for (int i=0; i < n1; i++) V [1].insert (V[1].end(), v1[i]);
    for (int i=0; i < n2; i++) V [2].insert (V[2].end(), v2[i]);
    for (int i=0; i < n3; i++) V [3].insert (V[3].end(), v3[i]);
    for (int i=0; i < n4; i++) V [4].insert (V[4].end(), v4[i]);
    for (int i=0; i < n5; i++) V [5].insert (V[5].end(), v5[i]);
    for (int i=0; i < n6; i++) V [6].insert (V[6].end(), v6[i]);
    for (int i=0; i < n7; i++) V [7].insert (V[7].end(), v7[i]);
    for (int i=0; i < n8; i++) V [8].insert (V[8].end(), v8[i]);
    for (int i=0; i < n9; i++) V [9].insert (V[9].end(), v9[i]);
    imprime (V);
    map_explora (V,M);
    imprime (M); 
  } // end if

  cout << endl;
  return 0;
}
// -----------------------------------------------------------------
