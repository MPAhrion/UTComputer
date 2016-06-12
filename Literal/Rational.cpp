#include "Rational.h"


Numeric* Rational::operator+(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer *>(c);
    if(entier==NULL){
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational* rationnel=dynamic_cast<Rational *>(c);
            Rational* result=new Rational(Integer(_numerator.getValue()*rationnel->getDenominator().getValue() + _denominator.getValue()*rationnel->getNumerator().getValue()),Integer(_denominator.getValue()*rationnel->getDenominator().getValue()));
            result->simplification();
            if(result->getDenominator().getValue()==1 || result->getNumerator().getValue()==0){
                Integer* resE = new Integer(result->getNumerator().getValue());
                delete result;
                return resE;
            }
            return result;
        }
        return new Real(this->toDouble()+reel->getValue());
    }
    Rational* res= new Rational(Integer(_numerator.getValue() + (entier->getValue()*_denominator.getValue())), Integer(_denominator.getValue()));
    res->simplification();
    return res;
}
//---------------------------------------------------------------------------------

Numeric* Rational::operator-(Numeric* c)const{
  Integer* entier = dynamic_cast<Integer *>(c);
  if(entier==NULL){
    Real* reel=dynamic_cast<Real*>(c);
    if(reel==NULL){
        Rational* rationnel=dynamic_cast<Rational *>(c);
        Rational* result=new Rational(Integer(_numerator.getValue()*rationnel->getDenominator().getValue() - _denominator.getValue()*rationnel->getNumerator().getValue()),Integer(_denominator.getValue()*rationnel->getDenominator().getValue()));
        result->simplification();
        if(result->getDenominator().getValue()==1 || result->getNumerator().getValue()==0){
            Integer* resE = new Integer(result->getNumerator().getValue());
            delete result;
            return resE;
        }
        return result;
    }
    return new Real(this->toDouble()-reel->getValue());
  }
  Rational* res= new Rational(Integer(_numerator.getValue() - (entier->getValue()*_denominator.getValue())), Integer(_denominator.getValue()));
  res->simplification();
  return res;
}
//---------------------------------------------------------------------------------

Numeric* Rational::operator*(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer*>(c);
    if(entier==NULL){
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational* rationnel=dynamic_cast<Rational*>(c);
            Rational* result=new Rational(Integer(_numerator.getValue()*rationnel->getNumerator().getValue()),Integer(_denominator.getValue()*rationnel->getDenominator().getValue()));
            result->simplification();
            if(result->getDenominator().getValue()==1 || result->getNumerator().getValue()==0){
                Integer* resE = new Integer(result->getNumerator().getValue());
                delete result;
                return resE;
            }
            return result;
        }
        return new Real(this->toDouble()*reel->getValue());
    }
    Rational* res= new Rational(Integer(_numerator.getValue()*entier->getValue()), Integer(_denominator.getValue()));
    res->simplification();
    if(res->getDenominator().getValue()==1 || res->getNumerator().getValue()==0){
        Integer* resE = new Integer(res->getNumerator().getValue());
        delete res;
        return resE;
    }
    return res;
}
//---------------------------------------------------------------------------------

Numeric* Rational::operator/(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer *>(c);
    if(entier==NULL){
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational* rationnel=dynamic_cast<Rational *>(c);
            Rational* result=new Rational(Integer(_numerator.getValue()*rationnel->getDenominator().getValue()),Integer(_denominator.getValue()*rationnel->getNumerator().getValue()));
            result->simplification();
            if(result->getDenominator().getValue()==1 || result->getNumerator().getValue()==0){
                Integer* resE = new Integer(result->getNumerator().getValue());
                delete result;
                return resE;
            }
            return result;
        }
        if(reel->getValue() ==0)
            throw QString("Can't divide by 0");
        return new Real(this->toDouble()/reel->getValue());
    }
    if(entier->getValue() ==0)
      throw QString("Can't divide by 0");
    Rational *res=new Rational(Integer(_numerator.getValue()), Integer(_denominator.getValue()*entier->getValue()));
    res->simplification();
    if(res->getDenominator().getValue()==1 || res->getNumerator().getValue()==0){
        Integer* resE = new Integer(res->getNumerator().getValue());
        delete res;
        return resE;
    }
    return res;
}

Numeric* Rational::neg()const{
  return new Rational(-_numerator.getValue(),_denominator.getValue());
}

Integer* Rational::num()const{
  return new Integer(_numerator.getValue());
}
Integer *Rational::den()const{
  return new Integer(_denominator.getValue());
}

Numeric* Rational::pow(Numeric* c)const{
    Integer* entier = dynamic_cast<Integer *>(c);
    if(entier==NULL){
        Real* reel=dynamic_cast<Real*>(c);
        if(reel==NULL){
            Rational *rationnel=dynamic_cast<Rational *>(c);

            return new Real(std::pow(toDouble(),rationnel->toDouble()));
        }
        return new Real(std::pow(toDouble(),reel->getValue()));
    }
    return new Rational(std::pow(_numerator.getValue(),entier->getValue()), std::pow(_denominator.getValue(),entier->getValue()));
}

Numeric* Rational::sqrt()const{
    return new Real(std::sqrt(_numerator.getValue()/_denominator.getValue()));
}

Numeric* Rational::cos()const{
    return new Real(std::cos(_numerator.getValue()/_denominator.getValue()));
}
Numeric* Rational::sin()const{
    return new Real(std::sin(_numerator.getValue()/_denominator.getValue()));
}
Numeric* Rational::tan()const{
    return new Real(std::tan(_numerator.getValue()/_denominator.getValue()));
}
Numeric* Rational::log()const{
    return new Real(std::log(_numerator.getValue()/_denominator.getValue()));
}
Numeric* Rational::exp()const{
    return new Real(std::exp(_numerator.getValue()/_denominator.getValue()));
}

//------------OPERATEURS LOGIQUES----------------------------------

bool Rational::operator==(Numeric* c)const{
  Rational* rationnel = dynamic_cast<Rational*>(c);
  if(rationnel==NULL){
      Real* reel = dynamic_cast<Real*>(c);
      if(reel == NULL)
        return false;
      return (toDouble() == reel->getValue());
  }
  return ( _numerator.getValue()== rationnel->getNumerator().getValue() && _denominator.getValue() == rationnel->getDenominator().getValue());
}

bool Rational::operator!=(Numeric* c)const{
  Rational* rationnel = dynamic_cast<Rational*>(c);
  if(rationnel==NULL){
      Real* reel = dynamic_cast<Real*>(c);
      if(reel == NULL)
        return false;
      return (toDouble() != reel->getValue());
  }
  return ( _numerator.getValue()!= rationnel->getNumerator().getValue() || _denominator.getValue() != rationnel->getDenominator().getValue());
}

bool Rational::operator<=(Numeric* c)const{
  Rational* rationnel = dynamic_cast<Rational*>(c);
  if(rationnel==NULL){
    Integer* entier = dynamic_cast<Integer*>(c);
    if (entier == NULL){
      Real* reel = dynamic_cast<Real*>(c);
      if (reel == NULL)
        return false;
      return (this->toDouble() <= reel->getValue());
    }
    return (this->toDouble() <= entier->getValue());
  }
  return ( this->toDouble() <= rationnel->toDouble() );
}

bool Rational::operator>=(Numeric* c)const{
  Rational* rationnel = dynamic_cast<Rational*>(c);
  if(rationnel==NULL){
    Integer* entier = dynamic_cast<Integer*>(c);
    if (entier == NULL){
      Real* reel = dynamic_cast<Real*>(c);
      if (reel == NULL)
        return false;
      return (this->toDouble() >= reel->getValue());
    }
    return (this->toDouble() >= entier->getValue());
  }
  return ( this->toDouble() >= rationnel->toDouble() );
}

bool Rational::operator<(Numeric* c)const{
  Rational* rationnel = dynamic_cast<Rational*>(c);
  if(rationnel==NULL){
    Integer* entier = dynamic_cast<Integer*>(c);
    if (entier == NULL){
      Real* reel = dynamic_cast<Real*>(c);
      if (reel == NULL)
        return false;
      return (this->toDouble() < reel->getValue());
    }
    return (this->toDouble() < entier->getValue());
  }
  return ( this->toDouble() < rationnel->toDouble() );
}

bool Rational::operator>(Numeric* c)const{
  Rational* rationnel = dynamic_cast<Rational*>(c);
  if(rationnel==NULL){
    Integer* entier = dynamic_cast<Integer*>(c);
    if (entier == NULL){
      Real* reel = dynamic_cast<Real*>(c);
      if (reel == NULL)
        return false;
      return (this->toDouble() > reel->getValue());
    }
    return (this->toDouble() > entier->getValue());
  }
  return ( this->toDouble() > rationnel->toDouble() );
}


// -----------------------------------------------------------

void Rational::simplification(){
  int numerator = this->getNumerator().getValue();
  int denominator = this->getDenominator().getValue();
	if (numerator == 0 || denominator == 0)
		return;
	int a= numerator, b=denominator;
	if (a<0)
		a = -a;
	if (b<0)
		b = -b;
	while (a!=b){
		if (a>b)
			a=a-b;
		else
			b=b-a;
	}
	numerator/=a;
	denominator/=a;
	if (denominator < 0){
		denominator = -denominator;
		numerator = -numerator;
	}

  this->setNumerator(Integer(numerator));
  this->setDenominator(Integer(denominator));
}

QString Rational::toString() const{
    QString str1,str2;
    str1.setNum(_numerator.getValue());
    str2.setNum(_denominator.getValue());
    return QString(str1+"/"+str2);
}

double Rational::toDouble()const{
    return (double)_numerator.getValue()/(double)_denominator.getValue();
}

Rational* Rational::clone() const{
    return new Rational(_numerator,_denominator);
}
