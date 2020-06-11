#include "abonnements.h"

abonnements::abonnements()
{
id_ouvrier=0;
}

abonnements::abonnements(int i,QString t,QString d)
{
    id_ouvrier=i;
    type=t;
    duree=d;
}

bool abonnements::ajouter()
{
    QSqlQuery query;
    QString i= QString::number(id_ouvrier);
    query.prepare("INSERT INTO ABONNEMENTS(TYPE,DURÉE,ID_OUVRIER) VALUES (:type,:duree,:id_ouvrier)");
    query.bindValue(":id_ouvrier",i);
    query.bindValue(":type",type);
    query.bindValue(":duree",duree);
    return query.exec();
}

QSqlQueryModel *abonnements::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from ABONNEMENTS");
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID_OUVRIER"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DURÉE"));
    return model;
}

bool abonnements::Modifier()
{
    QSqlQuery query;
    QString i= QString::number(id_ouvrier);
    query.prepare(" UPDATE ABONNEMENTS SET type=:type, durée=:duree WHERE id_ouvrier=:id_ouvrier ");
    query.bindValue(":id_ouvrier",i);
    query.bindValue(":type",type);
    query.bindValue(":duree",duree);
    return query.exec();
}

bool abonnements::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from ABONNEMENTS where id_ouvrier=:id_ouvrier");
    query.bindValue(":id_ouvrier",id);
    return query.exec();
}

