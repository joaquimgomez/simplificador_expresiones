#include <string>
#include <iostream>

class token {
  /* Un "token" guarda la informació de l'element d'una expressió com un string. */

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
      /* Pre: un token que sigui un número enter */
      /* Post: donat un token número enter retorna el valor enter */

    bool to_bool() const;
      /* Pre: un token que sigui booleà */
      /* Post: donat un token booleà retorna el valor booleà true o false */

    string to_string() const;
      /* Pre: cert */
      /* Post: donat un token retorna el valor string corresponent */

    bool operator==(const token &t) const;
      /* Pre: cert */
      /* Post: indica si el token del p.i. és igual al token t */

    bool operator!=(const token &t) const;
      /* Pre: cert*/
      /* Post: indica si el token del p.i. és diferent al token t */

    bool operator==(const char s[]) const;
      /* Pre: cert */
      /* Post: indica si el token del p.i. és igual al string s */

    bool operator!=(const char s[]) const;
      /* Pre: cert */
      /* Post: indica si el token del p.i. és diferent al string s */

    friend istream& operator>>(istream& is, token &t);
      /* Pre: cert */
      /* Post: llegeix del canal d'entrada el contingut del token */

    friend ostream operator<<(ostream& os, const token &t);
      /* Pre: cert*/
      /* Post: mostra al canal de sortida el contingut del token */

};
