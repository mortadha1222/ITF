#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class fournisseur
{
public:
    fournisseur();
    fournisseur(int,QString,QString,QString,int,QString,int);
    int get_id();
    QString get_adresse();
    QString get_nom();
    QString get_email();
    int get_tel();
    void set_id(int);
    void set_adresse(QString);
    void set_nom(QString);
    void set_email(QString);
    void set_tel(int);
   bool ajouter();
   QSqlQueryModel * afficher();
   bool supprimer(int);
   bool modifier();
   QSqlQueryModel * affichernfd(QString,QString);
   QSqlQueryModel * affichernfa(QString,QString);

private:
    int id,tel,age;
    QString adresse,nom,email,sexe;
};
#endif // FOURNISSEUR_H
