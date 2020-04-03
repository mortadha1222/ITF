#include "ouvrier.h"
#include<QDebug>

ouvrier::ouvrier()
{
   id_ouvrier=0;
}
ouvrier::ouvrier(long i,QString n,QString p,QString r,float s,long c,QDate dbt,QDate dbf,long num,QString fP)
{
    id_ouvrier=i;
    nom=n;
    prenom=p;
    role=r;
    salaire=s;
    cin=c;
    date_debut=dbt;
    date_fin=dbf;
    num_tel=num;
    filePath=fP;
}

bool ouvrier::ajouter()
{

    QSqlQuery query;
    QString i;

     query.exec("select id_ouvrier from OUVRIERS where id_ouvrier = ( select max(id_ouvrier) from OUVRIERS);");
      if (query.next()) {
            i = query.value(0).toString();
            qDebug() << i <<endl;
        }
   // QString res= QString::number(id_user);
      QString res =QString::number(salaire);
      QString res1 = QString::number(cin);
      QString res2 = QString::number(num_tel);
    query.prepare("INSERT INTO OUVRIERS(ID_OUVRIER,NOM,PRENOM,ROLE,SALAIRE,CIN,DATE_DEBUT,DATE_FIN,NUM_TEL,IMAGE)"
                  "VALUES (:id_ouvrier,:nom,:prenom,:role,:salaire,:cin,:date_debut,:date_fin,:num_tel,:image)");
    query.bindValue(":id_ouvrier",(i.toInt()+1));
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":role",role);
    query.bindValue(":salaire",res);
    query.bindValue(":cin",res1);
    query.bindValue(":date_debut",date_debut);
    query.bindValue(":date_fin",date_fin);
    query.bindValue(":num_tel",res2);
    query.bindValue(":image",filePath);
    return query.exec();

}
QSqlQueryModel *ouvrier:: afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from OUVRIERS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_OUVRIER"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_DEBUT"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_FIN"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("SALAIRE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ROLE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("PRENOM"));
    return model;
}
bool ouvrier::Modifier()
{
    QSqlQuery query;
    QString i;
    query.exec("select id_ouvrier from OUVRIERS where id_ouvrier = ( select max(id_ouvrier) from OUVRIERS);");
     if (query.next()) {
           i = query.value(0).toString();
           qDebug() << i <<endl;
       }
    QString res =QString::number(salaire);
    QString res1 = QString::number(cin);
    QString res2 = QString::number(num_tel);
    query.prepare(" UPDATE ouvriers SET nom=:nom, prenom=:prenom, ROLE=:role, date_debut=:date_debut, date_fin=:date_fin, salaire=:salaire, cin=:cin WHERE id_ouvrier=:id_ouvrier ");
    query.bindValue(":id_ouvrier",i);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":role",role);
    query.bindValue(":salaire",res);
    query.bindValue(":cin",res1);
    query.bindValue(":date_debut",date_debut);
    query.bindValue(":date_fin",date_fin);
    query.bindValue(":num_tel",res2);
    query.bindValue(":image",filePath);
    return query.exec();
}
bool ouvrier:: supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from OUVRIERS where id_ouvrier=:id_ouvrier");
    query.bindValue(":id_ouvrier",id);
    return query.exec();
}
QSqlQueryModel *ouvrier::sortid_up()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from ouvriers ORDER BY id_ouvrier ASC ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_OUVRIER"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_DEBUT"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_FIN"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("SALAIRE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ROLE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("PRENOM"));
    return model;
}
QSqlQueryModel *ouvrier::sortid_down()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from ouvriers ORDER BY id_ouvrier DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_OUVRIER"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_DEBUT"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_FIN"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("SALAIRE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUM_TEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ROLE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("PRENOM"));
    return model;
}
