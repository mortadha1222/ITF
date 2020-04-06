

#include "vehicule.h"
#include <QDebug>
//#include "connexion.h"
vehicule::vehicule()
{
matricule="";
marque="";
age=0;
datedachat="";
idf=0;
}
vehicule::vehicule(QString matricule,QString marque,int age,QString datedachat,int idf)
{
  this->matricule=matricule;
  this->marque=marque;
  this->age=age;
  this->datedachat=datedachat;
    this->idf=idf;
}
QString vehicule::get_matricule(){return matricule;}
QString vehicule::get_marque(){return  marque;}
int vehicule::get_age(){return  age;}
QString vehicule::get_datedachat(){return datedachat;}


bool vehicule::ajouter()
{
QSqlQuery query;
QString res2= QString::number(age);
QString res3= QString::number(idf);
query.prepare("INSERT INTO vehicule (matricule,marque,age,DATEDACHAT,ID_FOURNISSEUR) "
                    "VALUES (:matricule,:marque, :age, :datedachat,:idf)");
query.bindValue(":matricule", matricule);
query.bindValue(":marque", marque);
query.bindValue(":age", res2);
query.bindValue(":datedachat", datedachat);
query.bindValue(":idf", res3);

return    query.exec();
}

QSqlQueryModel * vehicule::afficher()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from vehicule");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("marque "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("datedachat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

    return model;
}

bool vehicule::supprimer(QString matricule)
{
QSqlQuery query;
query.prepare("Delete from vehicule where matricule = :matricule ");
query.bindValue(":matricule", matricule);
return    query.exec();
}

bool vehicule::modifier(QString id)
{
    QSqlQuery query;
    QString res= QString::number(idf);
    query.prepare("UPDATE vehicule SET matricule = :matricule,marque = :marque,age = :age,DATEDACHAT = :datedachat,ID_FOURNISSEUR=:idf where matricule = :id");
    query.bindValue(":matricule",matricule);
    query.bindValue(":marque",marque);
    query.bindValue(":age",age);
    query.bindValue(":datedachat",datedachat);
    query.bindValue(":id",id);
    query.bindValue(":idf",res);

    return    query.exec();
}

QSqlQueryModel * vehicule::recherche(const QString &id)
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from vehicule where (matricule LIKE '"+id+"%') ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("marque "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("datedachat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

return model;
}

QSqlQueryModel * vehicule::triasc()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from vehicule order by age asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("marque "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("datedachat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

return model;
}

QSqlQueryModel * vehicule::tridesc()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from vehicule order by age desc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("marque "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("datedachat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

return model;
}
