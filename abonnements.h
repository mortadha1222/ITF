#ifndef ABONNEMENTS_H
#define ABONNEMENTS_H
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>

class abonnements
{
public:
    abonnements();
    abonnements(int,QString,QString);
   bool ajouter();
   QSqlQueryModel * afficher();
   bool Modifier() ;
   bool supprimer(int );


private:
    int id_ouvrier;
    QString type;
    QString duree;
};

#endif // ABONNEMENTS_H
