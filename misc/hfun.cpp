//__INSERT_LICENSE__
// $Id: hfun.cpp,v 1.1 2004/05/24 01:06:05 mstorti Exp $

#include <string>
#include <iostream>

using namespace std;

int h(const string &t) {
  return t[0]-'a';
}

int main() {
  string s;
  char line[100];
  while (1) {
    cout << "Ingrese string: ";
    cin >> line;
    cout << "h(s): " << h(string(line)) << endl;
  }
}
