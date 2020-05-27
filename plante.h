#ifndef PLANTE_H
#define PLANTE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class plante
{public:
    plante();
    plante(QString,int,float,float,float,float,float,int,QString,int,int,int,QString);

   QString get_nom_plante();
   int get_nombre();
   float get_prix();
   float get_surface();
   float get_humidite();
   float get_fructification();
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
    QString nom_plante,reclote;
    int nombre,age,zone,type;
    float prix,fprix,humidite,surface;
    int idf;
    QString refn;
    float fructification;
};

#endif // PLANTE_H
