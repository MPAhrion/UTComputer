#include "Expression.h"
#include "Complex.h"
#include "Numeric.h"
#include <QStack>
#include <QRegExp>
#include <QStringList>
#include "factory.h"
#include "Manager.h"

bool isNotAnOperator(const QString& s);

Expression* Expression::evaluateVariables() const
 {
     QString variable;
     QString after;
     QString tmp=getExpressionSansGuillemets()+'\'';
     QChar c;
     QRegExp regexAtom("^([a-zA-Z]+[0-9]*)+$");
     for(int i=0;i<tmp.size();i++)
     {
         c=tmp[i];
         if(c!='+' && c!='-' && c!='*' && c!='/' && c!='(' && c!=',' && c!=')' && c!='$' && c!='\'')
         {
             variable.append(c);
         }
         else
         {
             Atom at(variable);
             Variable* var=NULL;
             QList<Variable*>l=Manager::getInstance()->getList();
             for(int i=0;i<l.size();i++)
             {
                 if(at.getValue()==l[i]->getId()->getValue()){
                     var=l[i];
                     break;
                 }
             }
             if(var!=NULL)
             {
                 variable=var->getValue()->toString();
             }
             after.append(variable);
             if (c!='\'')
                after.append(c);
             variable="";
         }
     }
     return new Expression("'"+after+"'");
 }

Expression::Expression(const QString& s){

  if(s.at(0)!='\'' || s.at(s.size()-1)!='\'' || s.size()<3)
      throw QString("ERREUR : impossible de créer une literrale expression");
  _expression=s;
}

bool Expression::isAnAtom() const{
    QRegExp regexAtom("^\'([a-zA-Z]+[0-9]*)+\'$");
    return regexAtom.exactMatch(_expression);
}

QString Expression::getExpressionSansGuillemets()const{
    QString part = _expression;
    part.remove(QChar('\''), Qt::CaseInsensitive);
    return part;
}

Expression* Expression::clone() const{
    return new Expression(_expression);
}

Expression* Expression::neg() const{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'NEG("+tmp+")'");
}


Expression* Expression::operator+(Literal* c) const{
    QString part1;
    QString part2;
    unsigned int degMinExp1=0;
    unsigned int degMinExp2=0;
    Expression* tmp=NULL;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be added with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
            degMinExp2=exp->getPrioriteMin();
        }
    }
    else
    {
        tmp = num->toExpression();
        degMinExp2=tmp->getPrioriteMin();
        part2=tmp->getExpressionSansGuillemets();
        delete tmp;
    }
    part1 = getExpressionSansGuillemets();
    degMinExp1=this->getPrioriteMin();
    if(degMinExp1<=1 && degMinExp2<=1)
        return new Expression("'("+part1+")+("+part2+")'");
    if(degMinExp1<=1)
    {
        if(part2.at(0)=='-')
            return new Expression("'("+part1+")"+part2+"'");
        return new Expression("'("+part1+")+"+part2+"'");
    }
    if(degMinExp2<=1)
        return new Expression("'"+part1+"+("+part2+")'");
    if(part2.at(0)=='-')
        return new Expression("'"+part1+part2+"'");
    return new Expression("'"+part1+"+"+part2+"'");
}

Expression* Expression::operator-(Literal* c) const{
    QString part1;
    QString part2;
    unsigned int degMinExp1=0;
    unsigned int degMinExp2=0;
    Expression* tmp=NULL;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be substracted with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
            degMinExp2=exp->getPrioriteMin();
        }
    }
    else
    {
        tmp = num->toExpression();
        degMinExp2=tmp->getPrioriteMin();
        part2=tmp->getExpressionSansGuillemets();
        delete tmp;
    }
    part1 = getExpressionSansGuillemets();
    degMinExp1=this->getPrioriteMin();
    if(degMinExp1<=1 && degMinExp2<=1)
        return new Expression("'("+part1+")+("+part2+")'");
    if(degMinExp1<=1)
    {
        if(part2.at(0)=='-')
        {
            part2.remove(0,1);
            return new Expression("'("+part1+")+"+part2+"'");
        }
        return new Expression("'("+part1+")+"+part2+"'");
    }
    if(degMinExp2<=1)
        return new Expression("'"+part1+"+("+part2+")'");
    if(part2.at(0)=='-')
    {
        part2.remove(0,1);
        return new Expression("'"+part1+"+"+part2+"'");
    }
    return new Expression("'"+part1+"-"+part2+"'");
}

Expression* Expression::operator*(Literal* c)const{
    QString part1;
    QString part2;
    unsigned int degMinExp1=0;
    unsigned int degMinExp2=0;
    Expression* tmp=NULL;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be multiplied with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
            degMinExp2=exp->getPrioriteMin();
        }
    }
    else
    {
        tmp = num->toExpression();
        degMinExp2=tmp->getPrioriteMin();
        part2=tmp->getExpressionSansGuillemets();
        delete tmp;
    }
    part1 = getExpressionSansGuillemets();
    degMinExp1=this->getPrioriteMin();
    if(degMinExp1<=2 && degMinExp2<=2)
        return new Expression("'("+part1+")*("+part2+")'");
    if(degMinExp1<=2)
        return new Expression("'("+part1+")*"+part2+"'");
    if(degMinExp2<=2)
        return new Expression("'"+part1+"*("+part2+")'");
    return new Expression("'"+part1+"*"+part2+"'");
 }

Expression* Expression::operator/(Literal* c)const{
    QString part1;
    QString part2;
    unsigned int degMinExp1=0;
    unsigned int degMinExp2=0;
    Expression* tmp=NULL;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be divided with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
            degMinExp2=exp->getPrioriteMin();
        }
    }
    else
    {
        tmp = num->toExpression();
        degMinExp2=tmp->getPrioriteMin();
        part2=tmp->getExpressionSansGuillemets();
        delete tmp;
    }
    part1 = getExpressionSansGuillemets();
    degMinExp1=this->getPrioriteMin();
    if(degMinExp1<=2 && degMinExp2<=2)
        return new Expression("'("+part1+")/("+part2+")'");
    if(degMinExp1<=2)
        return new Expression("'("+part1+")/"+part2+"'");
    if(degMinExp2<=2)
        return new Expression("'"+part1+"/("+part2+")'");
    return new Expression("'"+part1+"/"+part2+"'");
 }

Expression* Expression::mod(Literal* c)const{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be moduled with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'MOD("+part1+","+part2+")'");
}

Expression* Expression::div(Literal *c)const{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be divided with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'DIV("+part1+","+part2+")'");
}


Expression* Expression::pow(Literal *c)const{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be powered with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'POW("+part2+","+part1+")'");
}

Expression* Expression::sqrt() const{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'SQRT("+tmp+")'");
}
Expression* Expression::cos() const{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'COS("+tmp+")'");
}
Expression* Expression::sin() const{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'SIN("+tmp+")'");
}
Expression* Expression::tan() const{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'TAN("+tmp+")'");
}
Expression* Expression::exp() const{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'EXP("+tmp+")'");
}
Expression* Expression::log() const{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'LOG("+tmp+")'");
}
Expression* Expression::num() const
{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'NUM("+tmp+")'");
}

Expression* Expression::den()const{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'DEN("+tmp+")'");
}

Expression* Expression::re() const
{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'RE("+tmp+")'");
}

Expression* Expression::im() const
{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'IM("+tmp+")'");
}

Expression* Expression::dollar(Literal* c) const
{
    QString part1;
    QString part2;
    unsigned int degMinExp1=0;
    unsigned int degMinExp2=0;
    Expression* tmp=NULL;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be transformed into Complex with an Expression or a Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
            degMinExp2=exp->getPrioriteMin();
        }
    }
    else
    {
        tmp = num->toExpression();
        degMinExp2=tmp->getPrioriteMin();
        part2=tmp->getExpressionSansGuillemets();
        delete tmp;
    }
    part1 = getExpressionSansGuillemets();
    degMinExp1=this->getPrioriteMin();
    if(degMinExp1>=2 && degMinExp2>=2)
        return new Expression("'("+part1+")$("+part2+")'");
    if(degMinExp1>=2)
        return new Expression("'("+part1+")$"+part2+"'");
    if(degMinExp2>=2)
        return new Expression("'"+part1+"$("+part2+")'");
    return new Expression("'"+part1+"$"+part2+"'");
}

Expression* Expression::operator==(Literal* c) const
{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be compared with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'"+part1+"="+part2+"'");
}

Expression* Expression::operator!=(Literal* c)const{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be compared with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'"+part1+"!="+part2+"'");
}

Expression* Expression::operator>(Literal* c) const{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be compared with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'"+part1+">"+part2+"'");
}

Expression* Expression::operator<(Literal* c)const{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be compared with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'"+part1+"<"+part2+"'");
}

Expression* Expression::operator<=(Literal* c) const
{
QString part1;
QString part2;
Numeric *num=dynamic_cast<Numeric*>(c);
if (num==NULL)
{
    Expression* exp=dynamic_cast<Expression*>(c);
    if(exp==NULL)
    {
        throw QString("Expression only can be compared with Expression or Numeric");
    }
    else
    {
        part2=exp->getExpressionSansGuillemets();
    }
}
else
{
    part2=num->toString();
}
part1=getExpressionSansGuillemets();
return new Expression("'"+part1+"<="+part2+"'");
}

Expression* Expression::operator>=(Literal* c) const
{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be compared with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'"+part1+">="+part2+"'");
}

Expression* Expression::AND(Literal* c) const
{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be compared with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'AND("+part1+","+part2+")'");
}

Expression* Expression::OR(Literal *c) const
{
    QString part1;
    QString part2;
    Numeric *num=dynamic_cast<Numeric*>(c);
    if (num==NULL)
    {
        Expression* exp=dynamic_cast<Expression*>(c);
        if(exp==NULL)
        {
            throw QString("Expression only can be compared with Expression or Numeric");
        }
        else
        {
            part2=exp->getExpressionSansGuillemets();
        }
    }
    else
    {
        part2=num->toString();
    }
    part1=getExpressionSansGuillemets();
    return new Expression("'OR("+part1+","+part2+")'");
}

Expression* Expression::NOT() const
{
    QString tmp=getExpressionSansGuillemets();
    return new Expression("'NOT("+tmp+")'");
}


unsigned int getPriorite(QChar c)
{
    QRegExp regexAlpha("^[A-Z]$");
    if(c=='*' || c== '/' || regexAlpha.exactMatch(c) || c==' ')
        return 3;
    else if(c=='+' || c== '-' || c=='$')
        return 2;
    else if (c=='=' || c=='>' || c=='<' || c=='!' || c=='>')
        return 1;
    else
        return 0;
}


unsigned int Expression::getPrioriteMin() const{
    if(_expression.contains('=') || _expression.contains('>') ||_expression.contains('<') || _expression.contains("!=") || _expression.contains(">=") ||_expression.contains("<="))
        return 1;
    if(_expression.contains('+') || _expression.contains('-') || _expression.contains('$'))
        return 2;
    if(_expression.contains('*') || _expression.contains('/'))
        return 3;
    else return 5;
}

QString Expression::toPostfixe() const{
       QRegExp regexChiffre("^[0-9]$");
       QRegExp regexAlpha("^[A-Z]$");
       QString infix=this->getExpressionSansGuillemets();
       infix.replace(","," ");
       QString postfix;
       QStack<QChar> s;
       int size=infix.size();
       unsigned int priorite;
       int i = 0;
       int k = 0;
       int tmp;
       QChar c;
       // iterate over the infix expression
       while (i < size) {
          c = infix.at(i);
          if (c == '(') {
             // simply push the opening parenthesis
             s.push(c);
             i++;
             continue;
          }
          if (c== ')'){
             // if we see a closing parenthesis,
             // pop of all the elements and append it to
             // the postfix expression till we encounter
             // a opening parenthesis
             while (!s.empty() && s.top() != '(') {
                 if(s.top()=='!' || s.top()=='>' || s.top()=='<')
                 {
                     postfix.replace(k++,1,' ');
                     postfix.replace(k++,1,s.top());
                     s.pop();
                     if(s.top()=='='){
                        postfix.replace(k++,1,s.top());
                        s.pop();
                     }
                }
                 else{
                 if(!regexAlpha.exactMatch((s.top())))
                       postfix.replace(k++,1,' ');
                       postfix.replace(k++,1,s.top());
                       s.pop();
                 }
             }
             // pop off the opening parenthesis also
             if (!s.empty()) {
                s.pop();
                postfix.replace(k++,1,' ');
             }
             i++;
             continue;
          }
          priorite = getPriorite(c);
          if (priorite == 0){
             // we saw an operand
             // simply append it to postfix expression
             //if(i+1<infix.size() && !regexChiffre.exactMatch(infix.at(i+1)))
             postfix.replace(k++,1,c);

          }
          else {
             // we saw an operator
             if (s.empty()) {
                // simply push the operator onto stack if
                // stack is empty
                tmp=i;
                while(tmp < infix.size() && regexAlpha.exactMatch(infix.at(tmp)))
                {
                    tmp++;
                }
                if (tmp!=i)
                {
                    tmp--;
                    for(int j=tmp;j>=i;j--)
                    {
                        s.push(infix.at(j));
                    }
                    i=tmp;
                }
                else if(i+1<infix.size() && ((infix.at(i)=='!' ||infix.at(i)=='<' || infix.at(i)=='>') && infix.at(i+1)=='='))
                {
                    s.push(infix.at(i+1));
                    s.push(infix.at(i));
                    i++;
                }
                else
                    s.push(c);
                postfix.replace(k++,1,' ');
             }
             else {
                // pop of all the operators from the stack and
                // append it to the postfix expression till we
                // see an operator with a lower precedence that
                // the current operator
                while (!s.empty() && s.top() != '(' && priorite <= getPriorite(s.top())) {
                    if(s.top()=='!' || s.top()=='>' || s.top()=='<')
                    {
                        postfix.replace(k++,1,s.top());
                        s.pop();
                        if(s.top()!='=')
                            postfix.replace(k++,1,' ');

                    }
                    else
                    {
                       if(!regexAlpha.exactMatch(s.top()))
                            postfix.replace(k++,1,' ');
                       postfix.replace(k++,1,s.top());
                       s.pop();
                    }
                }
                tmp=i;
                while(tmp < infix.size() && regexAlpha.exactMatch(infix.at(tmp)))
                {
                    tmp++;
                }
                if (tmp!=i)
                {
                    tmp--;
                    for(int j=tmp;j>=i;j--)
                    {
                        s.push(infix.at(j));
                    }
                    i=tmp;
                }
                else if(i+1<infix.size() && ((infix.at(i)=='!' ||infix.at(i)=='<' || infix.at(i)=='>') && infix.at(i+1)=='='))
                {
                    s.push(infix.at(i+1));
                    s.push(infix.at(i));
                    i++;
                }
                else
                    s.push(c);
                if(!regexAlpha.exactMatch(c))
                    postfix.replace(k++,1,' ');
            }
          }
          i++;
       }
       // pop of the remaining operators present in the stack
       // and append it to postfix expression
       while (!s.empty()) {
           if(s.top()=='!' || s.top()=='>' || s.top()=='<')
           {
               postfix.replace(k++,1,' ');
               postfix.replace(k++,1,s.top());
               s.pop();
               if(s.top()=='='){
                  postfix.replace(k++,1,s.top());
                  s.pop();
               }
          }
          else{
          if(!regexAlpha.exactMatch((s.top())))
                postfix.replace(k++,1,' ');
                postfix.replace(k++,1,s.top());
                s.pop();
          }
       }
       //return new Expression("'"+postfix+"'");
       int cp=0;
       for (int i=0;i<postfix.size();i++)
       {
           if(regexChiffre.exactMatch(postfix.at(i)))
           {
               cp++;
           }
           if(postfix.at(i)=='-' && cp==1)
           {
               postfix.replace(i-2,3,"-"+postfix[i-2]+" ");
               i--;
               c=0;
           }
       }
       return postfix;

}
bool isAnOperator(const QString& s);
bool isALiteral(const QString& s);


void deleteEltsStacked(QStack<Literal*> Pile)
{
    while (!Pile.isEmpty())
    {
        Literal* tmp=Pile.pop();
        delete tmp;
    }
}

Literal* Expression::evaluer() const
{
    Expression*exp=evaluateVariables();
    QStringList liste= exp->toPostfixe().split(" ", QString::SkipEmptyParts);
    delete exp;
    QStack<Literal*> Pile;
    Literal* tmp;
    for (int i=0;i<liste.length();i++){
        if(isALiteral(liste[i]))
        {
            Pile.push(Factory::GetFactory()->CreerLiteral(liste[i]));
        }
        else if(liste[i]=="+")
        {
            if (Pile.size()< 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit1);
            if(num==NULL)
            {
                Complex* cplx=dynamic_cast<Complex*>(lit1);
                if(cplx==NULL)
                {
                    deleteEltsStacked(Pile);
                    return NULL;
                }
                else
                {
                    res=*cplx+lit2;
                }
            }
            else
            {
                res=*num+lit2;
            }
            if (res!=NULL)
            {
                Pile.push(res);
                delete lit1;
                delete lit2;
            }
        }
        else if(liste[i]=="-")
        {
            if (Pile.size()< 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit1);
            if(num==NULL)
            {
                Complex* cplx=dynamic_cast<Complex*>(lit1);
                if(cplx==NULL)
                {
                    deleteEltsStacked(Pile);
                    return NULL;
                }
                else
                {
                    res=*cplx-lit2;
                }
            }
            else
            {
                res=*num-lit2;
            }
            if (res!=NULL)
            {
                Pile.push(res);
                delete lit1;
                delete lit2;
            }
        }
        else if(liste[i]=="*")
        {
            if (Pile.size()< 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit1);
            if(num==NULL)
            {
                Complex* cplx=dynamic_cast<Complex*>(lit1);
                if(cplx==NULL)
                {
                    deleteEltsStacked(Pile);
                    return NULL;
                }
                else
                {
                    res=*cplx*lit2;
                }
            }
            else
            {
                res=*num*lit2;
            }
            if (res!=NULL)
            {
                Pile.push(res);
                delete lit1;
                delete lit2;
            }
        }
        else if(liste[i]=="/")
        {
            if (Pile.size()< 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit1);
            if(num==NULL)
            {
                Complex* cplx=dynamic_cast<Complex*>(lit1);
                if(cplx==NULL)
                {
                    deleteEltsStacked(Pile);
                    return NULL;
                }
                else
                {
                    res=*cplx/lit2;
                }
            }
            else
            {
                res=*num/lit2;
            }
            if (res!=NULL)
            {
                Pile.push(res);
                delete lit1;
                delete lit2;
            }
        }
        else if(liste[i]=="DIV")
        {
            if (Pile.size() < 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            Literal* res=NULL;
            Integer* e1=dynamic_cast<Integer*>(lit1);
            Integer* e2=dynamic_cast<Integer*>(lit2);
            if(e1==NULL || e2==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            res=e1->div(e2);
            delete lit1;
            delete lit2;
            Pile.push(res);
        }
        else if(liste[i]=="MOD")
        {
            if (Pile.size() < 2)
                return NULL;

            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            Literal* res=NULL;
            Integer* e1=dynamic_cast<Integer*>(lit1);
            Integer* e2=dynamic_cast<Integer*>(lit2);
            if(e1==NULL || e2==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            res=*e1%e2;
            delete lit1;
            delete lit2;
            Pile.push(res);
        }
        else if(liste[i]=="NEG")
        {
            if (Pile.size()<1)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit);
            if(num==NULL)
            {
                Expression* exp=dynamic_cast<Expression*>(lit);
                if(exp==NULL)
                {
                    deleteEltsStacked(Pile);
                    return NULL;
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
                Pile.push(res);
                delete lit;
            }
        }
        else if(liste[i]=="NUM")
        {
            if (Pile.size() < 1)
            {
                return NULL;
            }
            Literal* lit=Pile.pop();
            Rational* rat=dynamic_cast<Rational*>(lit);
                if(rat==NULL)
                {
                    Integer* e=dynamic_cast<Integer*>(lit);
                    if (e==NULL)
                    {
                        deleteEltsStacked(Pile);
                        return NULL;
                    }
                    else
                    {
                        Literal* res=e->num();
                        Pile.push(res);
                        delete lit;
                    }
                }
                else
                {
                    Literal* res=rat->num();
                    Pile.push(res);
                    delete lit;
                }
        }
        else if(liste[i]=="DEN")
        {
            if (Pile.size() < 1)
                return NULL;
            Literal* lit=Pile.pop();
            Rational* rat=dynamic_cast<Rational*>(lit);
                if(rat==NULL)
                {
                    Integer* e=dynamic_cast<Integer*>(lit);
                    if (e==NULL)
                    {
                        deleteEltsStacked(Pile);
                        return NULL;
                    }
                    else
                    {
                        Literal* res=e->den();
                        Pile.push(res);
                        delete lit;
                    }
                }
                else
                {
                    Literal* res=rat->den();
                    Pile.push(res);
                    delete lit;
                }
        }
        else if(liste[i]=="RE")
        {
            if (Pile.size() < 1)
                return NULL;
            Literal* lit=Pile.pop();
            Complex* c=dynamic_cast<Complex*>(lit);
                if(c==NULL)
                {
                    Numeric* num=dynamic_cast<Numeric*>(lit);
                    if (num==0)
                    {
                        deleteEltsStacked(Pile);
                        return NULL;
                    }
                    else
                    {
                        Literal* res=num->re();
                        Pile.push(res);
                        delete lit;
                    }
                }
                else
                {
                    Literal* res=c->re();
                    Pile.push(res);
                    delete lit;
                }
        }
        else if(liste[i]=="IM")
        {
            if (Pile.size() < 1)
                return NULL;
            Literal* lit=Pile.pop();
            Complex* c=dynamic_cast<Complex*>(lit);
                if(c==NULL)
                {
                    Numeric* num=dynamic_cast<Numeric*>(lit);
                    if (num==0)
                    {
                        deleteEltsStacked(Pile);
                        return NULL;
                    }
                    else
                    {
                        Literal* res=num->im();
                        Pile.push(res);
                        delete lit;
                    }
                }
                else
                {
                    Literal* res=c->im();
                    Pile.push(res);
                    delete lit;
                }
        }
        else if(liste[i]=="$")
        {
            if (Pile.size() < 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            if (lit2->toString()=="0")
            {
               Pile.push(lit1);
               delete lit2;
            }
            else{
                try{
                    Literal* res=new Complex(lit1,lit2);
                    Pile.push(res);
                    delete lit1;
                    delete lit2;
                }
                catch (QString s)
                {
                    Pile.push(lit1);
                    Pile.push(lit2);
                    throw s;
                }
            }
        }
        else if(liste[i]=="=")
        {
            if (Pile.size()< 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            bool res=false;
            Numeric* num1=dynamic_cast<Numeric*>(lit1);
            Numeric* num2=dynamic_cast<Numeric*>(lit2);
            if(num1==NULL || num2 == NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
            {
                res= *num1==num2;
            }
            if (res == true)
                Pile.push(new Integer(1));
            else
                Pile.push(new Integer(0));

            delete lit1;
            delete lit2;
        }
        else if(liste[i]=="!=")
        {
            if (Pile.size()< 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            bool res=false;
            Numeric* num1=dynamic_cast<Numeric*>(lit1);
            Numeric* num2=dynamic_cast<Numeric*>(lit2);
            if(num1==NULL || num2 == NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
            {
                res= *num1!=num2;
            }
            if (res == true)
                Pile.push(new Integer(1));
            else
                Pile.push(new Integer(0));

            delete lit1;
            delete lit2;
        }
        else if(liste[i]=="<=")
        {
            if (Pile.size()< 2)
                return NULL;
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            bool res=false;
            Numeric* num1=dynamic_cast<Numeric*>(lit1);
            Numeric* num2=dynamic_cast<Numeric*>(lit2);
            if(num1==NULL || num2 == NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
            {
                res= *num1<=num2;
            }
            if (res == true)
                Pile.push(new Integer(1));
            else
                Pile.push(new Integer(0));

            delete lit1;
            delete lit2;
        }
        else if(liste[i]==">=")
        {
            if (Pile.size()< 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            bool res=false;
            Numeric* num1=dynamic_cast<Numeric*>(lit1);
            Numeric* num2=dynamic_cast<Numeric*>(lit2);
            if(num1==NULL || num2 == NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
            {
                res= *num1>=num2;
            }
            if (res == true)
                Pile.push(new Integer(1));
            else
                Pile.push(new Integer(0));

            delete lit1;
            delete lit2;
        }
        else if(liste[i]==">")
        {
            if (Pile.size()< 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            bool res=false;
            Numeric* num1=dynamic_cast<Numeric*>(lit1);
            Numeric* num2=dynamic_cast<Numeric*>(lit2);
            if(num1==NULL || num2 == NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
            {
                res= *num1>num2;
            }
            if (res == true)
                Pile.push(new Integer(1));
            else
                Pile.push(new Integer(0));

            delete lit1;
            delete lit2;
        }
        else if(liste[i]=="<")
        {
            if (Pile.size()< 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            bool res=false;
            Numeric* num1=dynamic_cast<Numeric*>(lit1);
            Numeric* num2=dynamic_cast<Numeric*>(lit2);
            if(num1==NULL || num2 == NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
            {
                res= *num1<num2;
            }
            if (res == true)
                Pile.push(new Integer(1));
            else
                Pile.push(new Integer(0));

            delete lit1;
            delete lit2;
        }
        else if(liste[i]=="AND")
        {
            if (Pile.size() < 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            Literal* res=NULL;
            Integer* e1=dynamic_cast<Integer*>(lit1);
            Integer* e2=dynamic_cast<Integer*>(lit2);
            if(e1==NULL || e2==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            res=*e1&e2;
            Pile.push(res);
        }
        else if(liste[i]=="OR")
        {
            if (Pile.size() < 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            Literal* res=NULL;
            Integer* e1=dynamic_cast<Integer*>(lit1);
            Integer* e2=dynamic_cast<Integer*>(lit2);
            if(e1==NULL || e2==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            res=*e1|e2;
            Pile.push(res);
        }
        else if(liste[i]=="NOT")
        {
            if (Pile.size() < 1)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit=Pile.pop();
            Literal* res=NULL;
            Integer* e1=dynamic_cast<Integer*>(lit);
            if(e1==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            res=~*e1;
            Pile.push(res);
        }
        else if (liste[i]=="SIN")
        {
            if (Pile.size() < 1)
                return NULL;
            Literal* lit=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit);
            if(num==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
                res=num->sin();
            Pile.push(res);
        }
        else if (liste[i]=="TAN")
        {
            if (Pile.size() < 1)
                return NULL;
            Literal* lit=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit);
            if(num==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
                res=num->tan();
            Pile.push(res);
        }
        else if (liste[i]=="COS")
        {
            if (Pile.size() < 1)
                return NULL;
            Literal* lit=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit);
            if(num==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
                res=num->cos();
            Pile.push(res);
        }
        else if (liste[i]=="LOG")
        {
            if (Pile.size() < 1)
                return NULL;
            Literal* lit=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit);
            if(num==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
                res=num->log();
            Pile.push(res);
        }
        else if (liste[i]=="EXP")
        {
            if (Pile.size() < 1)
                return NULL;
            Literal* lit=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit);
            if(num==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
                res=num->exp();
            Pile.push(res);
        }
        else if (liste[i]=="POW")
        {
            if (Pile.size() < 2)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            Literal* lit2=Pile.pop();
            Literal* lit1=Pile.pop();
            Numeric* e1=NULL;
            Numeric* e2=NULL;
            Literal* res=NULL;
            if((e1=dynamic_cast<Numeric*>(lit1))==NULL || (e2=dynamic_cast<Numeric*>(lit2))==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
            {
                res=e1->pow(e2);
                delete lit1;
                delete lit2;
                Pile.push(res);
            }
        }
        else if (liste[i]=="SQRT")
        {
            if (Pile.size() < 1)
                return NULL;
            Literal* lit=Pile.pop();
            Literal* res=NULL;
            Numeric* num=dynamic_cast<Numeric*>(lit);
            if(num==NULL)
            {
                deleteEltsStacked(Pile);
                return NULL;
            }
            else
                res=num->sqrt();
            Pile.push(res);
        }
        else
        {
            deleteEltsStacked(Pile);
            return NULL;
        }

    }
    tmp=Pile.pop();
    return tmp;
}





