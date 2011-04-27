//__INSERT_LICENSE__
// $Id: trysort3.cpp,v 1.3 2004/06/28 02:13:05 mstorti Exp $

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
// #include <ctype.h>

using namespace std;

void tolower(string &s) {
  for (int j=0; j<s.size(); j++) 
    s[j] = tolower(s[j]);
}

bool string_less_ci2(const string &a,const string &b) {
  string 
    aa = a,
    bb = b;
  tolower(aa);
  tolower(bb);
  return aa<bb;
}

char tolower(char c) {                           //L-string-less-ci-b
  if (c>='A' && c<='Z') c += 'a'-'A';
  return c;
}

bool string_less_ci(const string &a,
		    const string &b) { 
  int na = a.size();
  int nb = b.size();
  int n = (na>nb ? nb : na);
  for (int j=0; j<n; j++) {
    char 
      aa = tolower(a[j]),
      bb = tolower(b[j]);
    if (aa < bb) return true; 
    else if (bb < aa) return false; 
  }
  return na<nb;
}
                                                 //L-string-less-ci-e
bool string_less_cs(const string &a,const string &b) { //L-string-less-cs-b
  int na = a.size();
  int nb = b.size();
  int n = (na>nb ? nb : na);
  for (int j=0; j<n; j++) {
    if (a[j] < b[j]) return true;        //L-comp-char-b
    else if (b[j] < a[j]) return false;  //L-comp-char-e
  }
  return na<nb;
}

char change_case(char a) {                           //L-string-less-cs-e
  if (a>='a' && a<='z') return a +'A'-'a';
  if (a>='A' && a<='Z') return a +'a'-'A';
}

bool string_less_cs2(const string &a,const string &b) {
  int na = a.size();
  int nb = b.size();
  int n = (na>nb ? nb : na);
  for (int j=0; j<n; j++) {
    char aa = change_case(a[j]);
    char bb = change_case(b[j]);
    if (aa < bb) return true;
    else if (bb < aa) return false;
  }
  return na < nb;
}

bool string_less_cs3(const string &a,const string &b) {  //L-string-less-cs3
  return a<b;
} 

void print(vector<string> &v) {              //L-print
  for (int j=0; j<v.size(); j++) {
    cout << v[j] << " ";
  }
  cout << endl;
}

int main(int argc,char **argv) {
  vector<string> v;
  v.push_back("Pepe");
  v.push_back("pepe");
  v.push_back("PEPE");
  v.push_back("Juana");
  v.push_back("juana");
  v.push_back("JUANA");

  random_shuffle(v.begin(),v.end());
  cout << "random shuffled: ";  print(v);

  sort(v.begin(),v.end(),string_less_ci);
  cout << "Case insensitive: ";  print(v);

  sort(v.begin(),v.end());
  cout << "Case sensitive: ";  print(v);

  sort(v.begin(),v.end(),string_less_cs3);
  cout << "Case sensitive (intrinseco): ";  print(v);

  random_shuffle(v.begin(),v.end());
  sort(v.begin(),v.end(),string_less_cs);
  cout << "Case sensitive (coded): ";  print(v);

  random_shuffle(v.begin(),v.end());
  sort(v.begin(),v.end(),string_less_cs2);
  cout << "Case sensitive (coded2): ";  print(v);
}
