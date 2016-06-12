#ifndef _CARETAKER_H
#define _CARETAKER_H

/*! \file CareTaker.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for CareTaker class declaration
*/

#include "Pile.h"
#include <QStack>

/*! \class CareTaker
   * \brief CareTaker class declaration. Manages all the Memento.
   *
   * CareTaker object is responsible for restoring object state from Memento.
   * Implements Undo/Redo functions
   *
   * Singleton Design Pattern is used.
   */

class CareTaker{ //Se charge de faire la liste des sauvegardes (liste de Memento)
    static CareTaker* _instance;
    int _indexPile;
    QStack<Pile::Memento*> _savedPiles;

    CareTaker():_indexPile(0){}
    CareTaker(const CareTaker& ct);
    CareTaker& operator=(const CareTaker& ct);
    ~CareTaker();
public:

    static CareTaker* getInstance();
    /*! \fn static CareTaker* getInstance()
     * \brief Get CareTaker instance. if it does not exist, create it.
     */
    static void freeInstance();
    /*! \fn static void freeInstance();
     * \brief Free CareTaker instance if it exists.
     */
    void addMemento(Pile::Memento* m);
    /*! \fn void addMemento(Pile::Memento* m);
     *  \brief Add a Memento to the Memento's Stack
     * \param m Memento pointer which contains the Stack snapshot to save.
     */

    Pile::Memento* getMementoUndo();
    /*! \fn Pile::Memento* getMementoUndo();
     *  \brief Get the previous Memento that precedes the actual Stack State (Undo action)
     * \return Previous Memento
     */
    Pile::Memento* getMementoRedo();
    /*! \fn Pile::Memento* getMementoRedo();
     *  \brief Get the previous Memento that follows the actual Stack State (Redo action)
     * \return Next Memento
     */

    void setIndex(unsigned int i){_indexPile =i;}
    /*! \fn  void setIndex(unsigned int i)
     *  \brief Set the index that determines the current state in Memento' Stack
     */
    int getIndex(){return _indexPile;}
    /*! \fn  int getIndex()
     *  \brief Get the current index that determines the current state in Memento' Stack
     */

};
#endif
