#ifndef PILE_H
#define PILE_H

/*! \file Pile.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Pile (Stack) class declaration
*/
//#include "./Literal/Literal.h"
#include "./Literal/Complex.h"
#include "./Literal/Integer.h"
#include "./Literal/Real.h"
#include "./Literal/Rational.h"
#include "./Literal/Expression.h"
#include <QStack>

using namespace std;

/*! \class Pile
   * \brief Pile (Stack) class declaration. Stores all the Literal
   *
   * Pile class stores and manipulates Literal.
   */

class Pile: public QStack<Literal*>{
    Pile* _pile;
public:
    Pile() : _pile(this){}
    /**
     * \brief Constructor
     */
    Pile* clone()const;
    /**
     * \fn   Pile* clone()const;
     * \brief Get a copy of a Pile (Stack).
     * \return Pile pointer to the new Pile.
     */


    /*! \class Memento
       * \brief Memento class declaration. Encapsulates a Pile state.
       *
       * Memento object captures a Pile (Stack) snapshot in order to save all Pile state for undo/redo
       */
 class Memento{ //Classe qui contiendra le "snapshot" de la pile.
            Pile* _state;
        public:
            Memento(const Pile* pileSave){_state = pileSave->clone();}
            /** \fn Memento(const Pile* pileSave)
             * \brief Constructor
             * \param pileSave Pointer of the Pile state to encapsulate.
             */

            Pile* getState() const {return _state;}
            /**
             * \fn   Pile* getState() const
             * \brief Get the Pile state encapsulated in a Memento
             * \return Pile pointer of the Pile state contained in the Memento.
             */
    };
    Memento* saveStackInMemento();
    /**
     * \fn   Memento* saveStackInMemento();
     * \brief Save the current state in a Memento, for Undo/Redo functions.
     * \return Memento pointer to the Pile "snapshot"
     */
    void restoreStackFromMemento(const Memento* m);
    /**
     * \fn   void restoreStackFromMemento(const Memento* m);
     * \brief Get the state encapsulated in the Memento, for Undo/Redo functions.
     * \param m Memento pointer to a Pile state.
     */
    Pile* getPile()const {return _pile;}
    /**
     * \fn    Pile* getPile()const
     * \brief Get the current Pile (Stack) state.
     * \return Pile pointer to the current Pile state.
     */

};


#endif // PILE_H
