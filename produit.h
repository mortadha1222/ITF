#ifndef PRODUIT_H
#define PRODUIT_H
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>

class Produit
{
private:
    int id,quantite;
    float prix;
    QString nom;
    int idf;
public:
    Produit();
     Produit(int,QString,int,float,int);
     QString get_nom();
     int get_id();
     int get_quantite();
     float get_prix();
     bool ajouter();
     bool modifier();
     QSqlQueryModel * afficher();
     QSqlQueryModel * rechercher(QString);
     QSqlQueryModel * afficherdown_ID();
     QSqlQueryModel * afficherup_ID();
     QSqlQueryModel * afficherdown_prix();
     QSqlQueryModel * afficherup_prix();
     QSqlQueryModel * afficherdown_nb();
     QSqlQueryModel * afficherup_nb();
     bool supprimer(int);
};

#endif // PRODUIT_H
