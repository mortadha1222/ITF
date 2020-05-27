#include "profil.h"
#include<QDebug>
profil::profil()
{
id=0;
}
profil::profil(int i,QString n,QString p,QString r)
{
id=i;
username=n;
password=p;
role=r;
}

bool profil::ajouter()
{

    QSqlQuery query;
    QString i;

      query.exec("select id from LOGIN where id = ( select max(id) from LOGIN);");
      if (query.next()) {
            i = query.value(0).toString();
            qDebug() << i <<endl;
        }
   // QString res= QString::number(id_user);
    query.prepare("INSERT INTO LOGIN(ID,USERNAME,PASSWORD,ROLE)"
                  "VALUES (:id,:username,:password,:role)");
    query.bindValue(":id",(i.toInt()+1));
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":role",role);
    return query.exec();
}
/*QSqlQueryModel *profil::chercher(QString u)
{
    QSqlQuery query;
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select *from LOGIN where USERNAME=:u");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("USERNAME"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PASSWORD"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ROLE"));
   query.bindValue(":USERNAME",u);
    return model;
}*/
bool profil::Modifier()
{
    QSqlQuery query;
    query.prepare(" UPDATE LOGIN SET  PASSWORD=:password, ROLE=:role WHERE USERNAME=:username ");
    //query.bindValue(":id",id);
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":role",role);
    return query.exec();
}

QSqlQueryModel *profil:: afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select *from LOGIN");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("USERNAME"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PASSWORD"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ROLE"));
    return model;
}
bool profil:: supprimer(QString username)
{
    QSqlQuery query;
    query.prepare("Delete from LOGIN where USERNAME=:username");
    query.bindValue(":username",username);
    return query.exec();
}
QSqlQueryModel *profil::sortid_up()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from LOGIN ORDER BY id ASC ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("USERNAME"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PASSWORD"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ROLE"));
    return model;
}
QSqlQueryModel *profil::sortid_down()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery(" select * from LOGIN ORDER BY id DESC ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("USERNAME"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PASSWORD"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ROLE"));
    return model;
}
