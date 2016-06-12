#include "Integer.h"
#include "Real.h"
#include "Rational.h"

Numeric* Integer::operator+(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer *>(c);
    if(entier==NULL){
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational *rationnel=dynamic_cast<Rational *>(c);
            Rational *result=new Rational(Integer(_value*rationnel->getDenominator().getValue()-rationnel->getNumerator().getValue()),Integer(rationnel->getDenominator().getValue()));
            result->simplification();
            return result;
        }
        return new Real(((double)_value)+reel->getValue());
    }
    return new Integer(_value+entier->getValue());
}
//---------------------------------------------------------------------------------

Numeric* Integer::operator-(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer *>(c);
    if(entier==NULL){
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational *rationnel=dynamic_cast<Rational *>(c);
            Rational *result=new Rational(Integer(_value*rationnel->getDenominator().getValue()-rationnel->getNumerator().getValue()),Integer(rationnel->getDenominator().getValue()));
            result->simplification();
            return result;
        }
        return new Real(((double)_value)-reel->getValue());
    }
    return new Integer(_value-entier->getValue());
}
//---------------------------------------------------------------------------------

Numeric* Integer::operator*(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer *>(c);
    if(entier==NULL){
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational *rationnel=dynamic_cast<Rational *>(c);
            Rational *result=new Rational(Integer(_value*rationnel->getNumerator().getValue()),Integer(rationnel->getDenominator().getValue()));
            result->simplification();
            if(result->getDenominator().getValue()==1 || result->getNumerator().getValue()==0){
                Integer* resE = new Integer(result->getNumerator().getValue());
                delete result;
                return resE;
            }
            return result;
        }
        return new Real(((double)_value)*reel->getValue());
    }
    return new Integer(_value*entier->getValue());
}
//---------------------------------------------------------------------------------

Numeric* Integer::operator /(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer *>(c);
    if(entier==NULL)
    {
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational *rationnel=dynamic_cast<Rational *>(c);
            Rational *result=new Rational(Integer(_value*rationnel->getDenominator().getValue()),Integer(rationnel->getNumerator().getValue()));
            result->simplification();
            if(result->getDenominator().getValue()==1 || result->getNumerator().getValue()==0){
                Integer* resE = new Integer(result->getNumerator().getValue());
                delete result;
                return resE;
            }
            return result;
        }
        if(reel->getValue() ==0)
            throw QString("Can't divide by 0 !");
        return new Real(((double)_value)/reel->getValue());
    }
    if(entier->getValue() ==0)
        throw QString("Can't divide by 0 !");
    Rational* res = new Rational(*this,*entier);
    res->simplification();
    if(res->getDenominator().getValue()==1 || res->getNumerator().getValue()==0){
        Integer* resE = new Integer(res->getNumerator().getValue());
        delete res;
        return resE;
    }
    return res;
}
//---------------------------------------------------------------------------------
Integer* Integer::operator%(Integer* c)const{
    return new Integer(_value%c->getValue());
}

Integer* Integer::div(Integer* c)const{
  return new Integer(_value/c->getValue());
}

Integer* Integer::neg()const{
  return new Integer(-_value);
}

Numeric* Integer::pow(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer *>(c);
    if(entier==NULL){
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational *rationnel=dynamic_cast<Rational *>(c);

            return new Real(std::pow(_value,rationnel->toDouble()));
        }
        return new Real(std::pow(_value,reel->getValue()));
    }
    return new Integer(std::pow(_value,entier->getValue()));
}

Numeric* Integer::sqrt()const{
    return new Real(std::sqrt(_value));
}


Numeric* Integer::cos()const{
    return new Real(std::cos(_value));
}
Numeric* Integer::sin()const{
    return new Real(std::sin(_value));
}
Numeric* Integer::tan()const{
    return new Real(std::tan(_value));
}

Numeric* Integer::exp()const{
    return new Real(std::exp(_value));
}
Numeric* Integer::log()const{
    return new Real(std::log(_value));
}
//------------------------OPERATEURS LOGIQUES-------------------------------
bool Integer::operator==(Numeric* c)const{
  Integer* entier = dynamic_cast<Integer*>(c);
  if(entier==NULL){
     return false;
  }
  return (_value == entier->getValue());
}

bool Integer::operator!=(Numeric* c)const{
  Integer* entier = dynamic_cast<Integer*>(c);
  if(entier==NULL){
     return false;
  }
  return (_value != entier->getValue());
}

bool Integer::operator<=(Numeric* c)const{
  Integer* entier = dynamic_cast<Integer*>(c);
  if(entier==NULL){
    Real* reel = dynamic_cast<Real*>(c);
    if (reel == NULL){
      Rational* rationnel = dynamic_cast<Rational*>(c);
      if (rationnel == NULL)
        return false;
      return ((double)_value <= rationnel->toDouble());
    }
    return ((double)_value <= reel->getValue());
  }
  return (_value <= entier->getValue());
}
bool Integer::operator>=(Numeric* c)const{
  Integer* entier = dynamic_cast<Integer*>(c);
  if(entier==NULL){
    Real* reel = dynamic_cast<Real*>(c);
    if (reel == NULL){
      Rational* rationnel = dynamic_cast<Rational*>(c);
      if (rationnel == NULL)
        return false;
      return ((double)_value >= rationnel->toDouble());
    }
    return ((double)_value >= reel->getValue());
  }
  return (_value >= entier->getValue());
}

bool Integer::operator<(Numeric* c)const{
  Integer* entier = dynamic_cast<Integer*>(c);
  if(entier==NULL){
    Real* reel = dynamic_cast<Real*>(c);
    if (reel == NULL){
      Rational* rationnel = dynamic_cast<Rational*>(c);
      if (rationnel == NULL)
        return false;
      return ((double)_value < rationnel->toDouble());
    }
    return ((double)_value < reel->getValue());
    }
  return (_value < entier->getValue());
}

bool Integer::operator>(Numeric* c)const{
  Integer* entier = dynamic_cast<Integer*>(c);
  if(entier==NULL){
    Real* reel = dynamic_cast<Real*>(c);
    if (reel == NULL){
      Rational* rationnel = dynamic_cast<Rational*>(c);
      if (rationnel == NULL)
        return false;
      return ((double)_value > rationnel->toDouble());
    }
    return ((double)_value > reel->getValue());
  }
  return (_value > entier->getValue());
}


Integer* Integer::operator&(Integer* c)const{
      return new Integer(_value & c->getValue());
}

Integer* Integer::operator|(Integer* c)const{
      return new Integer(_value | c->getValue());
}

Integer* Integer::operator~()const{
      return new Integer(~_value);
}

//---------------------------------------------------------------------------------

QString Integer::toString() const{
    QString str;
    str.setNum(_value);
    return str;
}

Integer* Integer::clone() const{
    return (new Integer(_value));
}
