#ifndef AJOUTERF_H
#define AJOUTERF_H

#include <QDialog>

namespace Ui {
class ajouterf;
}

class ajouterf : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterf(QWidget *parent = nullptr);
    ~ajouterf();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ajouterf *ui;
};

#endif // AJOUTERF_H
