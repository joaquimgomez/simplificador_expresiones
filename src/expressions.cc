#include <iostream>
#include <string>
#include <stack>
#include <list>
#include "arbre.h"
#include "token.h"
#include "expressions.h"
using namespace std;


string expressio_prefixa(arbre<token> a){

  /* Pre: a = A */
  /* Post: retorna un string amb el contingut d'A en notació prefixa */

  stack<arbre<token>> p;
  p.push(a);

  string ExpPre;
  int i = 0;
  while(not p.empty()){
    /* Inv: */

    arbre<int> a1 = p.top();
    p.pop();

    if (not a1.es_buit()){
      if (i == 0)  ExpPre = a1.arrel().to_string();
      else  ExpPre += " " + a1.arrel().to_string();

      if (not a1.fd().es_buit())  p.push(a1.fd());
      if (not a1.fe().es_buit())  p.push(a1.fe());
    }

    ++i;

  }

  return ExpPre;

}

string expressio_postfixa(arbre<token> a){

  /* Pre: a = A */
  /* Post: retorna un string amb el contingut d'A en notació postfixa */

  stack<arbre<token>> p;
  p.push(a);

  list<token> l;
  while (not p.empty()){
    /* Inv: */

    arbre<int> a1 = p.top();
    p.pop();

    if (not a1.es_buit()){
      l.insert(l.begin(), a1.arrel());
      if (not a1.fe().es_buit())  p.push(a1.fe());
      if (not a1.fd().es_buit())  p.push(a1.fd());
    }

  }

  string ExpPos;
  int i = 0;
  while (not l.empty()){
    if (i == 0)   ExpPos = (*(l.begin())).to_string();
    else  ExpPos += " " + (*(l.begin())).to_string();
  }

  return ExpPos;

}

string expressio_infixa(arbre<token> a){

  /* Pre: a = A */
  /* Post: retorna un string amb el contingut d'A en notació infixa */

  stack<arbre<token>> p;
  p.push(a)

  string ExpInf;
  while(not p.empty()){
    /* Inv:  */

    arbre<token> a1 = p.top();
    p.pop();

    if (a1.fd().es_buit() and a1.fe().es_buit())  ExpInf += a1.arrel().to_string();
    else {
      if (not a1.fd().es_buit())  p.push(a1.fd());
      if (not a1.fe().es_buit())  p.push(a1.fe());
    }

  }

  return ExpInf;

}

arbre<token> llegir_prefixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació prefixa rebuda pel canal
           estandar cin */

  arbre<token> a;
  token t;

  if (cin >> t and t!= "->")   return a = arbre(t, LlegirPrefixa(), LlegirPrefixa());
  else  return a;

  /* HP: */
  /* Funció de fita: contingut al canal estandar cin */

}

arbre<token> llegir_postfixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació postfixa rebuda pel canal
           estandar cin */

  stack<arbre<token> > p;

  token t;
  while(cin >> t and t!= "->"){
    if (not t.es_operador_unari() and not t.es_operador_unari()){
      p.push(arbre(t));
    } else if (t.es_operador_unari()){
      arbre<token> a = p.top();
      p.pop();

      p.push(arbre(t, a));
    } else {
      arbre<token> a1 = p.top();
      p.pop();
      arbre<token> a2 = p.top();
      p.pop();

      p.push(arbre(t, a1, a2));
    }
  }

  return p.top();

}

arbre<token> llegir_infixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació infixa rebuda pel
           canal estandar cin */

}

bool equivalents(arbre<token> a, arbre<token> b){

  /* Pre: a = A, b = B */
  /* Post: retorna true si A i B son equivalents */

}

arbre<token> simplificar_operador_unari(token op, arbre<token> b){

  /* Pre: op = OP, b = B */
  /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

}

arbre<token> simplificar_operador_boolea(token op, arbre<token> b1, arbre<token> b2){

  /* Pre: op = OP, b1 = B1, b2 = B2 */
  /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

}

arbre<token> simplificar_operador_comparacio(token op, arbre<token> b1, arbre<token> b2){

  /* Pre: op = OP, b1 = B1, b2 = B2 */
  /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

}

arbre<token> simplificar_operador_aritmetic(token op, arbre<token> b1, arbre<token> b2){

  /* Pre: op = OP, b1 = B1, b2 = B2 */
  /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

}

arbre<token> simplificar(arbre<token> a){

  /* Pre: a = A */
  /* Post: simplifica l'expressió tot el que pot i retorna l'arbre resultant */

}



int main(){
  
  arbre<token> a;
  string res, form1, form2;
  
  while (cin >> form1){
   if (form1 == "PREFIXA") a = llegir_prefixa();
   else if (form1 == "POSTFIXA") a = llegir_postfixa(); 
   cin >> form2;
    if (form2 == "PREFIXA") res = expressio_prefixa(a);
    else if (form2 == "POSTFIXA") res = expressio_postfixa(a);
    else if (form2 == "INFIXA") res = expressio_infixa(a);
  cout << res << endl;
  cout << a;
  }
}
