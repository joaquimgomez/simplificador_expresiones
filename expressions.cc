#include <iostream>
#include <string>
#include <stack>
#include <list>
#include "arbre.h"
#include "token.h"
using namespace std;


string expressio_prefixa(arbre<token> a){

  /* Pre: a = A */
  /* Post: retorna un string amb el contingut d'A en notació prefixa */

  stack<arbre<token> > p;
  p.push(a);

  string ExpPre;
  while(not p.empty()){
    /* Inv: */

    arbre<token> a1 = p.top();
    p.pop();

    if (not a1.es_buit()){
      ExpPre = ExpPre += a1.arrel().to_string() + " ";

      if (not a1.fd().es_buit())  p.push(a1.fd());
      if (not a1.fe().es_buit())  p.push(a1.fe());
    }

  }

  return ExpPre;

}

string expressio_postfixa(arbre<token> a){

  /* Pre: a = A */
  /* Post: retorna un string amb el contingut d'A en notació postfixa */

  stack<arbre<token> > p;
  p.push(a);

  list<token> l;
  while (not p.empty()){
    /* Inv: */

    arbre<token> a1 = p.top();
    p.pop();

    if (not a1.es_buit()){
      l.insert(l.begin(), a1.arrel());
      if (not a1.fe().es_buit())  p.push(a1.fe());
      if (not a1.fd().es_buit())  p.push(a1.fd());
    }

  }

  string ExpPos;
  while (not l.empty()){
    /* Inv: */
    ExpPos += (*(l.begin())).to_string() + " ";
    l.erase(l.begin());
  }

  return ExpPos;

}

string expressio_infixa(arbre<token> a){

  /* Pre: a = A */
  /* Post: retorna un string amb el contingut d'A en notació infixa */

  string ExpInf;
  if (not a.arrel().es_operador_binari() and not a.arrel().es_operador_unari())   ExpInf = a.arrel().to_string();
  else if (not a.fd().es_buit() and not a.fe().es_buit())  ExpInf = "(" + expressio_infixa(a.fe()) + " " + a.arrel().to_string() + " " + expressio_infixa(a.fd()) + ")";
  else  ExpInf = "(" + a.arrel().to_string() + " " + expressio_infixa(a.fe()) + ")";

  return ExpInf;

}

arbre<token> llegir_prefixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació prefixa rebuda pel canal
           estandar cin */

  arbre<token> a;
  token t;

  cin >> t;
  if (not t.es_operador_binari() and not t.es_operador_unari())  return arbre<token>(t);  // Cas Basic: t no es un operador.
  else {
    if (t.es_operador_unari())  return arbre<token>(t, llegir_prefixa(), arbre<token>());   // Cas Recursiu 1: t es un operador unari.
    else  return arbre<token>(t, llegir_prefixa(), llegir_prefixa());   // Cas Recursiu 2: t es un poperador binari
  }

  /* HP: */
  /* Funció de fita: contingut al canal estandar cin */

}

arbre<token> llegir_postfixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació postfixa rebuda pel canal
           estandar cin */

  stack<arbre<token> > p;

  token t;
  while(cin >> t and t != "->"){
    /* Inv: */
    if (not t.es_operador_unari() and not t.es_operador_binari()){
      p.push(arbre<token>(t));

    } else if (t.es_operador_unari()){
      arbre<token> a = p.top();
      p.pop();

      p.push(arbre<token>(t, a, arbre<token>()));

    } else {
      arbre<token> a1 = p.top();
      p.pop();
      arbre<token> a2 = p.top();
      p.pop();

      p.push(arbre<token>(t, a2, a1));

    }

  }

  return p.top();

}


int main(){

  arbre<token> a;
  string res, form1, form2;

  while (cin >> form1){
    if (form1 == "PREFIXA"){
      a = llegir_prefixa();
      string item;
      cin >> item;

    } else if (form1 == "POSTFIXA") a = llegir_postfixa();

    //cout << a << endl;
    cin >> form2;

    if (form2 == "PREFIXA") res = expressio_prefixa(a);
    else if (form2 == "POSTFIXA") res = expressio_postfixa(a);
    else if (form2 == "INFIXA") res = expressio_infixa(a);

    cout << res << endl;
  }

}
