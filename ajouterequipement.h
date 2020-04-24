#ifndef AJOUTEREQUIPEMENT_H
#define AJOUTEREQUIPEMENT_H

#include <QDialog>

namespace Ui {
class ajouterEquipement;
}

class ajouterEquipement : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterEquipement(QWidget *parent = nullptr);
    ~ajouterEquipement();

private:
    Ui::ajouterEquipement *ui;
};

#endif // AJOUTEREQUIPEMENT_H
