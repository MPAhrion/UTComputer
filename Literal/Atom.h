#ifndef Atom_H
#define Atom_H
/*! \file Atom.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Atom class declaration
*/
#include "Literal.h"

/*! \class Atom
   * \brief Atom class declaration
   *
*/

class Atom:public Literal{
  QString _value;
  Atom(const Atom& a);
  Atom& operator=(const Atom& a);
public:
  Atom(const QString &s);
  /**
   * \fn   Atom(const QString &s);
   * \param s QString to assign to the Atom
   * \brief Constructor
   */
  ~Atom(){}
  QString toString()const{return _value;}
  Atom* clone() const;
  const QString& getValue() const {return _value;}
  /**
   * \fn   const QString& getValue() const;
   * \brief Get the value of the atom
   */

   void setValue(const QString& s){_value = s;}
   /**
    * \fn   void setValue(const QString& s);
    * \param s QString to assign to the Atom
    * \brief Set value of an Atom
    */

};

#endif
