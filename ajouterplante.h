#ifndef AJOUTERPLANTE_H
#define AJOUTERPLANTE_H

#include <QDialog>

namespace Ui {
class ajouterplante;
}

class ajouterplante : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterplante(QWidget *parent = nullptr);
    ~ajouterplante();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::ajouterplante *ui;
};

#endif // AJOUTERPLANTE_H
