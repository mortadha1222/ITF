#include "ajoutervehicule.h"
#include "ui_ajoutervehicule.h"

ajoutervehicule::ajoutervehicule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutervehicule)
{
    ui->setupUi(this);
}

ajoutervehicule::~ajoutervehicule()
{
    delete ui;
}
