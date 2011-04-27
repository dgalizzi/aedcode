//__INSERT_LICENSE__
// $Id: mapl.cpp,v 1.1 2004/03/13 11:01:34 mstorti Exp $

using namespace aed;

namespace aed {
  ostream &operator<<(ostream &s,elem_t x) {
    s << "(" << x.first << "," << x.second << ")  " ;
  }
}
