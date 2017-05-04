#include "token.h"

token::token(){
  /* Pre: cert */
  /* Post: crea un token enter de valor 0 */

  t = "0";

}

token::token(int i){
  /* Pre: cert */
  /* Post: crea un token a partir de l'enter i */

  t = ::to_string(i);

}

token::token(bool b){
  /* Pre: cert */
  /* Post: crea un token a partir del booleà b */

  if (b)  t = "T";
  else  t = "F";

}

token::token(string s){
  /* Pre: cert */
  /* Post: crea un token a partir del string s (un operador o una variable) */

  t = s;

}

bool token::es_operador_unari() const{
  /* Pre: cert */
  /* Post: indica si el token és un operador unari */

  return t == "not";

}

bool token::es_operador_binari() const{
  /* Pre: cert */
  /* Post: indica si el token és un operador binari */

  return t == "or" or t == "and" or t == "==" or t == "!=" or t == "+" or t == "-" or t == "/" or t == "*" or t == "**";

}

bool token::es_operador_commutatiu() const{
  /* Pre: cert */
  /* Post: indica si el token és un operador commutatiu */

  return t == "or" or t == "and" or t == "==" or t == "!=" or t == "+" or t == "*";

}

bool token::es_boolea() const{
  /* Pre: cert */
  /* Post: indica si el token és una constant booleana */

  return t == "T" or t == "F";

}

bool token::es_enter() const{
  /* Pre: cert */
  /* Post: indica si el token és una constant entera */

  return t[0] >= '0' and t[0] <= '9';
  /*return t != "T" and t != "F" and not (t[0] >= 'a' and t[0] <= 'z') and not (t[0] >= 'A' and t[0] <= 'Z')
         and t != "or" and t != "not" and t != "and" and t != "!=" and t != "==" and t != "+" and t != "-"
         and t != "*" and t != "**" and t != "/"; */

}

bool token::es_variable() const{
  /* Pre: cert */
  /* Post: indica si el token és una variable */

  return t != "T" and t != "F" and t != "and" and t!= "or" and t != "not" and ((t[0] >= 'a' and t[0] <= 'z') or (t[0] >= 'A' and t[0] <= 'Z'));

}

int token::to_int() const{
  /* Pre: cert */
  /* Post: donat un token número enter retorna el valor enter */

  return stoi(t);

}

bool token::to_bool() const{
  /* Pre: cert */
  /* Post: donat un token booleà retorna el valor booleà true o false */

  return t == "T";

}

string token::to_string() const{
  /* Pre: cert */
  /* Post: donat un token retorna el valor string corresponent */

  return t;

}

bool token::operator==(const token &t) const{
  /* Pre: cert */
  /* Post: indica si el token del p.i. és igual al token t */

  return t.t == this->t;

}

bool token::operator!=(const token &t) const{
  /* Pre: cert*/
  /* Post: indica si el token del p.i. és diferent al token t */

  return t.t != this->t;

}

bool token::operator==(const char s[]) const{
  /* Pre: cert */
  /* Post: indica si el token del p.i. és igual al string s */

  return t == s;

}

bool token::operator!=(const char s[]) const{
  /* Pre: cert */
  /* Post: indica si el token del p.i. és diferent al string s */

  return t != s;

}

istream& operator>>(istream &is, token &t){
  /* Pre: cert */
  /* Post: llegeix del canal d'entrada el contingut del token */

  is >> t.t;
  return is;

}

ostream& operator<<(ostream &os, const token &t){
  /* Pre: cert*/
  /* Post: mostra al canal de sortida el contingut del token */

  os << t.t;
  return os;

}
