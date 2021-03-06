#include <iostream>
#include <string>
#include <stack>
#include <list>
#include <math.h>
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

arbre<token> simplificar_operador_unari(token op, arbre<token> b){

  /* Pre: op = OP operador unari i b = B arbre ja simplificat */
  /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

  if (b.arrel().es_boolea())  return arbre<token>(token(not b.arrel().to_bool()));
  else if (b.arrel() == "not")  return b.fe();
  else  return arbre<token>(op, b, arbre<token>());

}

arbre<token> simplificar_operador_boolea(token op, arbre<token> b1, arbre<token> b2){

  /* Pre: op = OP operador boolea, b1 = B1 i b2 = B2 arbres ja simplificats */
  /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

  arbre<token> simpl;

  if (op == "and" and (b1.arrel() == "F" or b2.arrel() == "F"))   simpl = arbre<token>(token(false));
  else if (op == "and" and b1.arrel() == "T")   simpl = arbre<token>(b2);
  else if (op == "and" and b2.arrel() == "T")   simpl = arbre<token>(b1);
  else if (op == "or" and (b1.arrel() == "T" or b2.arrel() == "T"))   simpl = arbre<token>(token(true));
  else if (op == "or" and b1.arrel() == "F")  simpl = arbre<token>(b2);
  else if (op == "or" and b2.arrel() == "F")  simpl = arbre<token>(b1);
  else if ((op == "and" or op == "or") and equivalents(b1, b2))   simpl = b2;
  else if (b1.arrel().es_boolea() and b2.arrel().es_boolea()){
    if (op == "or")   simpl = arbre<token>(token(b1.arrel().to_bool() or b2.arrel().to_bool()));
    else  simpl = arbre<token>(token(b1.arrel().to_bool() and b2.arrel().to_bool()));

  } else  simpl = arbre<token>(op, b1, b2);

  return simpl;

}

arbre<token> simplificar_operador_comparacio(token op, arbre<token> b1, arbre<token> b2){

  /* Pre: op = OP operador de comparació, b1 = B1 i b2 = B2 arbres ja simplificats */
  /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

  arbre<token> simpl;

  if (equivalents(b1, b2)){
    if (op == "==")   simpl = arbre<token>(token(true));
    else  simpl = arbre<token>(token(false));

  } else if ((b1.arrel().es_enter() and b2.arrel().es_enter()) or (b1.arrel().es_boolea() and b2.arrel().es_boolea())){
    if (op == "==")   simpl = arbre<token>(token(b1.arrel() == b2.arrel()));
    else  simpl = arbre<token>(token(b1.arrel() != b2.arrel()));

  } else  simpl = arbre<token>(op, b1, b2);

  return simpl;

}

arbre<token> simplificar_operador_aritmetic(token op, arbre<token> b1, arbre<token> b2){

  /* Pre: op = OP operador aritmètic, b1 = B1 i b2 = B2 arbres ja simplificats */
  /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

  arbre<token> simpl;

  if (b1.arrel().es_enter() and b2.arrel().es_enter()){
    if (op == "*")  simpl = arbre<token>(token(b1.arrel().to_int() * b2.arrel().to_int()));
    else if (op == "+")   simpl = arbre<token>(token(b1.arrel().to_int() + b2.arrel().to_int()));
    else if (op == "-")   simpl = arbre<token>(token(b1.arrel().to_int() - b2.arrel().to_int()));
    else if (op == "/")   simpl = arbre<token>(token(b1.arrel().to_int() / b2.arrel().to_int()));
    else  simpl = arbre<token>(token((int) pow(b1.arrel().to_int(), b2.arrel().to_int())));

  } else if (not b1.arrel().es_enter() or not b2.arrel().es_enter()){
    if (op == "*"){
      if (b1.arrel() == "0" or b2.arrel() == "0")   simpl = arbre<token>(token(0));
      else if (b1.arrel() == "1")   simpl = b2;
      else if (b2.arrel() == "1")   simpl = b1;
      else  simpl = arbre<token>(op, b1, b2);

    } else if (op == "+"){
      if (b1.arrel() == "0")  simpl = b2;
      else if (b2.arrel() == "0")   simpl = b1;
      else  simpl = arbre<token>(op, b1, b2);

    } else if (op == "-"){
      if (b2.arrel() == "0")  simpl = b1;
      else if (equivalents(b1, b2))   simpl = arbre<token>(token(0));
      else  simpl = arbre<token>(op, b1, b2);

    } else if (op == "/"){
      if (b1.arrel() == "0")  simpl = arbre<token>(token(0));
      else if (b2.arrel() == "1")  simpl = b1;
      else if (equivalents(b1, b2))   simpl = arbre<token>(token(1));
      else  simpl = arbre<token>(op, b1, b2);

    } else if (op == "**"){
      if (b1.arrel() == "0")  simpl = arbre<token>(token(0));
      else if (b1.arrel() == "1")   simpl = arbre<token>(token(1));
      else if (b2.arrel() == "0")   simpl = arbre<token>(token(1));
      else if (b2.arrel() == "1")   simpl = b1;
      else  simpl = arbre<token>(op, b1, b2);

    }
  } else simpl = arbre<token>(op, b1, b2);

  return simpl;

}

arbre<token> simplificar(arbre<token> a){

  /* Pre: a = A */
  /* Post: simplifica l'expressió tot el que pot i retorna l'arbre resultant */

  arbre<token> simpl;
  if (not a.arrel().es_operador_binari() and not a.arrel().es_operador_unari())  simpl = a;
  else if (a.arrel().es_operador_binari()){
    arbre<token> simpl_fe = simplificar(a.fe());
    /* HI1: simpl_fe = "simplificació del fill esquerre d'A" */
    arbre<token> simpl_fd = simplificar(a.fd());
    /* HI2: simpl_fd = "simplificació del fill dret d'A" */

    if (a.arrel() == "and" or a.arrel() == "or")  simpl = simplificar_operador_boolea(a.arrel(), simpl_fe, simpl_fd);
    else if (a.arrel() == "==" or a.arrel() == "!=")  simpl = simplificar_operador_comparacio(a.arrel(), simpl_fe, simpl_fd);
    else  simpl = simplificar_operador_aritmetic(a.arrel(), simpl_fe, simpl_fd);

  } else {
    arbre<token> simpl_fe = simplificar(a.fe());
    /* HI3: simpl_fe = "simplificació del fill esquerre d'A" */

    simpl = simplificar_operador_unari(a.arrel(), simpl_fe);
  }

  /* Funció de fita: tamany d'A */

  return simpl;

}

int prioritat_token(token op){

  /* Pre: op = OP i és un operador aritmétic */
  /* Post: retorna la prioritat de l'operador OP */

  int prioritat;

  if (op == "or")   prioritat = 1;
  else if (op == "and")   prioritat = 2;
  else if (op == "not")   prioritat = 3;
  else if (op == "==" or op == "!=")  prioritat = 4;
  else if (op == "+" or op == "-")  prioritat = 5;
  else if (op == "*" or op == "/")  prioritat = 6;
  else  prioritat = 7;

  return prioritat;

}

arbre<token> llegir_infixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació infixa rebuda pel
            canal estandar cin */

  stack<token> ops;
  stack<arbre<token> > res;

  token t;
  while(cin >> t and t != "->"){
    /* Inv: ops = "operadors que s'han llegit pel canal estandar i encara no s'han tractat",
       a1 = a2 = "subarbre que s'astà tractant actualment" i
       res = "arbres parcials de l'expressió infixa" */

    if (t == "(")   ops.push(t);
    else if (t == ")"){
      while (ops.top() != "("){
        /* Inv: ops = "operadors que s'han llegit pel canal estandar i encara no s'han tractat",
           res = "arbres parcials de l'expressió infixa" i
           a1 = a2 = "arbres parcials de l'expressió infixa" */

        if (ops.top().es_operador_unari()){
          arbre<token> a1 = res.top();
          res.pop();

          res.push(arbre<token>(ops.top(), a1, arbre<token>()));
        } else {
          arbre<token> a1 = res.top();
          res.pop();
          arbre<token> a2 = res.top();
          res.pop();

          res.push(arbre<token>(ops.top(), a2, a1));
        }

        ops.pop();

      }

      ops.pop();

    } else if (not t.es_operador_unari() and not t.es_operador_binari())  res.push(arbre<token>(t));
    else {
      while (ops.size() > 0 and ops.top() != "(" and ((prioritat_token(t) < prioritat_token(ops.top())) or (prioritat_token(t) == prioritat_token(ops.top()) and t != "not" and t != "**"))){
        /* Inv: op = "operador amb prioritat superior o igual a t",
           ops = "operadors que s'han llegit pel canal estandar i encara no s'han tractat",
           a1 = a2 = "subarbre que s'astà tractant actualment" i
           res = "arbres parcials de l'expressió infixa" */

        token op = ops.top();
        ops.pop();

        if (op.es_operador_unari()){
          arbre<token> a1 = res.top();
          res.pop();

          res.push(arbre<token>(op, a1, arbre<token>()));
        } else {
          arbre<token> a1 = res.top();
          res.pop();
          arbre<token> a2 = res.top();
          res.pop();

          res.push(arbre<token>(op, a2, a1));
        }

      }

      ops.push(t);

    }

  }


  while (not ops.empty()){
      /* Inv: ops = "operadors que s'han llegit pel canal estandar i encara no s'han tractat",
         a1 = a2 = "subarbre que s'astà tractant actualment" i
         res = "arbres parcials de l'expressió infixa" */

    if (ops.top() != "("){
      arbre<token> a1, a2;

      if (ops.top().es_operador_unari()){
        a1 = res.top();
        res.pop();

        res.push(arbre<token>(ops.top(), a1, arbre<token>()));
      } else {
        a1 = res.top();
        res.pop();
        a2 = res.top();
        res.pop();

        res.push(arbre<token>(ops.top(), a2, a1));
      }

    }

    ops.pop();

  }

  return res.top();

}


int main(){

  arbre<token> a, simpl;
  string res, form1, form2;

  while (cin >> form1){
    /* Inv: form1 = "format en que s'ha de llegir l'expressió per generar l'arbre",
       form2 = "format desitjat de sortida",
       item = "recollida de -> inservible",
       a = "arbre generat a partir de l'expressió rebuda en el format de form1" i
       res = "string amb l'expressió en el format de form2" */

    if (form1 == "PREFIXA"){
      a = llegir_prefixa();
      string item;
      cin >> item;

    } else if (form1 == "POSTFIXA") a = llegir_postfixa();
    else  a = llegir_infixa();
    //cout << a << endl;

    simpl = simplificar(a);
    //cout << simpl << endl;

    cin >> form2;
    if (form2 == "PREFIXA") res = expressio_prefixa(simpl);
    else if (form2 == "POSTFIXA") res = expressio_postfixa(simpl);
    else res = expressio_infixa(simpl);

    cout << res << endl;

  }

}
