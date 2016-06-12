#include "Complex.h"


Complex::Complex(Literal* r, Literal* i)
  {
    Numeric* numR=dynamic_cast<Numeric*>(r);
    Numeric* numI=dynamic_cast<Numeric*>(i);
    if (numR != NULL && numI != NULL){
        _re=numR->clone();
        _im=numI->clone();
    }
    else throw QString("Type error");
  }

//------------------------------- OPERATEUR + -------------------------------------

Literal* Complex::operator+(Literal* c)const{
    Numeric* num=dynamic_cast<Numeric*>(c);
    if(num==NULL){ //If we don't add a Numeric
        Complex* cplx=dynamic_cast<Complex*>(c);
        if(cplx == NULL){ //If we don't add a complex either, error
                throw QString("Complex can be added only between an other complex or a Numeric number");
        }
        Numeric* tmp=*_re+cplx->getR();
        Numeric* tmp2=*_im+cplx->getI();
        if(tmp2->toString()=="0"){
            delete tmp2;
            return tmp;
        }
        Complex* res= new Complex(tmp,tmp2);
        delete tmp;
        delete tmp2;
        return res;

    }
    Numeric* tmp=*_re+num;
    Complex* res= new Complex(tmp,_im);
    delete tmp;
    return res;
}
//---------------------------------------------------------------------------------

//------------------------------- OPERATEUR - -------------------------------------

Literal* Complex::operator-(Literal* c)const{
    Numeric* num=dynamic_cast<Numeric*>(c);
    if(num==NULL) //If we don't subtract a Numeric
    {
        Complex* cplx=dynamic_cast<Complex*>(c);
        if(cplx == NULL){ //if we don't subtract a complex either, error
                throw QString("Complex can be subtract only between an other complex or a Numeric number");
        }
        Numeric* tmp=*_re-cplx->getR();
        Numeric* tmp2=*_im-cplx->getI();
        if(tmp2->toString()=="0"){
            delete tmp2;
            return tmp;
        }
        Complex* res= new Complex(tmp,tmp2);
        delete tmp;
        delete tmp2;
        return res;

    }
    Numeric* tmp=*_re-num;
    Complex* res= new Complex(tmp,_im);
    delete tmp;
    return res;
}
//---------------------------------------------------------------------------------

//------------------------------- OPERATEUR * -------------------------------------

Literal* Complex::operator*(Literal* c)const{
    Numeric* num=dynamic_cast<Numeric*>(c);
    if(num==NULL) //If we don't multiply a Numeric
    {
        Complex* cplx=dynamic_cast<Complex*>(c);
        if(cplx == NULL){ //if we don't multiply a complex either, error
                throw QString("Complex can be multiply only between an other complex or a Numeric number");
        }
        Numeric* tmp1=*_re*cplx->getR();
        Numeric* tmp2=*_im*cplx->getI();
        Numeric* tmp3=*tmp1-tmp2;
        delete tmp1;
        delete tmp2;
        tmp1=*_im*cplx->getR();
        tmp2=*_re*cplx->getI();
        Numeric* tmp4=*tmp1+tmp2;
        delete tmp1;
        delete tmp2;
        if(tmp4->toString()=="0"){
            delete tmp4;
            return tmp3;
        }
        Complex* res= new Complex(tmp3,tmp4);
        delete tmp3;
        delete tmp4;
        return res;
    }
    Numeric* tmp1=*_re*num;
    Numeric* tmp2=*_im*num;
    if(tmp2->toString()=="0"){
        delete tmp2;
        return tmp1;
    }
    Complex* res= new Complex(tmp1,tmp2);
    delete tmp1;
    delete tmp2;
    return res;
}
//---------------------------------------------------------------------------------

//------------------------------- OPERATEUR / -------------------------------------

Literal* Complex::operator/(Literal* c)const{
    Numeric* num=dynamic_cast<Numeric*>(c);
    if(num==NULL) //If we don't divide a Numeric
    {
        Complex* cplx=dynamic_cast<Complex*>(c);
        if(cplx == NULL){ //if we don't divide a complex either, error
                throw QString("Complex can be divide only between an other complex or a Numeric number");
        }
        Numeric* tmp1=*_re*cplx->getR();
        Numeric* tmp2=*_im*cplx->getI();
        Numeric* tmp3=*tmp1+tmp2;
        delete tmp1;
        delete tmp2;
        tmp1=*(cplx->getR())*cplx->getR();
        tmp2=*(cplx->getI())*cplx->getI();
        Numeric* tmp4=*tmp1+tmp2;
        delete tmp1;
        delete tmp2;
        Numeric* tmp5=*tmp3/tmp4;
        delete tmp3;
        tmp1=*_im*cplx->getR();
        tmp2=*_re*cplx->getI();
        tmp3=*tmp1-tmp2;
        delete tmp1;
        delete tmp2;
        tmp1=*tmp3/tmp4;
        delete tmp3;
        delete tmp4;
        if(tmp1->toString()=="0")
        {
            delete tmp1;
            return tmp5;
        }
        Complex* res= new Complex(tmp5,tmp1);
        delete tmp5;
        delete tmp1;
        return res;
    }
    Numeric* tmp1=*_re/num;
    Numeric* tmp2=*_im/num;
    if(tmp2->toString()=="0")
    {
        delete tmp2;
        return tmp1;
    }
    Complex* res= new Complex(tmp1,tmp2);
    delete tmp1;
    delete tmp2;
    return res;

}


//---------------------------------------------------------------------------------

Expression* Complex::toExpression() const{
    return new Expression("'"+_re->toString()+"$"+_im->toString()+"'");
}

QString Complex::toString() const{
    QString str1,str2;
    str1 = _re->toString();
    str2= _im->toString();
    return QString(str1+"$"+str2);
}


Complex* Complex::clone() const{
    return(new Complex(_re,_im));
}
