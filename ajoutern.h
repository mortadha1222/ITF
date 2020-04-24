#ifndef AJOUTERN_H
#define AJOUTERN_H

#include <QDialog>

namespace Ui {
class ajoutern;
}

class ajoutern : public QDialog
{
    Q_OBJECT

public:
    explicit ajoutern(QWidget *parent = nullptr);
    ~ajoutern();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ajoutern *ui;
};

#endif // AJOUTERN_H
