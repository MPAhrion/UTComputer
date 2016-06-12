#ifndef _CALCULATRICE_H
#define _CALCULATRICE_H
/*! \file Calculatrice.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Calculatrice class declaration
*/
#include "Pile.h"
#include "CareTaker.h"
#include "Manager.h"
#include "factory.h"
#include <QString>
#include <QVector>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

using namespace std;


/*! \class Calculatrice
   * \brief Calculatrice class declaration
   *
   * Calculatrice allows to process computing, and manages all the entities such as the Stack, the CareTaker (undo/redo) and the Variable Manager.
   *
   * Singleton Design Pattern is used
    */
class Calculatrice {
private:
  static Calculatrice* _instance;
  Pile* _pile;
  CareTaker* _care;
  Manager* _manager;
  QVector<Literal*> _lastargs;
  unsigned int _nbAffichage;
  QString _lastop;
  Calculatrice():_pile(new Pile()),_care(CareTaker::getInstance()),_manager(Manager::getInstance()),_lastargs(),_nbAffichage(9), _lastop(){}
  Calculatrice(const Calculatrice& c);
  Calculatrice& operator=(const Calculatrice& c);
  ~Calculatrice();

public:
  static Calculatrice& getInstance();
  /*! \fn static Calculatrice& getInstance()
   * \brief Get Calculatrice instance. if it does not exist, create it.
   */
  static void freeInstance();
  /*! \fn static void freeInstance();
   * \brief Free Calculatrice instance if it exists.
   */
  unsigned int getNbAffichage()const{return _nbAffichage;}
  /*! \fn unsigned int getNbAffichage();
   * \brief Get the number of elements to display in the MainWindow
   */
  void setNbAffichage(unsigned int n){_nbAffichage=n;}
  /*! \fn void setNbAffichage(unsigned int n);
   * \param n unsigned int
   * \brief Set the number of elements to display in the MainWindow
   */
  QString getLastop()const{return _lastop;}
  /*! \fn QString getLastop()const;
   * \brief Get the last operator used by the user.
   */
  void setLastop(const QString& s){_lastop=s;}
  /*! \fn  void setLastop(const QString& s);
   * \brief Set the last operator used by the user.
   */
  QVector<Literal*> getLastargs() const {return _lastargs;}
  /*! \fn QVector<Literal*> getLastargs() const;
   * \brief Get the lasts operands used by the user.
   * \return QVector containing all the Literal from the previus calculation.
   */
  void addArg(Literal* c){_lastargs<<c->clone();}
  /*! \fn void addArg(Literal* c)
   * \brief Add a Literal into Lastarg vector.
   */
  void clearArgs();
  /*! \fn void void clearArgs();
   * \brief Clear the arguments into Lastargs vector.
   */
  Pile* getPile() const{return _pile;}
  /*! \fn Pile* getPile() const;
   * \brief Get the current Pile.
   */
  void setPile(Pile* p){_pile = p;}
  /*! \fn void setPile(Pile* p)
   * \brief Set Pile value.
   */
  CareTaker* getCareTaker() const{return _care;}
  /*! \fn CareTaker* getCareTaker() const
   * \brief Get the CareTaker instance.
   */
  Manager* getManager() const{return _manager;}
  /*! \fn Manager* getManager() const
   * \brief Get the Manager instance.
   */

  void PLUS();
  /*! \fn void PLUS();
   * \brief Calculator's Addition operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void MOINS();
  /*! \fn void MOINS();
   * \brief Calculator's Subtraction operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void MULT();
  /*! \fn void MULT();
   * \brief Calculator's Multiplication operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types.If the operation can't be established, return a message error.
   */
  void Div();
  /*! \fn void Div();
   * \brief Calculator's Division operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void MOD();
  /*! \fn void MOD();
   * \brief Calculator's Modulo operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void DIV();
  /*! \fn void DIV();
   * \brief Calculator's Euclidian Division operation.
   *
   *  When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void DOLLAR();
  /*! \fn void DOLLAR();
   * \brief Complex Creation.
   *
   * this function determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void DEN();
  /*! \fn void DEN();
   * \brief Get Denominator operation.
   *
   *  When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void DROP();
  /*! \fn void DROP();
   * \brief DROP Stack operation.
   *
   * Remove the Literal at the top of the Pile. If the operation can't be established, return a message error.
   */
  void DUP();
  /*! \fn void DUP();
   * \brief DUP Stack operation.
   *
   * Duplicate the Literal at the top of the Pile. If the operation can't be established, return a message error.
   */
  void SWAP();
  /*! \fn void SWAP();
   * \brief SWAP Stack operation.
   *
   * Swap the 2 Literal at the top of the Pile. If the operation can't be established, return a message error.
   */
  void NEG();
  /*! \fn void NEG();
   * \brief Calculator's NEG operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void NUM();
  /*! \fn void NUM();
   * \brief Get Numerator operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void RE();
  /*! \fn void RE();
   * \brief Get Real-Part operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void IM();
  /*! \fn void IM();
   * \brief Get Imaginary-Part operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void POW();
  /*! \fn void POW();
   * \brief Calculator's Power operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void SQRT();
  /*! \fn void SQRT();
   * \brief Calculator's Square Root operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void COS();
  /*! \fn void COS();
   * \brief Calculator's cosinus operation.
   *
   *  When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void SIN();
  /*! \fn void SIN();
   * \brief Calculator's sinus operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void TAN();
  /*! \fn void TAN();
   * \brief Calculator's tangente operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void EXP();
  /*! \fn void EXP();
   * \brief Calculator's Exponential operation.
   *
   *  When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void LOG();
  /*! \fn void LOG();
   * \brief Calculator's Logarithm operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void EQUALITY();
  /*! \fn void EQUALITY();
   * \brief Calculator's == operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void INEQUALITY();
  /*! \fn void INEQUALITY();
   * \brief Calculator's != operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void GT();
  /*! \fn void GT();
   * \brief Calculator's > operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void LT();
  /*! \fn void LT();
   * \brief Calculator's < operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void LET();
  /*! \fn void LET();
   * \brief Calculator's <= operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void GET();
  /*! \fn void GET();
   * \brief Calculator's >= operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void AND();
  /*! \fn void AND();
   * \brief Calculator's & operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void NOT();
  /*! \fn void NOT();
   * \brief Calculator's ~ operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void OR();
  /*! \fn void OR();
   * \brief Calculator's | operation.
   *
   * When the user asked for this operation, this function
   * determines which function has to be called, depending of Literal types. If the operation can't be established, return a message error.
   */
  void STO();
  /*! \fn void STO();
   * \brief Calculator's STO operation. Save a value into an Atom in order to make a Variable.
   */
  void FORGET();
  /*! \fn void FORGET();
   * \brief Calculator's FORGET operation. Forget a Variable.
   */
  void IFT();
  /*! \fn void IFT();
   * \brief Calculator's IFT operation.
   *
   * Pop 2 Literal. If the first is True (boolean test), the second is evaluated with EVAL.
   */
  void EVAL();
  /*! \fn void EVAL();
   * \brief Calculator's EVAL operation.
   *
   * Evaluate an Expression.
   */
  void LASTARGS();
  /*! \fn void LASTARGS();
   * \brief Calculator's LASTARGS operation.
   */
};

#endif
