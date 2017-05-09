
string expressio_prefixa(arbre<token> a);
  /* Pre: a = A */
  /* Post: retorna un string amb el contingut d'A en notació prefixa */

string expressio_postfixa(arbre<token> a);
    /* Pre: a = A */
    /* Post: retorna un string amb el contingut d'A en notació postfixa */

string expressio_infixa(arbre<token> a);
    /* Pre: a = A */
    /* Post: retorna un string amb el contingut d'A en notació infixa */

arbre<token> llegir_prefixa();
    /* Pre: cert */
    /* Post: retorna un arbre amb l'expressió en notació prefixa rebuda pel canal
           estandar cin */

arbre<token> llegir_postfixa();
    /* Pre: cert */
    /* Post: retorna un arbre amb l'expressió en notació postfixa rebuda pel canal
           estandar cin */

arbre<token> llegir_infixa();
    /* Pre: cert */
    /* Post: retorna un arbre amb l'expressió en notació infixa rebuda pel
           canal estandar cin */             

bool equivalents(arbre<token> a, arbre<token> b);
    /* Pre: a = A, b = B */
    /* Post: retorna true si A i B son equivalents */

arbre<token> simplificar_operador_unari(token op, arbre<token> b);
    /* Pre: op = OP, b = B */
    /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

arbre<token> simplificar_operador_boolea(token op, arbre<token> b1, arbre<token> b2);
    /* Pre: op = OP, b1 = B1, b2 = B2 */
    /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

arbre<token> simplificar_operador_comparacio(token op, arbre<token> b1, arbre<token> b2);
    /* Pre: op = OP, b1 = B1, b2 = B2 */
    /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

arbre<token> simplificar_operador_aritmetic(token op, arbre<token> b1, arbre<token> b2);
    /* Pre: op = OP, b1 = B1, b2 = B2 */
    /* Post: intenta simplificar l'operació i retorna l'arbre resultant */

arbre<token> simplificar(arbre<token> a);
    /* Pre: a = A */
    /* Post: simplifica l'expressió tot el que pot i retorna l'arbre resultant */
