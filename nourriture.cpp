#include "nourriture.h"
#include <QDebug>
#include <QDateEdit>

nourriture::nourriture()
{
ref="";
idf=0;
nomn="";
prix=0;
quantite=0;
img="";
}
nourriture::nourriture(QString r,int i,QString n,QDate d,float p , float q,QString img)
{
  this->ref=r;
  this->idf=i;
  this->nomn=n;
  this->datee=d;
  this->prix=p;
  this->quantite=q;
  this->img=img;
}
QString nourriture::get_ref(){return  ref;}
int nourriture::get_idf(){return idf;}
QString nourriture::get_nomn(){return  nomn;}
QDate nourriture::get_date(){return  datee;}
float nourriture::get_prix(){return  prix;}
float nourriture::get_q(){return  quantite;}

bool nourriture::ajoutern()
{
QSqlQuery query;
QString res2= QString::number(idf);
QString res5= QString::number(prix);
QString res6= QString::number(quantite);

query.prepare("INSERT INTO NOURRITURE (REF_NOURRITURE, ID_FOURNISSEUR,NOM_NOURRITURE,DATE_EXPIRATION,PRIX,QUANTITÉ,IMAGE) "
                    "VALUES (:ref, :i, :nomn, :d, :p,:q,:img)");
query.bindValue(":ref", ref);
query.bindValue(":i", res2);
query.bindValue(":nomn", nomn);
query.bindValue(":d", datee);
query.bindValue(":p", res5);
query.bindValue(":q", res6);
query.bindValue(":img", img);
return    query.exec();
}

bool nourriture::modifiern()
{
QSqlQuery query;
QString res= QString::number(idf);
QString res1= QString::number(prix);
QString res2= QString::number(quantite);

query.prepare("update  nourriture set REF_NOURRITURE=:r , ID_FOURNISSEUR=:i,NOM_NOURRITURE=:n,DATE_EXPIRATION=:d,PRIX=:p,QUANTITÉ=:q "
                    "where REF_NOURRITURE = :r");
query.bindValue(":r", ref);
query.bindValue(":i", res);
query.bindValue(":n", nomn);
query.bindValue(":d", datee);
query.bindValue(":p", res1);
query.bindValue(":q", res2);
//query.bindValue(":q", img);

return    query.exec();
}
QSqlQueryModel * nourriture::affichern()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from nourriture");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref_n"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("id_F "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom_n"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_n"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantite"));
return model;
}
QSqlQueryModel * nourriture::affichernqd(QString val,QString valt)
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from nourriture where REF_NOURRITURE  like '%"+val+"%' order by "+valt+" desc" );
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref_n"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("id_F "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom_n"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_n"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantite"));
return model;
}
QSqlQueryModel * nourriture::affichernqa(QString val,QString valt)
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from nourriture where REF_NOURRITURE  like '%"+val+"%' order by "+valt+" asc"  );
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref_n"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("id_F "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom_n"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_n"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantite"));
return model;
}

bool nourriture::supprimern(QString ref)
{
QSqlQuery query;
query.prepare("Delete from nourriture where REF_NOURRITURE = :id ");
query.bindValue(":id", ref);
return    query.exec();
}


