bool check2(stack &P,double &v1, double&v2) {
  if (P.size()<2) {
    cout << "Debe haber al menos 2 elementos en la pila!!\n";
    return false;
  } else {
    v2 = P.top(); P.pop();
    v1 = P.top(); P.pop();
    return true;
  }
}

bool check1(stack &P,double &v1) {
  if (P.size()<1) {
    cout << "Debe haber al menos 1 elemento en la pila!!\n";
    return false;
  } else {
    v1 = P.top(); P.pop();
    return true;
  }
}

int main() {
  stack P,Q;
  const int SIZE=100;
  char line[SIZE];
  double v1,v2;
  // REPL (read, eval print loop)
  while(true) {
    // Read 
    cout << "calc> ";
    assert(line);
    cin.getline(line,SIZE,'\n');
    if(!cin) break;
    // `Eval' y `print' dependiendo del caso
    if (!strcmp(line,"+")) {
      if (check2(P,v1,v2)) {
	P.push(v1+v2);
	printf("-> %lf\n",P.top());
      }
    } else if (!strcmp(line,"-")) {
      if (check2(P,v1,v2)) {
	P.push(v1-v2);
	printf("-> %lf\n",P.top());
      }
    } else if (!strcmp(line,"*")) {
      if (check2(P,v1,v2)) {
	P.push(v1*v2);
	printf("-> %lf\n",P.top());
      }
    } else if (!strcmp(line,"/")) {
      if (check2(P,v1,v2)) {
	P.push(v1/v2);
	printf("-> %lf\n",P.top());
      }
    } else if (!strcmp(line,"log")) {
      if (check1(P,v1)) {
	P.push(log(v1));
	printf("-> %lf\n",P.top());
      }
    } else if (!strcmp(line,"exp")) {
      if (check1(P,v1)) {
	P.push(exp(v1));
	printf("-> %lf\n",P.top());
      }
    } else if (!strcmp(line,"sqrt")) {
      if (check1(P,v1)) {
	P.push(sqrt(v1));
	printf("-> %lf\n",P.top());
      }
    } else if (!strcmp(line,"atan2")) {
      if (check2(P,v1,v2)) {
	P.push(atan2(v1,v2));
	printf("-> %lf\n",P.top());
      }
    } else if (!strcmp(line,"c")) {
      printf("vaciando la pila...\n");
      P.clear();
    } else if (!strcmp(line,"p")) {
      printf("pila: ");
      while(!P.empty()) { 
	double x = P.top();
	cout << x << " ";
	P.pop();
	Q.push(x);
      }
      while(!Q.empty()) {
	double x = Q.top();
	Q.pop();
	P.push(x);
      }
      cout << endl;
    } else if (!strcmp(line,"x")) {
      "Saliendo de calc!!\n";
      exit(0);
    } else {
      double val;
      int nread = sscanf(line,"%lf",&val);
      if (nread!=1) {
	printf("Entrada invalida!!: \"%s\"\n",line);
	continue;
      } else {
	P.push(val);
	printf("<- %g\n",val);
      }
    }
  }
}
