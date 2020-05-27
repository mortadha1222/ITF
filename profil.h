#ifndef PROFIL_H
#define PROFIL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class profil
{
    int id;
        QString username,password,role;
public:
    profil();
    profil(int,QString,QString,QString);
   // int Get_id(){ return id;}
     bool ajouter();
     QSqlQueryModel *afficher();
     QSqlQueryModel *sortid_up();
     QSqlQueryModel *sortid_down();
     bool supprimer(QString);
     bool Modifier();
    bool chercher();
};

#endif // PROFIL_H
