#include <iostream>
#include <string>
#include "token.h"
using namespace std;

int main(){
  token t, tAnt;

  int i = 0;
  while (cin >> t){
    cout << "=============================" << endl;
    cout << "TOKEN: " << t << endl;
    cout << "És un operador unari: " << t.es_operador_unari() << endl;
    cout << "És un operador binari: " << t.es_operador_binari() << endl;
    cout << "És un operador commutatiu: " << t.es_operador_commutatiu() << endl;
    cout << "És un valor booleà: " << t.es_boolea() << endl;
    cout << "És un valor enter: " << t.es_enter() << endl;
    cout << "És una variable: " << t.es_variable() << endl;
    cout << "Valor string: " << t.to_string() << endl;

    if (i != 0){
      cout << t << " i " << t << " són iguals: " << (t == t) << endl;
      cout << t << " i " << tAnt << " són iguals: " << (t == tAnt) << endl;
      cout << t << " i " << t << " són diferents: " << (t != t) << endl;
      cout << t << " i " << tAnt << " són diferents: " << (t != tAnt) << endl;
    }

    tAnt = t;
    ++i;
  }

  cout << "=============================" << endl;

}
