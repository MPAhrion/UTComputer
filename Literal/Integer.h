#ifndef Integer_H_INCLUDED
#define Integer_H_INCLUDED
/*! \file Integer.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Integer class declaration
*/
#include "Numeric.h"


/*! \class Integer
   * \brief Integer class declaration. Represents integers operands.
   */
class Integer : public Numeric{
      int _value;
  public:
      explicit Integer(int v=0):_value(v){}
      /**
       * \fn   explicit Integer(int v=0);
       * \param v value to assign to the Integer
       * \brief Constructor
       */
      int getValue()const {return _value;}
      /**
       * \fn  int getValue()const;
       * \brief Get the value of an Integer
       * \return Value of type int
       */
      void setValue(int v){_value=v;}
      /**
       * \fn  int setValue()const;
       * \brief Set the value of an Integer
       */
      //Arithmetic operators

      Numeric* operator+(Numeric* c)const;
      /**
       * \fn  Numeric* operator+(Numeric* c)const;
       * \param c Numeric to add
       * \brief Addition between an Integer and a Numeric
       * \return Numeric pointer which contains the result
       */
      Numeric* operator-(Numeric* c)const;
      /**
       * \fn  Numeric* operator-(Numeric* c)const;
       * \param c Numeric to subtract
       * \brief Subtraction between an Integer and a Numeric
       * \return Numeric pointer which contains the result
       */
      Numeric* operator*(Numeric* c)const;
      /**
       * \fn  Numeric* operator*(Numeric* c)const;
       * \param c Numeric to multiply
       * \brief Multiplication between an Integer and a Numeric
       * \return Numeric pointer which contains the result
       */
      Numeric* operator/(Numeric* c)const;
      /**
       * \fn  Numeric* operator/(Numeric* c)const;
       * \param c Numeric to divide
       * \brief Division between an Integer and a Numeric
       * \return Numeric pointer which contains the result
       */
      Integer* operator%(Integer* c)const;
      /**
       * \fn  Literal* operator%(Integer* c)const;
       * \param c
       * \brief Modulo operation between two Integer
       * \return Integer pointer which contains the result
       */
      Integer* div(Integer *c)const;
      /**
       * \fn  Integer* div(Integer* c)const;
       * \param c the divisor
       * \brief Euclidian division operation between two Integer
       * \return Integer pointer which contains the result
       */
      Integer* neg()const;

      Integer* num()const{return new Integer(getValue());}
      /**
       * \fn  Integer* num()const;
       * \brief Get the numerator part of an Integer
       * \return A new Integer with the same value.
       */
      Integer* den()const{return new Integer(1);}
      /**
       * \fn  Integer* den()const;
       * \brief Get the denumerator part of an Integer
       * \return A new Integer equals to 1
       */
      Numeric* pow(Numeric* c)const;
      Numeric* sqrt()const;
      Numeric* cos()const;
      Numeric* sin()const;
      Numeric* tan()const;
      Numeric* exp()const;
      Numeric* log()const;
      //Logic operators
      bool operator==(Numeric* c)const;
      bool operator!=(Numeric* c)const;
      bool operator<=(Numeric* c)const;
      bool operator>=(Numeric* c)const;
      bool operator<(Numeric* c)const;
      bool operator>(Numeric* c)const;
      Integer* operator&(Integer* c)const;
      /**
       * \fn  Integer* operator&(Integer* c)const;
       * \brief And bitwise operator
       * \return Integer result
       */
      Integer* operator|(Integer* c)const;
      /**
       * \fn  Integer* operator|(Integer* c)const;
       * \brief Or bitwise operator
       * \return Integer result
       */
      Integer* operator~()const;
      /**
       * \fn  Integer* operator~()const;
       * \brief Not bitwise operator
       * \return Integer result
       */

      QString toString() const;
      Integer* clone() const;
      ~Integer(){};
      /**
        * \brief Destructor
        **/
};

#endif
