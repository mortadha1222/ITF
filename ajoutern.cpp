#include "ajoutern.h"
#include "ui_ajoutern.h"

ajoutern::ajoutern(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajoutern)
{
    ui->setupUi(this);
}

ajoutern::~ajoutern()
{
    delete ui;
}

void ajoutern::on_pushButton_5_clicked()
{
    close();
}

void ajoutern::on_pushButton_4_clicked()
{
   close();

}
