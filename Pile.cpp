#include "Pile.h"

#include "./Literal/Literal.h"
//#include "./Literal/Real.h"
//#include "./Literal/Rational.h"
//#include "./Literal/Complex.h"


Pile* Pile::clone() const{
  Pile* newPile = new Pile();
  QStack<Literal*>::const_iterator it;
  Literal* l =0;
  for(it=begin(); it!=end(); it++){
    l = *it;
    newPile->push(l->clone());
  }
  return newPile;
}



Pile::Memento* Pile::saveStackInMemento(){ return new Pile::Memento(_pile); }

void Pile::restoreStackFromMemento(const Pile::Memento* m){
    _pile=m->getState();
}


