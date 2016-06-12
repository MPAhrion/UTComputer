#ifndef SETTINGS_H
#define SETTINGS_H
/*! \file Settings.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for UI Settings Edition.
*/
#include <QDialog>

namespace Ui {
class Settings;
}

/*! \class Settings
   * \brief Settings Edition User Interface
   */
class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
private slots:
    void on_bOk_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
