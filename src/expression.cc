#include <iostream>
#include <string>
#include <stack>
#include "arbre.h"
#include "token.h"
using namespace std;


string ExpressioPrefixa(arbre<token> a){

  /* Pre: a = A */
  /* Post: retorna un string amb el contingut d'A en notació prefixa */

  stack<arbre<token>> p;
  p.push(a);

  string ExpPre;
  while(not p.empty()){
    /* Inv: */

    arbre<int> a1 = p.top();
    p.pop();

    if (not a1.es_buit()){
      ExpPre += a1.arrel().to_string();
      if (not a1.fd().es_buit())  p.push(a1.fd());
      if (not a1.fe().es_buit())  p.push(a1.fe());
    }

  }

  return ExpPre;

}

string ExpressioPostfixa(arbre<token> a){

    /* Pre: a = A */
    /* Post: retorna un string amb el contingut d'A en notació postfixa */

    stack<arbre<token>> p;
    p.push(a);

    string ExpPos;
    while(not p.empty()){
      /* Inv: */

      arbre<int> a1 = p.top();
      p.pop();

      if (not a1.es_buit()){
        if (not a1.fd().es_buit())  p.push(a1.fd());
        if (not a1.fe().es_buit())  p.push(a1.fe());
      }

    }

}

string ExpressioInfixa(arbre<token> a){

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

arbre<token> LlegirPrefixa(){

    /* Pre: cert */
    /* Post: retorna un arbre amb l'expressió en notació prefixa rebuda pel canal
             estandar cin */

    arbre<token> a;
    token t;

    if (cin >> t)   return a = arbre(t, LlegirPrefixa(), LlegirPrefixa());
    else  return a;

    /* HP: */
    /* Funció de fita: contingut al canal estandar cin */

}

arbre<token> LlegirPostfixa(){

    /* Pre: cert */
    /* Post: retorna un arbre amb l'expressió en notació postfixa rebuda pel canal
             estandar cin */

    stack<arbre<token> > p;

    token t;
    while(cin >> t){
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

        p.push(t, a1, a2);
      }
    }

    return p.top();

}

arbre<token> LlegirInfixa(){

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
    /* Post: */

}

arbre<token> simplificar_operador_boolea(token op, arbre<token> b1, arbre<token> b2){

    /* Pre: op = OP, b1 = B1, b2 = B2 */
    /* Post: */

}

arbre<token> simplificar_operador_comparacio(token op, arbre<token> b1, arbre<token> b2){

    /* Pre: op = OP, b1 = B1, b2 = B2 */
    /* Post: */

}

arbre<token> simplificar_operador_aritmetic(token op, arbre<token> b1, arbre<token> b2){

    /* Pre: op = OP, b1 = B1, b2 = B2 */
    /* Post: */

}

arbre<token> simplificar(arbre<token> a){

    /* Pre: a = A */
    /* Post: */

}
