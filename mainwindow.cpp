#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

void MainWindow::ConnectSlots(){
    connect(ui->b0, SIGNAL(clicked()), this, SLOT(b0Pressed()));
    connect(ui->b1, SIGNAL(clicked()), this, SLOT(b1Pressed()));
    connect(ui->b2, SIGNAL(clicked()), this, SLOT(b2Pressed()));
    connect(ui->b3, SIGNAL(clicked()), this, SLOT(b3Pressed()));
    connect(ui->b4, SIGNAL(clicked()), this, SLOT(b4Pressed()));
    connect(ui->b5, SIGNAL(clicked()), this, SLOT(b5Pressed()));
    connect(ui->b6, SIGNAL(clicked()), this, SLOT(b6Pressed()));
    connect(ui->b7, SIGNAL(clicked()), this, SLOT(b7Pressed()));
    connect(ui->b8, SIGNAL(clicked()), this, SLOT(b8Pressed()));
    connect(ui->b9, SIGNAL(clicked()), this, SLOT(b9Pressed()));

    connect(ui->bMult, SIGNAL(clicked()), this, SLOT(bMultPressed()));
    connect(ui->bPlus, SIGNAL(clicked()), this, SLOT(bPlusPressed()));
    connect(ui->bMoins, SIGNAL(clicked()), this, SLOT(bMoinsPressed()));
    connect(ui->bDiv, SIGNAL(clicked()), this, SLOT(bDivPressed()));
    connect(ui->bMOD, SIGNAL(clicked()), this, SLOT(bMODPressed()));
    connect(ui->bPoint, SIGNAL(clicked()), this, SLOT(bPointPressed()));
    connect(ui->bPO, SIGNAL(clicked()), this, SLOT(bPOPressed()));
    connect(ui->bPF, SIGNAL(clicked()), this, SLOT(bPFPressed()));
    connect(ui->bSPACE, SIGNAL(clicked()), this, SLOT(bSPACEPressed()));
    connect(ui->bENTER, SIGNAL(clicked()), this, SLOT(bENTERPressed()));
    connect(ui->bDIV, SIGNAL(clicked()), this, SLOT(bDIVPressed()));
    connect(ui->bDollar, SIGNAL(clicked()), this, SLOT(bDollarPressed()));

    connect(ui->bGuillemets, SIGNAL(clicked()), this, SLOT(bGuillemetsPressed()));
    connect(ui->bPOW, SIGNAL(clicked()), this, SLOT(bPOWPressed()));
    connect(ui->bSQRT, SIGNAL(clicked()), this, SLOT(bSQRTPressed()));
    connect(ui->bSIN, SIGNAL(clicked()), this, SLOT(bSINPressed()));
    connect(ui->bCOS, SIGNAL(clicked()), this, SLOT(bCOSPressed()));
    connect(ui->bTAN, SIGNAL(clicked()), this, SLOT(bTANPressed()));
    connect(ui->bARCSIN, SIGNAL(clicked()), this, SLOT(bARCSINPressed()));
    connect(ui->bARCCOS, SIGNAL(clicked()), this, SLOT(bARCCOSPressed()));
    connect(ui->bARCTAN, SIGNAL(clicked()), this, SLOT(bARCTANPressed()));
    connect(ui->bEXP, SIGNAL(clicked()), this, SLOT(bEXPPressed()));
    connect(ui->bNUM, SIGNAL(clicked()), this, SLOT(bNUMPressed()));
    connect(ui->bDEN, SIGNAL(clicked()), this, SLOT(bDENPressed()));
    connect(ui->bRE, SIGNAL(clicked()), this, SLOT(bREPressed()));
    connect(ui->bIM, SIGNAL(clicked()), this, SLOT(bIMPressed()));
    connect(ui->bLN, SIGNAL(clicked()), this, SLOT(bLNPressed()));

    connect(ui->bEq, SIGNAL(clicked()), this, SLOT(bEqPressed()));
    connect(ui->bDiff, SIGNAL(clicked()), this, SLOT(bDiffPressed()));
    connect(ui->bInfEq, SIGNAL(clicked()), this, SLOT(bInfEqPressed()));
    connect(ui->bSupEq, SIGNAL(clicked()), this, SLOT(bSupEqPressed()));
    connect(ui->bSup, SIGNAL(clicked()), this, SLOT(bSupPressed()));
    connect(ui->bInf, SIGNAL(clicked()), this, SLOT(bInfPressed()));
    connect(ui->bAND, SIGNAL(clicked()), this, SLOT(bANDPressed()));
    connect(ui->bOR, SIGNAL(clicked()), this, SLOT(bORPressed()));
    connect(ui->bNOT, SIGNAL(clicked()), this, SLOT(bNOTPressed()));

    connect(ui->bErase, SIGNAL(clicked()), this, SLOT(bErasePressed()));
    connect(ui->bCLEAR, SIGNAL(clicked()), this, SLOT(bCLEARPressed()));
    connect(ui->bDROP, SIGNAL(clicked()), this, SLOT(bDROPPressed()));
    connect(ui->bDUP, SIGNAL(clicked()), this, SLOT(bDUPPressed()));
    connect(ui->bSWAP, SIGNAL(clicked()), this, SLOT(bSWAPPressed()));
    connect(ui->bLASTOP, SIGNAL(clicked()), this, SLOT(bLASTOPPressed()));
    connect(ui->bNEG, SIGNAL(clicked()), this, SLOT(bNEGPressed()));
    connect(ui->bSTO, SIGNAL(clicked()), this, SLOT(bSTOPressed()));
    connect(ui->bFORGET, SIGNAL(clicked()), this, SLOT(bFORGETPressed()));
    connect(ui->bLASTARGS,SIGNAL(clicked()), this, SLOT(bSLASTARGSPressed()));
    connect(ui->bIFT,SIGNAL(clicked()), this, SLOT(bIFTPressed()));
    connect(ui->bUNDO, SIGNAL(clicked()), this, SLOT(actionUndo()));
    connect(ui->bREDO, SIGNAL(clicked()), this, SLOT(actionRedo()));
    connect(ui->bEval, SIGNAL(clicked()), this, SLOT(bEVALPressed()));
    connect(ui->expression, SIGNAL(returnPressed()),this,SLOT(expressireturnPressed()));
    connect(ui->actionExit, SIGNAL(triggered()),this,SLOT(ExitTriggered()));
    connect(ui->actionShow_Keyboard, SIGNAL(triggered()),this, SLOT(showKeyboardTriggered()));
    connect(ui->actionParameters, SIGNAL(triggered()),this, SLOT(SettingsTriggered()));
    connect(ui->actionVariables, SIGNAL(triggered()),this, SLOT(VariablesTriggered()));
    connect(ui->actionPrograms, SIGNAL(triggered()),this, SLOT(ProgramsTriggered()));
    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(actionUndo()));
    connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(actionRedo()));

}


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow),settings("./settings.ini", QSettings::IniFormat){
    ui->setupUi(this);
    MainWindow::ConnectSlots();
    MainWindow::restoreContext();
    MainWindow::memorisePileUndo();
    MainWindow::displayPile();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::displayPile(){
    ui->PileAffichage->clear();
    unsigned int displayMax=Calculatrice::getInstance().getNbAffichage();
    unsigned int currentDisplay=displayMax;
       QStack<Literal*>::const_iterator it;
       //Affiche la pile avec sommet vers le bas
       it=Calculatrice::getInstance().getPile()->end();
       while ((it != Calculatrice::getInstance().getPile()->begin()) && currentDisplay>0) {
           --it;
           ui->PileAffichage->addItem(QString(QString::number(displayMax-currentDisplay+1) + " :  "+ (*it)->toString()));
           ui->PileAffichage->addItem(QString("------------------------------------------"));

           --currentDisplay;
       }
}

bool isNotAnOperator(const QString& s)
{
    if(s=="DUP" || s=="MOD"|| s=="NEG" || s=="POW"|| s=="REDO"|| s=="UNDO" || s=="SQRT"|| s=="NUM" || s=="SWAP" || s=="DROP" || s=="LASTOP" || s=="FORGET" || s=="LASTARGS" || s=="DEN" || s=="RE" || s=="IM" || s=="AND" || s=="OR" || s=="NOT" || s=="EVAL" || s=="CLEAR" || s=="STO" || s=="SIN" ||s=="COS" || s=="TAN" || s=="LOG" || s=="EXP"|| s=="IFT" || s=="DIV")
        return false;
    else
        return true;
}

bool isALiteral(const QString& s){
    QRegExp regexInteger("^-?[0-9]+$");
    QRegExp regexReal("^-?[0-9]+\\.[0-9]+$");
    QRegExp regexAtom("^([a-zA-Z]+[0-9]*)+$");
    QRegExp regexExpression("^\'[^\'].*\'$");
    return (regexInteger.exactMatch(s) || regexReal.exactMatch(s) || (regexAtom.exactMatch(s) && isNotAnOperator(s)) || regexExpression.exactMatch(s));//(s.at(0)=='\'' && s.at(s.size()-1)=='\''));
}
/* -----------------------------------------------------------------------------------
----------------------------UNDO REDO FUNCTIONS --------------------------------------
-------------------------------------------------------------------------------------- */

void MainWindow::memorisePileUndo(){
    CareTaker* g=Calculatrice::getInstance().getCareTaker();
    g->addMemento(Calculatrice::getInstance().getPile()->saveStackInMemento());
}

void MainWindow::actionUndo(){
    try{
        CareTaker* g=Calculatrice::getInstance().getCareTaker();
        Calculatrice::getInstance().getPile()->restoreStackFromMemento(g->getMementoUndo());
        Pile* p=Calculatrice::getInstance().getPile()->getPile();
        Calculatrice::getInstance().setPile(p);
        ui->PileAffichage->clear();
        displayPile();
    }
    catch (QString& s){QMessageBox::warning(this, "Error", s);}
}

void MainWindow::actionRedo(){
    try{
        CareTaker* g=Calculatrice::getInstance().getCareTaker();
        Calculatrice::getInstance().getPile()->restoreStackFromMemento(g->getMementoRedo());
        Pile* p=Calculatrice::getInstance().getPile()->getPile();
        Calculatrice::getInstance().setPile(p);
        ui->PileAffichage->clear();
        displayPile();
    }
    catch (QString& s){QMessageBox::warning(this, "Error", s);}
}

/* -----------------------------------------------------------------------------------
----------------------------NUMERIC KEYBOARD BUTTONS ---------------------------------
-------------------------------------------------------------------------------------- */
void MainWindow::b0Pressed(){ui->expression->setText(ui->expression->text() + "0");}
void MainWindow::b1Pressed(){ui->expression->setText(ui->expression->text() + "1");}
void MainWindow::b2Pressed(){ui->expression->setText(ui->expression->text() + "2");}
void MainWindow::b3Pressed(){ ui->expression->setText(ui->expression->text() + "3");}
void MainWindow::b4Pressed(){ui->expression->setText(ui->expression->text() + "4");}
void MainWindow::b5Pressed(){ui->expression->setText(ui->expression->text() + "5");}
void MainWindow::b6Pressed(){ui->expression->setText(ui->expression->text() + "6");}
void MainWindow::b7Pressed(){ui->expression->setText(ui->expression->text() + "7");}
void MainWindow::b8Pressed(){ui->expression->setText(ui->expression->text() + "8");}
void MainWindow::b9Pressed(){ui->expression->setText(ui->expression->text() + "9");}
void MainWindow::bGuillemetsPressed(){ui->expression->setText(ui->expression->text() + "'");}
void MainWindow::bPlusPressed(){ui->expression->setText(ui->expression->text() + " +");expressireturnPressed();}
void MainWindow::bMoinsPressed(){ui->expression->setText(ui->expression->text() + " -");expressireturnPressed();}
void MainWindow::bMultPressed(){ui->expression->setText(ui->expression->text() + " *");expressireturnPressed();}
void MainWindow::bDivPressed(){ui->expression->setText(ui->expression->text() + " /");expressireturnPressed();}
void MainWindow::bPointPressed(){ui->expression->setText(ui->expression->text() + ".");}
void MainWindow::bPOPressed(){ui->expression->setText(ui->expression->text() + "(");}
void MainWindow::bPFPressed(){ui->expression->setText(ui->expression->text() + ")");}


/* ------------------------------------------------------------------------------------
----------------------------------FUNCTIONS BUTTONS -----------------------------------
--------------------------------------------------------------------------------------- */
void MainWindow::bPOWPressed(){ui->expression->setText(ui->expression->text() + "POW"); expressireturnPressed();}
void MainWindow::bSQRTPressed(){ui->expression->setText(ui->expression->text() + "SQRT"); expressireturnPressed();}
void MainWindow::bMODPressed(){ui->expression->setText(ui->expression->text() + " MOD");expressireturnPressed();}
void MainWindow::bSINPressed(){ui->expression->setText(ui->expression->text() + "SIN");expressireturnPressed();}
void MainWindow::bCOSPressed(){ui->expression->setText(ui->expression->text() + "COS");expressireturnPressed();}
void MainWindow::bTANPressed(){ui->expression->setText(ui->expression->text() + "TAN");expressireturnPressed();}
void MainWindow::bARCSINPressed(){ui->expression->setText(ui->expression->text() + "ARCSIN");}
void MainWindow::bARCCOSPressed(){ui->expression->setText(ui->expression->text() + "ARCCOS");}
void MainWindow::bARCTANPressed(){ui->expression->setText(ui->expression->text() + "ARCTAN");}
void MainWindow::bLNPressed(){ui->expression->setText(ui->expression->text() + "LOG");expressireturnPressed();}
void MainWindow::bEXPPressed(){ui->expression->setText(ui->expression->text() + "EXP");expressireturnPressed();}
void MainWindow::bNUMPressed(){ui->expression->setText(ui->expression->text() + " NUM");expressireturnPressed();}
void MainWindow::bDENPressed(){ui->expression->setText(ui->expression->text() + " DEN");expressireturnPressed();}
void MainWindow::bDIVPressed(){ui->expression->setText(ui->expression->text() + " DIV");expressireturnPressed();}
void MainWindow::bDollarPressed(){ui->expression->setText(ui->expression->text() + " $");expressireturnPressed();}
void MainWindow::bREPressed(){ui->expression->setText(ui->expression->text() + " RE");expressireturnPressed();}
void MainWindow::bIMPressed(){ui->expression->setText(ui->expression->text() + " IM");expressireturnPressed();}
/* ------------------------------------------------------------------------------------
----------------------------LOGICAL OPERATORS BUTTONS ---------------------------------
--------------------------------------------------------------------------------------- */
void MainWindow::bEqPressed(){ui->expression->setText(ui->expression->text() + " =");expressireturnPressed();}
void MainWindow::bDiffPressed(){ui->expression->setText(ui->expression->text() + " !=");expressireturnPressed();}
void MainWindow::bSupEqPressed(){ui->expression->setText(ui->expression->text() + " >=");expressireturnPressed();}
void MainWindow::bInfEqPressed(){ui->expression->setText(ui->expression->text() + " <=");expressireturnPressed();}
void MainWindow::bSupPressed(){ui->expression->setText(ui->expression->text() + " >");expressireturnPressed();}
void MainWindow::bInfPressed(){ui->expression->setText(ui->expression->text() + " <");expressireturnPressed();}
void MainWindow::bANDPressed(){ui->expression->setText(ui->expression->text() + " AND");expressireturnPressed();}
void MainWindow::bORPressed(){ui->expression->setText(ui->expression->text() + " OR");expressireturnPressed();}
void MainWindow::bNOTPressed(){ui->expression->setText(ui->expression->text() + " NOT");expressireturnPressed();}
/* ------------------------------------------------------------------------------------
----------------------------MISCELLANEOUS BUTTONS -------------------------------------
--------------------------------------------------------------------------------------- */
void MainWindow::bFORGETPressed(){ui->expression->setText(ui->expression->text() + " FORGET");expressireturnPressed();}
void MainWindow::bEVALPressed(){ ui->expression->setText(ui->expression->text() + " EVAL"); expressireturnPressed();}
void MainWindow::bIFTPressed(){ ui->expression->setText(ui->expression->text() + " IFT"); expressireturnPressed();}
void MainWindow::bSPACEPressed(){ ui->expression->setText(ui->expression->text() + " ");}
void MainWindow::bErasePressed(){QString t = ui->expression->text(); ui->expression->setText(t.left(t.length()-1));}
void MainWindow::bENTERPressed(){ expressireturnPressed();}
void MainWindow::bSTOPressed(){ui->expression->setText(ui->expression->text() + " STO");expressireturnPressed();}


/* -----------------------------------------------------------------------------------
----------------------------STACK OPERATORS BUTTONS ----------------------------------
-------------------------------------------------------------------------------------- */
void MainWindow::bCLEARPressed(){
    Calculatrice::getInstance().setLastop("CLEAR");
    Calculatrice::getInstance().getPile()->clear();
    saveContext();
    displayPile();
}
void MainWindow::bLASTOPPressed(){
    try{
        QString lo = Calculatrice::getInstance().getLastop();
        if (lo ==0)
            throw QString("You must have done at least one operation before.");
        else{
            ui->expression->setText(lo);
            expressireturnPressed();
        }
    }
    catch (QString& s){QMessageBox::warning(this, "Erreur", s);}
}

void MainWindow::bSLASTARGSPressed()
{
    ui->expression->setText(ui->expression->text() + " LASTARGS");
    expressireturnPressed();
}

void MainWindow::bDROPPressed(){
    try{
        Calculatrice::getInstance().setLastop("DROP");

        Calculatrice::getInstance().DROP();
        memorisePileUndo();
        saveContext();
        displayPile();
    }
    catch (QString& s){QMessageBox::warning(this, "Erreur", s);}
}

void MainWindow::bDUPPressed(){
    try{
        Calculatrice::getInstance().setLastop("DUP");

        Calculatrice::getInstance().DUP();
        memorisePileUndo();
        saveContext();
        displayPile();

    }
    catch (QString& s){QMessageBox::warning(this, "Erreur", s);}
}

void MainWindow::bSWAPPressed(){
    try{
        Calculatrice::getInstance().setLastop("SWAP");
        Calculatrice::getInstance().SWAP();
        memorisePileUndo();
        saveContext();
        displayPile();
    }
    catch (QString& s){QMessageBox::warning(this, "Erreur", s);}
}

void MainWindow::bNEGPressed(){
    try{
        Calculatrice::getInstance().setLastop("NEG");
        Calculatrice::getInstance().NEG();

        displayPile();
    }
    catch (QString& s){QMessageBox::warning(this, "Erreur", s);}

}


/* -----------------------------------------------------------------------------------
------------------------------------ENTER PRESSED ------------------------------------
-------------------------------------------------------------------------------------- */
void MainWindow::expressireturnPressed(){
  try{
    QString commande = ui->expression->text().toUpper();
    QStringList listeEsp= commande.split(" ",QString::SkipEmptyParts);
    QStringList liste;
    for (int j=0;j<listeEsp.size();j++)
    {
        if(listeEsp[j].at(0)=='\'' && listeEsp[j].at(listeEsp[j].size()-1)!='\'')
        {
            QString oldExpression;
            int z=j;
            while(z<listeEsp.size() && listeEsp[z].at(listeEsp[z].size()-1)!='\'')
            {
                oldExpression= oldExpression+listeEsp[z];
                z++;
            }
            if(z==listeEsp.size() && listeEsp[z-1].at(listeEsp[z-1].size()-1)!='\'')
                throw QString("ERROR : invalid command, expression has invalid syntax");
            oldExpression= oldExpression+listeEsp[z];
            j=z;
            liste<<oldExpression;
        }
        else
            liste<<listeEsp[j];
    }
    for (int i=0;i<liste.length();i++){
        if(isALiteral(liste[i])){
            Literal* lit=Factory::GetFactory()->CreerLiteral(liste[i]);
            if(lit!=NULL)
                Calculatrice::getInstance().getPile()->push(lit);
            else
                throw QString("Opérateur inexistant");
        }
        else if(liste[i]=="+"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().PLUS();
        }
        else if(liste[i]=="-"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().MOINS();
        }
        else if(liste[i]=="*"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().MULT();
        }
        else if(liste[i]=="/"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().Div();
        }
        else if(liste[i]=="$"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().DOLLAR();
        }
        else if(liste[i]=="POW"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().POW();
        }
        else if(liste[i]=="SQRT"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().SQRT();
        }
        else if(liste[i]=="COS"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().COS();
        }
        else if(liste[i]=="SIN"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().SIN();
        }
        else if(liste[i]=="TAN"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().TAN();
        }
        else if(liste[i]=="EXP"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().EXP();
        }
        else if(liste[i]=="LOG"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().LOG();
        }
        else if(liste[i]=="MOD"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().MOD();
        }
        else if(liste[i]=="DIV"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().DIV();
        }
        else if (liste[i]=="DROP"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().DROP();
        }
        else if (liste[i]=="DUP"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().DUP();
        }
        else if (liste[i]=="SWAP"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().SWAP();
        }
        else if(liste[i]=="CLEAR"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().getPile()->clear();
        }
        else if(liste[i]=="STO"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().STO();
        }
        else if(liste[i]=="FORGET"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().FORGET();
        }
        else if(liste[i]=="LASTARGS")
        {
            Calculatrice::getInstance().LASTARGS();
        }
        else if(liste[i]=="LASTOP"){
            bLASTOPPressed();
        }
        else if(liste[i]=="NEG"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().NEG();
        }
        else if(liste[i]=="IFT"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().IFT();
        }
        else if(liste[i]=="DEN"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().DEN();
        }
        else if(liste[i]=="NUM"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().NUM();
        }
        else if(liste[i]=="RE"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().RE();
        }
        else if(liste[i]=="IM"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().IM();
        }
        else if(liste[i]=="="){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().EQUALITY();
        }
        else if(liste[i]=="!="){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().INEQUALITY();
        }
        else if(liste[i]==">="){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().GET();
        }
        else if(liste[i]=="<="){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().LET();
        }
        else if(liste[i]=="<"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().LT();
        }
        else if(liste[i]==">"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().GT();
        }
        else if(liste[i]=="AND"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().AND();
        }
        else if(liste[i]=="OR"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().OR();
        }
        else if(liste[i]=="NOT"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().NOT();
        }
        else if(liste[i]=="EVAL"){
            Calculatrice::getInstance().setLastop(liste[i]);
            Calculatrice::getInstance().EVAL();
        }
        else if (liste[i]=="UNDO")
        {
            Calculatrice::getInstance().setLastop(liste[i]);
            actionUndo();
        }
        else if (liste[i]=="REDO")
        {
            Calculatrice::getInstance().setLastop(liste[i]);
            actionRedo();
        }
        else{ //If we don't find what is it, the string is transformed into an Expression.
            throw QString("Opérateur inexistant");
        }
    }
  }
  catch (QString& s){
      QMessageBox::warning(this, "Error", s);
  }
  saveContext();
  memorisePileUndo();
  displayPile();
  ui->expression->clear();
}


/* -----------------------------------------------------------------------------------
------------------------------MENU ---------------------------------------------------
-------------------------------------------------------------------------------------- */
void MainWindow::showKeyboardTriggered(){
    if(ui->actionShow_Keyboard->isChecked())
    {
        this->setMinimumWidth(550);
        this->setMaximumWidth(550);
        this->setMinimumHeight(650);
        this->setMaximumHeight(650);
    }
    else
    {
        this->setMinimumWidth(230);
        this->setMaximumWidth(230);
        this->setMinimumHeight(456);
        this->setMaximumHeight(456);
    }
    saveContext();
    /**
     * \brief    Intéraction avec le bouton Clavier Visuel du menu
     * \details  Afficher/Masquer le clavier
     */
}

void MainWindow::SettingsTriggered(){
    Settings p(this);
    p.exec();
    saveContext();
}

void MainWindow::VariablesTriggered(){
    Variables p(this);
    p.exec();
}
void MainWindow::ExitTriggered(){
    saveContext();
    this->close();
}

void MainWindow::ProgramsTriggered(){
}


/* -----------------------------------------------------------------------------------
-------------------------SAVE AND RESTORE CALCULATOR STATE ---------------------------
-------------------------------------------------------------------------------------- */
void MainWindow::saveContext(){
    QString s;
    settings.remove("Pile");
    settings.beginGroup("Pile");

    for(int i=0;i< Calculatrice::getInstance().getPile()->size() ;i++)
        settings.setValue(s.setNum(i), Calculatrice::getInstance().getPile()->at(i)->toString());
    settings.endGroup();

    settings.remove("Variables");
    settings.beginGroup("Variables");
    for(int i=0;i< Manager::getInstance()->getList().size() ;i++)
        settings.setValue(Manager::getInstance()->getList().at(i)->getId()->toString(), Manager::getInstance()->getList().at(i)->getValue()->toString());
    settings.endGroup();

    settings.setValue("Settings/showKeyboard", ui->actionShow_Keyboard->isChecked());
    settings.setValue("Settings/nbAffichage", Calculatrice::getInstance().getNbAffichage());
}

void MainWindow::restoreContext(){
    QRegExp regexRational("^-?[0-9]+\\/[0-9]+$");
    //QRegExp regexComplex("^-?[0-9]+\\$[0-9]+$");
    QRegExp regexComplex("^-?.+\\$.+$");
    QString line,s;
    settings.beginGroup("Pile");
    foreach(const QString &key, settings.childKeys()){
        line = settings.value(key).toString();
        if (regexRational.exactMatch(line)){ //If it's a Rational
            QStringList rational= line.split("/",QString::SkipEmptyParts);
            for (int i=0 ; i < 2 ; i++)
                Calculatrice::getInstance().getPile()->push(Factory::GetFactory()->CreerLiteral(rational[i]));
            Calculatrice::getInstance().Div();
        }
        else if (regexComplex.exactMatch(line)){ //If it's a Complex
            QStringList complex= line.split("$",QString::SkipEmptyParts);
            for (int i=0 ; i < 2 ; i++){
                if (regexRational.exactMatch(complex[i])){ //If a part of a complex is a Rational
                    QStringList rational= complex[i].split("/",QString::SkipEmptyParts);
                    for (int i=0 ; i < 2 ; i++)
                        Calculatrice::getInstance().getPile()->push(Factory::GetFactory()->CreerLiteral(rational[i]));
                    Calculatrice::getInstance().Div();
                }
                else
                     Calculatrice::getInstance().getPile()->push(Factory::GetFactory()->CreerLiteral(complex[i]));
            }
            Calculatrice::getInstance().DOLLAR();
        }
        else // so it's a literal numeric or an expression
            Calculatrice::getInstance().getPile()->push(Factory::GetFactory()->CreerLiteral(line));
    }
    settings.endGroup();

    if (settings.contains("Settings/nbAffichage")){
            Calculatrice::getInstance().setNbAffichage(settings.value("Settings/nbAffichage").toInt());
            ui->actionShow_Keyboard->setChecked(settings.value("Settings/showKeyboard").toBool());
            showKeyboardTriggered();
    }

    settings.beginGroup("Variables");
    foreach(const QString &key, settings.childKeys()){
        Calculatrice::getInstance().getPile()->push(Factory::GetFactory()->CreerLiteral(settings.value(key).toString()));
            Calculatrice::getInstance().getPile()->push(Factory::GetFactory()->CreerLiteral(key));
            Calculatrice::getInstance().STO();
    }
    settings.endGroup();
}
