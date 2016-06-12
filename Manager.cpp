#include "Manager.h"
#include <iostream>

Manager* Manager::_instance=0;

Manager* Manager::getInstance(){
  if (!_instance)
   _instance = new Manager();
  return _instance;
}

void Manager::freeInstance(){
  if (_instance)
    delete _instance;
}

void Manager::addVariable(Variable* v){
    QList<Variable*>::iterator it=_listVar.begin();
    while(it < _listVar.end()){
        if ((*it)->getId()->toString() == v->getId()->toString()){
            throw QString("This variable already exists. Please edit it with the Edit menu.");
        }
        ++it;
    }
    if(it == _listVar.end())
        _listVar.push_back(v);

    /*if(_listVar.indexOf(v)==-1)
        _listVar<<v;
    else
        throw QString("This variable already exists. Please edit it with the Edit menu.");
    */
}

void Manager::removeVariable(const QString& s){
    QList<Variable*>::iterator it=_listVar.begin();
    while(it < _listVar.end()){
        if ((*it)->getId()->toString() == s)
            _listVar.erase(it);
        ++it;
    }
}
