#ifndef VEHICULE_H
#define VEHICULE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include <QDate>
class vehicule
{

public:
    vehicule();
    vehicule(QString,QString,int,QString,int);
    QString get_matricule();
    QString get_marque();
    int get_age();
    QString get_datedachat();
    bool ajouter();
    bool modifier(QString);
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    QSqlQueryModel *recherche(const QString &);
    QSqlQueryModel * triasc();
    QSqlQueryModel * tridesc();


private:
    QString matricule,marque,datedachat;
    int age,idf;

};

#endif // VEHICULE_H
