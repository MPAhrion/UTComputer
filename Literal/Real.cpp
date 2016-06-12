#include "Integer.h"
#include "Real.h"
#include "Rational.h"

//---------------------------------------------------------------------------------

Numeric* Real::operator+(Numeric* c)const{
    Real* reel = dynamic_cast<Real*>(c);
    if(reel==NULL){
        Integer* entier=dynamic_cast<Integer*>(c);
        if(entier==NULL){
            Rational* rationnel=dynamic_cast<Rational*>(c);
            return new Real(_value+rationnel->toDouble());
        }
        return new Real(_value+(double)entier->getValue());
    }
    return new Real(_value+reel->getValue());
}
//---------------------------------------------------------------------------------


Numeric* Real::operator-(Numeric* c)const{
    Real* reel = dynamic_cast<Real *>(c);
    if(reel==NULL){
        Integer *entier=dynamic_cast<Integer *>(c);
        if(entier==NULL){
            Rational* rationnel=dynamic_cast<Rational*>(c);
            return new Real(_value-rationnel->toDouble());
        }
        return new Real(_value-(double)entier->getValue());
    }
    return new Real(_value-reel->getValue());
}
//---------------------------------------------------------------------------------

Numeric* Real::operator*(Numeric* c)const{
    Real* reel = dynamic_cast<Real *>(c);
    if(reel==NULL){
        Integer *entier=dynamic_cast<Integer *>(c);
        if(entier==NULL){
            Rational* rationnel=dynamic_cast<Rational*>(c);
            return new Real(_value*rationnel->toDouble());
        }
        return new Real(_value*(double)entier->getValue());
    }
    return new Real(_value*reel->getValue());
}
//---------------------------------------------------------------------------------

Numeric* Real::operator/(Numeric* c)const{
    Real* reel = dynamic_cast<Real *>(c);
    if(reel==NULL){
        Integer *entier=dynamic_cast<Integer *>(c);
        if(entier==NULL){
            Rational* rationnel=dynamic_cast<Rational*>(c);
            return new Real(_value*rationnel->toDouble());
        }
        if(entier->getValue() ==0)
            throw QString("Can't divide by 0");
        return new Real(_value/(double)entier->getValue());
    }
    if(reel->getValue() ==0)
        throw QString("Can't divide by 0");
    return new Real(_value/reel->getValue());
}

Real* Real::neg()const{
  return new Real(-_value);
}

Numeric* Real::pow(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer *>(c);
    if(entier==NULL){
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational *rationnel=dynamic_cast<Rational *>(c);

            return new Real(std::pow(_value,rationnel->toDouble()));
        }
        return new Real(std::pow(_value,reel->getValue()));
    }
    return new Real(std::pow(_value,entier->getValue()));
}

Numeric* Real::sqrt()const{
    return new Real(std::sqrt(_value));
}
Numeric* Real::cos()const{
    return new Real(std::cos(_value));
}
Numeric* Real::sin()const{
    return new Real(std::sin(_value));
}
Numeric* Real::tan()const{
    return new Real(std::tan(_value));
}
Numeric* Real::exp()const{
    return new Real(std::exp(_value));
}
Numeric* Real::log()const{
    return new Real(std::log(_value));
}

//---------------------OPERATEURS LOGIQUES-----------------------------------

bool Real::operator==(Numeric* c)const{
  Real* reel = dynamic_cast<Real*>(c);
  if(reel==NULL){
      Rational* rat = dynamic_cast<Rational*>(c);
      if (rat == NULL)
          return false;
      else
          return (_value == rat->toDouble());
  }
  return (_value == reel->getValue());
}

bool Real::operator!=(Numeric* c)const{
  Real* reel = dynamic_cast<Real*>(c);
  if(reel==NULL){
     Rational* rat = dynamic_cast<Rational*>(c);
     if (rat == NULL)
         return false;
     else
         return (_value != rat->toDouble());
  }
  return (_value != reel->getValue());
}

bool Real::operator<=(Numeric* c)const{
  Real* reel = dynamic_cast<Real*>(c);
  if(reel==NULL){
    Integer* entier = dynamic_cast<Integer*>(c);
    if (entier == NULL){
      Rational* rationnel = dynamic_cast<Rational*>(c);
      if (rationnel == NULL)
        return false;
      return (_value <= rationnel->toDouble());
    }
    return (_value <= (double)entier->getValue());
  }
  return (_value <= reel->getValue());
}

bool Real::operator>=(Numeric* c)const{
  Real* reel = dynamic_cast<Real*>(c);
  if(reel==NULL){
    Integer* entier = dynamic_cast<Integer*>(c);
    if (entier == NULL){
      Rational* rationnel = dynamic_cast<Rational*>(c);
      if (rationnel == NULL)
        return false;
      return (_value >= rationnel->toDouble());
    }
    return (_value >= (double)entier->getValue());
  }
  return (_value >= reel->getValue());
}

bool Real::operator<(Numeric* c)const{
  Real* reel = dynamic_cast<Real*>(c);
  if(reel==NULL){
    Integer* entier = dynamic_cast<Integer*>(c);
    if (entier == NULL){
      Rational* rationnel = dynamic_cast<Rational*>(c);
      if (rationnel == NULL)
        return false;
      return (_value < rationnel->toDouble());
    }
    return (_value < (double)entier->getValue());
  }
  return (_value < reel->getValue());
}

bool Real::operator>(Numeric* c)const{
  Real* reel = dynamic_cast<Real*>(c);
  if(reel==NULL){
    Integer* entier = dynamic_cast<Integer*>(c);
    if (entier == NULL){
      Rational* rationnel = dynamic_cast<Rational*>(c);
      if (rationnel == NULL)
        return false;
      return (_value > rationnel->toDouble());
    }
    return (_value > (double)entier->getValue());
  }
  return (_value > reel->getValue());
}

QString Real::toString() const{
    QString str;
    str.setNum(_value);
    return str;
}

Real* Real::clone() const{
    return(new Real(_value));
}
