#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"profil.h"
#include "login.h"
#include"ouvrier.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include<QSystemTrayIcon>
#include <QFileDialog>
#include"smtpp.h"
namespace Ui {
class MainWindow;
}
class QSystemTrayIcon;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool get_etat(){return 0;}
    //bool set_etat(bool e){etat=e;}
    void mailSent(QString);
    void on_ajouter_profile_clicked();

    void on_supprimer_profile_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_56_clicked();

    void on_modifier_profile_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_36_clicked();

    void on_recherche_profile_clicked();

    void on_trieup_profile_clicked();

    void on_triedown_profile_clicked();

    int on_pushButton_42_clicked();

    void on_supprimer_ouvrier_clicked();

    void on_ajouter_ouvrier_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_50_clicked();

    void on_resource_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_52_clicked();

    void on_supprimer_ouv_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_54_clicked();

    void on_stats_clicked();

    void on_trieup_ouvrier_clicked();

    void on_triedown_ouvrier_clicked();

    void on_recherche_ouvrier_clicked();

    void on_modifier_ouvrier_clicked();

    void on_pushButton_59_clicked();

    void on_pushButton_58_clicked();

    void on_supprimer_ouv_2_clicked();

    void on_pushButton_60_clicked();

    void on_pushButton_61_clicked();

    void on_pushButton_55_clicked();

private:
    Ui::MainWindow *ui;
    bool etat=true;
    profil tmpprofil;
    ouvrier tmpouvrier;
QMediaPlayer *play;
QSystemTrayIcon *notif;
};

#endif // MAINWINDOW_H
