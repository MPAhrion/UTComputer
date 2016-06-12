#ifndef Rational_H_INCLUDED
#define Rational_H_INCLUDED
/*! \file Rational.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Rational class declaration
*/

#include "Numeric.h"
#include "Integer.h"
#include "Real.h"


/*! \class Rational
   * \brief Rational class declaration. Represents rationals operands.
   *
   * Rational is a Literal composed of 2 Integer : one is called the numerator, the other the denominator.
   * Both parts are separated by a "/" symbol.
   */
class Rational : public Numeric{
    Integer _numerator;
    Integer _denominator;
  public:
      Rational(Integer n=Integer(0),Integer d=Integer(1)):_numerator(n),_denominator(d){}
      /**
       *  \fn Rational(Integer n=Integer(0),Integer d=Integer(1));
       * \brief Constructor
       * \param n Integer to assign to the numerator
       * \param d Integer to assign to the denominator
       */
      Rational(int n,int d):_numerator(Integer(n)),_denominator(Integer(d)){}
      /**
       * \fn  Rational(int n,int d)
       * \brief Constructor
       * \param n int, d int
       */
      Integer getNumerator() const {return _numerator;}
      /**
       * \fn  Integer getNumerator() const;
       * \brief Get numerator
       * \return Integer with numerator value
       */
      Integer getDenominator() const {return _denominator;}
      /**
       * \fn  Integer getDenominator() const;
       * \brief Get denominator
       * \return Integer with denominator value
       */

      void setNumerator(Integer n) {_numerator=n;}
      /**
       * \fn  void setNumerator(Integer n);
       * \brief Set numerator
       * \param n Integer
       */
      void setDenominator(Integer d) {_denominator=d;}
      /**
       * \fn  void setDenominator(Integer d);
       * \brief Set denominator
       * \param n Integer
       */
      void simplification();
      /**
       * \fn  void simplification();
       * \brief Simplify a Rational
       */
      double toDouble()const;
      /**
       * \fn  double toDouble()const;
       * \brief Convert a Rational into double value.
       * \return double
       */

      //Arithmetic operators
      Numeric* operator+(Numeric*)const;
      Numeric* operator-(Numeric*)const;
      Numeric* operator*(Numeric*)const;
      Numeric* operator/(Numeric*)const;
      Numeric* neg()const;
      Integer* num()const;
      /**
       * \fn  Integer* num()const;
       * \brief Get numerator value into an Integer
       * \return Integer pointer with numerator value
       */
      Integer* den()const;
      /**
       * \fn  Integer* den()const;
       * \brief Get denominator value into an Integer
       * \return Integer pointer with denominator value
       */
      Numeric* pow(Numeric*)const;
      Numeric* sqrt()const;
      Numeric* cos()const;
      Numeric* sin()const;
      Numeric* tan()const;
      Numeric* exp()const;
      Numeric* log()const;

      //Logic operators
      bool operator==(Numeric*)const;
      bool operator!=(Numeric*)const;
      bool operator<=(Numeric*)const;
      bool operator>=(Numeric*)const;
      bool operator<(Numeric*)const;
      bool operator>(Numeric*)const;

      Rational* clone() const;
      QString toString() const;
      ~Rational(){};
      /**
        * \brief Destructor
        **/
};
#endif
