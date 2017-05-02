#ifndef ARBRE_H 
#define ARBRE_H

#include <string>
#include <cstdlib>
#include <iostream>


/// -----------------------------------------
///
///  Declaraci� operacions tipus ARBRE BINARI
///
/// -----------------------------------------

template <class T> 
class arbre { 
 
 private:
   T info;
   arbre<T> *dret;
   arbre<T> *esquerre;
   void clone(const arbre<T>&);

 public:
   //constructors
   arbre();
   /* Pre: cert */
   /* Post: el resultat �s un arbre sense cap element */
   arbre(const T &,const arbre<T> &,const arbre<T> &);
    /* Pre: cert */
    /* Post: el resultat �s un arbre amb un element i dos 
       subarbres */
   arbre(const arbre<T> &);
   /* Pre: cert */
   /* Post: el resultat �s una c�pia de l'arbre rebut */
    
    
   //destructor: esborra autom�ticament els objectes locals
   //en sortir d'un �mbit de visibilitat
   ~arbre();
    
    
    //modificadors
    void a_buit();
    /* Pre: cert */
    /* Post: el par�metre impl�cit no t� cap element */     
    arbre<T>& operator=(const arbre<T>&);  
    /* Pre: cert */
    /* Post: operaci� d'assignaci� d'arbres  */ 
       
   //consultors
   const T& arrel() const;
   /* Pre: el par�metre impl�cit no �s buit */
   /* Post: el resultat �s l�arrel del par�metre impl�cit */
   const arbre<T>& fd() const;
   /* Pre: el par�metre impl�cit no �s buit */
   /* Post: el resultat �s el fill dret del p.i. original */
   const arbre<T>& fe() const;
   /* Pre: el par�metre impl�cit no �s buit */
   /* Post: el resultat �s el fill esquerre del p.i. original */
   bool es_buit() const;
   /* Pre: cert */
   /* Post: el resultat indica si el p.i. �s buit o no */
   
};


/// ------------------------------------------
///
///  Codificaci� operacions tipus ARBRE BINARI
///
/// ------------------------------------------


//constructors ----------------------
template <class T>
arbre<T>::arbre()
/* Pre: cert */
/* Post: el resultat �s un arbre sense cap element */
{
  dret = NULL;
  esquerre = NULL;
}

template <class T>
arbre<T>::arbre(const arbre<T>& t)
/* Pre: cert */
/* Post: el resultat �s una c�pia de t */
{
  clone(t);
}

template <class T>
arbre<T>::arbre(const T& x, const arbre<T>& a1, const arbre<T>& a2)
/* Pre: cert */
/* Post: el resultat �s un arbre amb x com arrel, a1 com a fill
esquerre i a2 com a fill dret */
{
  info = x;
  esquerre = new arbre<T>; esquerre->clone(a1);
  dret = new arbre<T>; dret->clone(a2);
}


//destructor ----------------------
template <class T>
arbre<T>::~arbre() {
  if (dret != NULL) dret->~arbre();
  if (esquerre != NULL) esquerre->~arbre();
}



//modificadors ----------------------
template <class T>
void arbre<T>::a_buit()
/* Pre: cert */
/* Post: el par�metre impl�cit no t� cap element */  
{
  if (dret != NULL) dret = NULL;
  if (esquerre != NULL) esquerre = NULL;
}  

template <class T>
arbre<T>& arbre<T>::operator=(const arbre<T>& t) {
  if (this != &t) {
    clone(t);
  }
  return (*this);
}

//consultors ----------------------
template <class T>
bool arbre<T>::es_buit() const
/* Pre: cert */
/* Post: el resultat indica si el p.i. �s buit o no */
{
  return (dret==NULL && esquerre==NULL);
} 

template <class T>
const arbre<T> &  arbre<T>::fd() const
/* Pre: el par�metre impl�cit no �s buit */
/* Post: el resultat �s el fill dret del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operaci� 'fd' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return (*dret);
}

template <class T>
const arbre<T> &  arbre<T>::fe() const
/* Pre: el par�metre impl�cit no �s buit */
/* Post: el resultat �s el fill esquerre del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operaci� 'fe' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return (*esquerre);
}

template <class T>
const T& arbre<T>::arrel() const {
/* Pre: el par�metre impl�cit no �s buit */
/* Post: el resultat �s l�arrel del par�metre impl�cit */
  if (this->es_buit()) {
    std::cout<<"ERROR - Operaci� 'arrel' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return info;
}

//clone (operaci� auxiliar privada) ----------------------
template <class T>
void arbre<T>::clone(const arbre<T>& t) {

  if (not t.es_buit()) this->info = t.info;

  if (t.dret!=NULL) {
    this->dret = new arbre<T>;  
    this->dret->clone(*t.dret); 
  }
  else this->dret=NULL;

  if (t.esquerre!=NULL) {
    this->esquerre = new arbre<T>;
    this->esquerre->clone(*t.esquerre);  
  }
  else this->esquerre=NULL;

}

#endif











