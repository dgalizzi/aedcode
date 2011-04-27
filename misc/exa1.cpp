//__INSERT_LICENSE__
// $Id: exa1.cpp,v 1.1 2004/02/09 03:34:31 mstorti Exp $

#include <aedsrc/listpi.h>

using namespace aed;

int main() {
  list L;
  for (int j=0; j<4; j++) L.insert(L.end(),j);
  L.printd();
}
