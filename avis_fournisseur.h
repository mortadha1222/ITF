#ifndef AVIS_FOURNISSEUR_H
#define AVIS_FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class avis_fournisseur
{
private:
    int note,ida,idf;

public:
    avis_fournisseur();
    avis_fournisseur(int,int,int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();


};

#endif // AVIS_FOURNISSEUR_H
