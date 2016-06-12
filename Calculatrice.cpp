  #include "Calculatrice.h"


Calculatrice* Calculatrice::_instance=0;

Calculatrice& Calculatrice::getInstance(){
  if (!_instance)
   _instance = new Calculatrice();
  return *_instance;
}

void Calculatrice::freeInstance(){
  if (_instance)
    delete _instance;
}

Calculatrice::~Calculatrice(){
  delete _pile;
  CareTaker::freeInstance();
}


/* ------------------------------------------------------------------------------------
------------------------------- STACK OPERATORS  ------------------------------------
--------------------------------------------------------------------------------------- */
void Calculatrice::DROP(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Must have at least 1 element in the pile to DROP something");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    clearArgs();
    addArg(lit);
    delete lit;
}

void Calculatrice::DUP(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Must have at least 1 element in the pile to DUP something");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Literal* lit2=lit->clone();
    clearArgs();
    addArg(lit);
    Calculatrice::getInstance().getPile()->push(lit);
    Calculatrice::getInstance().getPile()->push(lit2);
}

void Calculatrice::SWAP(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Must have at least 2 elements in the pile to SWAP");
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    clearArgs();
    addArg(lit2);
    addArg(lit1);
    Calculatrice::getInstance().getPile()->push(lit1);
    Calculatrice::getInstance().getPile()->push(lit2);
}


void Calculatrice::NEG(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Must have at least 1 element in the pile to use NEG");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit);
    if(num==NULL)
    {
            Expression* exp=dynamic_cast<Expression*>(lit);
            if(exp==NULL)
            {
                Calculatrice::getInstance().getPile()->push(lit);
                throw QString("NEG can be used only with Numeric Litterals OR Expressions");
            }
            else
            {
                res=exp->neg();
            }
    }
    else
    {
        res=num->neg();
    }
    if (res!=NULL){
        clearArgs();
        addArg(lit);
        Calculatrice::getInstance().getPile()->push(res);
        delete lit;
    }
}

void Calculatrice::LASTARGS()
{
    if(_lastargs.empty())
        throw QString("No arguments were used");
    for (int i=0;i<_lastargs.size();i++)
    {
        Literal* tmp=_lastargs[i];
        Calculatrice::getInstance().getPile()->push(tmp->clone());
    }
}

void Calculatrice::clearArgs(){
      for(int i=0;i<_lastargs.size();i++)
          delete _lastargs[i];
      _lastargs.clear();
}


/* ------------------------------------------------------------------------------------
------------------------------- ARITHMETIC OPERATORS  ------------------------------------
--------------------------------------------------------------------------------------- */
void Calculatrice::PLUS(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");
    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit1);
    if(num==NULL)
    {
        Complex* cplx=dynamic_cast<Complex*>(lit1);
        if(cplx==NULL)
        {
            Expression * exp=dynamic_cast<Expression*>(lit1);
            if(exp==NULL)
            {
                Calculatrice::getInstance().getPile()->push(lit1);
                Calculatrice::getInstance().getPile()->push(lit2);
                throw QString ("Type error");
            }
            res=*exp+lit2;
        }
        else
        {
            Expression* exp=dynamic_cast<Expression*>(lit2);
            if (exp==NULL)
                res=*cplx+lit2;
            else
            {
                Expression* tmp=cplx->toExpression();
                res=*tmp+exp;
                delete tmp;
            }
        }
    }
    else
    {
        res=*num+lit2;
    }
    if (res!=NULL)
    {
        Calculatrice::getInstance().getPile()->push(res);
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}

void Calculatrice::MOINS(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");
    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit1);
    if(num==NULL)
    {
        Complex* cplx=dynamic_cast<Complex*>(lit1);
        if(cplx==NULL)
        {
            Expression * exp=dynamic_cast<Expression*>(lit1);
            if(exp==NULL)
            {
                Calculatrice::getInstance().getPile()->push(lit1);
                Calculatrice::getInstance().getPile()->push(lit2);
                throw QString ("Type error");
            }
            res=*exp-lit2;
        }
        else
        {
            Expression* exp=dynamic_cast<Expression*>(lit2);
            if (exp==NULL)
                res=*cplx-lit2;
            else
            {
                Expression* tmp=cplx->toExpression();
                res=*tmp-exp;
                delete tmp;
            }
        }
    }
    else
    {
        res=*num-lit2;
    }
    if (res!=NULL)
    {
        Calculatrice::getInstance().getPile()->push(res);
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}


void Calculatrice::MULT(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit1);
    if(num==NULL)
    {
        Complex* cplx=dynamic_cast<Complex*>(lit1);
        if(cplx==NULL)
        {
            Expression * exp=dynamic_cast<Expression*>(lit1);
            if(exp==NULL)
            {
                Calculatrice::getInstance().getPile()->push(lit1);
                Calculatrice::getInstance().getPile()->push(lit2);
                throw QString ("Type error");
            }
            res=*exp*lit2;
        }
        else
        {
            Expression* exp=dynamic_cast<Expression*>(lit2);
            if (exp==NULL)
                res=*cplx*lit2;
            else
            {
                Expression* tmp=cplx->toExpression();
                res=*tmp*exp;
                delete tmp;
            }
        }
    }
    else
    {
        res=*num*lit2;
    }
    if (res!=NULL)
    {
        Calculatrice::getInstance().getPile()->push(res);
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}

void Calculatrice::Div(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit1);
    if(num==NULL)
    {
        Complex* cplx=dynamic_cast<Complex*>(lit1);
        if(cplx==NULL)
        {
            Expression * exp=dynamic_cast<Expression*>(lit1);
            if(exp==NULL)
            {
                Calculatrice::getInstance().getPile()->push(lit1);
                Calculatrice::getInstance().getPile()->push(lit2);
                throw QString ("Type error");
            }
            res=*exp/lit2;
        }
        else
        {
            Expression* exp=dynamic_cast<Expression*>(lit2);
            if (exp==NULL)
                res=*cplx/lit2;
            else
            {
                Expression* tmp=cplx->toExpression();
                res=*tmp/exp;
                delete tmp;
            }
        }
    }
    else
    {
        res=*num/lit2;
    }
    if (res!=NULL)
    {
        Calculatrice::getInstance().getPile()->push(res);
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}

/* ------------------------------------------------------------------------------------
------------------------------- FUNCTION OPERATORS  ------------------------------------
--------------------------------------------------------------------------------------- */

void Calculatrice::DOLLAR(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Expression* exp=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         Literal* res=tmp->dollar(exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(res);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        Literal* res=tmp->dollar(exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(res);
    }
    else if (lit2->toString()=="0")
    {
        clearArgs();
        addArg(lit1);
        addArg(lit2);
       Calculatrice::getInstance().getPile()->push(lit1);
       delete lit2;
    }
    else{
        try{
            Literal* res=new Complex(lit1,lit2);
            Calculatrice::getInstance().getPile()->push(res);
            clearArgs();
            addArg(lit1);
            addArg(lit2);
            delete lit1;
            delete lit2;
        }
        catch (QString s)
        {
            Calculatrice::getInstance().getPile()->push(lit1);
            Calculatrice::getInstance().getPile()->push(lit2);
            throw s;
        }
    }
}

void Calculatrice::MOD(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Integer* e1=NULL;
    Integer* e2=NULL;
    Expression* exp=NULL;
    Literal* res=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         res=tmp->mod(exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(res);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        res=tmp->mod(exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(res);
    }
    else if((e1=dynamic_cast<Integer*>(lit1))==NULL || (e2=dynamic_cast<Integer*>(lit2))==NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString("MOD can only be used between integers or with an expression");
    }
    else
    {
        res=*e1%e2;
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
        Calculatrice::getInstance().getPile()->push(res);
    }

}

void Calculatrice::DIV(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Integer* e1=NULL;
    Integer* e2=NULL;
    Expression* exp=NULL;
    Literal* res=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         res=tmp->div(exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(res);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        res=tmp->div(exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(res);
    }
    else if((e1=dynamic_cast<Integer*>(lit1))==NULL || (e2=dynamic_cast<Integer*>(lit2))==NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString("DIV can only be used between integers or with an expression");
    }
    else
    {
        res=e1->div(e2);
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
        Calculatrice::getInstance().getPile()->push(res);
    }
}


void Calculatrice::POW(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Numeric* e1=NULL;
    Numeric* e2=NULL;
    Expression* exp=NULL;
    Literal* res=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         res=tmp->pow(exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(res);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        res=tmp->pow(exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(res);
    }
    else if((e1=dynamic_cast<Numeric*>(lit1))==NULL || (e2=dynamic_cast<Numeric*>(lit2))==NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString("POW can only be used between numerics or with an expression");
    }
    else
    {
        res=e1->pow(e2);
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
        Calculatrice::getInstance().getPile()->push(res);
    }
}

void Calculatrice::SQRT(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit);
    if(num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(lit);
        if(exp==NULL)
        {
            throw QString("SQRT can only be used with numerics or expressions");
        }
        else
            res=exp->sqrt();
    }
    else
        res=num->sqrt();
    Calculatrice::getInstance().getPile()->push(res);
    clearArgs();
    addArg(lit);
    delete lit;
}

void Calculatrice::COS(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit);
    if(num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(lit);
        if(exp==NULL)
        {
            throw QString("COS can only be used with numerics or expressions");
        }
        else
            res=exp->cos();
    }
    else
        res=num->cos();
    Calculatrice::getInstance().getPile()->push(res);
    clearArgs();
    addArg(lit);
    delete lit;

}

void Calculatrice::SIN(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit);
    if(num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(lit);
        if(exp==NULL)
        {
            throw QString("SIN can only be used with numerics or expressions");
        }
        else
            res=exp->sin();
    }
    else
        res=num->sin();
    Calculatrice::getInstance().getPile()->push(res);
    clearArgs();
    addArg(lit);
    delete lit;
}

void Calculatrice::TAN(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit);
    if(num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(lit);
        if(exp==NULL)
        {
            throw QString("TAN can only be used with numerics or expressions");
        }
        else
            res=exp->tan();
    }
    else
        res=num->tan();
    Calculatrice::getInstance().getPile()->push(res);
    clearArgs();
    addArg(lit);
    delete lit;

}

void Calculatrice::EXP(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit);
    if(num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(lit);
        if(exp==NULL)
        {
            throw QString("EXP can only be used with numerics or expressions");
        }
        else
            res=exp->exp();
    }
    else
        res=num->exp();
    Calculatrice::getInstance().getPile()->push(res);
    clearArgs();
    addArg(lit);
    delete lit;
}

void Calculatrice::LOG(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Numeric* num=dynamic_cast<Numeric*>(lit);
    if(num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(lit);
        if(exp==NULL)
        {
            throw QString("LOG can only be used with numerics or expressions");
        }
        else
            res=exp->log();
    }
    else
        res=num->log();
    Calculatrice::getInstance().getPile()->push(res);
    clearArgs();
    addArg(lit);
    delete lit;
}

void Calculatrice::DEN(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");

    Literal* lit=Calculatrice::getInstance().getPile()->top();
    Rational* rat=dynamic_cast<Rational*>(lit);
    Literal* res=NULL;
        if(rat==NULL)
        {
            Integer* e=dynamic_cast<Integer*>(lit);
            if (e==NULL){
                Expression* exp=dynamic_cast<Expression*>(lit);
                if(exp==NULL){
                    throw QString("DEN can only be used with integers,rationals or expressions");
                }
                lit=Calculatrice::getInstance().getPile()->pop();
                res=exp->den();
                Calculatrice::getInstance().getPile()->push(res);
            }
            else
            {
                lit=Calculatrice::getInstance().getPile()->pop();
                res=e->den();
                Calculatrice::getInstance().getPile()->push(res);
            }
        }
        else
        {
            lit=Calculatrice::getInstance().getPile()->pop();
            res=rat->den();
            Calculatrice::getInstance().getPile()->push(res);
        }
        clearArgs();
        addArg(lit);
        delete lit;
}

void Calculatrice::NUM(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");
    Literal* lit=Calculatrice::getInstance().getPile()->top();
    Rational* rat=dynamic_cast<Rational*>(lit);
        if(rat==NULL)
        {
            Integer* e=dynamic_cast<Integer*>(lit);
            if (e==NULL)
            {
                Expression* exp=dynamic_cast<Expression*>(lit);
                if(exp==NULL){
                    throw QString("NUM can only be used with integers,rationals or expressions");
                }
                lit=Calculatrice::getInstance().getPile()->pop();
                Literal* res=exp->num();
                Calculatrice::getInstance().getPile()->push(res);
            }
            else
            {
                lit=Calculatrice::getInstance().getPile()->pop();
                Literal* res=e->num();
                Calculatrice::getInstance().getPile()->push(res);
            }
        }
        else
        {
            lit=Calculatrice::getInstance().getPile()->pop();
            Literal* res=rat->num();
            Calculatrice::getInstance().getPile()->push(res);
        }
        clearArgs();
        addArg(lit);
        delete lit;

}



void Calculatrice::RE(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands");
    Literal* lit=Calculatrice::getInstance().getPile()->top();
    Complex* c=dynamic_cast<Complex*>(lit);
        if(c==NULL)
        {
            Numeric* num=dynamic_cast<Numeric*>(lit);
            if (num==0)
            {
                Expression* exp=dynamic_cast<Expression*>(lit);
                if(exp==NULL){
                    Calculatrice::getInstance().getPile()->push(lit);
                    throw QString("RE can only be used with numerics,complex or expressions");
                }
                lit=Calculatrice::getInstance().getPile()->pop();
                Literal* res=exp->re();
                Calculatrice::getInstance().getPile()->push(res);
            }
            else
            {
                lit=Calculatrice::getInstance().getPile()->pop();
                Literal* res=num->re();
                Calculatrice::getInstance().getPile()->push(res);
            }
        }
        else
        {
            lit=Calculatrice::getInstance().getPile()->pop();
            Literal* res=c->re();
            Calculatrice::getInstance().getPile()->push(res);
        }
        clearArgs();
        addArg(lit);
        delete lit;
}

void Calculatrice::IM(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands");
    Literal* lit=Calculatrice::getInstance().getPile()->top();
    Complex* c=dynamic_cast<Complex*>(lit);
        if(c==NULL)
        {
            Numeric* num=dynamic_cast<Numeric*>(lit);
            if (num==0)
            {
                Expression* exp=dynamic_cast<Expression*>(lit);
                if(exp==NULL){
                    Calculatrice::getInstance().getPile()->push(lit);
                    throw QString("IM can only be used with numerics,complex or expressions");
                }
                lit=Calculatrice::getInstance().getPile()->pop();
                Literal* res=exp->im();
                Calculatrice::getInstance().getPile()->push(res);
            }
            else
            {
                lit=Calculatrice::getInstance().getPile()->pop();
                Literal* res=num->im();
                Calculatrice::getInstance().getPile()->push(res);
            }
        }
        else
        {
            lit=Calculatrice::getInstance().getPile()->pop();
            Literal* res=c->im();
            Calculatrice::getInstance().getPile()->push(res);
        }
        clearArgs();
        addArg(lit);
        delete lit;
}


/* ------------------------------------------------------------------------------------
------------------------------- LOGICAL OPERATORS  ------------------------------------
--------------------------------------------------------------------------------------- */
void Calculatrice::EQUALITY(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    bool res=false;
    Numeric* num1=dynamic_cast<Numeric*>(lit1);
    Numeric* num2=dynamic_cast<Numeric*>(lit2);
    Expression* exp=NULL;
    Literal* resExp=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         resExp=(*tmp==exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        resExp=(*tmp==exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if(num1==NULL || num2 == NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString ("Logical operators can be used only between numeric numbers or expressions");
    }
    else
    {
        res= *num1==num2;

        if (res == true)
            Calculatrice::getInstance().getPile()->push(new Integer(1));
        else
            Calculatrice::getInstance().getPile()->push(new Integer(0));
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}

void Calculatrice::INEQUALITY(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    bool res=false;
    Numeric* num1=dynamic_cast<Numeric*>(lit1);
    Numeric* num2=dynamic_cast<Numeric*>(lit2);
    Expression* exp=NULL;
    Literal* resExp=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         resExp=(*tmp!=exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        resExp=(*tmp!=exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if(num1==NULL || num2 == NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString ("Logical operators can be used only between numeric numbers or expressions");
    }
    else
    {
        res= *num1!=num2;

        if (res == true)
            Calculatrice::getInstance().getPile()->push(new Integer(1));
        else
            Calculatrice::getInstance().getPile()->push(new Integer(0));
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}

void Calculatrice::LT(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    bool res=false;
    Numeric* num1=dynamic_cast<Numeric*>(lit1);
    Numeric* num2=dynamic_cast<Numeric*>(lit2);
    Expression* exp=NULL;
    Literal* resExp=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         resExp=(*tmp<exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        resExp=(*tmp<exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if(num1==NULL || num2 == NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString ("Logical operators can be used only between numeric numbers or expressions");
    }
    else
    {
        res= *num1<num2;

        if (res == true)
            Calculatrice::getInstance().getPile()->push(new Integer(1));
        else
            Calculatrice::getInstance().getPile()->push(new Integer(0));
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}

void Calculatrice::GT(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    bool res=false;
    Numeric* num1=dynamic_cast<Numeric*>(lit1);
    Numeric* num2=dynamic_cast<Numeric*>(lit2);
    Expression* exp=NULL;
    Literal* resExp=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         resExp=(*tmp>exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        resExp=(*tmp>exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if(num1==NULL || num2 == NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString ("Logical operators can be used only between numeric numbers or expressions");
    }
    else
    {
        res= *num1>num2;

        if (res == true)
            Calculatrice::getInstance().getPile()->push(new Integer(1));
        else
            Calculatrice::getInstance().getPile()->push(new Integer(0));
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}

void Calculatrice::LET(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    bool res=false;
    Numeric* num1=dynamic_cast<Numeric*>(lit1);
    Numeric* num2=dynamic_cast<Numeric*>(lit2);
    Expression* exp=NULL;
    Literal* resExp=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         resExp=(*tmp<=exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        resExp=(*tmp<=exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if(num1==NULL || num2 == NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString ("Logical operators can be used only between numeric numbers or expressions");
    }
    else
    {
        res= *num1<=num2;

        if (res == true)
            Calculatrice::getInstance().getPile()->push(new Integer(1));
        else
            Calculatrice::getInstance().getPile()->push(new Integer(0));

        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}

void Calculatrice::GET(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    bool res=false;
    Numeric* num1=dynamic_cast<Numeric*>(lit1);
    Numeric* num2=dynamic_cast<Numeric*>(lit2);
    Expression* exp=NULL;
    Literal* resExp=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         resExp=(*tmp>=exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        resExp=(*tmp>=exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(resExp);
    }
    else if(num1==NULL || num2 == NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString ("Logical operators can be used only between numeric numbers or expressions");
    }
    else
    {
        res= *num1>=num2;

        if (res == true)
            Calculatrice::getInstance().getPile()->push(new Integer(1));
        else
            Calculatrice::getInstance().getPile()->push(new Integer(0));

        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
    }
}


void Calculatrice::AND(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Integer* e1=dynamic_cast<Integer*>(lit1);
    Integer* e2=dynamic_cast<Integer*>(lit2);
    Expression* exp=NULL;
    Literal* res=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         res=tmp->AND(exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(res);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        res=tmp->AND(exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(res);
    }
    else if(e1==NULL || e2==NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString("AND can only be used between integers or with an expression");
    }
    else{
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
        res=*e1&e2;
        Calculatrice::getInstance().getPile()->push(res);
    }
}

void Calculatrice::OR(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Integer* e1=dynamic_cast<Integer*>(lit1);
    Integer* e2=dynamic_cast<Integer*>(lit2);
    Expression* exp=NULL;
    Literal* res=NULL;
    if((exp=dynamic_cast<Expression*>(lit2))!=NULL)
    {
         Expression* tmp=new Expression("'"+lit1->toString()+"'");
         clearArgs();
         addArg(lit1);
         addArg(lit2);
         delete lit1;
         res=tmp->OR(exp);
         delete lit2;
         delete tmp;
         Calculatrice::getInstance().getPile()->push(res);
    }
    else if((exp=dynamic_cast<Expression*>(lit1))!=NULL)
    {
        Expression* tmp=new Expression("'"+lit2->toString()+"'");
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit2;
        res=tmp->div(exp);
        delete lit1;
        delete tmp;
        Calculatrice::getInstance().getPile()->push(res);
    }
    else if(e1==NULL || e2==NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString("OR can only be used between integers or with an expression");
    }
    else{
        res=*e1|e2;
        clearArgs();
        addArg(lit1);
        addArg(lit2);
        delete lit1;
        delete lit2;
        Calculatrice::getInstance().getPile()->push(res);
    }
}

void Calculatrice::NOT(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");

    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Literal* res=NULL;
    Integer* e1=dynamic_cast<Integer*>(lit);
    if(e1==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(lit);
        if (exp==NULL){
            Calculatrice::getInstance().getPile()->push(lit);
            throw QString("NOT can only be used with an integer or an expression");
        }
        else
            res=exp->NOT();
    }
    else
    {
        res=~*e1;
    }
    clearArgs();
    addArg(lit);
    delete lit;
    Calculatrice::getInstance().getPile()->push(res);

}

/* ------------------------------------------------------------------------------------
------------------------------- MISCELLANEOUS OPERATORS  ------------------------------
--------------------------------------------------------------------------------------- */
void Calculatrice::STO(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Expression* exp=dynamic_cast<Expression*>(lit2);
    if(exp==NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString ("STO can only be used between an Expression(Atom) and a Literal.");
    }
    else
    {
        if(!exp->isAnAtom() || ( dynamic_cast<Complex*>(lit1)== NULL && dynamic_cast<Numeric*>(lit1)==NULL && dynamic_cast<Expression*>(lit1)==NULL))
        {
            Calculatrice::getInstance().getPile()->push(lit1);
            Calculatrice::getInstance().getPile()->push(lit2);
            throw QString ("STO can only be used between an Expression(Atom) and a Literal.");
        }
        QString s=exp->getExpressionSansGuillemets();
        Atom at(s);
        Variable* var=NULL;
        QList<Variable*>l=Manager::getInstance()->getList();
        for(int i=0;i<l.size();i++)
        {
            if(at.getValue()==l[i]->getId()->getValue())
                var=l[i];
        }
        if (var==NULL)
            Manager::getInstance()->addVariable(new Variable(new Atom(s),lit1->clone()));
        else{
            var->setValue(lit1->clone());
        }
        delete lit1;
        delete lit2;
    }
}

void Calculatrice::FORGET(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Not enough operands.");

    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Expression* exp=dynamic_cast<Expression*>(lit);
    if(exp==NULL){
        Calculatrice::getInstance().getPile()->push(lit);
        throw QString ("FORGET can only be used with an Expression(Atom).");
    }
    else{
        Manager::getInstance()->removeVariable(exp->getExpressionSansGuillemets());
        delete lit;
    }
}

void Calculatrice::EVAL(){
    if (Calculatrice::getInstance().getPile()->size() < 1)
        throw QString("Must have at least 1 element in the pile to EVAL something");
    Literal* lit=Calculatrice::getInstance().getPile()->pop();
    Expression* exp=dynamic_cast<Expression*>(lit);
    if (exp==NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit);
        throw QString("The literal must be an expression to be evaluated");
    }
    Literal* res=exp->evaluer();
    if(res==NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit);
        throw QString("Evaluation is incorrect");
    }
    clearArgs();
    addArg(lit);
    delete lit;
    Calculatrice::getInstance().getPile()->push(res);
}

void Calculatrice::IFT(){
    if (Calculatrice::getInstance().getPile()->size() < 2)
        throw QString("Not enough operands.");

    Literal* lit2=Calculatrice::getInstance().getPile()->pop();
    Literal* lit1=Calculatrice::getInstance().getPile()->pop();
    Expression* exp2=dynamic_cast<Expression*>(lit2);
    Expression* exp1=dynamic_cast<Expression*>(lit1);
    if(exp2==NULL || exp1==NULL)
    {
        Calculatrice::getInstance().getPile()->push(lit1);
        Calculatrice::getInstance().getPile()->push(lit2);
        throw QString ("IFT can only be used between two expressions");
    }
    else
    {
       Literal* tmp=exp1->evaluer();
       if(tmp->toString()=="1"){
            Calculatrice::getInstance().getPile()->push(exp2);
            Calculatrice::getInstance().EVAL();
       }
        delete tmp;
        delete lit1;
    }
}


