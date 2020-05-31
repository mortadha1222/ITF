#ifndef NOURRITURE_H
#define NOURRITURE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QDateEdit>

class nourriture
{
public:
    nourriture();
    nourriture(QString,int,QString,QDate,float,float,QString);
    QString get_ref();
    int get_idf();
    QString get_nomn();
    QDate get_date();
    float get_prix();
    float get_q();
   bool ajoutern();
   QSqlQueryModel * affichern();
   QSqlQueryModel * affichernqd(QString,QString);
   QSqlQueryModel * affichernqa(QString,QString);
   QSqlQueryModel * affichernr(QString , QString);
   bool supprimern(QString);
   bool modifiern();

private:
    float prix,quantite;
    QDate datee ;
    int idf;
    QString ref,nomn;
    QString img;
};
#endif // NOURRITURE_H
