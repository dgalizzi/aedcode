stack::stack() : size_m(0) { }

elem_t& stack::top() { 
  return retrieve(begin()); 
}

void stack::pop() { 
  erase(begin()); size_m--; 
}

void stack::push(elem_t x) { 
  insert(begin(),x); size_m++; 
}

void stack::clear() {
  erase(begin(),end()); size_m = 0; 
}

bool stack::empty() { 
  return begin()==end(); 
}

int stack::size() { 
  return size_m; 
}

