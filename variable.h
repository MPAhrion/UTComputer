#ifndef VARIABLE_H
#define VARIABLE_H
/*! \file variable.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Variable class declaration
*/
#include "Literal/Atom.h"
#include <QString>

/*! \class Variable
   * \brief Variable class declaration.
   *
   * A Variable is named with an id (an Atom) and it stores a value (a Literal). When the id is used, it is replaced by the Variable value.
   */
class Variable{
  Atom* _identificateur;
  Literal* _value;
public:
  Variable(Atom* id, Literal* v);
  /**
   * \fn   Variable(Atom* id, Literal* v);
   * \param id Variable name
   * \param v Value to assign.
   * \brief Constructor
   */
  const Literal* getValue() const{return _value;}
  /**
   * \fn  const Literal* getValue()const;
   * \brief Get the value of a Variable
   */
  const Atom* getId() const {return _identificateur;}
  /**
   * \fn   const Atom* getId() const;
   * \brief Get the ID of a Variable
   */
  void setValue(Literal* l){_value =l;}
  /**
   * \fn  void setValue(Literal* l)
   * \brief Set the value of a Variable
   */
  ~Variable(){delete _value; delete _identificateur;}
  /**
   *    \fn ~Variable();
   * \brief Destructor
   */
  QString toString() const;
};

#endif // VARIABLE_H
