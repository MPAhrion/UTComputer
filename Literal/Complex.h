#ifndef Complex_H_INCLUDED
#define Complex_H_INCLUDED
/*! \file Complex.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Complex class declaration
*/
#include "Literal.h"
#include "Numeric.h"
#include "Expression.h"
using namespace std;


/*! \class Complex
   * \brief Complex class declaration. Represents complex operands.
   *
   * A Complex literal is a Literal composed of 2 Numeric : one represents the real part, the other the imaginary part.
   * Both parts are separated by $ symbol. ex: 6$5 , 0.9$7.
   */
class Complex : public Literal{
  Numeric* _re;
  Numeric* _im;
public:
  Complex (Literal *r, Literal *i);
  /**
   *  \fn Complex (Literal* r, Literal* i);
   * \brief Constructor
   * \param r Literal to assign to the real part
   * \param i Literal to assign to the imaginary part
   */

  Numeric* getR()const{return _re;}
  /**
   * \fn  Numeric* getR()const;
   * \brief Get real part
   * \return Numeric with real part value
   */
  Numeric* getI()const{return _im;}
  /**
   * \fn  Numeric* getI()const;
   * \brief Get imaginary part
   * \return Numeric with imaginary part value
   */
  void setRe(Numeric* n){_re = n;}
  /**
   * \fn  void setRe(Numeric* n);
   * \brief Set real part
   * \param n Numeric to assign to real part
   */
  void setIm(Numeric* n){_im = n;}
  /**
   * \fn  void setIm(Numeric* n);
   * \brief Set imaginary part
   * \param n Numeric to assign to imaginary part
   */

  Literal* operator+(Literal* c)const;
  /**
   * \fn  Literal* operator+(Literal* c)const;
   * \brief Addition operation between a Complex and a Literal
   * \param c Literal to add
   * \return Literal pointer equals to the result
   */
  Literal* operator-(Literal* c)const;
  /**
   * \fn  Literal* operator-(Literal* c)const;
   * \brief Subtraction operation between a Complex and a Literal
   * \param c Literal to sub
   * \return Literal pointer equals to the result
   */
  Literal* operator*(Literal* c)const;
  /**
   * \fn  Literal* operator*(Literal* c)const;
   * \brief Multiplication operation between a Complex and a Literal
   * \param c Literal to multiply
   * \return Literal pointer equals to the result
   */
  Literal* operator/(Literal* c)const;
  /**
   * \fn  Literal* operator/(Literal* c)const;
   * \brief Division operation between a Complex and a Literal
   * \param c Literal to divide
   * \return Literal pointer equals to the result
   */

  Numeric* re() const{return _re->clone();}
  /**
   * \fn    Numeric* re() const;
   * \brief Get the real part in a new literal
   * \return Numeric equals to the real part
   */
  Numeric* im() const{return _im->clone();}
  /**
   * \fn    Numeric* im() const;
   * \brief Get the imaginary part in a new literal
   * \return Numeric equals to the imaginary part
   */

  Expression* toExpression() const;
  /**
   * \fn    Expression* toExpression()const;
   * \brief Transforms a Complex into an Expression
   * \return the Expression
   */
  QString toString() const;
  Complex* clone() const;


  ~Complex(){
      delete _re;
      delete _im;
  }
  /**
    * \brief Destructor
    **/
};
#endif
