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
       ExpPre = "expressió resultant de la part analitzada d'A" */
    /* Funció de fita: tamany de p (p.size()) */

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
       l = "elements d'A que ja s'han recollit" */
    /* Funció de fita: tamany de p (p.size()) */

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
       l = "elements que queden per tractar" */
    /* Funció de fita: tamany de l (l.size()) */

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
  /* HI1: ExpInf = "expressió infixa generada a partir del fill esquerre d'A" */
  /* HI2: ExpInf = "expressió infixa generada a partir del fill dret d'A" */
  else  ExpInf = "(" + a.arrel().to_string() + " " + expressio_infixa(a.fe()) + ")";  // Cas Recursiu 2: t és un operador unari.
  /* HI3: ExpInf = "expressió infixa generada a partir del fill esquerre d'A" */

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
    /* HI1: es retorna un subarbre esquerre a partir de l'expressió llegida pel canal estandar cin */
    else  return arbre<token>(t, llegir_prefixa(), llegir_prefixa()); // Cas Recursiu 2: t és un poperador binari
    /* HI2: es retorna un subarbre esquerre a partir de l'expressió llegida pel canal estandar cin */
    /* HI3: es retorna un subarbre dret a partir de l'expressió llegida pel canal estandar cin */
  }

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
    /* Funció de fita: tamany del flux del canal d'entrada estandar cin */

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
      /* HI1: eq ens diu si els fills esquerres d'A i de B son equivalents */
      else if (a.arrel().es_operador_commutatiu())   eq = (equivalents(a.fd(), b.fd()) and equivalents(a.fe(), b.fe())) or (equivalents(a.fd(), b.fe()) and equivalents(a.fe(), b.fd()));
      /* HI2: eq ens diu si els fills drets d'A i de B son equivalents i els fills esquerres d'A i de B son equivalents, alhora
         o si el fill dret d'A i el fill esquerre de B son equivalents i el fill esquerre d'A i el fill dret de B son equivalents, alhora */
      else  eq = equivalents(a.fe(), b.fe()) and equivalents(a.fd(), b.fd());
      /* HI3: eq ens diu si els fills esquerres d'A i de B son equivalents i els fills drets d'A i de B son equivalents, alhora */
    }
  }

  /* Funció de Fita: tamany d'A i de B */

  return eq;

}


int main(){
  arbre<token> a, b;
  string form_a, form_b;

  while (cin >> form_a){
    /* Inv: form_a = "format en que s'ha de llegir l'expressió a per generar l'arbre a",
       form_b = "format en que s'ha de llegir l'expressió b per generar l'arbre b",
       a = "arbre generat a partir de l'expressió rebuda en el format form_a" i
       b = "arbre generat a partir de l'expressió rebuda en el format form_b" */
       
    if (form_a == "PREFIXA")  a = llegir_prefixa();
    else if (form_a == "POSTFIXA") a = llegir_postfixa();

    cin >> form_b;
    if (form_b == "PREFIXA")  b = llegir_prefixa();
    else if (form_b == "POSTFIXA") b = llegir_postfixa();


    cout << equivalents(a,b) << " " << expressio_infixa(a) << " " << expressio_infixa(b) << endl;

  }

}
