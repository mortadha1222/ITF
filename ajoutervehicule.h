#ifndef AJOUTERVEHICULE_H
#define AJOUTERVEHICULE_H

#include <QDialog>

namespace Ui {
class ajoutervehicule;
}

class ajoutervehicule : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutervehicule(QWidget *parent = nullptr);
    ~ajoutervehicule();

private:
    Ui::ajoutervehicule *ui;
};

#endif // AJOUTERVEHICULE_H
