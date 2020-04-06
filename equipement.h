#ifndef AJOUTEREQUIPEMENT_H
#define AJOUTEREQUIPEMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include <QDate>


class equipement
{public:
    equipement();
    equipement(int,int,QString,QString,int);
    int get_reference();
    QString get_nom();
    int get_quantite();
    QString get_datedachat();
    bool ajouter();
    bool modifier(int);
    QSqlQueryModel * afficher();
    bool supprimer(int);
    QSqlQueryModel *recherche(const QString &);
    QSqlQueryModel * triasc();
    QSqlQueryModel * tridesc();


private:
    QString nom,datedachat;
    int quantite,reference,idf;
};


#endif // AJOUTEREQUIPEMENT_H
