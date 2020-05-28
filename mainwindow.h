#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plante.h"
#include "produitv.h"
#include <QSystemTrayIcon>
#include"conges.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_ajouterplante_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_18_clicked();




    void on_ajoutplante_clicked();

    void on_pushButton_2_clicked();


    void on_supprimerplante_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_19_clicked();

    void on_afficherplantes_activated(const QModelIndex &index);

    void on_pushButton_20_clicked();


    void on_nomrecherche_textChanged(const QString &arg1);



    void on_pushButton_21_clicked();

    void on_mod_clicked();

    void on_produitvdown_clicked();

    void on_produitvup_clicked();

    void on_ajouterproduitv_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_supprimerproduitv_clicked();

    void on_pushButton_25_clicked();

    void on_mod_2_clicked();

    void on_afficherproduitv_activated(const QModelIndex &index);

    void on_rechercherproduitv_clicked();



    void on_opplus_clicked();

    void on_opmoins_clicked();

    void on_opetoile_clicked();

    void on_opsur_clicked();

    void on_exitcalc_clicked();

    void on_calculator_clicked();

    void on_statplante_clicked();

    void on_anulerstato_clicked();

    void on_printplante_clicked();

    void on_supprimerplante_2_clicked();

    void on_anulersupprimerplante_clicked();

    void on_printprodv_clicked();

    void on_statsproduitv_clicked();

    void on_anulerajouterplante_clicked();

    void on_annulerajouterproduitv_clicked();

    void on_annulersupprimerproduitv_clicked();

    void on_supprimerproduitv_2_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_products_clicked();

    void on_nomproduitrecherche_textChanged(const QString &arg1);
    
    void on_graph_clicked();

    void on_homee_clicked();

    void on_demandec_clicked();

    void on_annulc_clicked();

    void on_ajouter_4_clicked();

    void on_minec_clicked();

private:
    Ui::MainWindow *ui;
    plante tmpplante;
    produitv tmpproduitv;
      QSystemTrayIcon *mysystem;
          conge tmpconge;
};
#endif // MAINWINDOW_H
