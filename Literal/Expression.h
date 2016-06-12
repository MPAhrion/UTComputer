#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED
/*! \file Expression.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for Expression class declaration
*/
#include "Literal.h"


/*! \class Expression
   * \brief Expression class declaration. Represents a string that could be evaluated.
   *
   * An Expression literal is a Literal composed of Numeric, Atom, Complex, and operands between brackets.
   * Infix notation is used in an Expression. It can be evaluated with the operand EVAL.
   * Ex: '(3+2)*5' EVAL gives 3 2 + 5 * = 30.
   */
class Expression : public Literal{
    QString _expression;
  public:
      Expression(const QString& s);
      /**
       * \fn   Expression(const QString& s);
       * \param s QString to assign to the Expression
       * \brief Constructor
       */

      QString getExpressionSansGuillemets() const;
      /**
       * \fn   QString getExpressionSansGuillemets() const;
       * \return The Expression withou brackets
       * \brief Get the Expression without brackets
       */
      
      QString toString() const {return _expression;}
      Expression *clone() const;

      
      Expression* operator+(Literal* c) const;
      /**
       * \fn    Expression* operator+(Literal* c) const;
       * \param c Literal used for the addtition
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+"+"+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* operator-(Literal* c) const;
      /**
       * \fn    Expression* operator-(Literal* c) const;
       * \param c Literal used for the subtraction
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+"-"+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* operator*(Literal* c) const;
      /**
       * \fn    Expression* operator*(Literal* c) const;
       * \param c Literal used for the multiplication
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+"*"+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* operator/(Literal* c) const;
      /**
       * \fn    Expression* operator/(Literal* c) const;
       * \param c Literal used for the division
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+"/"+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* neg() const;
      /**
       * \fn    Expression* neg() const;
       * \brief Create a new expression by using this : "'NEG("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* mod(Literal *c) const;
      /**
       * \fn    Expression* mod(Literal *c) const;
       * \param c Literal used for the mod operation
       * \brief By using this, create a new expression : "MOD("+this->getExpressionSansGuillemets()+","+c->toString+")"
       * \return Expression pointer on the result
       */
      Expression* div(Literal* c) const;
      /**
       * \fn    Expression* div(Literal* c) const;
       * \param c Literal used for the div operation
       * \brief By using this, create a new expression : "'DIV("+this->getExpressionSansGuillemets()+","+c->toString+")'"
       * \return Expression pointer on the result
       */
      Expression* pow(Literal *c)const;
      /**
       * \fn    Expression* pow(Literal *c)const;
       * \param c Literal used for the pow operation
       * \brief By using this, create a new expression : "'POW("+this->getExpressionSansGuillemets()+","+c->toString+")'"
       * \return Expression pointer on the result
       */
      Expression* sqrt() const;
      /**
       * \fn    Expression* sqrt() const;
       * \brief Create a new expression by using this : "'SQRT("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* num() const;
      /**
       * \fn    Expression* num() const;
       * \brief Create a new expression by using this : "'NUM("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* den() const;
      /**
       * \fn    Expression* den() const;
       * \brief Create a new expression by using this : "'DEN("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* re() const;
      /**
       * \fn    Expression* re() const;
       * \brief Create a new expression by using this : "'RE("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* im() const;
      /**
       * \fn    Expression* im() const;
       * \brief Create a new expression by using this : "'IM("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* dollar(Literal *c) const;
      /**
       * \fn    Expression* dollar(Literal *c) const;
       * \param c Literal to turn into the imaginary part of a complex
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+"$"+c->toString+"'"
       * \return Expression pointer on the result
       */
      Expression* cos() const;
      /**
       * \fn    Expression* cos() const;
       * \brief Create a new expression by using this : "'COS("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* sin() const;
      /**
       * \fn    Expression* sin() const;
       * \brief Create a new expression by using this : "'SIN("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* tan() const;
      /**
       * \fn    Expression* tan() const;
       * \brief Create a new expression by using this : "'TAN("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* exp() const;
      /**
       * \fn    Expression* exp() const;
       * \brief Create a new expression by using this : "'EXP("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* log() const;
      /**
       * \fn    Expression* log() const;
       * \brief Create a new expression by using this : "'LOG("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* operator==(Literal* c) const;
      /**
       * \fn    Expression* operator==(Literal* c) const;
       * \param c Literal used for the logical operation '='
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+"="+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* operator!=(Literal* c)const;
      /**
       * \fn    Expression* operator!=(Literal* c) const;
       * \param c Literal used for the logical operation '!='
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+"!="+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* operator>(Literal* c) const;
      /**
       * \fn    Expression* operator>(Literal* c) const;
       * \param c Literal used for the logical operation '>'
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+">"+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* operator<(Literal* c)const;
      /**
       * \fn    Expression* operator<(Literal* c) const;
       * \param c Literal used for the logical operation '<'
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+"<"+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* operator<=(Literal* c) const;
      /**
       * \fn    Expression* operator<=(Literal* c) const;
       * \param c Literal used for the logical operation '<='
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+"<="+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* operator>=(Literal* c) const;
      /**
       * \fn    Expression* operator>=(Literal* c) const;
       * \param c Literal used for the logical operation '>='
       * \brief By using this, create a new expression : "'"+this->getExpressionSansGuillemets()+">="+c->toString+"'",adding parenthesis if it's necessary
       * \return Expression pointer on the result
       */
      Expression* AND(Literal* c) const;
      /**
       * \fn    Expression* AND(Literal* c) const;
       * \param c Literal used for the logical operation 'AND'
       * \brief By using this, create a new expression : "'AND("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* OR(Literal *c) const;
      /**
       * \fn    Expression* OR(Literal* c) const;
       * \param c Literal used for the logical operation 'OR'
       * \brief By using this, create a new expression : "'OR("+this->getExpressionSansGuillemets()+")'"
       * \return Expression pointer on the result
       */
      Expression* NOT() const;
      /**
       * \fn    Expression* NOT() const;
       * \brief Create a new expression by using this : "NOT("+this->getExpressionSansGuillemets()+")"
       * \return Expression pointer on the result
       */

      Expression* evaluateVariables() const;
      /**
       * \fn   Expression* evaluateVariables() const;
       * \brief If there are variables identifiers in the expression, it creates a new expression by replacing variable identifiers by their value
       * \return Expression pointer in the result
       */
      bool isAnAtom()const;
      /**
       * \fn   bool isAnAtom()const;
       * \brief Check if the expression is contained into the manager as a variable or a program identifer
       * \return TRUE if it is and FALSE if it's not.
       */
      unsigned int getPrioriteMin() const;
      /**
       * \fn    unsigned int getPrioriteMin() const;
       * \brief Check the lowest priority of an expression thanks to the operators presents in it
       * \return unsigned int value which is the lowest priority
       */
      QString toPostfixe() const;
      /**
       * \fn    QString toPostfixe() const;
       * \brief transform an infix expression into a postfix expression but without the quotes. Eg : '3+5' is turned into : 3 5 +
       * \return Qstring value
       */
      Literal* evaluer() const;
      /**
       * \fn    Literal* evaluer() const;
       * \brief evaluate the expression if it's syntax is correct.
       * \return Literal pointer containing the result of the evaluation
       */
      ~Expression(){}
      /**
       * \brief Destructor
       */

};
    unsigned int getPrioriteMax(QChar c);
    bool estUneLiteral(const QString& s);

#endif // EXPRESSION_H_INCLUDED
