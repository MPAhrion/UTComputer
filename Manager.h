#ifndef MANAGER_H
#define MANAGER_H

/*! \file Manager.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Manager class declaration
*/
#include "variable.h"
#include "Literal/Atom.h"
#include <QVector>


/*! \class Manager
   * \brief Manager class declaration
   *
   * Manager stores all the Variables and Programs defines by the user.
   *
   * Singleton Design Pattern is used
    */
class Manager{
    QList<Variable*> _listVar;
    //QList<Programmes*> _listProg;
    static Manager* _instance;
    Manager(){}
    Manager(const Manager& m);
    ~Manager(){}
    Manager& operator=(const Manager& m);
public:
    static Manager* getInstance();
    /*! \fn static Manager* getInstance();
     * \brief Get Manager instance. if it does not exist, create it.
     */
    static void freeInstance();
    /*! \fn static void freeInstance();
     * \brief Free Manager instance if it exists.
     */
    void addVariable(Variable* v);
    /*! \fn void addVariable(Variable* v);
     * \brief Add a Variable
     * \param v Variable to add.
     */
    void removeVariable(const QString &s);
    /*! \fn void removeVariable(const QString &s);
     * \brief Remove a Variable
     * \param s QString which represents the Variable's name to remove
     */
    const QList<Variable*>& getList()const{ return _listVar;}
    /*! \fn const QList<Variable*>& getList()const
     * \brief Get the Variable list
     */
};

#endif // MANAGER_H
