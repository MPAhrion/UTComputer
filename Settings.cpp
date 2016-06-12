#include "Settings.h"
#include "Calculatrice.h"
#include "mainwindow.h"
#include "ui_Settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->bOk, SIGNAL(clicked()), this, SLOT(on_bOk_clicked()));
    ui->showElementsSpinBox->setValue(Calculatrice::getInstance().getNbAffichage());
}

void Settings::on_bOk_clicked(){
    Calculatrice::getInstance().setNbAffichage(ui->showElementsSpinBox->value());
    MainWindow* w = dynamic_cast<MainWindow *>(this->parent());
    w->displayPile();
    this->close();
}

Settings::~Settings()
{
    delete ui;
}
