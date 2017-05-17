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
    /* Inv: a1 = "part d'A que s'està tractant actualment",
       p = "elements d'A que queden per analitzar" i
       ExpPre = "expressió resultant de la part analitzada d'A". */

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
    /* Inv: a1 = "part d'A que s'està tractant actualment",
       p = "elements d'A que queden per analitzar" i
       l = "elements d'A que ja s'han recollit". */

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
    /* Inv: ExpPos = "expressió resultat de la part analitzada de l" i
       l = "elements que queden per tractar". */
    ExpPos += (*(l.begin())).to_string() + " ";
    l.erase(l.begin());
  }

  return ExpPos;

}

string expressio_infixa(arbre<token> a){

  /* Pre: a = A */
  /* Post: retorna un string amb el contingut d'A en notació infixa */

  string ExpInf;
  if (not a.arrel().es_operador_binari() and not a.arrel().es_operador_unari())   ExpInf = a.arrel().to_string();   // Cas Basic: t no és un operador, aleshores és una fulla.
  else if (not a.fd().es_buit() and not a.fe().es_buit())  ExpInf = "(" + expressio_infixa(a.fe()) + " " + a.arrel().to_string() + " " + expressio_infixa(a.fd()) + ")";  // Cas Recursiu 1: t és un operador binari.
  else  ExpInf = "(" + a.arrel().to_string() + " " + expressio_infixa(a.fe()) + ")";  // Cas Recursiu 2: t és un operador unari.

  /* HI: ExpInf = "expressió infixa generada a partir d'A" */
  /* Funció de fita: nombre d'elements d'A */

  return ExpInf;

}

arbre<token> llegir_prefixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació prefixa rebuda pel canal
           estandar cin */

  arbre<token> a;
  token t;

  cin >> t;
  if (not t.es_operador_binari() and not t.es_operador_unari())  return arbre<token>(t);  // Cas Basic: t no és un operador.
  else {
    if (t.es_operador_unari())  return arbre<token>(t, llegir_prefixa(), arbre<token>());   // Cas Recursiu 1: t és un operador unari.
    else  return arbre<token>(t, llegir_prefixa(), llegir_prefixa());   // Cas Recursiu 2: t és un poperador binari
  }

  /* HI: es retorna un subarbre a partir de l'expressió llegida pel canal estandar cin */
  /* Funció de fita: contingut al canal estandar cin */

}

arbre<token> llegir_postfixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació postfixa rebuda pel canal
           estandar cin */

  stack<arbre<token> > p;

  token t;
  while(cin >> t and t != "->"){
    /* Inv: t = "token actual que s'ha d'introduir a l'arbre",
       p = "subarbres ja costruits" i
       a = a1 = a2 = "subarbre que s'està construint actualment" */

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

bool equivalents(arbre<token> a, arbre<token> b){

  /* Pre: a = A, b = B */
  /* Post: retorna true si A i B son equivalents */

  bool eq = true;

  if (not a.es_buit() and not b.es_buit()){
    if (a.arrel() != b.arrel())   eq = false;
    else {
      if (a.arrel().es_operador_unari())  eq = equivalents(a.fe(), b.fe());
      else if (a.arrel().es_operador_commutatiu())   eq = (equivalents(a.fd(), b.fd()) and equivalents(a.fe(), b.fe())) or (equivalents(a.fd(), b.fe()) and equivalents(a.fe(), b.fd()));
      else  eq = equivalents(a.fe(), b.fe()) and equivalents(a.fd(), b.fd());
    }
  }

  /* HI: */
  /* Funció de Fita: */

  return eq;

}

arbre<token> simplificar_operador_unari(token op, arbre<token> b){

  /* Pre: op = OP, b = B */
  /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

  if (b.arrel() == "F")  return arbre<token>(token(true));
  else if (b.arrel() == "T")   return arbre<token>(token(false));
  else if (b.arrel() == "not") return b.fe().arrel();
  else return arbre<token>(op, b, arbre<token>());

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

arbre<token> llegir_infixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació infixa rebuda pel
           canal estandar cin */

}

int main(){

  arbre<token> a;
  string res, form1, form2;

  while (cin >> form1){
    /* Inv: form1 = "format en que s'ha de llegir l'expressió per generar l'arbre",
       form2 = "format desitjat de sortida",
       item = "recolliment de -> inservible",
       a = "arbre generat a partir de l'expressió rebuda en el format de form1" i
       res = "string amb l'expressió en el format de form2" */

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
