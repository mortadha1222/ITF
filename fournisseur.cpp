#include "fournisseur.h"
#include <QDebug>
fournisseur::fournisseur()
{
id=0;
adresse="";
nom="";
email="";
tel="";
type="";
}
fournisseur::fournisseur(int id,QString adresse,QString nom,QString email,QString tel,QString sexe ,int age,QString type)
{
  this->id=id;
  this->adresse=adresse;
  this->nom=nom;
  this->email=email;
  this->tel=tel;
  this->sexe=sexe;
  this->age=age;
  this->type=type;

}
int fournisseur::get_id(){return  id;}
QString fournisseur::get_adresse(){return adresse;}
QString fournisseur::get_nom(){return  nom;}
QString fournisseur::get_email(){return  email;}
QString fournisseur::get_tel(){return  tel;}
void fournisseur::set_id(int i){ id=i;}
void fournisseur::set_adresse(QString a){ adresse=a;}
void fournisseur::set_nom(QString n){  nom=n;}
void fournisseur::set_email(QString e){  email=e;}
void fournisseur::set_tel(QString t){  tel=t;}

bool fournisseur::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
//QString res2= QString::number(tel);
QString res3= QString::number(age);
query.prepare("INSERT INTO fournisseur (ID_FOURNISSEUR, ADRESSE_FOURNISSEUR,NOM_FOURNISSEUR,EMAIL_FOURNISSEUR,TEL_FOURNISSEUR,SEXE_FOURNISSEUR,AGE_FOURNISSEUR,TYPE) "
                    "VALUES (:id, :adresse, :nom, :email, :tel, :sexe, :age,:type)");
query.bindValue(":id", res);
query.bindValue(":adresse", adresse);
query.bindValue(":nom", nom);
query.bindValue(":email", email);
query.bindValue(":tel", tel);
query.bindValue(":sexe", sexe);
query.bindValue(":age", res3);
query.bindValue(":type", type);

return    query.exec();
}
bool fournisseur::modifier()
{
QSqlQuery query;
QString res= QString::number(id);
//QString res2= QString::number(tel);
QString res3= QString::number(age);
query.prepare("update  fournisseur set ID_FOURNISSEUR=:id , ADRESSE_FOURNISSEUR=:adresse,NOM_FOURNISSEUR=:nom,EMAIL_FOURNISSEUR=:email,TEL_FOURNISSEUR=:tel,SEXE_FOURNISSEUR=:sexe,AGE_FOURNISSEUR=:age,TYPE=:type "
                    "where ID_FOURNISSEUR = :id");
query.bindValue(":id", res);
query.bindValue(":adresse", adresse);
query.bindValue(":nom", nom);
query.bindValue(":email", email);
query.bindValue(":tel", tel);
query.bindValue(":sexe", sexe);
query.bindValue(":age", res3);
query.bindValue(":type", type);

return    query.exec();
}
QSqlQueryModel * fournisseur::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from fournisseur");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOUR"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE_FOUR"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_FOUR"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL_FOUR"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL_FOUR"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("SEXE_FOUR"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("AGE_FOUR"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("TYPE"));

return model;
}
bool fournisseur::supprimer(int idf)
{
QSqlQuery query;
QString res= QString::number(idf);
query.prepare("Delete from fournisseur where ID_FOURNISSEUR = :id ");
query.bindValue(":id", res);
return    query.exec();
}
QSqlQueryModel * fournisseur::afficherfr(QString val ,QString valt )
{QSqlQueryModel * model= new QSqlQueryModel();
if(valt =="Standard" )
 { model->setQuery("select * from FOURNISSEUR where ID_FOURNISSEUR ="+val+"");  }
else
{ model->setQuery("select * from FOURNISSEUR where ID_FOURNISSEUR like '%"+val+"%'"); }
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOUR"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE_FOUR"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_FOUR"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL_FOUR"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL_FOUR"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("SEXE_FOUR"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("AGE_FOUR"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("TYPE"));
return model;
}
QSqlQueryModel * fournisseur::affichernfd(QString val,QString valt)
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FOURNISSEUR where ID_FOURNISSEUR  like '%"+val+"%' order by "+valt+" desc" );
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOUR"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE_FOUR"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_FOUR"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL_FOUR"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL_FOUR"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("SEXE_FOUR"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("AGE_FOUR"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("TYPE"));
return model;
}
QSqlQueryModel * fournisseur::affichernfa(QString val,QString valt)
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FOURNISSEUR where ID_FOURNISSEUR  like '%"+val+"%' order by "+valt+" asc"  );
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOUR"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE_FOUR"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_FOUR"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL_FOUR"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL_FOUR"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("SEXE_FOUR"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("AGE_FOUR"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("TYPE"));
return model;
}
