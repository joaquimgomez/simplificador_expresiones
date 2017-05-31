#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
using namespace std;

class token{
  /* Tipus de modul: dades.
     Descripció del tipus: guarda la informació de l'element
                           d'una expressió com un string.*/

  private:

    string t;

  public:
    token();
      /* Pre: cert */
      /* Post: crea un token enter de valor 0 */

    token(int i);
      /* Pre: cert */
      /* Post: crea un token a partir de l'enter i */

    token(bool b);
      /* Pre: cert */
      /* Post: crea un token a partir del booleà b */

    token(string s);
      /* Pre: cert */
      /* Post: crea un token a partir del string s (un operador o una variable) */

    bool es_operador_unari() const;
      /* Pre: cert */
      /* Post: indica si el token és un operador unari */

    bool es_operador_binari() const;
     /* Pre: cert */
     /* Post: indica si el token és un operador binari */

    bool es_operador_commutatiu() const;
      /* Pre: cert */
      /* Post: indica si el token és un operador commutatiu */

    bool es_boolea() const;
      /* Pre: cert */
      /* Post: indica si el token és una constant booleana */

    bool es_enter() const;
      /* Pre: cert */
      /* Post: indica si el token és una constant entera */

    bool es_variable() const;
      /* Pre: cert */
      /* Post: indica si el token és una variable */

    int to_int() const;
      /* Pre: el p.i. es un enter */
      /* Post: retorna el valor enter del p.i. */

    bool to_bool() const;
      /* Pre: el p.i. es un booleà */
      /* Post: reotrna el valor booleà true o false del p.i. */

    string to_string() const;
      /* Pre: el p.i. es un string */
      /* Post: retorna un string del token del p.i. */

    bool operator==(const token &t) const;
      /* Pre: cert */
      /* Post: indica si el token del p.i. és igual al token t */

    bool operator!=(const token &t) const;
      /* Pre: cert */
      /* Post: indica si el token del p.i. és diferent al token t */

    bool operator==(const char s[]) const;
      /* Pre: cert */
      /* Post: indica si el token del p.i. és igual al string s */

    bool operator!=(const char s[]) const;
      /* Pre: cert */
      /* Post: indica si el token del p.i. és diferent al string s */

    friend istream& operator>>(istream &is, token &t);
      /* Pre: cert */
      /* Post: llegeix del canal d'entrada el contingut del token */

    friend ostream& operator<<(ostream &os, const token &t);
      /* Pre: cert */
      /* Post: mostra al canal de sortida el contingut del token */

};
