#ifndef OUVRIER_H
#define OUVRIER_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QDateEdit>
class ouvrier
{
    long id_ouvrier,num_tel,cin;
   QString filePath;
    float salaire;
    QString nom,prenom,role;
    QDate date_debut,date_fin;
public:
    ouvrier();
    ouvrier(long,QString,QString,QString,float,long,QDate,QDate,long,QString);
    QString get_nom(){return nom;}
    bool ajouter();
    bool Modifier();
    QSqlQueryModel *sortid_up();
    QSqlQueryModel *sortid_down();
    bool supprimer(int);
    QSqlQueryModel *afficher();
};

#endif // OUVRIER_H
