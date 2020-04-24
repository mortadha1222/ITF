#include "ajouterequipement.h"
#include "ui_ajouterequipement.h"

ajouterEquipement::ajouterEquipement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterEquipement)
{
    ui->setupUi(this);
}

ajouterEquipement::~ajouterEquipement()
{
    delete ui;
}

