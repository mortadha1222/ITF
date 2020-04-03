#include "ajout.h"
#include "ui_ajout.h"

ajout::ajout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajout)
{
    ui->setupUi(this);
}

ajout::~ajout()
{
    delete ui;
}
