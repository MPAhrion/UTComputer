#ifndef Numeric_H_INCLUDED
#define Numeric_H_INCLUDED

/*! \file Numeric.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Numeric class declaration
*/

#include "Literal.h"
#include "Expression.h"



/*! \class Numeric
   * \brief Numeric class declaration.
   *
   * A Numeric is a specific Literal type. It could be an Integer, a Real or a Rational.
   */
class Numeric : public Literal{
public:
  //Arithmetic operators

  Literal* operator+(Literal* c)const;
  /**
   * \fn  Literal* operator+(Literal* c)const;
   * \param c Literal to add
   * \brief Addition between a Numeric and a Litteral (in general)
   * \return Literal result
   */
  Literal* operator-(Literal* c)const;
  /**
   * \fn  Literal* operator-(Literal* c)const;
   * \param c Literal to subtract
   * \brief Subtraction between a Numeric and a Literal (in general)
   * \return Literal result
   */
  Literal* operator*(Literal* c)const;
  /**
   * \fn  Literal* operator*(Literal* c)const;
   * \param c Literal to multiply
   * \brief Multiplication between a Numeric and a Literal (in general)
   * \return Literal result
   */
  Literal* operator/(Literal* c)const;
  /**
   * \fn    Literal* operator/(Literal* c)const;
   * \param c Literal to divide
   * \brief Division between a Numeric and a Literal (in general)
   * \return Literal result
   */

  virtual Numeric* operator+(Numeric* c)const=0;
  /**
   * \fn    virtual Numeric* operator+(Numeric* c)const=0;
   * \param c Numeric to add
   * \brief Addition between two Numerics
   * \return Numeric result
   */
  virtual Numeric* operator-(Numeric* c)const=0;
  /**
   * \fn    virtual Numeric* operator-(Numeric* c)const=0;
   * \param c Numeric to subtract
   * \brief Subtraction between two Numerics
   * \return Numeric result
   */

  virtual Numeric* operator*(Numeric* c)const=0;
  /**
   * \fn    virtual Numeric* operator*(Numeric* c)const=0;
   * \param c Numeric to multiply
   * \brief Multiplication between two Numerics
   * \return Numeric result
   */
  virtual Numeric* operator/(Numeric* c)const=0;
  /**
   * \fn    virtual Numeric* operator/(Numeric* c)const=0;
   * \param c Numeric to divide
   * \brief Division between two Numerics
   * \return Numeric result
   */
  virtual Numeric* neg()const=0;
  /**
   * \fn    virtual Numeric* neg()const=0;
   * \brief Transform a positive Numeric into a negative Numeric and vice versa
   * \return Numeric result
   */
  Numeric* re()const{return this->clone();}
  /**
   * \fn    Numeric* re()const;
   * \brief Get the real part of a Numeric
   * \return A copy of the same Numeric.
   */
  Numeric* im()const;
  /**
   * \fn    Numeric* im()const;
   * \brief Get the imaginary part of a Numeric
   * \return Integer with value 0.
   */
  virtual Numeric* pow(Numeric* c)const=0;
  /**
   * \fn    virtual Numeric* pow(Numeric* c)const=0;
   * \param c Power
   * \brief Power operation
   * \return Numeric result
   */
  virtual Numeric* sqrt()const=0;
  /**
   * \fn    virtual Numeric* sqrt()const=0;
   * \brief Square root operation
   * \return Numeric result
   */
  virtual Numeric* sin()const=0;
  /**
   * \fn    virtual Numeric* sin()const=0;
   * \brief Sinus operation
   * \return Numeric result
   */
  virtual Numeric* cos()const=0;
  /**
   * \fn    virtual Numeric* cos()const=0;
   * \brief Cosinus operation
   * \return Numeric result
   */

  virtual Numeric* tan()const=0;
  /**
   * \fn    virtual Numeric* tan()const=0;
   * \brief Tangente operation
   * \return Numeric result
   */

  virtual Numeric* exp()const=0;
  /**
   * \fn    virtual Numeric* exp()const=0;
   * \brief Exponential operation
   * \return Numeric result
   */
  virtual Numeric* log()const=0;
  /**
   * \fn    virtual Numeric* log()const=0;
   * \brief Logarithm operation
   * \return Numeric result
   */

  //Logic operators
  virtual bool operator==(Numeric* c)const=0;
  /**
   * \fn    virtual bool operator==(Numeric* c)const=0;
   * \param c the Numeric to compare with
   * \brief Equality operation
   * \return 1 if true, 0 else.
   */
  virtual bool operator!=(Numeric* c)const=0;
  /**
   * \fn    virtual bool operator!=(Numeric* c)const=0;
   * \param c the Numeric to compare with
   * \brief Inequality operation
   * \return 1 if true, 0 else.
   */
  virtual bool operator<=(Numeric* c)const=0;
  /**
   * \fn    virtual bool operator<=(Numeric* c)const=0;
   * \param c the Numeric to compare with
   * \brief "Less or equal than" operation
   * \return 1 if true, 0 else.
   */
  virtual bool operator>=(Numeric* c)const=0;
  /**
   * \fn    virtual bool operator>=(Numeric* c)const=0;
   * \param c the Numeric to compare with
   * \brief "Greater or equal than" operation
   * \return 1 if true, 0 else.
   */
  virtual bool operator<(Numeric* c)const=0;
  /**
   * \fn    virtual bool operator<(Numeric* c)const=0;
   * \param c the Numeric to compare with
   * \brief "Less than" operation
   * \return 1 if true, 0 else.
   */
  virtual bool operator>(Numeric* c)const=0;
  /**
   * \fn    virtual bool operator>(Numeric* c)const=0;
   * \param c the Numeric to compare with
   * \brief "Greater than" operation
   * \return 1 if true, 0 else.
   */

  Expression* toExpression()const;
  /**
   * \fn    Expression* toExpression()const;
   * \brief Transforms a Numeric into an Expression
   * \return the Expression
   */
  virtual QString toString() const = 0;
  virtual Numeric* clone() const=0;
  virtual ~Numeric(){};

protected:
    Numeric(){}

};

#endif
