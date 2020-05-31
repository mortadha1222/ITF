#include "conges.h"
#include <QDebug>
#include <QString>

#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QDate>
//#include <QVariant>
#include <QMessageBox>
#include <QSqlRecord>
conge::conge()
{
id=0;
date_debut="";
date_fin="";
cause="";
reponse="en cours";
}
conge::conge(int id,QString date_debut,QString date_fin,QString cause,QString reponse,int ido)
{
  this->id=id;
  this->date_debut=date_debut;
  this->date_fin=date_fin;
  this->cause=cause;
  this->reponse=reponse;
  this->ido=ido;
}
QString conge::get_date_debut(){return  date_debut;}
QString conge::get_date_fin(){return date_fin;}
QString conge::get_cause(){return cause;}
QString conge::get_reponse(){return reponse;}
int conge::get_id(){return  id;}

bool conge::ajouter()
{
QSqlQuery query;
srand(time(NULL));
QString res= QString::number(id);
QString res2= QString::number(ido);
query.prepare("INSERT INTO conges (ID,DATE_DEBUT,DATE_FIN,CAUSE,REPONSE,IDO) "
              "VALUES (:id,:date_debut,:date_fin ,:cause ,:reponse,:ido)");
query.bindValue(":id",res);
query.bindValue(":ido",res2);
query.bindValue(":date_debut",date_debut);
query.bindValue(":date_fin",date_fin);
query.bindValue(":cause",cause);
query.bindValue(":reponse",reponse);
return    query.exec();
}


QSqlQueryModel *conge::afficher()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select id,date_debut,date_fin,cause,reponse,IDO from conges");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_debut "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_fin"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("cause"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("reponse"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_OUVRIER"));
 return model;
}


QSqlQueryModel *conge::affichercroissant(){
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from conges order by  id ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_debut "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_fin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cause"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("reponse"));
 return model;
}


QSqlQueryModel *conge::afficherdecroissant(){
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from conges order by  id  DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_debut "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_fin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cause"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("reponse"));
 return model;


}


QSqlQueryModel *conge::recherche(int idd)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    QString res= QString::number(idd);
    model->setQuery("select * from conges where IDO like '%"+res+"%'" );
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_debut"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_fin"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("cause"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("reponse"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_OUVRIER"));

    return model;
}

QSqlQueryModel *conge::recherches(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;

    model->setQuery("select * from conges where ID like '%"+res+"%'" );
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_debut"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_fin"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("cause"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("reponse"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_OUVRIER"));

    return model;
}



bool conge::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("DELETE from conges where ID = :id ");
query.bindValue(":id",res);
return    query.exec();
}


bool conge::modifier()
{QSqlQuery q;
    q.prepare("UPDATE conges SET date_debut =:date_debut,  date_fin =:date_fin, cause =:cause ,reponse=:reponse  WHERE id=:id");
    q.bindValue(":date_debut", date_debut);
    q.bindValue(":date_fin", date_fin);
    q.bindValue(":cause", cause);
    q.bindValue(":reponse", reponse);
    q.bindValue(":id",id);
    return    q.exec();

}
