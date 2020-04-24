#ifndef PLANTE_H
#define PLANTE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class plante
{public:
    plante();
    plante(QString,int,float,float,float,QString,float,int,QString,int,int);

   QString get_nom_plante();
   int get_nombre();
   float get_prix();
   float get_surface();
   float get_humidite();
   QString get_fructification();
   float get_fprix();
   int get_age();
   QString get_reclote();
   int get_type();
   int get_zone();

    bool ajouter();
     bool modifier();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherup();
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * afficherdown();
    bool supprimer(QString);
private:
    QString nom_plante,fructification,reclote;
    int nombre,age,zone,type;
    float prix,fprix,humidite,surface;
};

#endif // PLANTE_H
