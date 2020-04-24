#include "ajouterf.h"
#include "ui_ajouterf.h"

ajouterf::ajouterf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterf)
{
    ui->setupUi(this);
}

ajouterf::~ajouterf()
{
    delete ui;
}

void ajouterf::on_buttonBox_accepted()
{
    close();
}
