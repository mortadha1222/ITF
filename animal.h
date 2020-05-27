#ifndef ANIMAL_H
#define ANIMAL_H
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>

class Animal
{
private:
    int id,nb;
    float prix;
    QString nom;
    int idf;
public:
    Animal();
     Animal(int,QString,int,float,int);
     QString get_nom();
     int get_id();
     int get_nb();
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

#endif // ANIMAL_H
