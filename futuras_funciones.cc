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

  if (b.arrel() == "F")  return arbre<token>(token("T"));
  else if (b.arrel() == "T")   return arbre<token>(token("F"));
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
