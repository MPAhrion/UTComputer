#ifndef VARIABLES_H
#define VARIABLES_H
/*! \file Variables.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for UI Variables Edition.
*/
#include <QDialog>
#include <QListWidget>
#include <QMessageBox>

namespace Ui {
class Variables;
class Addvariables;
class EditVariables;
}

/*! \class Variables
   * \brief Variables Edition User Interface
   */
class Variables : public QDialog{
    Q_OBJECT

public:
    explicit Variables(QWidget *parent = 0);
    ~Variables();

private:
    Ui::Variables *ui;

private slots:
    void on_bAdd_clicked();
    void itemDoubleClicked(QListWidgetItem* item);
    void displayVariables();
};


class EditVariables : public QDialog{
    Q_OBJECT

public:
    explicit EditVariables(QStringList att, QWidget *parent = 0);
    ~EditVariables();

private:
    Ui::EditVariables *ui;

private slots:
    void on_bDelete_clicked();
    void on_bOK_clicked();
};

class Addvariables : public QDialog{
    Q_OBJECT

public:
    explicit Addvariables(QWidget *parent = 0);
    ~Addvariables();

private:
    Ui::Addvariables *ui;
private slots:
    void on_bCancel_clicked();
    void on_bOK_clicked();
};
#endif // VARIABLES_H
