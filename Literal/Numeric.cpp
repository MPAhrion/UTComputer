#include "Numeric.h"
#include "Complex.h"
#include "Expression.h"
#include "Integer.h"

Numeric* Numeric::im()const{return new Integer(0);}

Literal* Numeric::operator+(Literal* c)const{
    Numeric* num=dynamic_cast<Numeric*>(c);
    if (num==0) //Si c'est pas une Numeric
    {
        Complex* cplx=dynamic_cast<Complex*>(c);
        if(cplx == NULL){
            Expression* exp=dynamic_cast<Expression*>(c);
            if(exp==NULL)
                throw QString("ERROR : can't add those types");
            Expression* tmp=this->toExpression();
            QString part1= tmp->getExpressionSansGuillemets();
            delete tmp;
            QString part2= exp->getExpressionSansGuillemets();
            return new Expression("'"+part1+"+"+part2+"'");
        }
        Numeric* tmp=*this+(cplx->getR());
        Complex *res=new Complex(tmp,cplx->getI());
        delete tmp;
        return res;
    }
    return *this+num;
}

Literal* Numeric::operator-(Literal* c)const{
    Numeric* num=dynamic_cast<Numeric*>(c);
    if (num==0) //Si c'est pas une Numeric
    {
        Complex* cplx=dynamic_cast<Complex*>(c);
        if(cplx == NULL){
            Expression* exp=dynamic_cast<Expression*>(c);
            if(exp==NULL)
                throw QString("ERROR : can't subtract those types");
            Expression* tmp=this->toExpression();
            QString part1= tmp->getExpressionSansGuillemets();
            delete tmp;
            QString part2= exp->getExpressionSansGuillemets();
            return new Expression("'"+part1+"-"+part2+"'");
        }
        Numeric* tmp=*this-(cplx->getR());
        Complex *res=new Complex(tmp,cplx->getI());
        delete tmp;
        return res;
    }
    return *this-num;
}

Literal* Numeric::operator*(Literal* c)const{
    Numeric* num=dynamic_cast<Numeric*>(c);
    if (num==0) //Si c'est pas une Numeric
    {
        Complex* cplx=dynamic_cast<Complex*>(c);
        if(cplx == NULL){
            Expression* exp=dynamic_cast<Expression*>(c);
            if(exp==NULL)
                throw QString("ERROR : can't multiply those types");
            unsigned int prioMinExp2=0;
            Expression* tmp=this->toExpression();
            QString part1= tmp->getExpressionSansGuillemets();
            prioMinExp2=exp->getPrioriteMin();
            delete tmp;
            QString part2= exp->getExpressionSansGuillemets();
            if (prioMinExp2==2)
                return new Expression("'"+part1+"*("+part2+")'");
            return new Expression("'"+part1+"*"+part2+"'");
        }
        Numeric* tmp1=*this*(cplx->getR());
        Numeric* tmp2=*this*(cplx->getI());
        if(tmp2->toString()=="0")
        {
            delete tmp2;
            return tmp1;
        }
        Complex *res=new Complex(tmp1,tmp2);
        delete tmp1;
        delete tmp2;
        return res;
    }
    return *this*num;
}

Literal* Numeric::operator/(Literal* c)const{
    Numeric* num=dynamic_cast<Numeric*>(c);
    if (num==0) //Si c'est pas une Numeric
    {
        Complex* cplx=dynamic_cast<Complex*>(c);
        if(cplx == NULL){
            Expression* exp=dynamic_cast<Expression*>(c);
            if(exp==NULL)
                throw QString("ERROR : can't divide those types");
            unsigned int prioMinExp2=0;
            Expression* tmp=this->toExpression();
            QString part1= tmp->getExpressionSansGuillemets();
            prioMinExp2=exp->getPrioriteMin();
            delete tmp;
            QString part2= exp->getExpressionSansGuillemets();
            if (prioMinExp2==2)
                return new Expression("'"+part1+"/("+part2+")'");
            return new Expression("'"+part1+"/"+part2+"'");
        }
        Numeric* tmp1=*this/(cplx->getR());
        Numeric* tmp2=*this/(cplx->getI());
        Complex *res=new Complex(tmp1,tmp2);
        delete tmp1;
        delete tmp2;
        return res;
    }
    return *this/num;
}

Expression* Numeric::toExpression()const{
    return new Expression("'"+this->toString()+"'");
}
