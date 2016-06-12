#ifndef Real_H_INCLUDED
#define Real_H_INCLUDED
/*! \file Real.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Real class declaration
*/
#include "Numeric.h"



/*! \class Real
   * \brief Real class declaration. Represents reals operands.
   */
class Real : public Numeric{
    double _value;
  public:
      Real(double v=0):_value(v){}
      /**
       *  \fn Real(double v=0);
       * \brief Constructor
       * \param v value to assign to the Real
       */
      double getValue()const {return _value;}
      /**
       *  \fn double getValue()const;
       * \brief Get Real value
       * \return double equals to the Real value
       */
      void setValue(double v){_value=v;}
      /**
       *  \fn void setValue(double v);
       * \brief Set a Real value
       * \param v value to assign to the Real
       */

      //Arithmetic operators
       Numeric* operator+(Numeric*)const;
       Numeric* operator-(Numeric*)const;
       Numeric* operator*(Numeric*)const;
       Numeric* operator/(Numeric*)const;
       Real* neg()const;
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

      Real* clone() const;
      QString toString() const;
      ~Real(){};
      /**
        * \brief Destructor
        **/
};
#endif
