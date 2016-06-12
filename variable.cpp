#include "variable.h"
#include "Literal/Complex.h"
#include "Literal/Numeric.h"

Variable::Variable(Atom* id, Literal* v){
    //Numeric* num=dynamic_cast<Numeric*>(v);
    _value=v->clone();
    _identificateur=id;
}

QString Variable::toString() const{
    return QString(_identificateur->toString() + " "+ _value->toString());
}
