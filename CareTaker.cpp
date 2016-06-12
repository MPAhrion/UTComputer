#include "CareTaker.h"

CareTaker* CareTaker::_instance=0;

CareTaker* CareTaker::getInstance(){
  if (!_instance)
   _instance = new CareTaker();
  return _instance;
}

void CareTaker::freeInstance(){
  if (_instance)
    delete _instance;
  _instance = 0;
}
CareTaker::~CareTaker(){
    freeInstance();
}

void CareTaker::addMemento(Pile::Memento* m){
    while(_savedPiles.size() > _indexPile){
        _savedPiles.pop_back();
    }
    _savedPiles.push_back(m);
    _indexPile++;
}

Pile::Memento* CareTaker::getMementoUndo(){
    if(!_savedPiles.isEmpty() && _indexPile > 1)
        return _savedPiles.at((--_indexPile)-1);
    throw QString("Error Undo");
}
Pile::Memento* CareTaker::getMementoRedo(){
    if(!_savedPiles.isEmpty() && _indexPile < _savedPiles.size())
        return _savedPiles.at((++_indexPile)-1);
    throw QString("Error Redo");
}
