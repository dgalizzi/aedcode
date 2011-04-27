//PP>if 0
//__INSERT_LICENSE__
// $Id: stack.cpp,v 1.2 2005/04/08 21:05:12 mstorti Exp $

#include <aedsrc/stack.h>

using namespace aed;

//PP>endif


stack::stack() : size_m(0) { }
void stack::clear() { erase(begin(),end()); size_m = 0; }
elem_t& stack::top() { return retrieve(begin()); }
void stack::pop() { erase(begin()); size_m--; }
void stack::push(elem_t x) { insert(begin(),x); size_m++; }
bool stack::empty() { return begin()==end(); }
int stack::size() { return size_m; }
