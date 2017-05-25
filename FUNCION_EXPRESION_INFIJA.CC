arbre<token> llegir_infixa(){

  /* Pre: cert */
  /* Post: retorna un arbre amb l'expressió en notació infixa rebuda pel
           canal estandar cin */

  stack<token> ops;
  stack<arbre<token> > res;

  token t;
  while (cin >> t and t != "->"){
    /* Inv: */

    //cout << "while" << endl;

    if (t == "(")   ops.push(t);
    else if (t == ")") {
      while (ops.top() != ")"){
        /* Inv: */

        if (ops.top().es_operador_unari()){
          arbre<token> a1 = res.top();
          res.pop();

          res.push(arbre<token>(t, a1, arbre<token>()));
        } else {
          arbre<token> a1 = res.top();
          res.pop();
          arbre<token> a2 = res.top();
          res.pop();

          res.push(arbre<token>(t, a2, a1));
        }

        ops.pop();

      }

      ops.pop();

    } else if (not t.es_operador_unari() and not t.es_operador_binari())  res.push(t);
    else {
      if (ops.size() > 1 and ops.top() != "("){
        if (t == "**"){
          arbre<token> a1 = res.top();
          res.pop();
          arbre<token> a2 = res.top();
          res.pop();

          res.push(arbre<token>(t, a2, a1));
        } else if (t == "not" and prioritat_token(t) > prioritat_token(ops.top())) {
          arbre<token> a1 = res.top();
          res.pop();



          res.push(arbre<token>(t, a1, arbre<token>()));
        } else if (prioritat_token(t) <= prioritat_token(ops.top())){
          token opAux = ops.top();
          ops.pop();

          arbre<token> a1 = res.top();
          res.pop();
          arbre<token> a2 = res.top();
          res.pop();

          res.push(arbre<token>(opAux, a2, a1));

          ops.push(t);

        } else  ops.push(t);

      } else  ops.push(t);

    }

    if (not res.empty())   cout << res.top() << endl;

  }

  while (not ops.empty()){
    if (ops.top() != "(") {
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
