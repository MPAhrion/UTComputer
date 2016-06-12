#ifndef MAINWINDOW_H
#define MAINWINDOW_H


/*! \file mainWindow.h
  * \author Valentin Montupet, Alexis Dutot
  * \brief Header file for UI MainWindow.
*/
#include <QMainWindow>
#include <QApplication>
#include "Calculatrice.h"
#include "Pile.h"
#include <QSettings>
#include "CareTaker.h"
#include "Manager.h"
#include "factory.h"
#include "Settings.h"
#include "Variables.h"

namespace Ui {
class MainWindow;
}
/*! \class MainWindow
   * \brief MainWindow User Interface
   */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ConnectSlots();
    /*! \fn  void ConnectSlots();
     * \brief Connect all slots at the launch.
     */
    void memorisePileUndo();
    /*! \fn  void memorisePileUndo();
     * \brief Memorise Pile state each time it's modified for Undo/Redo functions.
     */
    void displayPile();
    /*! \fn  void displayPile();
     * \brief Display all the Literal stores into the Pile in main window.
     */

    void saveContext();
    /*! \fn  void saveContext();
     * \brief Each time an action is done or the application is closed, save Application's context in a INI file in order to restore it later.
     */
    void restoreContext();
    /*! \fn  void restoreContext();
     * \brief Restore context previously saved from the INI File
     */
private:
    Ui::MainWindow *ui;
    QSettings settings;

private slots:
  void actionUndo();
  void actionRedo();
  void bDROPPressed();
  void bDUPPressed();
  void bSWAPPressed();
  void b1Pressed();
  void b2Pressed();
  void b3Pressed();
  void b4Pressed();
  void b5Pressed();
  void b6Pressed();
  void b7Pressed();
  void b8Pressed();
  void b9Pressed();
  void b0Pressed();
  void bGuillemetsPressed();
  void bPointPressed();
  void bPlusPressed();
  void bMoinsPressed();
  void bDivPressed();
  void bMultPressed();
  void bPOWPressed();
  void bSQRTPressed();
  void bMODPressed();
  void bSINPressed();
  void bARCSINPressed();
  void bCOSPressed();
  void bARCCOSPressed();
  void bTANPressed();
  void bARCTANPressed();
  void bLNPressed();
  void bNEGPressed();
  void bErasePressed();
  void bSPACEPressed();
  void bENTERPressed();
  void bPOPressed();
  void bPFPressed();
  void bEXPPressed();
  void bNUMPressed();
  void bDENPressed();
  void bDIVPressed();
  void bREPressed();
  void bIMPressed();
  void bDollarPressed();
  void bSTOPressed();
  void bFORGETPressed();
  void bIFTPressed();
  void bEVALPressed();
  void bEqPressed();
  void bDiffPressed();
  void bInfEqPressed();
  void bSupEqPressed();
  void bInfPressed();
  void bSupPressed();
  void bNOTPressed();
  void bANDPressed();
  void bORPressed();
  void bLASTOPPressed();
  void bCLEARPressed();
  void bSLASTARGSPressed();
  void expressireturnPressed();
  void ExitTriggered();
  void showKeyboardTriggered();
  void SettingsTriggered();
  void VariablesTriggered();
  void ProgramsTriggered();
};

#endif // MAINWINDOW_H
