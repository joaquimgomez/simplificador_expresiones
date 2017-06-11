#include "token.h"

token::token(){
  /* Pre: cert */
  /* Post: crea un token enter de valor 0 */

  t = "0";

}

token::token(int i){
  /* Pre: cert */
  /* Post: crea un token a partir de l'enter i */

  stringstream ss;
  ss << i;
  t = ss.str();

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

  return (t[0] >= '0' and t[0] <= '9') or (t.size() >= 2 and t[0] == '-' and t[1] >= '0' and t[1] <= '9');

}

bool token::es_variable() const{
  /* Pre: cert */
  /* Post: indica si el token és una variable */

  return t != "T" and t != "F" and t != "and" and t!= "or" and t != "not" and ((t[0] >= 'a' and t[0] <= 'z') or (t[0] >= 'A' and t[0] <= 'Z'));

}

int token::to_int() const{
  /* Pre: el p.i. és un enter */
  /* Post: retorna el valor enter del p.i. */

  return atoi(t.c_str());

}

bool token::to_bool() const{
  /* Pre: el p.i. és un booleà */
  /* Post: reotrna el valor booleà true o false del p.i. */

  return t == "T";

}

string token::to_string() const{
  /* Pre: el p.i. és un string */
  /* Post: retorna un string del token del p.i. */

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
