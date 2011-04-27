//__INSERT_LICENSE__
// $Id: util.cpp,v 1.1 2004/02/05 00:01:00 mstorti Exp $

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "./util.h"

double drand() {
  return double(rand())/double(RAND_MAX);
}

int irand(int M) {
  return int(double(M)*drand());
}
