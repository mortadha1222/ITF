#ifndef CONGES_H
#define CONGES_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QSqlRecord>
//#include <QTableView>
#include <QDate>
class conge
{public:
    conge();
    conge(int,QString,QString,QString,QString,int);
    QString get_date_debut();
    QString get_date_fin();
    QString get_cause();
    QString get_reponse();
    int get_id();
    void set_cause(QString val){cause=val;}
    void set_id(int val){id=val;}
    bool ajouter();
    bool modifier();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    QSqlQueryModel * affichercroissant();
    QSqlQueryModel * afficherdecroissant();
    QSqlQueryModel * recherche(int);
     QSqlQueryModel * recherches(QString);
private:
    QString date_debut,date_fin,cause,reponse;
    int id,ido;
};
#endif
