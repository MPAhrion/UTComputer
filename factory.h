#ifndef FACTORY_H
#define FACTORY_H
#include "Literal/Integer.h"
#include "Literal/Rational.h"
#include "Literal/Real.h"
#include "Literal/Complex.h"
#include "Literal/Atom.h"
/*! \class Factory
   * \brief Factory class declaration.
   *
   * The factory will determine and create Literals Expression, Integer or Real thanks to a string passed to it.
   */
class Factory
{
private:
    /**
     * \fn   Factory();
     * \brief Constructor
     */
    Factory(){}
    Factory(const Factory &) { }
    Factory& operator=(const Factory &) { return *this; }

public:
    ~Factory(){}
    static Factory* GetFactory()
    {
        static Factory instance;
        return &instance;
    }
    /**
     * \fn   Literal* CreerLiteral(const QString& s);
     * \return The literal created.
     * \brief Create the right literal which match with regular expressions defined in the method.
     */
    Literal* CreerLiteral(const QString& s);
};


#endif // FACTORY_H
