#include "factory.h"
#include "QRegExp"
#include "Manager.h"

Literal* Factory::CreerLiteral(const QString& s){
    QRegExp regexInteger("^-?[0-9]+$");
    QRegExp regexReal("^-?[0-9]+.[0-9]+$");
    QRegExp regexAtom("^([a-zA-Z]+[0-9]*)+$");
    if(regexInteger.exactMatch(s))
        return new Integer(s.toInt());
    else if(regexReal.exactMatch(s))
        return new Real(s.toDouble());
    else if(regexAtom.exactMatch(s))
    {
        Atom at(s);
        Variable* var=NULL;
        Literal* res=NULL;
        QList<Variable*>l=Manager::getInstance()->getList();
        for(int i=0;i<l.size();i++)
        {
            if(at.getValue()==l[i]->getId()->getValue())
                var=l[i];
        }
        if (var!=NULL)
            res=var->getValue()->clone();
        else
            res=new Expression("'"+s+"'");
        return res;
    }
    else if((s.at(0)=='\'' && s.at(s.size()-1)=='\'' && s.size()>=3))
        return new Expression(s);
    else
        return NULL;
}

