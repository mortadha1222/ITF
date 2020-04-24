#include "ajouterplante.h"
#include "ui_ajouterplante.h"

ajouterplante::ajouterplante(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterplante)
{
    ui->setupUi(this);
}

ajouterplante::~ajouterplante()
{
    delete ui;
}

void ajouterplante::on_pushButton_5_clicked()
{
    close();
}
