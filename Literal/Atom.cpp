#include "Atom.h"

Atom::Atom(const QString& s):_value(s.toUpper()){}

Atom* Atom::clone() const{
    return new Atom(_value);
}

Atom& Atom::operator=(const Atom& a){
    _value = a._value;
    return *this;
}

