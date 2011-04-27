//__INSERT_LICENSE__
// $Id: hashsetbas.h,v 1.15 2004/06/12 16:18:20 mstorti Exp $
#ifndef AED_HASHSETBAS_H
#define AED_HASHSETBAS_H

#include <vector>
#include <stack>
#include <utility>

namespace aed {
  typedef int key_t;

  //L-hash-set-bas-b
  typedef int iterator_t;
  typedef int (*hash_fun)(key_t x);
  typedef int (*redisp_fun)(int j);

  int linear_redisp_fun(int j) { return j; }

  class hash_set {
  private:
    hash_set(const hash_set&) {}
    hash_set& operator=(const hash_set&) {}
    int undef, deleted;
    hash_fun h;
    redisp_fun rdf;
    int B;
    int count;
    std::vector<key_t> v;
    std::stack<key_t> S;
    iterator_t locate(key_t x,iterator_t &fdel) {
      int init = h(x)+rdf(0);
      int bucket;
      bool not_found = true;
      for (int i=0; i<B; i++) {
	op_count++; //S
	bucket = (init+rdf(i)) % B;
	key_t vb = v[bucket];
	if (vb==x || vb==undef) break;
	if (not_found && vb==deleted) {
	  fdel=bucket;
	  not_found = false;
	}
      }
      if (not_found) fdel = end();
      return bucket;
    }
    iterator_t next_aux(iterator_t bucket) {
      int j=bucket;
      while(j!=B && v[j]!=undef && v[j]!=deleted) {
	op_count++; //S
	j++;
      }
      return j;
    }
  public:
    int op_count;  //S
    int purge_deleted; //S
    hash_set(int B_a,hash_fun h_a,
	     key_t undef_a,key_t deleted_a,
	     redisp_fun rdf_a=&linear_redisp_fun) 
      : B(B_a), undef(undef_a), v(B,undef_a), h(h_a), 
	deleted(deleted_a), rdf(rdf_a), count(0)
	,op_count(0), purge_deleted(0) //S
    { }
    std::pair<iterator_t, bool> 
      insert(key_t x) {
      iterator_t fdel;
      int bucket = locate(x,fdel);
      if (v[bucket]==x) 
	return std::pair<iterator_t,bool>(bucket,false);
      if (fdel!=end()) bucket = fdel;
      if (v[bucket]==undef || v[bucket]==deleted) {
	v[bucket]=x;
	count++;
	return std::pair<iterator_t,bool>(bucket,true);
      } else {
	std::cout << "Tabla de dispersion llena!!\n";
	abort();
      }
    }
    key_t retrieve(iterator_t p) { return v[p]; }
    iterator_t find(key_t x) {
      iterator_t fdel;
      int bucket = locate(x,fdel);
      if (v[bucket]==x) return bucket;
      else return(end());
    }
    int erase(const key_t& x) {
      iterator_t fdel;
      int bucket = locate(x,fdel);
      if (v[bucket]==x) {
	v[bucket]=deleted; 
	count--;
	if (purge_deleted) {  //S
	  // Trata de purgar elementos `deleted' //L-reins-b 
	  // Busca el siguiente elemento `undef'
	  int j;
	  for (j=1; j<B; j++) {
	    op_count++;
	    int b = (bucket+j) % B;
	    key_t vb = v[b];
	    if (vb==undef) break;
	    S.push(vb);
	    v[b]=undef;
	    count--;
	  }
	  v[bucket]=undef;
	  // Va haciendo erase/insert de los elementos
	  // de atras hacia adelante hasta que se llene 
	  // `bucket'
	  while (!S.empty()) {
	    op_count++;
	    insert(S.top());
	    S.pop();
	  }                  //L-reins-e
	}                    //S
	return 1;
      } else return 0;
    }
    iterator_t begin() {
      return next_aux(0);
    }
    iterator_t end() { return B; }
    iterator_t next(iterator_t p) {
      return next_aux(p++);
    }
    void clear() {
      count=0;
      for (int j=0; j<B; j++) v[j]=undef;
    }
    int size() { return count; }
  };
  //L-hash-set-bas-e

}
#endif
// Local Variables: *
// mode: c++ *
// End: *
