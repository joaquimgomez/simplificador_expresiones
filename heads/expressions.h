
string ExpressioPrefixa(arbre<token> a);
  /* Pre: */
  /* Post: */

string ExpressioPostfixa(arbre<token> a);
    /* Pre: */
    /* Post: */

string ExpressioInfixa(arbre<token> a);
    /* Pre: */
    /* Post: */

arbre<token> LlegirPrefixa();
    /* Pre: */
    /* Post: */

arbre<token> LlegirPostfixa();
    /* Pre: */
    /* Post: */

arbre<token> LlegirInfixa();
    /* Pre: */
    /* Post: */

bool equivalents(arbre<token> a, arbre<token> b);
    /* Pre: */
    /* Post: */

arbre<token> simplificar_operador_unari(token op, arbre<token> b);
    /* Pre: */
    /* Post: */

arbre<token> simplificar_operador_boolea(token op, arbre<token> b1, arbre<token> b2);
    /* Pre: */
    /* Post: */

arbre<token> simplificar_operador_comparacio(token op, arbre<token> b1, arbre<token> b2);
    /* Pre: */
    /* Post: */

arbre<token> simplificar_operador_aritmetic(token op, arbre<token> b1, arbre<token> b2);
    /* Pre: */
    /* Post: */

arbre<token> simplificar(arbre<token> a);
    /* Pre: */
    /* Post: */
