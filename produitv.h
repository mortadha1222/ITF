#ifndef PRODUITV_H
#define PRODUITV_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class produitv
{public:
    produitv();
  produitv(QString,int,float);

   QString get_nom_produit();
   int get_quantite();
   float get_prixunitaire();


    bool ajouter();
     bool modifier();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherup();
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * afficherdown();
    bool supprimer(QString);
private:
    QString nom_produit;
    float prixunitaire;
    int quantite;
};
#endif // PRODUITV_H
