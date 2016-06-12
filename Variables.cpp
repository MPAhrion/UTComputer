#include "Variables.h"
#include "Manager.h"
#include "Calculatrice.h"
#include "ui_Variables.h"
#include "ui_Editvariables.h"
#include "ui_addvariables.h"

Variables::Variables(QWidget *parent) :QDialog(parent),ui(new Ui::Variables){   
    ui->setupUi(this);
    connect(ui->bAdd, SIGNAL(triggered()), this, SLOT(on_bAdd_clicked()));
    connect(ui->listVariables,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemDoubleClicked(QListWidgetItem*)));
    displayVariables();
}

Variables::~Variables(){
    delete ui;
}


void Variables::on_bAdd_clicked(){
   Addvariables d;
   d.exec();
   displayVariables();
}


void Variables::itemDoubleClicked(QListWidgetItem* item){
    QString t = item->text();
    QStringList attributs = t.split(" ",QString::SkipEmptyParts);
    EditVariables d(attributs);
    d.exec();
    displayVariables();
}

void Variables::displayVariables(){
    ui->listVariables->clear();
    for(int i=0;i<Calculatrice::getInstance().getManager()->getList().size();i++)
        ui->listVariables->addItem(Calculatrice::getInstance().getManager()->getList().at(i)->toString());
}

EditVariables::EditVariables(QStringList attributs, QWidget *parent) :QDialog(parent),ui(new Ui::EditVariables){
    ui->setupUi(this);
    ui->lName->setText(attributs[0]);
    ui->lValue->setText(attributs[1]);
    connect(ui->bOK, SIGNAL(triggered()), this, SLOT(on_bOK_clicked()));
    connect(ui->bDelete, SIGNAL(triggered()), this, SLOT(on_bDelete_clicked()));
}

EditVariables::~EditVariables(){
    delete ui;
}

void EditVariables::on_bDelete_clicked(){
    Calculatrice::getInstance().getManager()->removeVariable(ui->lName->text());
    this->done(0);
}
void EditVariables::on_bOK_clicked(){
    this->done(0);
}


Addvariables::Addvariables(QWidget *parent) :QDialog(parent),ui(new Ui::Addvariables){
    ui->setupUi(this);
    connect(ui->bOK, SIGNAL(triggered()), this, SLOT(on_bOK_clicked()));
    connect(ui->bCancel, SIGNAL(triggered()), this, SLOT(on_bCancel_clicked()));
}

void Addvariables::on_bCancel_clicked(){
    this->done(0);
}

void Addvariables::on_bOK_clicked(){
    QString name = ui->tName->text();
     QString value = ui->tValue->text();
     Calculatrice::getInstance().getPile()->push(Factory::GetFactory()->CreerLiteral(value));
     Calculatrice::getInstance().getPile()->push(Factory::GetFactory()->CreerLiteral(name));
     Calculatrice::getInstance().STO();
     this->done(0);
}
Addvariables::~Addvariables(){
    delete ui;
}

