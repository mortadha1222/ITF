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
    equipement(int,QString,QString,QString,int);
    QString get_reference();
    QString get_nom();
    int get_quantite();
    QString get_datedachat();
    bool ajouter();
    bool modifier(QString);
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    QSqlQueryModel *recherche(const QString &);
    QSqlQueryModel * triasc();
    QSqlQueryModel * tridesc();


private:
    QString nom,datedachat,reference;
    int quantite,idf;
};


#endif // AJOUTEREQUIPEMENT_H
