//__INSERT_LICENSE__
// $Id: huffman.cpp,v 1.13 2004/05/18 20:10:58 mstorti Exp $

#include <aedsrc/btree.h>
#include <aedsrc/btreetools.h>
#include <aedsrc/util.h>
#include <unistd.h>
#include <float.h>
#include <list>
#include <queue>
#include <cstdio>

using namespace aed;
int verbosity=0;
typedef unsigned char char_t;
typedef vector<char_t> codigo_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
struct huffman_tree {         //L-htree-b
  double p;
  btree<int> T;
};                            //L-htree2

void 
huffman(const vector<double> &prob,btree<int> &T) {
  typedef list<huffman_tree> bosque_t; //L-htree3

  // Contiene todos los arboles
  bosque_t bosque;
  // Numero de caracteres del codigo
  int N = prob.size();
  // Crear los arboles iniciales poniendolos en
  // una lista Los elementos de la lista contienen
  // la probabilidad de cada caracter y un arbol
  // con un solo nodo. Los nodos interiores del
  // arbol tienen un -1 (es solo para
  // consistencia) y las hojas tienen el indice
  // del caracter. (entre 0 y N-1)
  for (int j=0; j<N; j++) {                      //L-ini-b
    // Agrega un nuevo elemento a la lista
    bosque_t::iterator htree = 
      bosque.insert(bosque.begin(),huffman_tree());
    htree->p = prob[j];
    htree->T.insert(htree->T.begin(),j);
  }                                              //L-ini-e

  // Aqui empieza el algoritmo de Huffman.
  // Tmp va a contener el arbol combinado
  btree<int> Tmp;                               //L-huf-b
  for (int j=0; j<N-1; j++) {
    if (verbosity) cout << "--------\non j: " << j << endl; //S
    // En la raiz de Tmp (que es un nodo interior)
    // ponemos un -1 (esto es solo para chequear).
    Tmp.insert(Tmp.begin(),-1);
    // Tmp_p es la probabilidad del arbol combinado
    // (la suma de las probabilidades de los dos subarboles)
    double Tmp_p = 0.0;
    // Para `k=0' toma el menor y lo pone en el
    // hijo izquierdo de la raiz de Tmp. Para `k=1' en el
    // hijo derecho. 
    for (int k=0; k<2; k++) {
      // recorre el `bosque' (la lista de arboles)
      //  busca el menor. `qmin' es un iterator al menor
      bosque_t::iterator q = bosque.begin(), qmin=q;
      while (q != bosque.end()) {            //L-loop-b
	if (q->p < qmin->p) qmin = q;
	q++;
      }                                      //L-loop-e
      if (verbosity) {                                   //S-b
	cout << "prob= " << qmin->p << "  ";
	qmin->T.lisp_print();
	cout << endl;
      }                                                  //S-e
      // Asigna a `node' el hijo derecho o izquierdo
      // de la raiz de `Tmp' dependiendo de `k'
      btree<int>::iterator node = Tmp.begin();           //L-asig-b
      node = (k==0 ? node.left() : node.right());        //L-asig-e
      // Mueve todo el nodo que esta en `qmin'
      // al nodo correspondiente de `Tmp'
      Tmp.splice(node,qmin->T.begin());                  //L-huff1
      // Acumula las probabilidades
      Tmp_p += qmin->p;                                  //L-acum 
      // Elimina el arbol correspondiente del bosque. 
      bosque.erase(qmin);                                //L-era
    }
    if (verbosity) {                                     //S-b
      cout << "combined: ";
      Tmp.lisp_print();
      cout << endl;
    }                                                    //S-e
    // Inserta el arbol combinado en el bosque
    bosque_t::iterator r = 
      bosque.insert(bosque.begin(),huffman_tree());
    // Mueve todo el arbol de `Tmp' al nodo
    // recien insertado
    r->T.splice(r->T.begin(),Tmp.begin());
    // Pone la probabilidad en el elemento de la
    // lista
    r->p = Tmp_p;
  }
  // Debe haber quedado 1 solo elemento en la lista
  assert(bosque.size()==1);
  // Mueve todo el arbol que quedo a `T'
  T.clear();
  T.splice(T.begin(),bosque.begin()->T.begin());      //L-huff2
}                                      //L-huf-e
                                       //L-htree-e

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void                                                 //L-hufzip-b
huffman_codes(btree<int> &T,btree<int>::iterator node,
	      const vector<double> &prob,
	      codigo_t &codigo, vector<codigo_t> &codigos) {
  //ES `codigo' es el codigo calculado hasta node.
  // La funcion se va llamando recursivamente y a
  // medida que va bajando en el arbol va
  // agregando bits al codigo.
  if (*node>=0) {
    //ES Si es una hoja directamente inserta un
    // codigo en `codigos'
    codigos[*node] = codigo; //L-agrega-cod
    return;
  } else {
    //ES Le va pasando `codigo' a los hijos los
    // cuales van agregando codigos a `codigos'.
    // `codigo' se va pasando por referencia de
    // manera que las llamadas recursivas lo deben
    // dejar tal como estaba. Por eso, despues
    // despues de agregar un 0 hay que sacarlo
    // y lo mismo con el 1. 
    codigo.push_back(0);   //L-entra
    huffman_codes(T,node.left(),prob,codigo,codigos);
    codigo.pop_back();

    codigo.push_back(1);
    huffman_codes(T,node.right(),prob,codigo,codigos);
    codigo.pop_back();
    return;     //L-return
  }
}

void
huffman_codes(btree<int> &H,const vector<double> &prob,
	      vector<codigo_t> &codigos) {
  //ES Este es el codigo de un caracter en particular. Es
  // pasado por referencia, de manera que hay una sola instancia
  // de codigo. 
  codigo_t codigo;
  huffman_codes(H,H.begin(),prob,codigo,codigos);
}

const int NB = 8;
const int bufflen = 1024;

void qflush(queue<char> &Q, queue<char_t> &Qbytes, 
	    int &nbits) {
  //EN Convert `NB' bytes from `Q' to a char. 
  // If `Q' gets empty pad with 0's.
  //ES Convierte `NB' bytes de `Q' a un char.
  // Si `Q' queda viacia entonces rellena con 0's. 
  char_t c=0;
  for (int j=0; j<NB; j++) {
    int b = 0;
    if (!Q.empty()) {
      b = Q.front();
      Q.pop();
      nbits++;
    }
    if (verbosity) cout << b; //S
    c <<= 1;
    if (b) c |= 1;
    else c &= ~1;
  }
  if (verbosity) cout << endl; //S
  Qbytes.push(c);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void bflush(queue<char_t> &Qbytes, 
	    vector<char_t> &buff,int &nbits,
	    FILE *zip) {
  // Numero de bits a ser escrito
  int nb = nbits;
  if (nb>bufflen*NB) nb = bufflen*NB;
  nbits -= nb;
  // Guarda en el archivo la longitud del siguiente bloque
  fwrite(&nb,sizeof(int),1,zip); //L-bflush1
  // Pone en el buffer los `nb' bits
  int nbytes = 0;
  while (nb>0) {
    buff[nbytes++] = Qbytes.front();
    Qbytes.pop();
    nb -= NB;
  }
  fwrite(&buff[0],sizeof(char_t),nbytes,zip);  //L-bflush2
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void hufzip(char *file,char *zipped) {
  // Abre el archivo a compactar
  FILE *fid;
  if (file) {
    fid = fopen(file,"r");
    assert(fid);
  } else fid = stdin;
  // Numero total de caracteres posibles. Consideramos caracteres de 8
  // bits, es decir que puede haber 256 caracteres
  const int NUMCHAR=256;
  // table[j] va a ser el numero de veces que aparece el caracter `j'
  // en el archivo. De manera que la probabilidad del caracter es
  // prob[j] = table[j]/(sum_k=0^numchar table[k]) indx[j] es el
  // indice asignado al caracter `j'. Si el caracter `j' no aparece en
  // el archivo entonces hacemos indx[j]=-1 y si no le asignamos un
  // numero correlativo de 0 a N-1.  N es el numero total de
  // caracteres distintos que aprecen en el archivo.
  vector<int> table(NUMCHAR),indx(NUMCHAR);
  // Ponemos los caracteres en una cola de `char_t'
  queue<char_t> fin;
  // Contador de cuantos caracteres hay en el archivo
  int n = 0;
  while(1) {
    int c = getc(fid);
    if (c==EOF) break;
    fin.push(c);
    assert(c<NUMCHAR);
    n++;
    table[c]++;
  }
  fclose(fid);
  // Detecta cuantos caracteres distintos hay fijandose en solo
  // aquellos que tienen table[j]>0. Define prob[k] que es la
  // probabilidad de aparecer del caracter con indice `k'
  int N=0;
  // prob[k] es la probabilidad correspondiente al caracter de indice k
  vector<double> prob;
  // `letters[k]' contiene el caracter (de 0 a NUMCHAR-1)
  // correspondiente al indice `k'
  vector<char_t> letters;
  for (int j=0; j<NUMCHAR; j++) {
    if (table[j]) {
      double p = double(table[j])/double(n);
      if (verbosity)                              //S-b
	cout << char(j) << ": " 
	     << table[j] << "/" << p << endl;     //S-e
      indx[j] = N++;
      letters.push_back((char_t)j);
      prob.push_back(p);
    } else indx[j] = -1;
  }

  // H va a contener al arbol de codigos
  btree<int> H;
  // Calcula el arbol usando el algoritmo de Huffman
  huffman(prob,H);                   //L-huffman-zip

  // Construye la tabla de codigos. `codigos[j]' va a ser
  // un vector de enteros (bits)
  vector<codigo_t> codigos(N);
  // Calcula la tabla de codigos y la longitud media. 
  huffman_codes(H,prob,codigos);

  if (verbosity) {    //S-b
#if 0
    double maxl = ceil(log2(N));
    cout << "[Max length: " << maxl 
	 << ", gain " << (maxl-avl)/maxl*100.0 << "%]\n";
#endif

    // Imprime los codigos
    for (int k=0; k<N; k++) {
      int c = letters[k];
      printf("char #%d \"%c\" code: ",k,(char)c);
      codigo_t &cod = codigos[k];
      for (int j=0; j<cod.size(); j++) cout << cod[j] << " ";
      cout << endl;
    }
  }                   //S-e

  // Abre el archivo zippeado
  FILE *zip;
  if (zipped) {
    zip = fopen(zipped,"w");
    assert(zip);
  } else zip = stdout;

  // Guarda encabezamiento en archivo zippeado conteniendo
  // las probabilidades para despues poder reconstruir el arbol
  for (int j=0; j<N; j++) {                    //L-write-prob-b
    fwrite(&prob[j],sizeof(double),1,zip);
    fwrite(&letters[j],sizeof(char_t),1,zip);
  }                                            //L-write-prob-e
  // Terminador (probabilidad negativa)
  double p = -1.0;
  fwrite(&p,sizeof(double),1,zip);

  vector<char_t> buff(bufflen);
  // Cantidad de bits almacenados en buff
  int nbits=0;

  // Zippea.  Va convirtiendo los caracteres de `fin' en codigos y los
  // inserta en la cola `Q', o sea que `Q' contiene todos elementos 0
  // o 1. Por otra parte va sacan dode a 8 bits de Q y los convierte
  // en un byte en `Qbytes'. O sea que `Qbytes' contiene caracteres que pueden
  // tomar cualquier valor entre 0 y NUMCHAR-1. 
  queue<char> Q;
  queue<char_t> Qbytes;
  assert(fid);
  while(!fin.empty()) {                //L-zip-b
    // Va tomando de a un elemento de `fin' y pone todo el codigo
    // correspondiente en `Q' 
    int c = fin.front();
    fin.pop();
    assert(c<NUMCHAR);
    int k = indx[c];
    assert(k>=0 && k<N);
    codigo_t &cod = codigos[k];
    if (verbosity) {                    //S-b
      cout << (char)c << ": ";
      for (int j=0; j<cod.size(); j++) {
	assert(cod[j]==0 || cod[j]==1);
	cout << cod[j];
      }
      cout << endl;
    }                                   //S-e
    for (int j=0; j<cod.size(); j++) Q.push(cod[j]);
    //EN Convert Q to char 
    //ES Convierte bits de `Q' a caracteres
    while (Q.size()>NB) qflush(Q,Qbytes,nbits);
    //EN Write to zipped file
    //ES Escribe en el archivo zippeado. 
    while (Qbytes.size()>bufflen) bflush(Qbytes,buff,nbits,zip);
  }                                     //L-zip-e

  // Convierte el resto que puede quedar en Q
  while (Q.size()>0) qflush(Q,Qbytes,nbits);             //L-flush1
  // Escribe el resto de lo que esta en Qbytes en `zip'
  while (Qbytes.size()>0) bflush(Qbytes,buff,nbits,zip); //L-flush2
  // Terminador final con longitud de bloque=0
  int nb=0;
  // Escribe un terminador (un bloque de longitud 0)
  fwrite(&nb,sizeof(int),1,zip);
  fclose(zip);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
int pop_char(queue<char> &Q,btree<int> &H,
	     btree<int>::iterator &m,int &k) {
  // `m' es un nodo en el arbol. Normalmente deberia estar en la raiz
  // pero en principio puede estar en cualquier nodo. Se supone que ya
  // se convirtieron una seride de bits. Si en la ultima llamada se
  // llego a sacar un caracter entonces `m' termina en la raiz, listo
  // para extraer otro caracter.  Entonces `pop_char' extrae tantos
  // caracteres como para llegar a una hoja y, por lo tanto, extraer
  // un caracter. En ese caso pasa en `k' el indice correspondiente,
  // vuelve a `m' a la raiz (listo para extraer otro caracter) y
  // retorna 1. Si no, retorna 0 y deja a `m' en el nodo al que llega.
  while (!Q.empty()) {
    int f = Q.front();
    Q.pop();
    if (verbosity) cout << f;   //S
    // El valor binario 0 o 1 almacenado en `Q' dice que hijo hay que tomar. 
    if (f) m = m.right();
    else m = m.left();
    // Verificar si llego a una hoja. 
    if (m.left()==H.end()) {
      // Pudo sacar un caracter completo
      k = *m;
      assert(k != -1);
      m = H.begin();
      return 1;
    }
  }
  // No pudo sacar un caracter completo. 
  return 0;
}

void hufunzip(char *zipped,char *unzipped) {
  // Deszippea el archivo de nombre `zipped' en `unzipped'
  // El vector de probabilidades (esta guardado en `zipped'). 
  vector<double> prob;
  // Los caracteres correspondientes a cada indice 
  vector<char> letters;
  // Numero de bits por caracter
  const int NB=8;

  // Abre el archivo `zipped', si no es `stdin'
  FILE *zip;
  if (zipped) {
    zip = fopen(zipped,"r");
    assert(zip);
  } else zip = stdin;

  // Lee la tabla de probabilidades y codigos, estan escritos
  // en formato binario probabilidad,caracter,probabilidad,caracter,...
  // hasta terminar con una probabilidad <0
  // Los va poniendo en `prob[]' y las letras en `letters[]'
  int N=0;
  int nread;
  while (true) {               //L-read-prob-b
    double p;
    char c;
    nread = fread(&p,sizeof(double),1,zip);
    assert(nread==1);
    if (p<0.0) break;
    N++;
    prob.push_back(p);
    nread = fread(&c,sizeof(char),1,zip);
    assert(nread==1);
    letters.push_back(c);
  }                            //L-read-prob-e

  //ES `H' va a tener el arbol de codigos.
  // `huffman()' calcula el arbol.
  btree<int> H;
  huffman(prob,H);             //L-huffman-unzip

  // Los codigos se almacenan en un vector de
  // codigos.
  vector<codigo_t> codigos(N);
  // `huffman_codes()' calcula los codigos y tambien
  // la longitud promedio del codigo. 
  huffman_codes(H,prob,codigos);

#if 0                               //S-b
  if (verbosity) {
    cout << "Average length: " << avl << endl;
    double maxl = ceil(log2(N));
    cout << "[Max length: " << maxl 
	 << ", gain " << (maxl-avl)/maxl*100.0 
	 << "%]\n";
  }
#endif                             //S-e
  // El archivo donde descompacta. Si no se pasa
  // el nombre entoces descompacta sobre `stdout'.
  FILE *unz;
  if (unzipped) {
    unz = fopen(unzipped,"w");
    assert(unz);
  } else unz = stdout;

  // Los bloques de bytes del archivo compactado
  // se van leyendo sobre una cola `Q' y se va
  // descompactando directamente sobre el archivo
  // descompactado con `putc' (el cual ya es
  // buffereado)
  queue<char> Q;
  int read=0;
  // Posicion en el arbol
  btree<int>::iterator m = H.begin();
  // indice de caracter que se extrajo
  int k;
  // Buffer para poner los bytes que se leen del
  // archivo compactado.
  vector<char_t> buff;
  char_t c;
  while (1) {                //L-hufu-b
    int nb;
    //EN Read length (in bits) of next block
    //ES Lee longitud (en bits) del siguiente bloque. 
    nread = fread(&nb,sizeof(int),1,zip);
    assert(nread==1);

    //EN If block length is null stop.
    //ES Detenerse si el siguiente bloque es nulo. 
    if (!nb) break;

    //EN Resize buffer appropriately.
    //ES Redimensionar la longitud del
    //  buffer apropriadamente. 
    int nbytes = nb/NB + (nb % NB ? 1 : 0);
    if (buff.size()<nbytes) buff.resize(nb);

    //EN Read the block
    //ES Lee el bloque
    nread = fread(&buff[0],sizeof(char_t),nbytes,zip); //L-hufu1
    assert(nread==nbytes);
    
    vector<char_t> v(NB);
    int j = 0, read=0;
    while (read<nb) {
      c = buff[j++];
      //EN unpack the char in bits
      //ES Desempaqueta el caracter tn bits
      for (int l=0; l<NB; l++) {
	int b = (c & 1 ? 1 : 0);
	c >>= 1;
	v[NB-l-1] = b;
      }
      for (int l=0; l<NB; l++) {
	if (verbosity) cout << (int)v[l];  //S
	if (read++ < nb) Q.push(v[l]);     //L-hufu2
      }
      if (verbosity) cout << endl;  //S
      //ES Va convirtiendo bits de `Q' en
      // caracteres.  Si `pop_char()' no puede
      // sacar un caracter, entonces va a devolver
      // 0 y se termina el lazo. En ese caso `m'
      // queda en la posicion correspondiente en el
      // arbol.
      while(pop_char(Q,H,m,k)) putc(letters[k],unz); //L-hufu3
    }
  }                        //L-hufu-e

  assert(!.empty());       //L-assert
  //ES Cerrar los archivos abiertos. 
  fclose(zip);
  fclose(unz);
}
                                              //L-hufzip-e

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void main2() {
#if 0
  { // artificial scope for verifying cell count
    vector<double> prob;
    btree<int> H;
    int m=0;
    while (1) {
      prob.clear();
      H.clear();
#if 0
      double prob_a[]={0.3,0.2,0.1,0.1,0.1,0.05,0.05,0.05,0.05,-1.0};
      insertv(prob,prob_a,-1.0);
#elif 0
      int N=64;
      for (int j=0; j<N; j++) prob.push_back(1./double(N));
#elif 0
      int N=32;
      double sum=0.;
      for (int j=0; j<N; j++) {
	double v = drand();
	// if (v<0.9) v /= 100.;
	double la = 10.0;
	v = (exp(la*v)-1.0)/(exp(la)-1.0);
	sum +=v;
	prob.push_back(v);
      }
      for (int j=0; j<N; j++) prob[j] /= sum;
      sort(prob.begin(),prob.end());
#if 1
      cout << "probs: ";
      for (int j=0; j<N; j++) cout << prob[j] << endl;
      cout << endl;
#endif
#endif
      // huffman(H,prob);
      // H.lisp_print();
      m++; 
      break;
    }
  }
  cout << "cell_count: " << btree<int>::cell_count() << endl;
#endif
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
typedef btree<int> btree_t;
typedef btree_t::iterator node_t;

list<int> indx;

typedef void (*traverse_tree_fun) (btree_t &T, void *data); //L-comb-b

typedef list< btree<int> > list_t;
typedef list_t::iterator pos_t;

void comb(list_t &L,traverse_tree_fun f,void *data=NULL) {
  if (L.size()==1) {
    f(*L.begin(),data);
    if (verbosity) {         //S-b
      cout << "perm: ";
      list<int>::iterator k = indx.begin();
      while (k!=indx.end())
	cout << "(" << *k++ << "," << *k++ << ") ";
      cout << endl; 
    }                        //S-e
    return;
  } 
  int n=L.size();
  for (int j=0; j<n-1; j++) {
    for (int k=j+1; k<n; k++) {
      if (verbosity) {                              //S-b
	indx.push_back(j); 
	indx.push_back(k);
      }                                             //S-e
      btree_t T;                                    //L-comb1-b
      T.insert(T.begin(),-1);
      node_t m = T.begin();

      pos_t pk=L.begin();
      for (int kk=0; kk<k; kk++) pk++;
      T.splice(m.left(),pk->begin());
      L.erase(pk);

      pos_t pj=L.begin();
      for (int jj=0; jj<j; jj++) pj++;
      T.splice(m.right(),pj->begin());
      L.erase(pj);

      pos_t p = L.insert(L.begin(),btree_t());
      p->splice(p->begin(),T.begin());             //L-comb1-e

      assert(L.size()==n-1); //S
      comb(L,f,data);  //L-comb-rec

      p = L.begin();                               //L-comb2-b
      m = T.splice(T.begin(),p->begin());
      L.erase(p);

      pj=L.begin();
      for (int jj=0; jj<j; jj++) pj++;
      pj = L.insert(pj,btree_t());
      pj->splice(pj->begin(),m.right());
	
      pk=L.begin();
      for (int kk=0; kk<k; kk++) pk++;
      pk = L.insert(pk,btree_t());
      pk->splice(pk->begin(),m.left());            //L-comb2-e
      assert(L.size()==n); //S

      if (verbosity) {        //S-b
	indx.pop_back();
	indx.pop_back();
      }                       //S-e
    }
  }
}
                              //L-comb-e

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
double codelen(btree_t &T,node_t n,     //L-code-len-b
	       const vector<double> &prob,double &w) {
  if (n.left()==T.end()) {
    w = prob[*n];;
    return 0.;
  } else {
    double wl,wr,lr,ll;
    ll = codelen(T,n.left(),prob,wl);
    lr = codelen(T,n.right(),prob,wr);
    w = wr+wl;
    return wl+wr+ll+lr;
  }
}

double codelen(btree_t &T,
	       const vector<double> &prob) {
  double ww;
  return codelen(T,T.begin(),prob,ww);
}
                                        //L-code-len-e
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
struct huf_exh_data {      //L-huf-exh-b
  btree_t best;
  double best_code_len;
  const vector<double> *prob;
};

void min_code_len(btree_t &T,void *data) { 
#if 0                            //S-b
  if (0 && verbosity) {   
    print_tree(T);
    cout << endl; 
    cout << "averg. code length: " 
	 << codelen(T,prob) << endl;
  }
#endif                           //S-e
  huf_exh_data *hp = (huf_exh_data *)data; //L-cast
  double l = codelen(T,*(hp->prob));
  if (l < hp->best_code_len) {
    hp->best_code_len = l;
    hp->best = T;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
void 
huffman_exh(const vector<double> &prob,btree_t &T) {
  int nchar = prob.size();
  list_t L;
  pos_t p;
  huf_exh_data h;
  h.prob = &prob;
  h.best_code_len = DBL_MAX;
  for (int j=0; j<nchar; j++) {
    p = L.insert(L.end(),btree_t());
    p->insert(p->begin(),j);
  }
  comb(L,&min_code_len,&h);
  T.clear();
  T.splice(T.begin(),h.best.begin());
}
                                     //L-huf-exh-e
