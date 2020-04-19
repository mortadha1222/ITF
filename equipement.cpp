#include "equipement.h"
#include <QDebug>
//#include "connexion.h"
equipement::equipement()
{
reference="";
nom="";
quantite=0;
datedachat="";
idf=0;
}
equipement::equipement(int quantite,QString reference,QString nom,QString datedachat,int idf)
{
  this->quantite=quantite;
  this->reference=reference;
  this->nom=nom;
  this->datedachat=datedachat;
  this->idf=idf;

}
QString equipement::get_reference(){return reference;}
QString equipement::get_nom(){return  nom;}
int equipement::get_quantite(){return  quantite;}
QString equipement::get_datedachat(){return datedachat;}


bool equipement::ajouter()
{
QSqlQuery query;
QString res2= QString::number(quantite);
QString res3= QString::number(idf);

query.prepare("INSERT INTO EQUIPEMENT (REFERENCE,NOM,QUANTITE,DATEDACHAT,ID_FOURNISSEUR) "
                    "VALUES (:reference,:nom, :quantite, :datedachat,:idf)");
query.bindValue(":reference", reference);
query.bindValue(":nom", nom);
query.bindValue(":quantite", res2);
query.bindValue(":datedachat", datedachat);
query.bindValue(":idf", res3);

return    query.exec();
}

QSqlQueryModel * equipement::afficher()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from EQUIPEMENT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("datedachat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
return model;
}

bool equipement::supprimer(QString referencee)
{
QSqlQuery query;
query.prepare("Delete from EQUIPEMENT where REFERENCE = :reference ");
query.bindValue(":reference", referencee);
return    query.exec();
}

bool equipement::modifier(QString id)
{
    QSqlQuery query;
    QString res2= QString::number(idf);

    query.prepare("UPDATE equipement SET reference = :reference,NOM = :nom,QUANTITE = :quantite,DATEDACHAT = :datedachat,ID_FOURNISSEUR=:idf  where REFERENCE = :id");
    query.bindValue(":reference",reference);
    query.bindValue(":nom",nom);
    query.bindValue(":quantite",quantite);
    query.bindValue(":datedachat",datedachat);
    query.bindValue(":id", id);
    query.bindValue(":idf",res2);

    return    query.exec();
}

QSqlQueryModel * equipement::recherche(const QString &id)
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from equipement where (reference LIKE '"+id+"%') ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("datedachat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

return model;
}

QSqlQueryModel * equipement::triasc()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from equipement order by QUANTITE asc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("datedachat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

return model;
}

QSqlQueryModel * equipement::tridesc()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from equipement order by QUANTITE desc");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("datedachat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

return model;
}
