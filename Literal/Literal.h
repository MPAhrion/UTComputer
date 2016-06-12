#ifndef Literal_H_INCLUDED
#define Literal_H_INCLUDED
#include <cmath>
#include <QString>
#include <QChar>

/*! \file Literal.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Literal class declaration
*/

class Complex;
class Integer;
class Real;
class Rational;
class Numeric;

using namespace std;

/*! \class Literal
   * \brief Literal class declaration. Mother abstract class of all operands that manipulates the Calculator
   *
   * Literal is the type of objects handled by the calculator
   */
class Literal{

public:
  Literal(){}
  /**
   * \fn Literal()
   * \brief Constructor
   */

  virtual ~Literal(){}
  /**
   * \fn virtual ~Literal()
   * \brief Destructor
   */

  virtual QString toString()const=0;
  /**
   * \fn  virtual QString toString()const=0
   * \brief Get a literal value into a QString.
   * \return Qstring with the literal value.
   */

  virtual Literal* clone() const=0;
  /**
   * \fn  virtual Literal* clone() const=0;
   * \brief Copy a literal
   * \return The new literal
   */
};


#endif // Literal_H_INCLUDED
