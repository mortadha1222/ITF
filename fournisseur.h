#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class fournisseur
{
public:
    fournisseur();
    fournisseur(int,QString,QString,QString,QString,QString,int,QString);
    int get_id();
    QString get_adresse();
    QString get_nom();
    QString get_email();
    QString get_tel();
    void set_id(int);
    void set_adresse(QString);
    void set_nom(QString);
    void set_email(QString);
    void set_tel(QString);
   bool ajouter();
   QSqlQueryModel * afficher();
   bool supprimer(int);
   bool modifier();
   QSqlQueryModel * afficherfr(QString  ,QString  );
   QSqlQueryModel * affichernfd(QString,QString);
   QSqlQueryModel * affichernfa(QString,QString);

private:
    int id,age;
    QString adresse,nom,email,sexe,tel,type;
};
#endif // FOURNISSEUR_H
